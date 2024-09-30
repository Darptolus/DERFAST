# B.3. Basic parallel programming concepts (tasks, threads)

## Table of content:
- Thread and multithread


## Thread and multithreads
Simply speaking, a thread is a worker that execute instructions. Current CPU architectures are mostly multi threaded, where each worker is independent to each other.

Let's see how many cores are in our current system using lscpu.

```
lscpu
```

```
Architecture:                    x86_64
CPU op-mode(s):                  32-bit, 64-bit
Byte Order:                      Little Endian
Address sizes:                   39 bits physical, 48 bits virtual
CPU(s):                          6
On-line CPU(s) list:             0-5
Thread(s) per core:              1
Core(s) per socket:              6
Socket(s):                       1
NUMA node(s):                    1
Vendor ID:                       GenuineIntel
CPU family:                      6
Model:                           158
Model name:                      Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz
Stepping:                        10
CPU MHz:                         4301.747
CPU max MHz:                     4700.0000
CPU min MHz:                     800.0000
BogoMIPS:                        7399.70
Virtualization:                  VT-x
L1d cache:                       192 KiB
L1i cache:                       192 KiB
L2 cache:                        1.5 MiB
L3 cache:                        12 MiB
NUMA node0 CPU(s):               0-5
Vulnerability Itlb multihit:     KVM: Mitigation: Split huge pages
Vulnerability L1tf:              Mitigation; PTE Inversion; VMX conditional cach
                                 e flushes, SMT disabled
Vulnerability Mds:               Mitigation; Clear CPU buffers; SMT disabled
Vulnerability Meltdown:          Mitigation; PTI
Vulnerability Mmio stale data:   Mitigation; Clear CPU buffers; SMT disabled
Vulnerability Retbleed:          Mitigation; IBRS
Vulnerability Spec store bypass: Mitigation; Speculative Store Bypass disabled v
                                 ia prctl and seccomp
Vulnerability Spectre v1:        Mitigation; usercopy/swapgs barriers and __user
                                  pointer sanitization
Vulnerability Spectre v2:        Mitigation; IBRS, IBPB conditional, RSB filling
                                 , PBRSB-eIBRS Not affected
Vulnerability Srbds:             Mitigation; Microcode
Vulnerability Tsx async abort:   Mitigation; Clear CPU buffers; SMT disabled
Flags:                           fpu vme de pse tsc msr pae mce cx8 apic sep mtr
                                 r pge mca cmov pat pse36 clflush dts acpi mmx f
                                 xsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rd
                                 tscp lm constant_tsc art arch_perfmon pebs bts 
                                 rep_good nopl xtopology nonstop_tsc cpuid aperf
                                 mperf pni pclmulqdq dtes64 monitor ds_cpl vmx s
                                 mx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid s
                                 se4_1 sse4_2 x2apic movbe popcnt tsc_deadline_t
                                 imer aes xsave avx f16c rdrand lahf_lm abm 3dno
                                 wprefetch cpuid_fault epb invpcid_single pti ss
                                 bd ibrs ibpb stibp tpr_shadow vnmi flexpriority
                                  ept vpid ept_ad fsgsbase tsc_adjust bmi1 hle a
                                 vx2 smep bmi2 erms invpcid rtm mpx rdseed adx s
                                 map clflushopt intel_pt xsaveopt xsavec xgetbv1
                                  xsaves dtherm ida arat pln pts hwp hwp_notify 
                                 hwp_act_window hwp_epp md_clear flush_l1d arch_
                                 capabilities
```


In the output above you can find the number of CPUs (e.g. 6) and the number of Threads per CPU (e.g. 2). Each Thread is capable of independently handle a different stream of instructions. However, software often creates more threads than available in the hardware system.

You can ignore the syntax in the following command, but its output will show the number of threads running within all processes in the system (or at least those that your user can obtain information about). Most likely you will find that the number of software threads is much larger than the number of hardware threads. This is because the operating system uses a scheduling scheme to execute all the threads concurrently.

The focus of this lab is not to learn about OS threads, but it is worth knowing that the number of software threads in a given program can be larger than the number of hardware threads running in the system.

```
ps -eo nlwp | tail -n +2 | awk '{ num_threads += $1 } END { print num_threads }'
```

```
929
```

## 0. OpenMP Installation
```
sudo apt-get install libomp-dev -y
```
Check OpenMP
```
echo |cpp -fopenmp -dM |grep -i open
```

<!-- hardware thread vs software thread -->
<!-- process vs thread -->