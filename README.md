# ECE478-Project3

## Producer and consumer problem

### How to run

First *make* the project, then run the command from the command line using this template:

`./boundedBuffer <number of iterations> <size of buffer>`

### Implementation

We have implemented a bounded buffer using semaphores. The consumer can not consume if the buffer is empty. The producer must first produce some data for the consumer. A semaphore is used to prevent the producer and consumer from interfering with one another while their critical sections are being executed. A producer must wait for the consumer to finish consuming before it produces again, and visa versa.

In the producer this is done with:

```C
sem_wait(&empty);
data = produced;
sem_post(&full);
```

In the consumer this is done with:

```C
sem_wait(&full);
total = total + data;
sem_post(&empty);
```

Adding a loop for creating and joining threads allows multiple producers and consumers. The buffer size can be changed via a command line parameter. This parameter is loaded into `bufferSize` and then used to initialize the empty semaphore, because an empty semaphore would have a size *n* with *n* being the maximum buffer size.

### Sample outputs

```bash
$ ./boundedBuffer 100 100
the total is 9900
the total is 9900
the total is 9900
```

```bash
$ ./boundedBuffer 100 10
the total is 5049
the total is 4991
the total is 5302
```

```bash
$ ./boundedBuffer 10000 100
the total is 50669150
the total is 50145380
the total is 50838559
```

## The one-lane bridge problem
