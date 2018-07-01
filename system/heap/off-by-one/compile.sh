#/bin/bash
gcc heap.c -pie -fPIE -Wl,-z,relro,-z,now -o heap