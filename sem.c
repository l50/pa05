/**
 * @file   sem.c
 * @author Jayson Grace (jaysong@unm.edu)
 * @date   9/27/2015
 * @brief  Semaphore for PA05, part 1.
 */
#include <pthread.h>

typedef struct
{
    int S;
    pthread_mutex_t mut;
    pthread_cond_t cond;
} Sem437;

void Sem437Init(Sem437*, int);
void Sem437P(Sem437*);
void Sem437V(Sem437*);

/**
 * @brief Used to initialize the mutex and condition variable
 * @param sem semaphore to initialize
 * @param i value to associate with the semaphore
 */
void Sem437Init(Sem437* sem, int i)
{
    sem->S = i;
    pthread_mutex_init(&sem->mut, NULL);
    pthread_cond_init(&sem->cond, NULL);
}

/**
 * @brief Used for decrementing
 * @param sem semaphore to decrement
 */
void Sem437P(Sem437* sem)
{
    pthread_mutex_lock(&sem->mut);
    // If semaphore is negative, block
    while(sem->S <= 0)
        pthread_cond_wait(&sem->cond, &sem->mut);
    sem->S -= 1;
    pthread_mutex_unlock(&sem->mut);
}

/**
 * @brief Used for incrementing
 * @param sem semaphore to increment
 */
void Sem437V(Sem437* sem)
{
    pthread_mutex_lock(&sem->mut);
    sem->S += 1;
    pthread_cond_signal(&sem->cond);
    pthread_mutex_unlock(&sem->mut);
}
