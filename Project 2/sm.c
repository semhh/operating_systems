#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<wait.h>
#include<sys/time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<sys/shm.h>


int throws[3];
int score1=0, score2=0, score3=0;
int turn = 0;


int rockCount=0;
int paperCount=0; 
int scissorsCount=0;

int p1=0;
int p2=1;
int p3=2;

void* select_num(void *threadid){

   int pid;
   pid = *(int *)threadid;
   
   struct timeval tv;
   gettimeofday(&tv, NULL);
   srand(tv.tv_sec + tv.tv_usec + getpid());
   
  
   throws[pid] = rand() % 3;
}


char * convertString(int value)
{
  
   if(value==0){
        rockCount++;
    	return "Rock";
   }
   
   else if(value==1){
   	paperCount++;
   	return "Paper";
   	
   }
   
   else if(value==2){
   	scissorsCount++;
   	return "Scissors";
   
   }

	return NULL;

}

void compare(){


while(score1!=5 && score2!=5 && score3!=5){

select_num(&p1);
select_num(&p2);
select_num(&p3);

printf("--\n");
printf("--\n");

printf("%d. Turn, 1.Thread: %s, 2.Thread: %s, 3.Thread: %s\n", turn+1, convertString(throws[p1]), convertString(throws[p2]), convertString(throws[p3]));
	
if((throws[p1]==0 && throws[p2]==2 && throws[p3]==2) || (throws[p1]==1 && throws[p2]==0 && throws[p3]==0) || (throws[p1]==2 && throws[p2]==1 && throws[p3]==1))
{
  printf("\n1. Thread Wins, ");
  score1++;
  
}

else if((throws[p1]==2 && throws[p2]==0 && throws[p3]==2) || (throws[p1]==0 && throws[p2]==1 && throws[p3]==0) || (throws[p1]==1 && throws[p2]==2 && throws[p3]==1))
{
  printf("\n2. Thread Wins, ");
  score2++;
}	
	
else if((throws[p1]==2 && throws[p2]==2 && throws[p3]==0) || (throws[p1]==0 && throws[p2]==0 && throws[p3]==1) || (throws[p1]==1 && throws[p2]==1 && throws[p3]==2))
{
  printf("\n3. Thread Wins, ");
  score3++;
}

else{
  printf("\nDraw, ");

}


turn++;
printf("Score1: %d -- Score2: %d -- Score3: %d\n", score1, score2, score3);


}

if(score1==5){

	printf("--\n--\n");
	printf("1. Thread has won the game with score: Score1: %d -- Score2: %d -- Score3: %d in %d Turns.\n", score1, score2, score3, turn);
	printf("--\n--\n");
}

else if(score2==5){

	printf("--\n--\n");
	printf("2. Thread has won the game with score: Score1: %d -- Score2: %d -- Score3: %d in %d Turns.\n", score1, score2, score3, turn);
	printf("--\n--\n");
}

else if(score3==5){

	printf("--\n--\n");
	printf("3. Thread has won the game with score: Score1: %d -- Score2: %d -- Score3: %d in %d Turns.\n", score1, score2, score3, turn);
	printf("--\n--\n");
}

	printf("how many times items were selected: SCISSORS: %d, PAPER: %d, ROCK: %d\n", scissorsCount, paperCount, rockCount);
	printf("--\n--\n");
	

	

}

int main(){

pthread_t thread1;
pthread_t thread2;
pthread_t thread3;


int i;

printf("The game has launched\n");

if(pthread_create(&thread1, NULL, &select_num, &p1)!=0){

	printf("\n1. Thread cannot be created!\n");
	return -1;
}


if(pthread_create(&thread2, NULL, &select_num, &p2)!=0){

	printf("2. Thread cannot be created!\n");
	return -1;
}

if(pthread_create(&thread3, NULL, &select_num, &p3)!=0){

	printf("3. Thread cannot be created!\n");
	return -1;
}
   
printf("3 threads will be created\n");


printf("The game starts\n");

compare();


printf("1.Thread terminated\n");
printf("2.Thread terminated\n");
printf("3.Thread terminated\n");

if(pthread_join(thread1, NULL)!=0){

	return -1;
}


if(pthread_join(thread2, NULL)!=0){

	return -1;
}

if(pthread_join(thread3, NULL)!=0){

	return -1;
}

printf("Threads are joined by main process\n");
printf("Game finished\n");



return 0;
}
