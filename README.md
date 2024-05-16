# DERFAST
## DEMAC Educational Resources and Framework for Advanced Supercomputing Training

## Table of Contents
1. Framework Description
2. Prerequisites
3. Learning Outcomes
4. Learning Resources
5. Learning Assessment
6. Course Calendar

---
## 1. Framework Description

This educational framework for HPC includes the development of a low-cost and flexible platform design for users in diverse fields. It allows study and experimentation with multiple realistic elements involved in a production HPC ecosystem. DEMAC, the Delaware Modular Assembly Cluster, is a set of 3D-printable frames designed to house embedded systems and auxiliary systems in a way that emulates HPC platforms. The teaching framework focuses on practical training as an education model in which learners reinforce theoretical knowledge with hands-on experience. If successful, this effort will contribute fundamentally to scientific research, technological advancements, HPC workforce development, and economic growth.

## 2. Prerequisites

## 3. Learning Outcomes

At the conclusion of this course, you should have the ability to:
- Build a multi-node platform.
- Understand the basis of computer architecture and organization.
- Develop a set of skills suited for high-performance computing.
- Have practical experience with a system that can mimic supercomputers.
- Analyze and Execute distributed and parallel software.
- Design and implement parallel programs.

## 4. Learning Resources

### Github Repository

### DEMAC Resources
#### Instructables
#### STL Files for 3D Printing

### External Material

- Organization and Design: The Hardware/Software Interface by David Patterson and John Hennessy


## 5. Learning Assessment

Most of the tasks will have examples of the expected outcome, like guides and tutorials. Some other tasks will have open questions for the participant to propose their own answer.
Instructors are encouraged to develop aditional exercises that can be used to further asses the proficiency of the participants. 


## 6. Course Organization and Chronology

The framework contains a collection of interrelated modules encompassing multiple HPC elements. Users can tailor their own experience to their needs and goals. For example, a set of demo applications or microbenchmarks can be used as course material to integrate research into teaching. 

Modules include an aproximate execution time that can be used as a guide to select the amount of content based on the available time. Instructors might have to consider the participants background to adjust the available time for each module accordingly.

Each folder contains a README file with additional information for a specific module. 

### [A. Single Core](Modules/A_Single_Core/README.md)
> #### A.1. Introduction to computer organization and CPU abstractions
> #### [A.2. DEMAC: Single node installation and setup](Modules/A_Single_Core/A_2/README.md)
> #### A.3. Basic programming concepts (variables, loops, conditionals)

> #### A.4. Compiler technology (from code to execution)
> #### A.5. Hardware interoperability, bits and pieces
> #### A.6. Intermediate programming concepts (functions, classes, libraries)

> #### A.7. Pipelining techniques (superscalar, dynamic scheduling)
> #### A.8. Advanced programming concepts (templates, macros, polymorphism)
> #### A.9. Program Execution Model (The Codelet Model PXM)

### [B. Multiple Cores](Modules/B_Multiple_Cores/README.md)
> #### [B.1. Taxonomy and abstractions of shared memory architectures](Modules/B_Multiple_Cores/B_1/README.md)
> #### [B.2. DEMAC: Setup a multi-core platform](Modules/B_Multiple_Cores/B_2/README.md)
> #### [B.3. Basic parallel programming concepts (tasks, threads)](Modules/B_Multiple_Cores/B_3/README.md)

> #### B.4. Synchronization and scheduling techniques
> #### B.5. Memory scopes and hierarchy
> #### [B.6. Parallel programming models (OpenMP)](Modules/B_Multiple_Cores/B_6/README.md)

> #### B.7. Compiler optimizations for parallel programs
> #### B.8. Advanced hardware techniques (multi-threading)
> #### B.9. DARTS: A runtime based on the Codelet Model

### [C. Accelerators](Modules/C_Accelerators/README.md)
> #### C.1. Types of accelerators concepts and abstractions
> #### [C.2. DEMAC: The Epiphany co-processor](Modules/C_Accelerators/C_2/README.md)
> #### [C.3. Basic accelerators programming concepts (offloading)](Modules/C_Accelerators/C_3/README.md)

> #### C.4. Compiler techniques for heterogeneous architectures
> #### C.5. Memory Management for heterogeneous architectures
> #### C.6. Accelerator programming models

> #### C.7. Emulating a GPU with the Parallella board
> #### C.8. FPGAs and ASICs with the Parallella board
> #### C.9. PXM for accelerators, static dataflow

### [D. Multiple Nodes](Modules/D_Multiple_Nodes/README.md)
> #### D.1. Hardware abstractions of multi-node systems
> #### [D.2. DEMAC: A distributed memory architecture](Modules/D_Multiple_Nodes/D_2/README.md)
> #### D.3. Basic multi-node programming concepts (inter-node operations)

> #### [D.4. Message Passing Interface (MPI)](Modules/D_Multiple_Nodes/D_4/README.md)
> #### D.5. Network trafic vs memory accesss
> #### D.6. Multi-node programming models

> #### D.7. Compiler techniques for distributed memory systems
> #### D.8. Hardware-Software codesign for multi-node machines
> #### D.9. DECARD: A distributed runtime based on the Codelet Model

### [E. Complex Topologies](Modules/E_Complex_Topologies/README.md)
> #### E.1. Introduction to complex network topologies
> #### E.2. DEMAC and complex network topologies
> #### E.3. Basic cluster programming concepts (workload management)

> #### E.4. Network monitor and management, In-Network Computing
> #### E.5. Topology aware programming and metadata
> #### E.6. Memory and I/O, communications and storage (NFS, FSS)

> #### E.7. Compiler technology and network management
> #### E.8. Scalability and advanced design considerations
> #### E.9. PXM and complex network topologies, HW-SW codesign in clusters
