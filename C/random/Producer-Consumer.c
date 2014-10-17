/*
    Q4a: Write a multithreaded program, with two producer threads and
    a single consumer threads. The producers should add to a shared
    queue, and the consumer should dequeue it. Use a mutex lock to
    avoid race conditions.

    Author : Arun K
*/

#include <stdio.h>
#include <pthread.h>

#define MAX_PRODUCERS 2
#define MAX_CONSUMERS 1

//Enter 1 more than required, because effective size is BUFFER_SIZE-1
//The reason behind wasting one entry is find when buffer is full or empty
#define BUFFER_SIZE 26

//If buffer count decreases to this value, then start producing again
#define PRODUCE_THRESHOLD (BUFFER_SIZE-1)/2
//If buffer count increases to this value, then start consuming again
#define CONSUME_THRESHOLD (BUFFER_SIZE-1)/3

typedef struct{
	int data;
	int *producer_id;
}DATA_STRUCT;

DATA_STRUCT buffer[BUFFER_SIZE];
pthread_mutex_t mutex_buffer=PTHREAD_MUTEX_INITIALIZER;
//Statically initializing the condition variables
//The conditions is the signal to start producing / consuming again.
pthread_cond_t resume_production=PTHREAD_COND_INITIALIZER, resume_consumption=PTHREAD_COND_INITIALIZER;

//This is the next index in the buffer where the producer can put data
int current_producer_index;
//This is the index in the buffer from where the consumer can retrieve the data
int current_consumer_index;

//This is a multiple read, single write variable
//If this is true, then all producers and consumers exit.
char is_exit;

#define BUFFER_COUNT ((current_producer_index>=current_consumer_index)? (current_producer_index-current_consumer_index) : (BUFFER_SIZE-current_consumer_index+current_producer_index))
/*
 * Buffer Empty =>> consumer_index == producer_index
 * Buffer Full ==>> (producer_index+1)%Buffer_size = consumer_index
 */

void* producer_run(void *data){

	int *id = ((int *)data);

	//produce for ever, until interrupted by user
	while(!is_exit) {
		//first get a lock on the mutex
		pthread_mutex_lock (&mutex_buffer);
		//buffer already full
		if ((current_producer_index+1)%BUFFER_SIZE == current_consumer_index){
			printf("########## BUFFER FULL ###################\n");
			//wait on the condition, this wont busy wait, instead suspends the thread
			pthread_cond_wait(&resume_production,&mutex_buffer);
		}
		//Add to the buffer
		buffer[current_producer_index].producer_id=id;
		buffer[current_producer_index].data=current_producer_index;
		current_producer_index=(current_producer_index+1)%BUFFER_SIZE;

		//signal resuming consumption, if threshold is reached.
		if(BUFFER_COUNT == CONSUME_THRESHOLD)
			pthread_cond_signal (&resume_consumption);
		//Release the lock so, that the waiting thread can proceed
		pthread_mutex_unlock(&mutex_buffer);
		// Here we call sleep to explicitly yield the CPU, but not necessary to do so
		usleep(rand()%10000);
	}
	pthread_exit(NULL);
	return NULL;

}

void* consumer_run(void *data){

	int *id = ((int *)data);
	int consumed, *producer_id;
	//produce for ever, until interrupted by user
	while(!is_exit) {
		//first get a lock on the mutex
		pthread_mutex_lock (&mutex_buffer);
		//buffer is empty
		if (current_producer_index == current_consumer_index){
			printf("******** BUFFER EMPTY ************* \n");
			//wait on the condition, this wont busy wait, instead suspends the thread
			pthread_cond_wait(&resume_consumption,&mutex_buffer);
		}
		//Here instead of just printing the value, we do some dummy calculations
		consumed = buffer[current_consumer_index].data;
		consumed+=1;	consumed-=1;
		consumed *= 3; consumed /=3;
		producer_id = buffer[current_consumer_index].producer_id;
		current_consumer_index = (current_consumer_index + 1)%BUFFER_SIZE;

		//signal resuming consumption, if threshold is reached.
		if(BUFFER_COUNT == PRODUCE_THRESHOLD)
			pthread_cond_signal (&resume_production);
		//Release the lock so, that the waiting thread can proceed
		pthread_mutex_unlock(&mutex_buffer);

		//Print the consumed value, after releasing the lock, it is not in the critical section
		printf("Consumer%d: Got data = %d added by Producer%d\n",id,consumed,producer_id);

		// Here we can call sleep to explicitly yield the CPU, not necessary though
		usleep(rand()%10000);
	}
	pthread_exit(NULL);
	return NULL;

}
//This is run in a separate thread, and it waits for a key press
//Once a key is pressed, all producer and consumer threads are exited.
void* exit_all_threads(void *args){

	char ch;
	int i;

	//First clear the stdin buffer
	fflush(stdin);

	while((ch = getchar())!='\n');
	printf("Caught user input, EXITING...\n\n");
	is_exit= 1;
	//try to get the lock and signal all the threads to proceed
	pthread_mutex_lock (&mutex_buffer);
	//send broadcast signal
	pthread_cond_broadcast(&resume_production);
	pthread_cond_broadcast(&resume_consumption);
	pthread_mutex_unlock(&mutex_buffer);
	pthread_exit(NULL);
	return NULL;
}

int main(){

	int i=0;
	char ch;

	//Array of Producer and Consumer threads
	pthread_t producer_thread[MAX_PRODUCERS], consumer_thread[MAX_CONSUMERS];
	//thread to exit on key press
    pthread_t wait_for_key_press;

    //Attribute to set it joinable
    pthread_attr_t pthread_attribute;

    //Initialize the global variables
    current_producer_index = 0;
    current_consumer_index = 0;
    is_exit = 0;

    pthread_attr_init(&pthread_attribute);
    pthread_attr_setdetachstate(&pthread_attribute, PTHREAD_CREATE_JOINABLE);

    printf("\nThis will create %d Producer threads and %d Consumer threads.\n\n",MAX_PRODUCERS,MAX_CONSUMERS);
    printf("To exit press ENTER once the program starts.\n");
    printf("Press ENTER to start...");
    while((ch = getchar())!='\n');
    printf("\n");
    //Create the threads
    for (i = 0; i < MAX_PRODUCERS; ++i) {
    	pthread_create(&producer_thread[i], &pthread_attribute, producer_run, (void *)i);
	}
    for (i = 0; i < MAX_CONSUMERS; ++i) {
    	pthread_create(&consumer_thread[i], &pthread_attribute, consumer_run, (void *)i);
	}
   //Create the thread which will wait for a key press
    pthread_create(&wait_for_key_press,&pthread_attribute,exit_all_threads,NULL);

    pthread_attr_destroy(&pthread_attribute);

    //Wait for tht threads to finish
    for (i = 0; i < MAX_PRODUCERS; ++i) {
    	pthread_join(producer_thread[i], NULL);
	}
    for (i = 0; i < MAX_CONSUMERS; ++i) {
    	pthread_join(consumer_thread[i], NULL);
	}

    //Cleanup
    pthread_cond_destroy(&resume_production);
    pthread_cond_destroy(&resume_consumption);
    pthread_mutex_destroy(&mutex_buffer);
    pthread_exit(NULL);

    return 0;
}
