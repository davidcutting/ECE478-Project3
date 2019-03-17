#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define NUMTHRDS 50

pthread_t t[NUMTHRDS];
int car[NUMTHRDS];

int j=-1;
int a=-1,b=-1,c=-1;
int i;
int n=0,s=0;
int p=-1;
int currentNumber=0, bridgeDirec, d;

int success=0;

pthread_mutex_t mlock;

bool isSafe(int dir){
    if (currentNumber == 0)
            return true;    // always safe when bridge is empty
    else if ((currentNumber < 3) && (bridgeDirec == dir)){
        return true;    // room for us to follow others in direc
    }
    else
        return false;   // bridge is full or has oncoming traffic.
}

void arriveBridge()
{
    pthread_mutex_lock(&mlock);
    p++;
    if(car[p]==0){
        printf("car %d dir 0 arrived at the bridge.\n",p+1);
        s++;
        d=0;
    }
    else{
        printf("car %d dir 1 arrived at the bridge.\n",p+1);
        n++;
        d=1;
    }
    pthread_mutex_unlock(&mlock);
}

void crossBridge()
{
    b++;
    while(isSafe(d)==false){
        int x=0; //do work
        x=1;
    }
    pthread_mutex_lock(&mlock);

    currentNumber++;

    if(car[b]==0){
    printf("car %d dir 0 crossing the bridge. Current dir: %d #cars: %d\n",b+1,bridgeDirec,currentNumber);
    bridgeDirec=0;
    }
    else{
    printf("car %d dir 1 crossing the bridge. Current dir: %d #cars: %d\n",b+1,bridgeDirec,currentNumber);
    bridgeDirec=1;
    }

    pthread_mutex_unlock(&mlock);
}

void exitBridge()
{
    pthread_mutex_lock(&mlock);
    //printf("exitBridge\n");
    currentNumber--;
    c++;
    if(car[c]==0){
    printf("car %d dir 0 exits the bridge.\n",c+1);
    s--;
    }
    else{
    printf("car %d dir 0 exits the bridge.\n",c+1);
    n--;
    }
    success++;
    pthread_mutex_unlock(&mlock);
}

static void *thread1(void *_){
    arriveBridge();
    crossBridge();
    exitBridge();
    return 0;
}


int main()
{
    srand(time(NULL));
    pthread_mutex_init(&mlock,NULL);

    for(i=0; i<NUMTHRDS; i++){
        car[i] = rand() % 2;
        pthread_create(&t[i], NULL, thread1, NULL);
    }
    pthread_mutex_destroy(&mlock);

    pthread_exit(NULL);
    return 0;
}
