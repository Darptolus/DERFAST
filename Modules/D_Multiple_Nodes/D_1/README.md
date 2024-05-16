# D.1. Hardware abstractions of multi-node systems

A distributed system is composed of several independent computers that are linked together via a network and distribution middleware. This setup allows these computers to synchronize their tasks and pool their resources. As a result, users experience the distributed system as a unified computing environment rather than individual machines.

## Divide and conquer 
Imagine you have a really big task to complete, like building a massive building. You could either try to build it all by yourself, which would take a lot of time and resources, or you could distribute the work among a group of people, each focusing on different parts of the building.

In computer science, a distributed architecture is like that group of people working together. Instead of having one single computer do all the work, you spread the work across multiple computers, which we call nodes or servers. Each of these computers has its own processing power and resources.

Now, why do we do this? Well, there are a few reasons:

- Scalability: If you need more computing power, instead of upgrading one big machine, you can just add more computers to your network.

- Reliability: If one computer fails, the whole system doesn't crash because the workload is distributed across multiple computers. It's like if one worker building the big building gets sick, the others can still keep working.

- Performance: By spreading out tasks, you can often get things done faster. It's like having multiple workers working on different parts of the building at the same time, making the construction process more efficient.

- Flexibility: You can have computers in different locations, which can be helpful for things like handling users from different parts of the world or ensuring data redundancy and disaster recovery.

So, in a nutshell, a distributed architecture is like teamwork for computers, where tasks are divided among multiple machines to make things faster, more reliable, and easier to manage.


        +------------------+        +------------------+
        |    Node 1        |        |    Node 2        |
        |  (Server)        |        |  (Server)        |
        |                  |        |                  |
        +------------------+        +------------------+
                 |                          |
                 |                          |
        +------------------+        +------------------+
        |    Node 3        |        |    Node 4        |
        |  (Server)        |        |  (Server)        |
        |                  |        |                  |
        +------------------+        +------------------+
                       \                 /
                        \               /
                         \             /
                          \           /
                           \         /
                            \       /
                             \     /
                              \   /
                               \ /
                        +------------------+
                        |    Network       |
                        |                  |
                        +------------------+

Nodes 1, 2, 3, and 4 represent individual servers or computers within the distributed system.

The lines between the nodes represent the network connections that allow them to communicate with each other.

The network facilitates the exchange of data and messages between the nodes.

Each node operates autonomously but can communicate and share resources with other nodes in the system.