#include "philo.h"

int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int res = 0;

pthread_mutex_t x;
pthread_mutex_t y;
	// typedef struct s_tst
	// {
	// 	int a;
	// 	int b;
	// }	t_tst;


void*   routine(void* i)
{
	
	// sleep (1);
	int *a = (int *)i;
	
	pthread_mutex_lock(&x);
	res += arr[*a];
	pthread_mutex_unlock(&x);

	free(a);
   return NULL;
}

int main(int ac, char *av[])
{

	int j;
	pthread_t   t[10];
    int *a;
	pthread_mutex_init(&x, NULL);
	// int i = atoi(av[1]);
	for(j = 0; j < 10; j++)
	{
		a = malloc (sizeof(int ));
		*a = j;
		if (pthread_create(&t[j], NULL, &routine, a))
			perror("Failed to create thread");
	}
	for(j = 0; j < 10; j++)
		pthread_join(t[j], NULL);
	pthread_mutex_destroy(&x);
	
	printf("%d\n", res);
  
	
	
	return 0;
}