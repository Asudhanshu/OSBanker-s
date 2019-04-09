#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
//Structure of processes to define their burst time,arrival time and process id ....
typedef struct Process{
	int Process_Id;
	int Initial_Burst;
	int Burst_Time;
	int Start_Time;
	int Finish_Time;
	bool Completed;
}Process;
//Making a Gantt chart of processes to tell their starting time and when they finish
typedef struct Gantt{
	int Process_Id;
	int Start_Time;
	int Finish_Time;
}Gantt;
//Initializing a Queue with process id,burst time,arrival time or whether they have completed or not ..they are of process structure type
Process Process_Queue[]={{2132,2,2,0,0,false},{2102,4,4,0,0,false},{2483,8,8,0,0,false}};
//Assigning the maximum array length of gantt chart
Gantt Gantt_Chart[15];
//Initializing the value of time 
int Time_Value=0,i;
int Turnaround_Time[3],Waiting_Time[3],Avg_TT,Avg_WT;
//function to display the sequence of process in Gantt chart
void Sequence_Display();
//Function to display the Average waiting time and turn around time
int Display_Avg();

int main(){ 
	int count=0;
	//taking pointer variables of structure type Process
	Process *t,*pq;
	//taking pointer variables of structure type Gantt and assigiing the array to structure value to it
	Gantt *g=Gantt_Chart;
	//Taking the start time of Gantt chart as 0
	int startime=0;
	while(count<3){
		t=Process_Queue; //assigining process queue to t
		pq=Process_Queue;//assigning process queue to pq
		for(i=0;i<2;i++){
			*pq++;
			if(!pq->Completed){ //checking process is completed or not
				if(pq->Burst_Time>t->Burst_Time)t=pq; //if burst time of Queue pq is greater than burst time of Queue t then assign process of pq to t
				else if(pq->Burst_Time==t->Burst_Time)
					if(pq->Process_Id<t->Process_Id)
						t=pq;
			}
		}
		t->Burst_Time-=1; //reduce the burst time of t queue by 1 after each iteration
		g->Process_Id=t->Process_Id;
		g->Start_Time=Time_Value;//start time is assigned time value
		g->Finish_Time=++Time_Value;
		if(t->Burst_Time<=0){ //checking if burst time is equal to 0 then the process is completed 
			t->Finish_Time=Time_Value;
			t->Completed=true;
			count++;
		}
		*g++;
	}
	t=Process_Queue; //assiging t the value of process_queue
	for(i=0;i<3;i++){
		printf("P%d finished at %d \n",t->Process_Id,t->Finish_Time); //showing finishing time of each process
		t++;
	}
	printf("\n");
	Sequence_Display(); //calling function to display the gantt chart
	Display_Avg(); //calling function to display the avg waiting time and turn around time
	return 0;
}

int Display_Avg(){ //calculating average turn around time and waiting time and display that
	int *Tt=Turnaround_Time,*Wt=Waiting_Time; //assigning turnaround time to pointer tt and waiting time to pointer wt
	Process *t=Process_Queue;//assigning process queue to structure of pointer  
	for(i=0;i<3;i++){
		*(Tt+i)=t->Finish_Time-t->Burst_Time; //calculating turn around time of each process
		*(Wt+i)=*(Tt+i)-(t->Initial_Burst); //calculating waiting time of each process
		*t++; //incrementing the processes
	}
	for(i=0;i<3;i++){
		printf("TT: %d WT: %d\n",*(Tt+i),*(Wt+i));//printing turn around time and waiting time of each processes
		Avg_TT+=*(Tt+i);//final average turn around time of each processes
		Avg_WT+=*(Wt+i);//final average waiting time of each proecess
	}
	printf("Avg TT: %d Avg WT: %d\n",Avg_TT/3,Avg_WT/3);
}
void Sequence_Display(){//showing how the processes execute in the form of gantt chart
	Gantt *g=Gantt_Chart;
	int i;
	for(i=0;i<Time_Value;i++){
		if(g->Start_Time>=9)printf("|P%d|   ",g->Process_Id);//checking whether start time of process is greater than 9 or not
		else printf("|P%d| ",g->Process_Id);
		*g++;
	}
	g=Gantt_Chart;
	printf("\n");
	for(i=0;i<Time_Value;i++){
		if(g->Start_Time>9)printf("%d    %d  ",g->Start_Time,g->Finish_Time);//printing start time and finishing time of each processes
		else printf("%d     %d ",g->Start_Time,g->Finish_Time);
		*g++;
	}
	printf("\n");
}
