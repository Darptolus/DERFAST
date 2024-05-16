# B.6. Parallel programming models (OpenMP)

OpenMP is an application programming interface that supports multi-platform shared-memory multiprocessing programming in C, C++, and Fortran, on many platforms, instruction-set architectures and operating systems, including Solaris, AIX, FreeBSD, HP-UX, Linux, macOS, and Windows.

Install OpenMP

sudo apt-get install libomp-dev -y

Check OpenMP

echo |cpp -fopenmp -dM |grep -i open




## Introduction to OpenMP
(Based on https://github.com/josemonsalve2/openmp_tutorial/)

The objective of this lab is to get familiar with the basic concepts behind OpenMP. Some of these concepts are shared with other programming models, and are important to understand how systems are programmed in parallel. These concepts are introduced directly using OpenMP syntax. It is not expected for the reader to know OpenMP, but they should be familiar with C-like syntax.

This tutorial is expected to run in a unix-like environment.

Table of content:
- First parallel program
- Thinking in parallel
- Exercise 1
- Memory: Shared, private, distributed
- Atomic operations
- Private vs Firstprivate
- Reductions
- Lastprivate
- Exercise 2
- OpenMP Syntax
- Function outlining, implementation and runtime

## First parallel program
Let's create our first threaded program

```
#include <omp.h>

int main() {
    #pragma omp parallel num_threads(10)
    {
        printf("Hello from thread %d\n",omp_get_thread_num());
    }
    return 0;
}
```


1.  First, let's compile it

```
gcc -fopenmp C/parallel.c -o C/parallel.exe
```

2. Now it is time to run it.

```
C/./parallel.exe
```

```
Hello from thread 0
Hello from thread 1
Hello from thread 3
Hello from thread 2
Hello from thread 5
Hello from thread 6
Hello from thread 9
Hello from thread 8
Hello from thread 7
Hello from thread 4
```

You should immediately notice that (likely) the output of the above program is not in a given order. This is because all the threads are running concurrently, and, if the number of hardware threads is larger than 1, a set of them may be running in parallel.

Open the file parallel.c and play with different number of threads by changing the value inside the clause num_threads(), and re-running the above two commands.

## Thinking in parallel
If you're experienced in sequential programming, you're likely familiar with writing code for a single thread. When thinking sequentially, the developer must primarly think of the instructions that are executed. Parallel programming adds an additional complexity to the development program. When writting programs, a developer must think of the following aspects of the code:

Workers creation: How to create workers and how many to create
Work assignment: How to assign work to different workers
Workers/resources communication and coordination: How workers communicate and synchronize in order to coordinate their work.
Note: Different programming models exist that balance these three tasks. Here I am referring to the most popular programming models. Allow me to be simplistic here.
The fork-join model - An example.
OpenMP is mainly known for its Fork-Join model. Programs execute with an initial sequential thread until a directive (code anotation) is reached that initiates parallel threads (workers). Different directives are used to assign work to these threads. At the end of the parallel region, threads synchronize, forming again a single thread.

For the above example. worker creation is achieved through the #pragma omp parallel num_threads(10) directive. It allows to create 10 threads. Each worker is associated with an identifier, obtained through the omp_get_thread_num() function call. Work assignment is achieved through the code in the region enclosed by the brackets {...}. All threads are executing the same set of instructions, in this case only printf("hello from thread %d\n",...);. Notice that having a different identifier allows for each thread to access different data, or follow different paths. Finally Worker synchronization and coordination is relatively simple in this example, since there's not much communication between them. However, at the end of the parallel region, all workers must wait for each other to finish before continuing with the sequential code.

### Exercise 1
Can you modify the code above to make the odd and even threads print something different?

Go to exercise1.c and use the code region below to build and execute your code

```
gcc -fopenmp Exercises/exercise1.c -o Exercises/exercise1.exe && Exercises/./exercise1.exe
```

```
Hello from thread 2
Hello from thread 0
Hello from thread 5
Hello from thread 1
Hello from thread 4
Hello from thread 6
Hello from thread 8
Hello from thread 7
Hello from thread 9
Hello from thread 3
```

See a possible solution to Exercise 1.

```
gcc -fopenmp Solutions/exercise1.c -o Solutions/exercise1.exe && Solutions/./exercise1.exe
```

```
Hello from thread 0 I am Odd
Hello from thread 1 I am Even
Hello from thread 2 I am Odd
Hello from thread 3 I am Even
Hello from thread 5 I am Even
Hello from thread 4 I am Odd
Hello from thread 7 I am Even
Hello from thread 6 I am Odd
Hello from thread 8 I am Odd
Hello from thread 9 I am Even
```

## Memory: Shared vs Private
When programming we often imagine memory as a single "monolithic" element. However, this is not the reality. Current architectures feature a complex memory organization that includes registers, caches, multiple DRAM banks, and even devices with a different memory space. When programming in parallel, such complex structures become more important for correctness and performance.

Multithreading programming often features shared memory, meaning that all threads have access to the same varibles, located in the same memory address (I expect the reader to be familiar with pointers). However, it is also possible for each thread to have private memory, even if the name of variables are the same.

Take for example the next program:

```
int main() {
    int i;
    double share;
    int Array[10];

    printf("Address of i prior to the parallel region is: %lx\n",(unsigned long)&i);
    printf("Address of shared prior to the parallel region is: %lx\n",(unsigned long)&share);
    printf("Address of Array prior to the parallel region is: %lx\n",(unsigned long)Array);

    #pragma omp parallel private(i, Array) shared(share)
    {
        printf("Address of i as seen by thread %d: %lx\n", omp_get_thread_num(), (unsigned long)&i);
        printf("Address of Array as seen by thread %d: %lx\n", omp_get_thread_num(), (unsigned long)Array);
        printf("Address of share as seen by thread %d: %lx\n", omp_get_thread_num(), (unsigned long)&share);
    }
}
```

```
gcc -fopenmp C/memory.c -o C/memory.exe
```

```
C/./memory.exe
```

```
Address of i prior to the parallel region is: 7ffe351c043c
Address of shared prior to the parallel region is: 7ffe351c0440
Address of Array prior to the parallel region is: 7ffe351c0450
Address of i as seen by thread 0: 7ffe351c03ac
Address of Array as seen by thread 0: 7ffe351c03b0
Address of share as seen by thread 0: 7ffe351c0440
Address of i as seen by thread 1: 7fa39d045dec
Address of Array as seen by thread 1: 7fa39d045df0
Address of share as seen by thread 1: 7ffe351c0440
Address of i as seen by thread 3: 7fa39c043dec
Address of Array as seen by thread 3: 7fa39c043df0
Address of share as seen by thread 3: 7ffe351c0440
Address of i as seen by thread 5: 7fa39b041dec
Address of Array as seen by thread 5: 7fa39b041df0
Address of share as seen by thread 5: 7ffe351c0440
Address of i as seen by thread 4: 7fa39b842dec
Address of Array as seen by thread 4: 7fa39b842df0
Address of share as seen by thread 4: 7ffe351c0440
Address of i as seen by thread 2: 7fa39c844dec
Address of Array as seen by thread 2: 7fa39c844df0
Address of share as seen by thread 2: 7ffe351c0440
```

You can play with this code going to memory.c

Private memory allows for variables to be visible only by the current worker. Shared memory, allows variables to be visible from and modified by multiple workers (read and write). However, it is important to be careful. As previously mentioned, memory organization is complex, and requires additional coordination.

Take for example the following program:

```
int main() {
    int i = 0;

    #pragma omp parallel shared(i) num_threads(10000)
    {
        i++;
    }
    
    printf("i = %d\n",i);
    return 0;
}
```

```
gcc -fopenmp C/datarace.c -o C/datarace.exe
```

```
C/./datarace.exe
```

```
i = 9873
```

If 10000 workers are created, and each is adding 1 to the value of i, the "expected" value would be 10000. If you're running this in a machine that has multiple threads, I expect you to see a number less than 10000. Moreover, multiple executions may lead to different results. This is what is known as a data race. It occurs because reading i, incrementing, and writting to i are three different instructions. Therefore, it is possible for two threads to write the same value of i, increment it and obtain the same value twice.

For this reason, shared memory requires additional coordination between workers, such that reads and writes to the same region are perceived in the expected order.

Notice that this is part of thinking about Workers/resource communication and coordination. We are coordinating memory acesses and operations to variables, as they are shared across different workers.

You can modify the above code going to datarace.c

Note: Data races are a difficult aspect of parallel programming. Multiple executions may lead to different results, but among the different results that can be obtained, it is still possible to obtain the "expected" result. Some data races are more difficult to debug than others, because they have a higher chance of choosing the "expected" result. Imagine that 1 out of a million executions of your code in a given hardware shows a datarace. Now imagine this program running the automatic pilot of an airplane...

## Atomic operations

Atomic operations allows different threads to perform different operations to the same memory location in a single instruction (or as if they were executed in a single instruction). In the example above, atomic operations would allow for read, increment and write to happen in a single instruction (or "atomically"). Thus, atomic operations can solve the datarace issue of the previous example.

```
int main() {
    int i = 0;

    #pragma omp parallel shared(i) num_threads(10000)
    {
        #pragma omp atomic
        i++;
    }
    
    printf("i = %d\n",i);
    return 0;
}
```

```
gcc -fopenmp C/atomic.c -o C/atomic.exe
```

```
C/./atomic.exe
```

```
i = 10000
```

You can play with the above code going to atomic.c

## Private vs Firstprivate
Privatization of variables means that a single variable name will have different memory locations. Privatization does not guarantee that the new address has the same value of the original address (i.e. the address before the parallel region).

Take for example the following code:

```
int main() {
    int i = 999;

    #pragma omp parallel private(i) num_threads(10)
    {
        print("Thread %d sees %d", omp_get_thread_num(), i);
    }

    return 0;
}
```

```
gcc -fopenmp C/private.c -o C/private.exe
```

```
C/./private.exe
```

```
i is 999 before parallel region
Thread 0 sees 0 on memory 7ffc564c2c14
Thread 4 sees 0 on memory 7f01eca53e14
Thread 2 sees 0 on memory 7f01eda55e14
Thread 3 sees 0 on memory 7f01ed254e14
Thread 9 sees 0 on memory 7f01ea24ee14
Thread 6 sees 0 on memory 7f01eba51e14
Thread 7 sees 0 on memory 7f01eb250e14
Thread 8 sees 0 on memory 7f01eaa4fe14
Thread 5 sees 0 on memory 7f01ec252e14
Thread 1 sees 0 on memory 7f01ee256e14
```

You can play with the above code going to private.c

Firstprivate allows for each new address location to be initialized with the value prior to the parallel region. Take for example the following code.

```
int main() {
    int i[3] = {999,888,666};

    printf("i is [%d,%d,%d] before parallel region\n",i[0],i[1],i[2]);

    #pragma omp parallel firstprivate(i) num_threads(10)
    {
        printf("Thread %d sees [%d,%d,%d] on memory %lx\n", omp_get_thread_num(), i[0],i[1],i[2], (unsigned long)i);
    }

    return 0;
}
```

```
gcc -fopenmp C/firstprivate.c -o C/firstprivate.exe
```

```
C/./firstprivate.exe
```

```
i is [999,888,666] before parallel region
Thread 0 sees [999,888,666] on memory 7ffcc7ca4e7c
Thread 5 sees [999,888,666] on memory 7f72b4e9fdfc
Thread 9 sees [999,888,666] on memory 7f72b2e9bdfc
Thread 6 sees [999,888,666] on memory 7f72b469edfc
Thread 8 sees [999,888,666] on memory 7f72b369cdfc
Thread 4 sees [999,888,666] on memory 7f72b56a0dfc
Thread 7 sees [999,888,666] on memory 7f72b3e9ddfc
Thread 2 sees [999,888,666] on memory 7f72b66a2dfc
Thread 1 sees [999,888,666] on memory 7f72b6ea3dfc
Thread 3 sees [999,888,666] on memory 7f72b5ea1dfc
```

You can play with the above code going to firstprivate.c

Notice how each location for i is different on each thread, yet, all have the same expected value. This also means that memory copies need to be performed in order to achieve this behavior. Hence, if your array is large, it may incur in additional overhead.

There are still a lot of good reasons to privatize variables.

## Reductions
So far we have discussed what happens to variables when going from a sequential region to a parallel region. However, what happens to these multiple private memory locations when a parallel region is over? In principle, private variables are discarded (freed) at the end of a parallel region, hence, if their value are important, it is necessary to store them into a shared location that lives after the parallel region. Yet, it is often desireable to update the original memory location of the variable.

But wait, all of these variables may have different values. How do I decide what's the final value to be used after the parallel region? Reductions are collective operations that aggregate the different values into a single value, by applying an operation. Ideally, this operation should be commutative, otherwise, how do I decide the order in which they are applied?

Note: Surprisingly enough OpenMP used to support the minus (-) operation for reductions. It wasn't until version 5.2 that they removed support for this operation. If thread 1 and thread 2 are reducing A, should it be At1 - At2 or At2 - At1?
Let's take for example the following code:

```
int main() {
    int i = 99;

    printf("Value if i prior to parallel region is %d\n",i);

    // Private values are not transferred back
    #pragma omp parallel private(i)
    {
        i=1000;
    }
    printf("Value if i after parallel region with private(i) is %d\n",i);

    i = 0;
    // Reductions for addition.
    #pragma omp parallel reduction(+:i) num_threads(10)
    {
        i=1;
    }
    printf("Value if i after parallel region with reduction(+:i) is %d\n",i);

    // Reductions for max.
    #pragma omp parallel reduction(max:i) num_threads(20)
    {
        i=omp_get_thread_num();
    }
    printf("Value if i after parallel region with reduction(max:i) is %d\n",i);

    return 0;
}
```

```
gcc -fopenmp C/reductions.c -o C/reductions.exe
```

```
C/./reductions.exe
```

```
Value if i prior to parallel region is 99
Value if i after parallel region with private(i) is 99
Value if i after parallel region with reduction(+:i) is 10
Value if i after parallel region with reduction(max:i) is 19
```

You can play with the above code going to reductions.c. Other reduction operations are:

- Multiplication (*)
- Minimun (min)
- Bitwise AND (&)
- Bitwise OR (|)
- Bitwise XOR (^)
- Logic AND (&&)
- Logic OR (&&)

## Lastprivate
Finally, there is lastprivate. Later on we will discuss more about loops and how to distribute them across workers. However, lastprivate allows for the value to be the last value in the iteration space. This means, if we have 10 iterations in a for loop, the value for i = 9 will be copied over.

This code shows this behavior. Let us ignore for now the for construct. We will go back to it later on.

```
int Array[10];
    int i, b;

    for (i = 0; i < 10; i++) {
        Array[i] = i;
    }

    #pragma omp parallel for lastprivate(b)
    for (i = 0; i < 10; i++)
    {
        b = Array[i];
    }
    printf("b is %d after the parallel region\n", b);

    return 0;
```

```
gcc -fopenmp C/lastprivate.c -o C/lastprivate.exe
```

```
C/./lastprivate.exe
```

```
b is 9 after the parallel region
```

You can play with this code going to lastprivate.c.

### Exercise 2
Create a program that:

Initializes an array of 100 elements to random numbers by assigning a thread per element of the array.
- Finds the max value of the array.
- Finds the min value of the array.
- Finds the average value of the array.

Go to exercise2.c and use the code region below to build and execute your code

```
gcc -fopenmp Exercises/exercise2.c -o Exercises/exercise2.exe && Exercises/./exercise2.exe
```

See a possible solution to Exercise 2.

```
gcc -fopenmp Solutions/exercise2.c -o Solutions/exercise2.exe && Solutions/./exercise2.exe
```

```
[ 9383  886  2777  6915  7793  8335  492  8690  5386  27  6649  1421  7763  2362  6327  6429  5736  846  5857  59  9582  8814  3926  3426  3929  5368  2862  7739  540  5211  9172  1530  4067  4022  8456  2567  4421  5782  4324  5123  9802  4919  5011  3069  7373  1393  3135  8167  5434  8042  4043  3784  8315  3058  6091  6862  2305  336  1729  6124  8537  6229  4370  9956  6996  7084  6505  1313  3895  545  5198  3367  1087  364  3750  7276  5788  6808  6413  3526  7178  8980  5403  3584  2754  2651  1873  2399  5060  9170  9932  7281  9676  3368  12  925  6226  8586  8094  7539 ]
max is 9383
min is 886
Avg is 357
```
