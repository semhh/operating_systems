
 #include <stdio.h>  
 #include <stdlib.h>  
 #include <unistd.h> 
 #include<sys/types.h>
#include<wait.h>
#include <time.h>
#include<sys/time.h>
#include<string.h>
int randomInt(int min,int max){
   
   return min+(rand()% (max-min+1));
}

void seedit(void){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    srand(tv.tv_sec * tv.tv_usec);
    }
int main(void) {
int child_score=0;
   int turn=1;
   int parent_score=0;
   char ch_item[25];
   int n;
   int size;
   pid_t id;
   int number;
   char child_item[25];
   char parent_item[25];
   int fd[2];
   int status=pipe(fd);
   if(status==-1){
      printf("Error");
   }
    id=fork();
   if(id==0){
     printf("The game has launched \n");
     printf("Child process has created\n");
     printf("The game starts\n-------\n");
     seedit();
     number= randomInt(1,3);
     if(number==1){
      strncpy(child_item,"ROCK",25);
   }
   else if(number==2){
     strncpy(child_item,"PAPER",25);
      
   }
   else{
     strncpy(child_item,"SCISSORS",25);
     
     }
     
     close(fd[0]);
     size=strlen(child_item)+1;
     write(fd[1],&size,sizeof(int)); 
     write(fd[1],child_item,sizeof(char)*size);
     close(fd[1]);
    
     exit(0);
     
   }
  
   if(id>0){
     
     seedit();
     number= randomInt(1,3);  
     
     if(number==1){
     strncpy(parent_item,"ROCK",25);
     
   }
     else if(number==2){
     strncpy(parent_item,"PAPER",25);
     
   }
     else{
     strncpy(parent_item,"SCISSORS",25);
     }
    
     close(fd[1]);
     read(fd[0],&n,sizeof(int));
     read(fd[0],ch_item,sizeof(char)*n);
     close(fd[0]);
     
          while(child_score<5 && parent_score<5){
     if ((strcmp(parent_item,"ROCK")==0 && strcmp(ch_item,"SCISSORS")==0) || (strcmp(parent_item,"PAPER")==0 && strcmp(ch_item,"ROCK")==0) || (strcmp(parent_item,"SCISSORS")==0 && strcmp(ch_item,"PAPER")==0)){
     printf("Turn %d, Parent: %s  Child: %s\n",turn,parent_item,ch_item);
           parent_score++;
           printf("Parent win! Score %d-%d\n----\n",parent_score,child_score);
           turn++;
     }
     else if ((strcmp(ch_item,"ROCK")==0 && strcmp(parent_item,"SCISSORS")==0) || (strcmp(ch_item,"PAPER")==0 && strcmp(parent_item,"ROCK")==0) || (strcmp(ch_item,"SCISSORS")==0 && strcmp(parent_item,"PAPER")==0)){
           printf("Turn, %d Parent: %s  Child: %s\n",turn,parent_item,ch_item);
           child_score++;
           printf("Child win! Score %d-%d \n----\n",child_score,parent_score);
           turn++;
     }
     else if(strcmp(parent_item,ch_item)==0){
           
           while(strcmp(parent_item,ch_item)==0){
                 printf("Turn %d , Parent: %s Child : %s \nDraw ! Score %d-%d\n-----\n",turn,parent_item,ch_item,parent_score,child_score);
                 turn++;
                 
    if(id==0){
     seedit();
     number= randomInt(1,3);
     if(number==1){
      strncpy(child_item,"ROCK",25);
   }
   else if(number==2){
     strncpy(child_item,"PAPER",25);
      
   }
   else{
     strncpy(child_item,"SCISSORS",25);
     
     }
     
  
     close(fd[0]);
     size=strlen(child_item)+1;
     write(fd[1],&size,sizeof(int)); 
     write(fd[1],child_item,sizeof(char)*size);
     close(fd[1]);
     exit(0);
     
     }
   
     if(id>0){
     seedit();
     number= randomInt(1,3);  
     
     if(number==1){
     strncpy(parent_item,"ROCK",25);
     
   }
     else if(number==2){
     strncpy(parent_item,"PAPER",25);
     
   }
     else{
     strncpy(parent_item,"SCISSORS",25);
     }
    
     close(fd[1]);
     read(fd[0],&n,sizeof(int));
     read(fd[0],ch_item,sizeof(char)*n);
     close(fd[0]);
   
     
       }  
          if(id<0){
     printf("Error");
       } 
                 
        if(strcmp(parent_item,ch_item)!=0){    
                  if ((strcmp(parent_item,"ROCK")==0 &&  strcmp(ch_item,"SCISSORS")==0) || (strcmp(parent_item,"PAPER")==0 && strcmp(ch_item,"ROCK")==0) || (strcmp(parent_item,"SCISSORS")==0 && strcmp(ch_item,"PAPER")==0)){
           printf("Turn: %d Parent: %s  Child %s\n",turn,parent_item,ch_item);
           parent_score++;
           printf("Parent: win! Score %d-%d\n-----\n",parent_score,child_score);
           turn++;
           }
                  else if ((strcmp(ch_item,"ROCK")==0 && strcmp(parent_item,"SCISSORS")==0) || (strcmp(ch_item,"PAPER")==0 && strcmp(parent_item,"ROCK")==0) || (strcmp(ch_item,"SCISSORS")==0 && strcmp(parent_item,"PAPER")==0)){
           printf("Turn: %d Parent: %s  Child %s\n",turn,parent_item,ch_item);
           child_score++;
           printf("Child win! Score %d-%d\n-----\n",child_score,parent_score);
           turn++;
          }
                 
                 }
                 
              }
            
     
         }    
         fd[2];
       status=pipe(fd);
  if(status==-1){
      printf("Error");
   }
   id=fork();
   if(id==0){
   seedit();
     number= randomInt(1,3);
     if(number==1){
      strncpy(child_item,"ROCK",25);
   }
   else if(number==2){
     strncpy(child_item,"PAPER",25);
      
   }
   else{
     strncpy(child_item,"SCISSORS",25);
     
     }
      close(fd[0]);
     size=strlen(child_item)+1;
     write(fd[1],&size,sizeof(int)); 
     write(fd[1],child_item,sizeof(char)*size);
     close(fd[1]);
     exit(0);
     }
    
     if(id>0){
     
     seedit();
     number= randomInt(1,3);  
     
     if(number==1){
     strncpy(parent_item,"ROCK",25);
     
   }
     else if(number==2){
     strncpy(parent_item,"PAPER",25);
     
   }
     else{
     strncpy(parent_item,"SCISSORS",25);
     }
    
     
     close(fd[1]);
     read(fd[0],&n,sizeof(int));
     read(fd[0],ch_item,sizeof(char)*n);
     close(fd[0]);
     }
        if(id<0){
     printf("Error");
       } 

         }
          
        }
           if(id<0){
     printf("Error");
       } 
        

          if(child_score==5 || parent_score==5){

                if(child_score==5){printf("Child has won the game with Score: %d-%d in %d turns.\n-------------\n",child_score,parent_score,turn-1);}
            
                else {
                printf("Parent has won the game with Score: %d-%d in %d turns.\n--------------\n",parent_score,child_score,turn-1);

         } 
       
         }
           if(id>0){
           printf("Child has terminated\n");
           printf("Parent waits child with wait()\n");
           wait(NULL);
           printf("Parent has terminated\n");
          }
    return(0); 
     
   } 
    


    
    

 






      
  
  

