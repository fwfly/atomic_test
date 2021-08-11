like this [commit](https://github.com/fwfly/atomic_test/commit/7cb576f2872bde345d37336a4624a812ae65d703)
There's no any protection on foo.
If we compile it with `-fsanitize=thread -g`, the result will show data race error
```
 $ gcc -fsanitize=thread -g thread_test.c -lpthread
 $./a.out 
==================
WARNING: ThreadSanitizer: data race (pid=263793)
  Read of size 8 at 0x55b8f766b018 by thread T2:
    #0 add_foo /home/fwfly/project/thread_test/thread_test.c:15 (a.out+0x1277)

  Previous write of size 8 at 0x55b8f766b018 by thread T1:
    #0 add_foo /home/fwfly/project/thread_test/thread_test.c:15 (a.out+0x128e)

  Location is global 'foo' of size 8 at 0x55b8f766b018 (a.out+0x000000004018)

  Thread T2 (tid=263796, running) created by main thread at:
    #0 pthread_create ../../../../src/libsanitizer/tsan/tsan_interceptors_posix.cpp:962 (libtsan.so.0+0x5ea79)
    #1 main /home/fwfly/project/thread_test/thread_test.c:26 (a.out+0x1317)

  Thread T1 (tid=263795, running) created by main thread at:
    #0 pthread_create ../../../../src/libsanitizer/tsan/tsan_interceptors_posix.cpp:962 (libtsan.so.0+0x5ea79)
    #1 main /home/fwfly/project/thread_test/thread_test.c:26 (a.out+0x1317)

SUMMARY: ThreadSanitizer: data race /home/fwfly/project/thread_test/thread_test.c:15 in add_foo
==================
 ```
 
 But if we use atomic operation, the error will be resolved and the result will be correct.
 Which means the data race is resolved by atomic operations.
