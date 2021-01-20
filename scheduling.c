#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include "Queue.h"

int remaining = 15;

void function(){
	printf("Long Term Scheduler Started\n");
	printf("Short Term Scheduler Started\n");
	printf("================================================================================================================================================\n");
	printf("Long Term Scheduler : Remaining Processes = %d\n", remaining);
	printf("|------------|----------------|----------------------------------------------------------------------------|\n");
	printf("| Process_Id | Execution_Time |                                                                            |\n");
	printf("|------------|----------------|----------------------------------------------------------------------------|\n");

	
}


void function0(int size_r){
		printf("\nShort Term Scheduler : \n");
		printf("Ready Queue : size = %d \n", size_r);
		printf("|------------|----------------|----------------------------------------------------------------------------|\n");
		printf("| Process_Id | Time_Remaining |                                                                            |\n");
		printf("|------------|----------------|----------------------------------------------------------------------------|\n");


}


int total_execution_time = 0;
time_t time0 = 0;
Queue *processQueue, *readyQueue;
bool swich;	
pthread_t _longThread, _shortThread;
pthread_mutex_t lock;
pthread_cond_t check;


void *longScheduler(void *args)
{
	//Lond Term Scheduling Srarted
	function();
	while(sizeOf(processQueue) > 0 || sizeOf(readyQueue) > 0){
    	pthread_mutex_lock(&lock);
		if(!swich){
			//Long Term Scheduling Paused
			pthread_cond_wait(&check, &lock);
			//Long Term Scheduling Resumed
		}
  		swich = false;
		if(sizeOf(processQueue) > 0){  
			int size_r = sizeOf(readyQueue);
			while(sizeOf(processQueue) > 0 && sizeOf(readyQueue)  < 5){
				Task *process = dequeue(processQueue);
				enqueue(readyQueue,process);
				printf("|      %02d    |       %02d       |  Moved to the Ready Queue                                                  |\n", process->pid, process->time);	
				remaining -= 1;
			}
			int i=0;
			for(i=0; i < size_r; i++){
				printf("|            |                |                                                                            |\n");
			}	
		printf("|------------|----------------|----------------------------------------------------------------------------|\n");
		}
		pthread_cond_signal(&check);
		pthread_mutex_unlock(&lock);
	}
	printf("Long Term Scheduler Stopped\n");
 
	return NULL;
}

void * shortScheduler(void *args)
{
  	int ctr;
	  // Short Term Scheduler Started
	
	while(true){
		pthread_mutex_lock(&lock);
		
		if(swich == true){
			// Short Term Scheduler Paused
			pthread_cond_wait(&check, &lock);
			// Short Term Scheduler Resumed  
		}

		swich = true;
		
		int size_r = sizeOf(readyQueue);
		
		function0(size_r);
		 
		for(ctr = 0; ctr < size_r; ctr++){
					int i=0;
					Task *process = dequeue(readyQueue);
					process->time -= 2;
					total_execution_time += 2;
					if(process->time < 0)
						process->time = 0; 
					printf("|      %02d    |       %02d       |  ",process->pid , process->time );
					for(i=0;i<process->time;i++){
						printf("####");
					}
					if(process->time > 0){
						enqueue(readyQueue, process);
					}
					else{
						printf("-> TERMINATED");
					}
					printf("\n");
					time0 = time(NULL);			
		}
		printf("|------------|----------------|----------------------------------------------------------------------------|\n");
		printf("================================================================================================================================================\n");
		while(true)
			if(time(NULL)- time0 == 2)
				break;
		system("clear");
		
		function();

		pthread_cond_signal(&check); 
		pthread_mutex_unlock(&lock); 
   		if( sizeOf(readyQueue)==0){
			printf("================================================================================================================================================\n");
			printf("Total Execution time of All Processes is %d\n", total_execution_time);
			printf("Short Term Scheduler Stopped\n");
			break;
		}
	}	
	return NULL;
}

int main()
{
	processQueue = makeQueue();
	readyQueue = makeQueue();
	int ctr;
	swich=true;
	for(ctr=1; ctr<=15; ctr++){
		int time = rand()%20+1;
		Task *process = makeTask(ctr, time);
		enqueue(processQueue, process);
	}
	system("clear");
	pthread_mutex_init(&lock, NULL);  				
	pthread_cond_init(&check, NULL);				
  	pthread_mutex_lock(&lock);  				
	pthread_create(&_longThread, NULL, longScheduler, NULL); 		
	pthread_create(&_shortThread, NULL, shortScheduler, NULL); 	 	
	pthread_cond_signal(&check);  					
	pthread_mutex_unlock(&lock);  					
	pthread_join(_longThread, NULL);  					  
	pthread_join(_shortThread, NULL); 	 			  
	pthread_mutex_destroy(&lock);  					
	pthread_cond_destroy(&check);  

	printf("All Processes Exicuted Succesfuly\n");	
     
	return 0;
}
