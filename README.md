# House of Gods - Second Revision

House-of-Gods is a new heap exploitation technique for older versions of the GNU C Library (<= glibc 2.26).

This technique hijacks the arena within only 8 allocations and drops a shell after a total of 10 allocations. 
Furthermore, only a single UAF (write-after-free) bug on a smallchunk/largechunk is needed to initiate House-of-Gods.

# Executing the POC

```console
./patch && ./exploit.py
```

# Note

This is the second revision of House-of-Gods. The first one is currently private and will be set to public as soon as possible.


