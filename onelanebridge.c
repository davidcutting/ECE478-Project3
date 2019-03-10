



//Monitor Bridge {
    int nWaiting=0, sWaiting=0, sOnBridge=0, nOnBridge=0;
    pthread_cond_t north_turn, south_turn;
    pthread_mutex_t count_mutex;
    void enterNorth() {
        if (sWaiting>0 || sOnBridge>0)
        {
            nWaiting++;
            pthread_cond_wait(&north_turn,&count_mutex);
            while (sOnBridge>0)
                pthread_cond_wait(&north_turn,&count_mutex);
            nWaiting--;
        }
        nOnBridge++;
        if (sWaiting==0)
        {
            pthread_mutex_lock(&count_mutex);
            pthread_cond_signal(&north_turn);
        }
    }
    void exitNorth() {
        nOnBridge--;
        pthread_mutex_unlock(&count_mutex);
        if (nOnBridge ==0)
            pthread_cond_signal(&south_turn);
    }
    void enterSouth() {
        if (nWaiting>0 || nOnBridge>0)
        {
            sWaiting++;
            pthread_cond_wait(&south_turn,&count_mutex);
            while (nOnBridge>0)
                pthread_cond_wait(&south_turn,&count_mutex);
            sWaiting--;
        }
        sOnBridge++;
        pthread_mutex_lock(&count_mutex);
        if (nWaiting==0)
            pthread_cond_signal(&south_turn);
        pthread_mutex_unlock(&count_mutex);
    }
    void exitSouth() {
        sOnBridge--;
        if(sOnBridge == 0)
            pthread_cond_signal(&north_turn);
    }
//}

int main() {
    pthread_mutex_init(&count_mutex, NULL);
    pthread_cond_init (&count_threshold_cv, NULL);
    
    /*
     For portability, explicitly create threads in a joinable state
     */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&threads[0], &attr, inc_count, (void *)&thread_ids[0]);
    pthread_create(&threads[1], &attr, inc_count, (void *)&thread_ids[1]);
    pthread_create(&threads[2], &attr, watch_count, (void *)&thread_ids[2]);
     
     /* Wait for all threads to complete */
    for (i = 0; i < NUM_THREADS; i++) {
     pthread_join(threads[i], NULL);
     }
     //printf ("Main(): Waited on %d  threads. Done.\n", NUM_THREADS);
    
     
     /* Clean up and exit */
     pthread_attr_destroy(&attr);
     pthread_mutex_destroy(&count_mutex);
     pthread_cond_destroy(&count_threshold_cv);
     pthread_exit (NULL);
}
