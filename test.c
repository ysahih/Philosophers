#include "philo.h"

int a;
    pthread_mutex_t x;

void*   routine2(void* i)
{
    sleep (1);
    for(long j = 0; j < 9000000000; j++){
    pthread_mutex_lock(&x);
        a++;
    pthread_mutex_unlock(&x);
    }
    printf("%d\n", a);
    return NULL;
}

// void*   routine(void* i)
// {
//     pthread_t   t;
    
//     if (pthread_create(&t, NULL, &routine2, NULL))
//                 return 0;
//     printf("before : %d\n", a);
//     pthread_join(t, NULL);
//     return NULL;
// }

int main(int ac, char *av[])
{
    pthread_t   t;
    pthread_mutex_init(&x, NULL);
    int i = atoi(av[1]);
    for(int j = 1; j <= i; j++)
    {
        if (pthread_create(&t, NULL, &routine2, NULL))
            perror("Failed to create thread");
        printf("hello from thread 1, I created new thread (%d)\n", j);
        pthread_join(t, NULL);
    }
    pthread_mutex_destroy(&x);
    return 0;
}