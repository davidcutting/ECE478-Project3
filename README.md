# ECE478-Project3

## Producer and consumer problem

### How to run

First *make* the project, then run the command from the command line using this template:

`boundedBuffer <number of iterations> <size of buffer>`

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

### How to run

First *make* the project, then run the command from the command line using this template:

`condvar1`

## The professor and students problem

### How to run

First *make* the project, then run the command from the command line using this template:

`professorStudent <number of students>`

### Implementation

The challenge of this problem is to only allow one person to speak at a time, and have the professor answer each question. Each student must wait for their turn to ask the professor a question. We achieved this with the use of semaphores.

Each time either a professor or student thread speaks, the other threads must wait to be signaled before executing. We used a semaphore called *speak* for this. At the end of their execution they signal, and the next thread is allowed to speak.

Another semaphore called *question* is used to control the professor thread. A professor may not answer a question before a question is asked, therefore it waits for a question and then it executes. The student starts a question by signaling the *question* semaphore, which prompts the professor to answer.

Last, to complete the event the student must know when the professor has answered. Another semaphore called *answer* allows the professor to signal that the answer was given. The student thread that has asked a question waits until it is signaled via the *answer* semaphore. Once the student gets the answer it signals the next student to speak.

This flow is continued until each student has asked, and been answered.

### Sample outputs

```bash
$ ./professorStudent 5
The professor wants to be asked a question.
0 : The student is ready to ask a question.
0 : The student is asking a question.
The professor is answering the question.
The professor is finished answering.
The professor wants to be asked a question.
0 : The student is done asking a question.
1 : The student is ready to ask a question.
1 : The student is asking a question.
The professor is answering the question.
The professor is finished answering.
The professor wants to be asked a question.
1 : The student is done asking a question.
2 : The student is ready to ask a question.
2 : The student is asking a question.
The professor is answering the question.
The professor is finished answering.
The professor wants to be asked a question.
2 : The student is done asking a question.
3 : The student is ready to ask a question.
3 : The student is asking a question.
The professor is answering the question.
The professor is finished answering.
The professor wants to be asked a question.
3 : The student is done asking a question.
4 : The student is ready to ask a question.
4 : The student is asking a question.
The professor is answering the question.
The professor is finished answering.
The professor wants to be asked a question.
4 : The student is done asking a question.
```
