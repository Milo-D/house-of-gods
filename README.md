# House of Gods - Arena Hijacking Technique

House-of-Gods is a new heap exploitation technique for older versions of the GNU C Library (< glibc 2.27). There
are currently two different revisions of the same exploit. The first revision is way more inefficient and less
applicable in real world scenarios compared to the second revision.

The goal of both revisions is to hijack the ```thread_arena``` by corrupting the ```malloc_state.next``` pointer.

## Revision 1

This revision requires a lot of allocations i.e. 200 allocations on my test-system. The exact number is
system dependent. The rootcause is a repeatable WAF on an unsorted-chunk.

Paper: https://github.com/Milo-D/house-of-gods/blob/master/rev1/HOUSE_OF_GODS.TXT

## Revision 2

This revision hijacks the arena within only 8 allocations and drops a shell after a total of 10 allocations.
Furthermore, only a single WAF bug on an unsorted-chunk is needed in order to launch the attack.

Paper: https://github.com/Milo-D/house-of-gods/blob/master/rev2/HOUSE_OF_GODS.TXT

## Executing the POC (for both revisions)

```console
./patch && ./exploit.py
```
