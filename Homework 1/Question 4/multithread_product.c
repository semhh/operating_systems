#include <stdio.h>
#include <pthread.h>

// size of array
#define MAX 16

// maximum number of threads
#define MAX_THREAD 8

//typedef namespace std;

int a[] = { 1, 5, 7, 10, 12, 14, 15, 18, 20, 22, 25, 27, 30, 64, 110, 220 };
int sum[8] = { 0 };
int part = 0;

void* sum_array(void* arg) {
	// Each thread computes sum of 1/8th of array
	int thread_part = part++;

	for (int i = thread_part * (MAX / 8);
	i < (thread_part + 1) * (MAX / 8); i++)
	sum[thread_part] += a[i];
}

// Driver Code
int main(){

	pthread_t threads[MAX_THREAD];

	// Creating 8 threads
	for (int i = 0; i < MAX_THREAD; i++)
		pthread_create(&threads[i], NULL, sum_array, (void*)NULL);

	// joining 8 threads i.e. waiting for all 8 threads to complete
	for (int i = 0; i < MAX_THREAD; i++)
		pthread_join(threads[i], NULL);

	// adding sum of all 8 parts
	int total_sum = 0;
	for (int i = 0; i < MAX_THREAD; i++)
		total_sum += sum[i];

	//cout « "sum is " « total_sum « endl;
	 printf("product is %d\n",total_sum);

	return 0;
}
