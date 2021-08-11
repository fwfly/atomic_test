#include<pthread.h>
#include<stdint.h>
#include<stdio.h>
#include<stdatomic.h>

static  atomic_int_fast64_t foo = 0;

#define N_THREADS 128

void add_foo(){
    for (int64_t i = 0; i < 100000; ++i){
        atomic_fetch_add(&foo, 1);
        //printf("foo %ld\n", foo); 
    }
}

int main(void)
{

    pthread_t thr[N_THREADS];

    for (size_t i = 0; i < N_THREADS; i++)
        pthread_create(&thr[i], NULL, (void *(*) (void *) )add_foo,
                       NULL);

    for (size_t i = 0; i < N_THREADS; i++)
        pthread_join(thr[i], NULL);

    printf("Final foo %ld\n", foo);

    
    return 0;
}
