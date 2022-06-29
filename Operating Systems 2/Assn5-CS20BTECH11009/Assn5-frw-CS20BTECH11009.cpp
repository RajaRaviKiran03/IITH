#include <bits/stdc++.h>
#include<unistd.h> //header to be included fro sleep
#include <chrono> 
#include <semaphore.h>
#include <time.h>
#include <sys/time.h>
using namespace std;

int nw , nr , kw , kr ; //delaring varaibles as global
double mcs , mrt ;
sem_t wr_mutex ; //2 semaphores
sem_t mutex1;
sem_t queueorder;
int reading_count ;

ofstream output_file; //log files
ofstream output_file1; // avg file

double ** writing_waittime; // 2d array for waiting times for writing threads
double ** reading_waittime; /// 2d array for waiting times for writing threads

double func( double x) // function for exponential distribution
{
    double y ;
    uniform_real_distribution<double> distribute(pow(x,-1));
	random_device randomdevice;
	default_random_engine generate(randomdevice());
	y = distribute(generate);
    return y ;

}

string getsystime() //function to get system time
{
    using namespace std::chrono;
    auto current_time =   system_clock::now();
    auto milli_sec = duration_cast<milliseconds>(current_time.time_since_epoch()) % 1000;
    auto t = system_clock::to_time_t(current_time);
    tm broken_time = *std::localtime(&t);
    ostringstream s;
    s << std::put_time(&broken_time, "%H:%M:%S"); // HH:MM:SS
    s << '.' << std::setfill('0') << std::setw(3) << milli_sec.count();
    return s.str();
}

void writer(int index)  //writer funtion
{
    struct timeval start,end;
    for(int j = 0 ; j < kw ; j++)
    {
        double t1 , t2 ;
        string request_time = getsystime();
        gettimeofday(&start, NULL);
        output_file << j << "th CS request by writer thread " << index << " at "<< request_time << endl ;
        
        //lock 
        sem_wait(&queueorder);
        sem_wait(&wr_mutex);
        sem_post(&queueorder);

        string entry_time = getsystime();
    	gettimeofday(&end, NULL);
        double waiting_time1 = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
        writing_waittime[index][j]=waiting_time1;

        output_file << j << "th CS entry by writer thread " << index << " at "<< entry_time << endl ;

        t1 = func( mcs);   // critical section
        sleep(t1/1000);

        string exit_time = getsystime();
        output_file << j << "th CS exit by writer thread " << index << " at "<< exit_time << endl ;

        sem_post(&wr_mutex); //release

        t2 = func( mrt);
        sleep(t2/1000);
    }
}

void reader( int index) //reader function.
{
    struct timeval start,end;
    for( int i = 0 ; i < kr ; i++)
    {
        double t1 , t2 ;
        string request_time = getsystime();
        gettimeofday(&start, NULL);
        output_file << i << "th CS request by reader thread " << index << " at "<< request_time << endl ;

        // lock
        sem_wait(&queueorder);
        sem_wait(&mutex1);
        reading_count++ ;
        if ( reading_count == 1)
        {
            sem_wait(&wr_mutex);
        }
        sem_post(&queueorder);
        sem_post(&mutex1);


        string entry_time = getsystime();
    	gettimeofday(&end, NULL);

        double waiting_time2 = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
        reading_waittime[index][i]=waiting_time2;

        output_file << i << "th CS entry by reader thread " << index << " at "<< entry_time << endl ;

        t1 = func( mcs);   // critical section
        sleep(t1/1000);

        //release 
        sem_wait(&mutex1);
        reading_count--;
        if ( reading_count == 0 )
        {
            sem_post(&wr_mutex);
        }
        sem_post(&mutex1);

        string exit_time = getsystime();
        output_file << i << "th CS exit by reader thread " << index << " at "<< exit_time << endl ;

        t2 = func( mrt);
        sleep(t2/1000);
    }
}

void fair_RW( )
{
    reading_count = 0 ;
    sem_init(&wr_mutex , 0 , 1);
    sem_init(&mutex1 , 0 , 1);
    sem_init(&queueorder,0,1);

    thread* writing_threads[nw];
    thread* reading_threads[nr];
   
    for(int i=0 ; i< nr ; i++)
    {
       reading_threads[i] = new thread(reader,i); //creating and calling reader threads
    }
    for(int i=0 ; i< nw ; i++)
    {
       writing_threads[i] = new thread(writer,i); //creating and calling writer threads
    }
    for(int j = 0 ; j< nr ; j++)
    {
        reading_threads[j]->join(); // joining reader threads
    }
    for(int j = 0 ; j< nw ; j++)
    {
        writing_threads[j]->join(); // joining writer threads
    }
    for(int k =0 ; k<nr ;k++)
    {
        delete reading_threads[k]; //deleting reader threads
    }
    for(int k =0 ; k<nw ;k++)
    {
        delete writing_threads[k]; //deleting writer threads
    }
    sem_destroy(&wr_mutex);
    sem_destroy(&mutex1);
    sem_destroy(&queueorder);
}



int main()
{
    output_file.open("FairRW-Log.txt");
    output_file1.open("FairRW-Avg_time.txt");
    FILE* file_ptr;
    file_ptr = fopen("inp-params.txt","r"); //opening inp-params.txt

    fscanf(file_ptr,"%d",&nw);
    fscanf(file_ptr,"%d",&nr);
    fscanf(file_ptr,"%d",&kw);
    fscanf(file_ptr,"%d",&kr);
    fscanf(file_ptr,"%lf",&mcs);
    fscanf(file_ptr,"%lf",&mrt);

    reading_waittime = new double*[nr];
    for(int i = 0 ; i<nr ; i++)
    {
        reading_waittime[i] = new double[kr];
    }

    writing_waittime = new double*[nw];
    for(int i = 0 ; i<nw ; i++)
    {
        writing_waittime[i] = new double[kw];
    }

    fair_RW();

    double reader_sum = 0 ;
    double reader_totalsum = 0 ;
    double reader_max = 0 ;
    double avg ;
    for ( int i = 0 ; i< nr ; i++)
    {
        for ( int j = 0 ; j < kr ; j++ )
        {
            if(  reading_waittime[i][j] > reader_max)
            {
                reader_max = reading_waittime[i][j];
            }
            reader_sum += reading_waittime[i][j];
            avg = reader_sum / kr ;
        }

        output_file1 << "Average waittime for Readerthread "<< i << " is " << avg/1000 <<"ms"<< endl;
        reader_totalsum += avg;
        reader_sum = 0 ;
    }
    output_file1 << "Total avg waittime for all Readerthreads is " << reader_totalsum / (nr* 1000)<<"ms" << endl;
    output_file1<< "Max waittime for all Readerthreads  is " << reader_max / 1000 << "ms"<< endl;

    double writer_sum = 0 ;
    double writer_totalsum = 0 ;
    double writer_max = 0 ;

    for ( int i = 0 ; i< nw ; i++)
    {
        for ( int j = 0 ; j < kw ; j++ )
        {
            if( writing_waittime[i][j] > writer_max)
            {
                writer_max = writing_waittime[i][j];
            }
            writer_sum += writing_waittime[i][j];
            avg = writer_sum / kw;
        }
        output_file1 <<"Average waittime for Writerthread " << i <<" is " << avg/1000 <<"ms"<< endl;
        writer_totalsum += avg;
        writer_sum = 0;
    }
    output_file1<< "Total avg waittime for all Writerthreads is " << writer_totalsum / ( nw * 1000)<<"ms" << endl;
    output_file1<< "Max waittime for all Writerthreads  is " << writer_max / 1000 <<"ms" <<endl;

    return 0 ;
}









