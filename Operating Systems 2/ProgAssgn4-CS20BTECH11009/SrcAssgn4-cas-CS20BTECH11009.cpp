#include<bits/stdc++.h>
#include<unistd.h> //header to be included fro sleep
using namespace std;

int n , k; 
// no of varibles , no of times each process to be executed

atomic<bool> locking(false) ;
//atomic bool
//bool flag = false;

FILE* output;//output file


vector<double> wait_times; // vector for storing waiting time for each iteration

double func( double x) // function for exponential distribution
{
    double y ;
    uniform_real_distribution<double> distribute(pow(x,-1));
	random_device randomdevice;
	default_random_engine generate(randomdevice());
	y = distribute(generate);
    return y ;

}

void message_print ( char c , int x , int time_ ,int id)
{
    if ( c == 'R')
    {
        fprintf(output,"%dth CS request at %d by thread %d\n",x,time_,id);
    }
    else if ( c == 'E')
    {
        fprintf(output,"%dth CS entry at %d by thread %d\n",x,time_,id);
    }
    else if ( c == 'X')
    {
        fprintf(output,"%dth CS exit at %d by thread %d\n",x,time_,id);
    }
}


void TESTCS(int index , int t1 , int t2)   //Test CS function
{   
    for(int i = 0 ; i < k ; i++)
    {
        int request_time = clock();
        bool flag2 = false;

       
        message_print('R' , i+1 ,request_time , index  );
        while( ! atomic_compare_exchange_strong(&locking,&flag2,true))
        flag2 = false; // locking

        int entry_time = clock();
        double waiting_time = 1000* (entry_time-request_time) / CLOCKS_PER_SEC;
        // waiting time for each iteration

        wait_times.push_back( waiting_time);

        
        message_print('E' , i+1 ,entry_time , index  );

      
        sleep(t1/1000); // critical section

        locking = false; //unlocking
        int exit_time = clock();
        
        message_print('X' , i+1 ,exit_time, index  );

       
        sleep(t2/1000); //remainder section
    
    }
}


void cas(double t1 , double t2)
{
    thread* working_threads[n];
    for(int i=0 ; i< n ; i++)
    {
       working_threads[i] = new thread(TESTCS,i, t1, t2); //creating and calling threads
    }

    for(int j = 0 ; j< n ; j++)
    {
        working_threads[j]->join(); // joining threads
    }

    for(int k =0 ; k<n ;k++)
    {
        delete working_threads[k]; //deleting threads
    }

}

double find_avg( vector<double> vec) //function for calculating average from a vector
{
    double avg = 0 ;
    for(int i = 0 ; i< vec.size(); i++)
    {
        avg = avg + vec[i];

    }

    avg = avg / vec.size();
    return avg ;
    
}

double find_max ( vector<double> vec) //function for calculating maximum from a vector
{
    double maximum = vec[0]; 
    for(int i = 0 ; i< vec.size(); i++)
    {
        if( vec[i]> maximum)
        {
            maximum = vec[i];
        }

    }
    return maximum;
}



int main()
{
    output = fopen("cas_output.txt","w"); //output file opening
    FILE* file_ptr; 
    double l1, l2;
    file_ptr = fopen("inp-params.txt","r"); //opening inp-params.txt
    fscanf(file_ptr,"%d",&n);
    fscanf(file_ptr,"%d",&k);
    fscanf(file_ptr,"%lf",&l1);
    fscanf(file_ptr,"%lf",&l2);

    cas(func(l1), func(l2));

    double average_waiting_time = find_avg( wait_times);
    double maximum_waiting_time = find_max( wait_times);

    cout<<"Average waiting time is "<< average_waiting_time<<"ms"<<endl;//printing average waiting time
    cout<<"Maximum waiting time is "<< maximum_waiting_time<<"ms"<<endl;// printing maximum waiting time


    return 0;
}