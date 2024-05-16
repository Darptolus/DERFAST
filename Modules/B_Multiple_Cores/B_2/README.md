# B.2. DEMAC: Setup a multi-core platform

Multicore System consists of two or more processors which have been attached to a single chip to enhance performance, reduce power consumption, and more efficient simultaneous processing of multiple tasks. Multicore system has been in recent trend where each core appears as a separate processor. Multicore system is capable of executing  more than one threads parallelly whereas in Single core system only one thread can execute at a time. 

Implementing Multicore system is more beneficial than implementing single core system by increasing number of transistors on single chip to enhance performance because increasing number of transistors on a single chip increases complexity of the system. 

Challenges of multicore system : 
Since multicore system consists of more than one processors, so the need is to keep all of them busy so that you can make better use of multiple computing cores. Scheduling algorithms must be designed to use multiple computing core to allow parallel computation. The challenge is also to modify the existing and new programs that are multithreaded to take advantage of multicore system. 

In general five areas present challenges in programming for multicore systems :