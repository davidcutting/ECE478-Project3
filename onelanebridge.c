#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <cstdlib>


//One Lane Bridge Monitor Solution

int thread_ids[50];
pthread_mutex_t count_mutex;
pthread_cond_t count_threshold_cv;

//monitor Bridge {
    //Condition safe;
    
    int currentDirec;
    int currentNumber;

    //don't lock here or else you'll get deadlock
    bool isSafe(int carID) {
        if ( currentNumber == 0 )
            return true;    // always safe when bridge is empty
        else if ((currentNumber < 3) && (currentDirec == carID))
            return true;    // room for us to follow others in direc
        else
            return false;   // bridge is full or has oncoming traffic.
    }
    void ArriveBridge(int carID) {
        printf("A car in direction %d has arrived at the bridge\n",carID);
        pthread_mutex_lock(&count_mutex);
        while (!isSafe(carID) )
            pthread_cond_wait(&count_threshold_cv, &count_mutex);
        currentNumber++;
        currentDirec = carID;
        printf("current number %d current direction %d\n", currentNumber, currentDirec);
        pthread_mutex_unlock(&count_mutex);
    }
    void CrossBridge (int carID) {
        pthread_mutex_lock(&count_mutex);
        printf("A car is crossing the bridge with direction %d\n", carID);
        pthread_mutex_unlock(&count_mutex);
    }
    void ExitBridge(int carID) {
        pthread_mutex_lock(&count_mutex);
        currentNumber--;
        printf("A car is exiting the bridge from direction %d\n\n", carID);
        //safe.Signal();
        pthread_mutex_unlock(&count_mutex);
    }

    
//}
void OneVehicle(int carID) {
    ArriveBridge(carID);
    CrossBridge(carID);
    ExitBridge(carID);
}

int main()
{
    pthread_t threads[50];
    pthread_attr_t attr;

    pthread_mutex_init(&count_mutex, NULL);
    pthread_cond_init (&count_threshold_cv, NULL);
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    for(int i=0; i<50; i++)
        pthread_create(&threads[i], &attr, <#void * _Nullable (* _Nonnull)(void * _Nullable)#>, (void *)&thread_ids[i]);

    srand(time(NULL));
    for(int i=0; i<50; i++)
        thread_ids[i] = rand() % 2;
    for(int i=0; i<50; i++){
        OneVehicle(thread_ids[i]);
        
        for (i = 0; i < 50; i++) {
            pthread_join(threads[i], NULL);
        }
        pthread_attr_destroy(&attr);
        pthread_mutex_destroy(&count_mutex);
        pthread_cond_destroy(&count_threshold_cv);
        pthread_exit (NULL);
    }
}
