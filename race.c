/*=========================================================*/
/* race.c --- for playing with ECE437 */
/*=========================================================*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <pthread.h>

typedef int bool;
enum { false, true };

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
 * @bried Used for incrementing
 * @param sem semaphore to increment
 */
void Sem437V(Sem437* sem)
{
    pthread_mutex_lock(&sem->mut);
    sem->S += 1;
    pthread_cond_signal(&sem->cond);
    pthread_mutex_unlock(&sem->mut);
}

struct 
{
    int balance[2];
}

Bank = {{100, 100}}; //global variable defined

// Semaphore lock we'll be using
Sem437 lock;

// Specify whether or not debug mode should be run
bool DEBUG = false;

void *MakeTransactions() 
{ //routine for thread execution
    int i, j, tmp1, tmp2, rint;
    double dummy;
    if (DEBUG)
        printf("\nSemaphore value: %i\n",lock.S);
    Sem437P(&lock);
    for (i = 0; i < 100; i++) 
    {
        rint = (rand() % 30) - 15;
        if (((tmp1 = Bank.balance[0]) + rint) >= 0 && ((tmp2 = Bank.balance[1]) - rint) >= 0) 
        {
            Bank.balance[0] = tmp1 + rint;
            for (j = 0; j < rint * 100; j++) 
            {
                dummy = 2.345 * 8.765 / 1.234;
            }
            Bank.balance[1] = tmp2 - rint;
        }
    }
    Sem437V(&lock);
    return NULL;
}

int main(int argc, char **argv) 
{
    int i;
    void *voidptr = NULL;
    pthread_t tid[2];
    Sem437Init(&lock, 1);
    srand(getpid());
    printf("Init balances A:%d + B:%d ==> %d!\n", Bank.balance[0], Bank.balance[1], Bank.balance[0] + Bank.balance[1]);
    for (i = 0; i < 2; i++)
        if (pthread_create(&tid[i], NULL, MakeTransactions, NULL)) 
        {
            perror("Error in thread creating\n");
            return (1);
        }
    for (i = 0; i < 2; i++)
        if (pthread_join(tid[i], (void *) &voidptr)) 
        {
            perror("Error in thread joining\n");
            return (1);
        }
    printf("Let's check the balances A:%d + B:%d ==> %d ?= 200\n",
            Bank.balance[0], Bank.balance[1], Bank.balance[0] + Bank.balance[1]);
    return 0;
}
