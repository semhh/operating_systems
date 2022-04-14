#include<stdio.h>
#include<stdlib.h>

int blockSize = 4 , numHole=0;
int hole[10][2];
int i , j , count=1 , sizeOfMemory , allocStrategy , p_id , p_size;
char operation;

void boslukbul(int arr[],int arsize)
{
	int i,j;
	int sayac=0,a=0,sifir=0,basla,son=0;
	
	for( i=son;i<arsize;i++)
	{
		if(arr[i]==0)
		{	
			sayac=0;
	 		if(arr[i-1]!=0)
			{	 		
		 		sayac++;
		 		basla=i;
		      	for( j=basla;j<arsize;j++)
				{
		      		if(arr[j+1]!=0)
					{
		            	son=j; 
		                break;
				    }
		         	else if(arr[j+1]==0)
		           		sayac++;
		        }
		    	hole[a][0]=basla;
	 	        hole[a][1]=sayac;
		        a++;   
		    }
	 	}	
	}
	numHole=a;
}
void first_fit(int memory[],FILE *inp)
{
	int tmp,temp,cursor=0,remain=sizeOfMemory;
	int counter_ext_frag=0,counter_ins_mem=0,counter_int_frag=0;
	while(fscanf(inp,"%c %d %d\n",&operation,&p_id,&p_size)!=EOF)
	{
		int controller=0,flag_fill=1,flag_delete=1;
		if(operation=='B')
		{
			tmp=p_size;
			p_size=(p_size+3)/4;
			//printf("p size is %d\n",p_size);
			if(remain<p_size)  // if the process size grater than remain error message printed
			{
				printf("%c %d %d -> ERROR! Insufficient memory\n",operation,p_id,tmp);
				counter_ins_mem++;
			}
			deneme:
			flag_fill=1;
			for(i=cursor;i<cursor+p_size;i++) //checking the next indexes are empty or not
			{
				if(memory[i]!=0)
					flag_fill=0;
			}
			if(flag_fill==1)  // fill the indexes with process id
			{
				for(i=cursor;i<cursor+p_size;i++)
				{
					memory[i]=p_id;	
				}
				cursor=cursor+p_size; //increment the cursor by process size
				remain=remain-p_size; // decrement the remain by process size
				printf("%c %d %d -> %d frames will be used, remaining #frame: %d\n",operation,p_id,tmp,p_size,remain);
				if(tmp%4!=0)
					counter_int_frag = counter_int_frag + blockSize - (tmp%4); // calculating the internal fragmentation
			}
			if(flag_fill==0)  // try to fing appropriate hole for process
			{
				for(i=0;i<=numHole;i++)
				{
					if(p_size<=hole[i][1])  // if this holes appropriate for process cursor goes here and fill after goto
					{
						cursor=hole[i][0];
						goto deneme;  // go to the deneme label
					}	
					if(hole[i][1]==0 && remain>p_size) // if there is no appropriate hole printed the external fragmentation message
					{
						printf("%c %d %d -> %d frames will be used, ERROR! External fragmentation\n",operation,p_id,tmp,p_size);
						counter_ext_frag++;
						break;	
					}	
				}
			}
		}
		if(operation=='E')  // deletion operation
		{
			for(i=0;i<sizeOfMemory;i++)
			{
				if(memory[i]==p_id && controller==0)
				{
					cursor=i; // setting the cursor to the first index of the process
					controller=1; // to aviod entering the if block more than one time
					flag_delete=0;
				}
				if(memory[i]==p_id)
				{
					memory[i]=0; // making the indexes 0 to delete process
					remain++; // incremeneting the remains 
				}	
			}
			if(flag_delete==0)
				printf("%c %d     -> %d frames are dealllocated, available  #frame: %d\n",operation,p_id,p_size,remain);
		}
		boslukbul(memory,sizeOfMemory);
	}
	printf("\nTotal free memory in holes: %d frames, %d KB\n",remain,remain*blockSize);
	printf("Total memory wasted on internal fragmentation: %d KB\n",counter_int_frag);
	printf("Total number of rejected process due to external fragmentation is: %d\n",counter_ext_frag);
	printf("Total number of rejected process due to insufficient memory is: %d\n",counter_ins_mem);
	printf("\nHoles:\n");
	for(i=0;i<numHole;i++)
	{		 
		printf("%d 	%d\n",hole[i][0],hole[i][1]);   
	}
	
	printf("the indexes of memory array is\n");
	for(i=0;i<sizeOfMemory;i++)
	{
		printf("%d",memory[i]);
	}
	printf("\n");
}
void best_fit(int memory[], FILE *inp)
{
	int tmp,temp,cursor=0,remain=sizeOfMemory;
    int counter_ext_frag=0,counter_ins_mem=0,counter_int_frag=0;
    int cursorArray[10][2];
    int c_c=0;
    while(fscanf(inp,"%c %d %d\n",&operation,&p_id,&p_size)!=EOF)
    {
        //cursor buldurma
        c_c=0;
        for(i=0;i<10;i++)
        {
            cursorArray[i][0]=-1;
            cursorArray[i][1]=-1;
        }
        int controller=0,flag_fill=1,flag_delete=1;
        int min,c=0;
        tmp=p_size;
        int check = (p_size+3)/4;
        boslukbul(memory,sizeOfMemory);
        for(i=0;i<=numHole;i++)
        {
            if(hole[i][1]>=check)
            {
                cursorArray[c_c][0]=hole[i][0];
                cursorArray[c_c][1]=hole[i][1];
                c_c++;
            }
        }
        min=cursorArray[0][1];
        if(c_c==0)
        {
            flag_fill=0;
        }
        for(j=0;j<=c_c;j++)
        {
            if(min>cursorArray[j][1] && 0<cursorArray[j][1])
            {
                min=cursorArray[j][1];
                c=j;
            }
        }
        cursor=cursorArray[c][0];
        if(operation=='E')  // deletion operation
        {
            int p_counter=0;
            for(i=0;i<sizeOfMemory;i++)
            {
                if(memory[i]==p_id)
                {
                    memory[i]=0; // making the indexes 0 to delete process
                    remain++;
                    p_counter++;
                }
            }
            printf("%c %d     -> %d frames are dealllocated, available  #frame: %d\n",operation,p_id,p_counter,remain);
        }
        else
        {
        	tmp=p_size;
            p_size=(p_size+3)/4;
            if(remain<p_size)  // if the process size grater than remain error message printed
            {
                printf("%c %d %d -> ERROR! Insufficient memory\n",operation,p_id,tmp);
                counter_ins_mem++;
            }
            else
            {
                if(flag_fill==1)  // fill the indexes with process id
                {
                    for(i=cursor;i<cursor+p_size;i++)
                    {
                        memory[i]=p_id;
                    }
                    remain=remain-p_size; // decrement the remain by process size
                    printf("%c %d %d -> %d frames will be used, remaining #frame: %d\n",operation,p_id,tmp,p_size,remain);
                    if(tmp%4!=0)
                        counter_int_frag = counter_int_frag + blockSize - (tmp%4); // calculating the internal fragmentation
                }
                if(flag_fill==0)  // try to fing appropriate hole for process
                {
                    boslukbul(memory,sizeOfMemory);
                    for(i=0;i<=numHole;i++)
                    {
                        if(hole[i][1]==0 && remain>p_size) // if there is no appropriate hole printed the external fragmentation message
                        {
                            printf("%c %d %d -> %d frames will be used, ERROR! External fragmentation\n",operation,p_id,tmp,p_size);
                            counter_ext_frag++;
                            break;
                        }
                    }
                }
            }
        }
    }
    boslukbul(memory,sizeOfMemory);
    printf("\nTotal free memory in holes: %d frames, %d KB\n",remain,remain*blockSize);
	printf("Total memory wasted on internal fragmentation: %d KB\n",counter_int_frag);
	printf("Total number of rejected process due to external fragmentation is: %d\n",counter_ext_frag);
	printf("Total number of rejected process due to insufficient memory is: %d\n",counter_ins_mem);
	printf("\nHoles:\n");
	for(i=0;i<numHole;i++)
	{		 
		printf("%d 	%d\n",hole[i][0],hole[i][1]);   
	}
	
	printf("the indexes of memory array is\n");
	for(i=0;i<sizeOfMemory;i++)
	{
		printf("%d",memory[i]);
	}
	printf("\n");
}
void worst_fit(int memory[], FILE *inp)
{
	int tmp,temp,cursor=0,remain=sizeOfMemory;
    int counter_ext_frag=0,counter_ins_mem=0,counter_int_frag=0;
    int cursorArray[10][2];
    int c_c=0;
    while(fscanf(inp,"%c %d %d\n",&operation,&p_id,&p_size)!=EOF)
    {
        //cursor buldurma
        c_c=0;
        for(i=0;i<10;i++)
        {
            cursorArray[i][0]=-1;
            cursorArray[i][1]=-1;
        }
        int controller=0,flag_fill=1,flag_delete=1;
        int max,c=0;
        tmp=p_size;
        int check = (p_size+3)/4;
        boslukbul(memory,sizeOfMemory);
        for(i=0;i<=numHole;i++)
        {
            if(hole[i][1]>=check)
            {
                cursorArray[c_c][0]=hole[i][0];
                cursorArray[c_c][1]=hole[i][1];
                c_c++;
            }
        }
        max=cursorArray[0][1];
        if(c_c==0)
        {
            flag_fill=0;
        }
        for(j=0;j<=c_c;j++)
        {
            if(max<cursorArray[j][1] && 0<cursorArray[j][1])
            {
                max=cursorArray[j][1];
                c=j;
            }
        }
        cursor=cursorArray[c][0];
        if(operation=='E')  // deletion operation
        {
            int p_counter=0;
            for(i=0;i<sizeOfMemory;i++)
            {
                if(memory[i]==p_id)
                {
                    memory[i]=0; // making the indexes 0 to delete process
                    remain++;
                    p_counter++;
                }
            }
            printf("%c %d     -> %d frames are dealllocated, available  #frame: %d\n",operation,p_id,p_counter,remain);
        }
        else
        {
        	tmp=p_size;
            p_size=(p_size+3)/4;
            if(remain<p_size)  // if the process size grater than remain error message printed
            {
                printf("%c %d %d -> ERROR! Insufficient memory\n",operation,p_id,tmp);
                counter_ins_mem++;
            }
            else
            {
                if(flag_fill==1)  // fill the indexes with process id
                {
                    for(i=cursor;i<cursor+p_size;i++)
                    {
                        memory[i]=p_id;
                    }
                    remain=remain-p_size; // decrement the remain by process size
                    printf("%c %d %d -> %d frames will be used, remaining #frame: %d\n",operation,p_id,tmp,p_size,remain);
                    if(tmp%4!=0)
                        counter_int_frag = counter_int_frag + blockSize - (tmp%4); // calculating the internal fragmentation
                }
                if(flag_fill==0)  // try to fing appropriate hole for process
                {
                    boslukbul(memory,sizeOfMemory);
                    for(i=0;i<=numHole;i++)
                    {
                        if(hole[i][1]==0 && remain>p_size) // if there is no appropriate hole printed the external fragmentation message
                        {
                            printf("%c %d %d -> %d frames will be used, ERROR! External fragmentation\n",operation,p_id,tmp,p_size);
                            counter_ext_frag++;
                            break;
                        }
                    }
                }
            }
        }
    }
    boslukbul(memory,sizeOfMemory);
    printf("\nTotal free memory in holes: %d frames, %d KB\n",remain,remain*blockSize);
	printf("Total memory wasted on internal fragmentation: %d KB\n",counter_int_frag);
	printf("Total number of rejected process due to external fragmentation is: %d\n",counter_ext_frag);
	printf("Total number of rejected process due to insufficient memory is: %d\n",counter_ins_mem);
	printf("\nHoles:\n");
	for(i=0;i<numHole;i++)
	{		 
		printf("%d 	%d\n",hole[i][0],hole[i][1]);   
	}
	
	printf("the indexes of memory array is\n");
	for(i=0;i<sizeOfMemory;i++)
	{
		printf("%d",memory[i]);
	}
	printf("\n");
}
int main(int argc, char *argv[])
{
	
	printf("program has launched\n");
	if(argv[1]==NULL || argv[2]==NULL || argv[3]==NULL)
	{
		printf("you made a missing or incorrect entry\n");
		return 0;		
	}
	FILE *inp=fopen(argv[2],"r");
	sizeOfMemory=atoi(argv[1]);
	allocStrategy=atoi(argv[3]);
	sizeOfMemory=sizeOfMemory/blockSize;
	
	/*FILE *inp=fopen("file.txt","r");
	int sizeOfMemory=1024;
	int allocStrategy=1;
	sizeOfMemory=sizeOfMemory/blockSize;*/
	
	int memory[sizeOfMemory];
	for(i=0;i<sizeOfMemory;i++)
	{
		memory[i]=0;
	}	
	
	switch(allocStrategy)
	{
		case 1:
			first_fit(memory,inp);
			break;
		case 2:
			best_fit(memory,inp);
			break;
		case 3:
			worst_fit(memory,inp);
			break;
		default:
			printf("incorrect chose try again\n");
			break;
	}
}
