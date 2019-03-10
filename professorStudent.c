/*
 * professorStudent.c
 *
 *  You have been hired by the CIS Department to write code to help synchronize
 *  a professor and his/her students during office hours. The professor, of
 *  course, wants to take a nap if no students are around to ask questions; if
 *  there are students who want to ask questions, they must synchronize with
 *  each other and with the professor so that
 *      (i)   only one person is speaking at any one time,
 *      (ii)  each student question is answered by the professor, and
 *      (iii) no student asks another question before the professor is done
 *            answering the previous one.
 *
 *  You are to write four procedures:
 *      AnswerStart(),
 *      AnswerDone(),
 *      QuestionStart(), and
 *      QuestionDone()
 *
 *  The professor loops running the code:
 *      AnswerStart(); give answer;
 *      AnswerDone().
 *
 *  AnswerStart doesn't return until a question has been asked. Each student
 *  loops running the code:
 *      QuestionStart(); ask question;
 *      QuestionDone().
 *
 *  QuestionStart() does not return until it is the student's turn to ask a
 *  question. Since professors consider it rude for a student not to wait for an
 *  answer, QuestionDone() should not return until the professor has finished
 *  answering the question. Use semaphores for synchronization.
 */

 #include <pthread.h>
 #include <semaphore.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <iostream>
 #include <ostream>

 // 0 sem is shared between threads of the process
 // 1 sem is shared between processes
 #define SHARED 1

void* Professor(void* arg);
void* Student(void* arg);
void AnswerStart();
void AnswerDone();
void QuestionStart();
void QuestionDone();

int numStudents;
int student;
sem_t speak, question, answer;

int main(int argc, char* argv[]) {

    // check to see if user gave appropriate arguments
    if (argc < 2) {
	    printf("Usage: professorStudent <number of students>\n");
	    exit(0);
    }
    numStudents = atoi(argv[1]); // number of students from command line params

    pthread_t prof_id, stud_id;

    sem_init(&speak, SHARED, 1);
    sem_init(&question, SHARED, 1);
    sem_init(&answer, SHARED, 1);

    for (student = 0; student < numStudents; student++) {
        pthread_create(&stud_id, NULL, Student, NULL);
        pthread_join(stud_id, NULL);
    }

    pthread_create(&prof_id, NULL, Professor, NULL);
    pthread_join(prof_id, NULL);
    pthread_exit(0);
}

void* Professor(void* arg) {
    while(true) {
        AnswerStart();
        std::cout << "The professor is answering the question." << std::endl;
        AnswerDone();
    }
}

void* Student(void* arg) {
    int studentNum = student;
    std::cout << studentNum << " : The student is ready to ask a question." << std::endl;
    QuestionStart();
    std::cout << studentNum << " : The student is asking a question." << std::endl;
    QuestionDone();
    std::cout << studentNum << " : The student is done asking a question." << std::endl;
}

void AnswerStart() {
    std::cout << "The professor wants to be asked a question." << std::endl;
    sem_wait(&question); // wait for a question
}

void AnswerDone() {
    std::cout << "The professor is finished answering." << std::endl;
    sem_post(&answer); // post an answer
}
void QuestionStart() {
    sem_wait(&speak); // wait to speak
    sem_post(&question); // post a question
}
void QuestionDone() {
    sem_wait(&answer); // wait for an answer
    sem_post(&speak); // let others speak
}
