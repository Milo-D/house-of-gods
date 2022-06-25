# House of Gods - Second Revision

House-of-Gods is a new heap exploitation technique for an older version of the GNU C Library (glibc 2.26).

This technique hijacks the arena within only 9 allocations and drops a shell after a total of 11 allocations. 
Furthermore, only a single UAF (write-after-free) bug on a smallchunk/largechunk is needed to initiate House-of-Gods.

***Note:*** I am still working on a detailed write-up/paper for this technique. It will be published as soon as possible.

# Important

This is the second revision of House-of-Gods. The first one is currently private and will be set to public as soon as possible.


