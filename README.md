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

First *make* the project, then run the command from the command line:

`onelanebridge`

### Implementation

We implemented the one-lane bridge problem using mutexes and condition variables. We wrote 3 functions arrival void arriveBridge(), void crossBridge(), and void exitBridge() each with a mutex lock and unlock in the beginning and end of the function to ensure one thread at a time is accessing shared data. First a car direction array acquires 50 random values which are either 0 or 1. In main the oneVehicle thread is created 50 times. Then...

arriveBridge() is done by acquiring the mutex lock then based on what value is containted in the car array value either 0 or 1, will determine the direction it is from. Mutex is now unlocked.

```C
car 47 dir 1 arrived at the bridge.
```

crossBridge() is done by checking if the bridge is safe by using a isSafe bool function to check. If it is unsafe the thread will wait until it is. Once the bridge is safe the mutex lock is acquired. The number of cars on the bridge is incremented and information about the car number, direction, and number of cars is printed to the screen. Lastly the mutex is unlocked again.

```C
car 47 dir 1 crossing the bridge. Current dir: 1 #cars: 3
```

exitBridge() is done by first acquiring the mutex lock then decrementing the number of cars on the bridge by one. Now some text about the car number that exited the bridge and its direction. Finally the mutex lock unlocks once again.

```C
car 47 dir 1 exits the bridge.
```

### Sample output

```bash
$ ./onelanebridge
car 1 dir 1 arrived at the bridge.
car 1 dir 1 crossing the bridge. Current dir: 0 #cars: 1
car 1 dir 0 exits the bridge.
car 2 dir 1 arrived at the bridge.
car 2 dir 1 crossing the bridge. Current dir: 1 #cars: 1
car 2 dir 0 exits the bridge.
car 3 dir 0 arrived at the bridge.
car 3 dir 0 crossing the bridge. Current dir: 1 #cars: 1
car 3 dir 0 exits the bridge.
car 4 dir 1 arrived at the bridge.
car 4 dir 1 crossing the bridge. Current dir: 0 #cars: 1
car 4 dir 0 exits the bridge.
car 5 dir 0 arrived at the bridge.
car 5 dir 0 crossing the bridge. Current dir: 1 #cars: 1
car 5 dir 0 exits the bridge.
car 6 dir 0 arrived at the bridge.
car 6 dir 0 crossing the bridge. Current dir: 0 #cars: 1
car 6 dir 0 exits the bridge.
car 7 dir 0 arrived at the bridge.
car 7 dir 0 crossing the bridge. Current dir: 0 #cars: 1
car 7 dir 0 exits the bridge.
car 8 dir 1 arrived at the bridge.
car 8 dir 1 crossing the bridge. Current dir: 0 #cars: 1
car 8 dir 0 exits the bridge.
car 9 dir 0 arrived at the bridge.
car 9 dir 0 crossing the bridge. Current dir: 1 #cars: 1
car 9 dir 0 exits the bridge.
car 10 dir 0 arrived at the bridge.
car 10 dir 0 crossing the bridge. Current dir: 0 #cars: 1
car 10 dir 0 exits the bridge.
car 11 dir 1 arrived at the bridge.
car 12 dir 1 arrived at the bridge.
car 13 dir 1 arrived at the bridge.
car 12 dir 1 crossing the bridge. Current dir: 1 #cars: 1
car 14 dir 0 arrived at the bridge.
car 13 dir 1 crossing the bridge. Current dir: 1 #cars: 2
car 12 dir 0 exits the bridge.
```

## The professor and students problem

### How to run

First *make* the project, then run the command from the command line using this template:

`professorStudent <number of students>`

### Implementation

This was implemented by using semaphores for synchronization. We made four procedures: QuestionStart(), QuestionDone(), AnswerStart(), and AnswerDone(). One thread is made for the professor, and any number of threads is made for the students.

The number of students can be changed via the command line prompt and the student threads are created by the following for loop below while there is only one professor thread in this problem.

```C
for (student = 0; student < numStudents; student++) {
        pthread_create(&stud_id, NULL, Student, NULL);
        pthread_join(stud_id, NULL);
```

The challenge of this problem is to only allow one person to speak at a time, and have the professor answer each question. Each student must wait for their turn to ask the professor a question. We achieved this with the use of semaphores.

Students will display that they are ready to ask a question, once the professor is ready to answer a question one student begins asking a question. No other student will ask a question until the professor finishes with an answer and that student has recieved the answer. 

This program is designed to keep students from asking questions at the same time using semaphors to signal whether the thread must wait for another student thread or the professor to complete until it is allowed to carry on.

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
The professor is answering the question.
The professor is finished answering.
The professor wants to be asked a question.
2 : The student is asking a question.
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
