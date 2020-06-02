#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

sem_t lock;
pthread_mutex_t mutex_lock;

void * func1(void * arg)
{
        pthread_t id;

        id = pthread_self();
        printf("in the context of %d\n", (int)id);

        sem_wait(&lock);
        printf("lock acquired for %d\n", (int)id);
        sleep(10);
        sem_post(&lock);
        printf("lock released for %d\n", (int)id);
}

void * func2(void * arg)
{
	pthread_t id;
	
	id = pthread_self();
	printf("in the context of %d\n", (int)id);
	
	sem_post(&lock);
	sem_wait(&lock);
	printf("lock acquired for %d\n", (int)id);
	sleep(10);
	sem_post(&lock);
	printf("lock released for %d\n", (int)id);
}

int main()
{
	int ret = 0;
	pthread_t tid1, tid2;
	
	sem_init(&lock, 0, 1);
	pthread_mutex_init(&lock, NULL);
	ret = pthread_create(&tid1, NULL, &func1, NULL);
	ret = pthread_create(&tid2, NULL, &func2, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	sem_destroy(&lock);
	return 0;
}
