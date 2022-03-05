//Aleyna Elif ÖZKAN 1801042652 HW-11

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Node{
	long int data;
	struct Node *next;
}nums; //for part1

typedef struct structForLinked{
	int data;
	struct structForLinked *next;
}forLinked;//for part2 linked list

typedef struct structNotSame{
	int n1;
	int n2;
}notSame;//for part2



//part1 functions
long int *read_array(char *filename,long int *dataNumberArr);
nums *read_linkedlist (char *filename,long int * dataNumLinked);
void  charArrNULL(char *Arr,int n);
float * stats_array(long int *arr, long int *datanum);
float * stats_linkedlist(nums *head, long int *datanum);
float power(float base,int exponent);
float returnReadTime(char *filename,long int *dataNumberArr,long int *arr,long int *dataNumLinked,nums *head,float *arrReadTime,float *linkedReadTime);
float returnStatsTime(long int *dataNumberArr,long int *arr,long int *dataNumLinked,nums *head,float *arrStatTime,float *linkedStatTime);
//part2 function
notSame * part2(int *numOfNotSame);



int main(){
char filename[20]="list.txt";
long int *dataNumberArr,b=0,*Arr,sizeArr=0,i=0;
float *resArr, *arrReadTime, *linkedReadTime,c=0.0,d=0.0,*arrStatTime,*linkedStatTime, e=0.0,f=0.0;
long int * dataNumLinked,a=0,sizeLinked=0;
float *resLinked;

dataNumLinked=&a;
dataNumberArr=&b;
arrReadTime=&c;
linkedReadTime=&d;
//assignin initial value as 0

	Arr=read_array(filename,dataNumberArr);		//returning array in main

	nums *head=(nums*)malloc(sizeof(nums));
	head=read_linkedlist(filename,dataNumLinked);	// returning linked list in main 

//calculates time for the read functions
returnReadTime(filename, dataNumberArr,Arr,dataNumLinked,head,arrReadTime,linkedReadTime);

printf("\n******************************* PART-1 *******************************\n");
printf("\nTime for function read_array: %f seconds.\n",*arrReadTime);
printf("Time for function read_linkedlist: %f seconds.\n\n",*linkedReadTime);
printf("-----------------------------------------------------------------------\n\n");

		sizeArr=4*(*dataNumberArr);
//calculates size of array		
	printf("Size of function read_array: %ld bytes.\n",sizeArr );

		sizeLinked=(4+4)*(*dataNumLinked+1);
//calculates size of linked list
	printf("Size of function read_linkedlist: %ld bytes.\n\n",sizeLinked);

printf("-----------------------------------------------------------------------\n\n");
	resArr=stats_array(Arr,dataNumberArr);	//returning float array for array
	resLinked=stats_linkedlist(head,dataNumLinked);		//returning float array for linked list

arrStatTime=&e;
linkedStatTime=&f;
//initalize the values with 0

returnStatsTime(dataNumberArr,Arr,dataNumLinked,head,arrStatTime,linkedStatTime);
//calculates the  stat funcitons time
printf("Time for function stats_array: %f seconds.\n",*arrStatTime);
printf("Time for function stats_linkedlist: %f seconds.\n\n",*linkedStatTime);
printf("-----------------------------------------------------------------------\n\n");
printf("All of the values above are bigger for linked list funcitons.\n\n");
printf("-----------------------------------------------------------------------\n\n");

printf("\t\t Min\t\tMax\t\tMean\t Std Deviation \n");
printf("array\t--> \t%.2f \t  %.2f \t  %.2f \t  %.2f \t \n",resArr[0],resArr[1],resArr[2],resArr[3] );
printf("linked list --> %.2f \t  %.2f \t  %.2f \t  %.2f \t \n\n",resLinked[0],resLinked[1],resLinked[2],resLinked[3] );

//part2
printf("\n\n******************************* PART-2 *******************************\n\n");
int *numOfNotSame,h=0;
numOfNotSame=&h;


notSame * X=(notSame*)malloc(sizeof(notSame));

	X=part2(numOfNotSame);		//returning struct array  in main

	if(*numOfNotSame==0)
		printf("All of the values are the same.\n");

	
	for(i=0;i<*numOfNotSame;i++){	//printing the numbers that are not same
		printf("%d & ",X[i].n1);
		printf("%d are not the same.\n",X[i].n2);
	}

	free(head);
	free(X);

		return 0;
}



long int *read_array(char *filename,long int *dataNumberArr){
FILE *fp;
char temp[20],c,*helper;
int size=200,flag=0;
long int j=0,i=0 ,k=0,*arr,datanumArr=0;

charArrNULL(temp,20);	//creating a  fix sized char array for reading numbers from file and assigining NULL

	fp = fopen (filename, "r");

	if (fp == NULL) {
	     printf("Error!");
	     exit(1);
	}
	
arr=(long int *) malloc(size*sizeof(long int));	//creating an array with size=200,it will get bigger later

while(!feof(fp)){
	if(datanumArr%size==0 && datanumArr!=0 && flag==0){
		size+=200;
		arr=(long int*)realloc(arr,sizeof(arr)*size);	//for every 200 number, array gets bigger
		flag=1;
	}
	else{
		while((c=fgetc(fp))!=',' && c!=EOF){
			temp[i]=c;			//reading file to char array
			i++;
		}
		if(c==','){
			j= strtol (temp,&helper,10);		//converting it into long int 
			arr[k]=j;							//and taking the value in dynamic array
		    k++;
			charArrNULL(temp,20);				//assignin null to char array again
			i=0;
			datanumArr++;						//increasing the data number
			flag=0;
		}
	}
}

*dataNumberArr=datanumArr;			//returning data number to the main with the help of pointer

  	fclose(fp);
  	return arr;						//returning dynamic array

}



nums *read_linkedlist (char *filename,long int * dataNumLinked){
FILE *fp;
char c;
char temp[20],*helper;
long int j=0,datanum=0,i=0;

nums *head=(nums*)malloc(sizeof(nums));			//same things for the linked list
nums *current=(nums*)malloc(sizeof(nums));		//I'm creating a head node, but I'm making calculations on current node
												//for not losing the head of the linked list
	charArrNULL(temp,20);
	fp=fopen(filename,"r");
	if(fp==NULL){
		printf("Error!!\n");
		exit(1);
	}


	while((c=fgetc(fp))!=','){
			temp[i]=c;
			i++;
	}

	j= strtol (temp,&helper,10);
	charArrNULL(temp,20);
	i=0;
	head->data=j;			//assigning the first value as head
	head->next=NULL;
	current=head;			//current is  same with head for the beggining 

	while((c=fgetc(fp))!=EOF){
		if(c!=','){
			temp[i]=c;
			i++;
		}
		else{
			j= strtol (temp,&helper,10);
			nums *new=(nums*)malloc(sizeof(nums));		//then creating a new node and adding it to currents next 
		    new->data = j;
		    new->next = NULL;
		    current->next=new;							//so new becomes current
		    current=new;
			charArrNULL(temp,20);
			i=0;
			datanum++;
		}

	}
	*dataNumLinked=datanum;
	fclose(fp);

	return head; 
}

void  charArrNULL(char *Arr,int n){
//helper for temp char array
	for(int i=0;i<n;i++)
		Arr[i]='\0';
}

float * stats_array(long int *arr, long int *datanum){
long int max=0,min=0,i=0;
float sum=0.0,mean=0.0,sd=0.0;


float *result=(float*)malloc(4*sizeof(float));		//creating a float array 

max=arr[0];		//set first value as max and min values
min=arr[0];

    while (i!=*datanum) { 
        if (arr[i]> max) 	//if there is  bigger num, it becomes max
            max=arr[i]; 
        if(arr[i]< min)		//if there is smaller num,it becomes min
        	min=arr[i];
        sum+=arr[i];		//summing all of the data
        i++;
    }
    
	mean=sum/((float)*datanum);		//calculate mean
	i=0;

    while (i!=*datanum) { 
        sd += power((arr[i]) - mean, 2);		//calculate standard deviation
        i++;
    }
        
    sd= sqrt(sd / *datanum);

    result[0]=min;
    result[1]=max;
    result[2]=mean;
    result[3]=sd;

		return result;		//returning the float array in main

}


float * stats_linkedlist(nums *head, long int *datanum){
long int max=0,min=0,i=0;
float sum=0.0,mean=0.0,sd=0.0;

//same things for linked list
float *result=(float*)malloc(4*sizeof(float));

max=head->data;
min=head->data;

nums *current = head;  // Initialize current 
    while (current != NULL) { 
        if (current->data> max) 
            max=current->data; 
        if(current->data< min)
        	min=current->data;
        sum+=current->data;
        current = current->next; 
    }
    
	mean=sum/((float)*datanum+1);


nums *current1 = head;  // Initialize current 
    while (current1 != NULL) { 
        sd += power((current1->data) - mean, 2);
        current1 = current1->next; 
    }
        
    sd= sqrt(sd / (*datanum+1));

    result[0]=min;
    result[1]=max;
    result[2]=mean;
    result[3]=sd;

		return result;

}


float power(float base,int exponent){
//helper funciton 
float result=1;
	for (exponent; exponent>0; exponent--){
		result = result * base;
	}
		return result;
}

float returnReadTime(char *filename,long int *dataNumberArr,long int *arr,long int *dataNumLinked,nums *head,float *arrReadTime,float *linkedReadTime){
float resA=0.0;
clock_t s1A,s2A,s3A,s4A,e1A,e2A,e3A,e4A;
float resL=0.0;
clock_t s1L,s2L,s3L,s4L,e1L,e2L,e3L,e4L;

//calling all of the funcitons 4 times and calculating the average of them
//returning the values to the main by using pointers

	s1A=clock();
	read_array(filename,dataNumberArr);
	e1A=clock();

	s1L=clock();
	read_linkedlist(filename,dataNumLinked);
	e1L=clock();

	s2L=clock();
	read_linkedlist(filename,dataNumLinked);
	e2L=clock();

	s2A=clock();
	read_array(filename,dataNumberArr);
	e2A=clock();

	s3A=clock();
	read_array(filename,dataNumberArr);
	e3A=clock();

	s3L=clock();
	read_linkedlist(filename,dataNumLinked);
	e3L=clock();

	s4A=clock();
	read_array(filename,dataNumberArr);
	e4A=clock();

	s4L=clock();
	read_linkedlist(filename,dataNumLinked);
	e4L=clock();


	resL=((e1L-s1L)+(e2L-s2L)+(e3L-s3L)+(e4L-s4L))/(4.0);
	resL=resL/CLOCKS_PER_SEC;

	resA=((e1A-s1A)+(e2A-s2A)+(e3A-s3A)+(e4A-s4A))/(4.0);
	resA=resA/CLOCKS_PER_SEC;

	*linkedReadTime=resL;
	*arrReadTime=resA;

}


float returnStatsTime(long int *dataNumberArr,long int *arr,long int *dataNumLinked,nums *head,float *arrStatTime,float *linkedStatTime){
float resA=0.0;
clock_t s1A,s2A,s3A,s4A,e1A,e2A,e3A,e4A;
float resL=0.0;
clock_t s1L,s2L,s3L,s4L,e1L,e2L,e3L,e4L;

//calling all of the funcitons 4 times and calculating the average of them
//returning the values to the main by using pointers


	s1A=clock();
	stats_array(arr,dataNumberArr);
	e1A=clock();

	s1L=clock();
	stats_linkedlist(head,dataNumLinked);
	e1L=clock();

	s2L=clock();
	stats_linkedlist(head,dataNumLinked);
	e2L=clock();

	s2A=clock();
	stats_array(arr,dataNumberArr);
	e2A=clock();

	s3A=clock();
	stats_array(arr,dataNumberArr);
	e3A=clock();

	s3L=clock();
	stats_linkedlist(head,dataNumLinked);
	e3L=clock();

	s4A=clock();
	stats_array(arr,dataNumberArr);
	e4A=clock();

	s4L=clock();
	stats_linkedlist(head,dataNumLinked);
	e4L=clock();


	resL=((e1L-s1L)+(e2L-s2L)+(e3L-s3L)+(e4L-s4L))/(4.0);
	resL=resL/CLOCKS_PER_SEC;

	resA=((e1A-s1A)+(e2A-s2A)+(e3A-s3A)+(e4A-s4A))/(4.0);
	resA=resA/CLOCKS_PER_SEC;

	*linkedStatTime=resL;
	*arrStatTime=resA;
}


notSame * part2(int *numOfNotSame){
int count=0,i=0,j=0;
int *dynamic,numberOfNotSame=0,flag=0;

//taking input from user

	printf("Please enter how many numbers that you want to enter:");
	scanf("%d",&count);

	printf("\nEnter %d numbers for dynamic array:\n",count);

	dynamic=(int *)malloc(sizeof(int )*count);	//creating a dynamic array

	for(i=0;i<count;i++){
		scanf("%d",&dynamic[i]);
	}

	printf("Enter %d numbers for linked list:\n",count);

forLinked *Head=(forLinked*)malloc(sizeof(forLinked));
forLinked *Current=(forLinked*)malloc(sizeof(forLinked));

//taking the first as head

	scanf("%d",&(Head->data));
	Head->next=NULL;
	Current=Head;
//creating new array for other values using realloc
	for(i=1;i<count;i++){
		forLinked *New=(forLinked*)malloc(sizeof(forLinked));
		    scanf("%d",&(New->data));
		    New->next = NULL;
		    Current->next=New;
		    Current=New;
	}

	Current=Head;
	i=0;

	notSame * X=(notSame*)malloc(sizeof(notSame));	//creating a dynamic struct array

while(i<count){

	if(flag==0 && Current->data!=dynamic[i]){	//if values are not same,then taking values in array which is created with malloc
		X[j].n1=dynamic[i];						//for the first value only
		X[j].n2=Current->data;
		numberOfNotSame++;
		flag=1;
		Current=Current->next;
		i++;
		j++;
	}

	else if(flag==1 && Current->data!=dynamic[i]){
		X=(notSame*)realloc(X,sizeof(notSame)*(numberOfNotSame+1));
		X[j].n1=dynamic[i];			//for other values,array  gets bigger
		X[j].n2=Current->data;
		numberOfNotSame++;
		Current=Current->next;
		i++;
		j++;
	}

	else if(Current->data==dynamic[i]){
		Current=Current->next;
		i++;
	}
		
}

*numOfNotSame=numberOfNotSame; 


return X;		//returning struct array
}
