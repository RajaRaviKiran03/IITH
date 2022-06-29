#include <bits/stdc++.h>
using namespace std;


struct PCB
{
    int pid ; //process id
    int pt ;
    int pp ;
    int k ;
    int available_time;
    int deadline;
    int time_rem;
    bool status;
    vector<int> waiting_time;
    int k_1;

};
typedef struct PCB pcb;
int n ;

//find_highest_priority
int highest_priority(pcb *arr1, int size)
{
    int min= 0;
    for (int i = 0; i < size; i++)
    {
        if (arr1[i].status) 
        {
            min = i;
            break;
        }
    }

    if(arr1[min].status == false) return -1;
    
    for(int i = 0 ; i<size ; i++)
    {
        if (arr1[i].status)
        {
            if(arr1[i].pp<arr1[min].pp)
            {
                min = i ;
            }
        }
    }
    if (arr1[min].status)
    {
        return min;
    }

    else 
    return -1 ;

}
int low_avail_time( pcb *arr1, int size)
{
    int min = 0 ;
    for(int i = 0 ; i<size ; i++)
    {
        if(arr1[min].available_time > arr1[i].available_time)
        {
            min = i;
        }

    }
    return min ;
}

pcb *arr;
int main()
{
    int count1 = 0 ;
    int count2 = 0 ;
    FILE* file_ptr;
    file_ptr=fopen("inp-params.txt","r");
    fscanf(file_ptr,"%d",&n);
    arr =  (pcb *)malloc(n*sizeof(pcb));
    int i ;
    for(i=0;i<n;i++)
    {
        fscanf(file_ptr,"%d %d %d %d",&arr[i].pid,&arr[i].pt,&arr[i].pp,&arr[i].k);
        arr[i].available_time=0;
        arr[i].deadline=arr[i].pp;
        arr[i].time_rem=arr[i].pt;
        arr[i].status=true;
        arr[i].k_1=arr[i].k;
    }
    fclose(file_ptr);
  
    FILE* output1;
    FILE* output2;
    output1=fopen("RMS-Log.txt","w");
    output2=fopen("RMS-Stats.txt","w");
    for(int b=0 ; b<n ; b++)
    {
        fprintf(output1,"Process P%d : processing time: %d , deadline : %d , period: %d joined at time 0\n",
        arr[b].pid,arr[b].pt,arr[b].deadline,arr[b].pp);
    }
    
    int cpu_time=0;
    int cpu_index= highest_priority(arr, n);
    for(cpu_time=0;;cpu_time++)
    {
        int k ;
        for(k =0 ; k<n ; k++)
        {
            if( arr[k].available_time == INT_MAX) 
            continue;
            else break;

        }
        if ( k == n )
        {
            fprintf(output1,"All process completed\n");
            break;
        }
        //scheduler
        for(int i =0 ; i<n ; i++)
        {
            if( arr[i].available_time <= cpu_time && arr[i].k != 0)
            {
                arr[i].status= true ;
            }
        }
       
        if(cpu_index<0)
        {
            int a = 0 ;
            for(int j = 0 ; j<n ; j++)
            {
                if( arr[j].status)
                {
                    a++;
                }
            }
            if( a == 0)
            {
                cpu_index = low_avail_time(arr,n);
                cpu_time = arr[cpu_index].available_time;
                fprintf(output1,"Cpu is idle till time %d\n",cpu_time);
            }
            else
            {
                cpu_index=highest_priority(arr,n);
                fprintf(output1,"Process P%d is started at time %d\n",arr[cpu_index].pid, cpu_time);
            }


        }
        else if ( cpu_index == highest_priority(arr,n))
        {
            cpu_index = highest_priority(arr,n);
        }
        else
        {
            //  it is preempted
            int ex_cpu_index = cpu_index;
            cpu_index = highest_priority(arr,n);
            fprintf(output1,"Process P%d is preempted by process %d at time %d\n",arr[ex_cpu_index].pid,arr[cpu_index].pid,cpu_time);
        }

        if ( arr[cpu_index].deadline > cpu_time)
        {
            arr[cpu_index].time_rem -- ;
            
        }
        else
        {
            count2++ ;
            //missed deadline
            arr[cpu_index].waiting_time.push_back(cpu_time-arr[cpu_index].available_time-arr[cpu_index].pt+arr[cpu_index].time_rem);
            fprintf(output1,"Process P%d has missed deadline at time %d\n",arr[cpu_index].pid, cpu_time);
            arr[cpu_index].k-- ;
            if( arr[cpu_index].k != 0)
            {
                arr[cpu_index].available_time += arr[cpu_index].pp;
                arr[cpu_index].deadline += arr[cpu_index].pp;
                arr[cpu_index].time_rem += arr[cpu_index].pt;  
                arr[cpu_index].status = false ;
                cpu_index = -1 ;
            }
            else 
            {
                arr[cpu_index].available_time = INT_MAX;
                arr[cpu_index].deadline = INT_MAX;
                arr[cpu_index].status = false ;
                 arr[cpu_index].time_rem += arr[cpu_index].pt; 
                cpu_index = -1 ;

            }
           // cpu_time--;
            continue;

        }
        if(arr[cpu_index].time_rem == 0)
        {
            count1++ ;
            arr[cpu_index].waiting_time.push_back(cpu_time+1-arr[cpu_index].available_time-arr[cpu_index].pt);

            
         
            arr[cpu_index].k-- ;
            if( arr[cpu_index].k != 0)
            {
                fprintf(output1,"Process P%d has completed at time %d\n",arr[cpu_index].pid, cpu_time);
                arr[cpu_index].available_time += arr[cpu_index].pp;
                arr[cpu_index].deadline += arr[cpu_index].pp;
                arr[cpu_index].time_rem += arr[cpu_index].pt;  
                arr[cpu_index].status = false ;
                cpu_index = -1 ;
            }
            else 
            {
                arr[cpu_index].available_time = INT_MAX;
                arr[cpu_index].deadline = INT_MAX;
                arr[cpu_index].status = false ;
                 arr[cpu_index].time_rem += arr[cpu_index].pt; 
                cpu_index = -1 ;

            }

        }

    }

    float total_sum = 0.0 ;
    int total_count=0;
    for(int p = 0 ; p<n ; p++)
    {
        float sum = 0.0 ;
        for(int wait : arr[p].waiting_time) 
        {
            sum += wait ;
        }
        float avg = sum/ arr[p].k_1;
        total_sum += sum;
        total_count+=arr[p].k_1;
        fprintf(output2,"Average waiting time for process P%d is %f\n",arr[p].pid,avg);
    }
    float total_avg = total_sum / total_count;
    fprintf(output2,"Average waiting for all proceses is  %f\n",total_avg);

    fprintf(output2,"No of processes completed is %d\n",count1);
    fprintf(output2,"No of processes missed deadline is %d\n",count2);

    free(arr);
    return 0 ;
}