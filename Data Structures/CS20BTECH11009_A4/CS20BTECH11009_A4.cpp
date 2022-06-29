#include<bits/stdc++.h>
#include<stdlib.h>
#include<time.h>
using namespace std ;

typedef struct event event;
//struct event for person
struct event{
	int timestamp ;
	char status ;
	int id ;
} ;

//function to implement graph using adjacency matrix
//This function tosses coin and place an edge between if heads
void Graph(int **matr, int n)
{
  srand(time(NULL));
  for(int i=0;i<n;i++)
  {
    for(int j=i+1;j<n;j++) 
    {
      if(rand()%2 == 1) // 1 means tail 
      {matr[i][j] = 0; matr[j][i] = 0;}

      else //else head
      {matr[i][j] = 1; matr[j][i] = 1;}
    }
  }
}
// function to get the shortest distance form first node to given node
int bfs(int first,int** mat, int node)
{
	int checked[100]= {0};
  vector<int> d(100,-1);
	queue<int> q;
	q.push(first);

   d[first]= 0; //First node distance node is 0
   checked[first]= 1 ;

	while (!q.empty()) {
    int v;
		v = q.front();
    q.pop();
		for (int i = 0; i < 100; i++) {
			if (!checked[i]) 
       {
        if(mat[v][i]==1)
				{  q.push(i);
				   checked[i] = 1;
           d[i] = d[v] + 1; // Updating min distance
        }
			}
		}
	}
  return d[node] ; //Returning Minimum distance of required node 
}
struct comp
{
  bool operator()(event a,event b) const {
  	if(a.timestamp == b.timestamp)
  	{
  		return a.id < b.id ;
  	}
  	else
  		return a.timestamp>b.timestamp ;
  }
} ;

int main ()
{
  // Memory allotment for adjacency matrix in heap

 int **mat = (int**)malloc(100*sizeof(int*));
 for(int i = 0 ; i < 100 ;i++)
 {
   mat[i]=(int*) malloc( 100 * sizeof(int));

 }

  Graph(mat, 100); // Implementing Graph
  // Take 100 events
	vector<event> events(100) ;
  // 3 sets S is suceptible people I is infected people R is recovered people
  set<int> S,I,R;
	srand(time(0)) ;
	bool flag[100] ;

  //Initialising events
	for(int i=0;i<100;i++)
	{
		events[i].id=i ;
		events[i].status='S' ;
		events[i].timestamp=0 ;
		S.insert(i) ;
	}
  
  //Choosing a random node
  int fnode=rand()%100 ;
  // Assuming person with above id is infected
	events[fnode].status='I' ;
	priority_queue<event,vector<event>,comp> Q ;
	Q.push(events[fnode]) ;
  event rec;
  // Updating recovery of the first person
  rec.id = events[fnode].id ;
  srand(time(0)) ;
  rec.timestamp = events[fnode].timestamp + 1 + rand()%5;
  rec.status = 'R';
  Q.push(rec);
  //initial size of sets
  cout<<"intial Susceptible"<<" "<<"intial Infected"<<" "<<"intial Recovery\n" ;
  cout<<"100       0       0"<<endl;

  //Simulation Table
	cout<<"Day"<<" Susceptible"<<" Infected"<<" "<<"Recovery\n" ;
  int m =0 ;
  while( !Q.empty())
  {
    event A=Q.top() ;
		int time1=A.timestamp ;
		Q.pop() ;
    
    // Updating recovery set
    if(A.status == 'R')
    {
      R.insert(A.id) ;
			I.erase(A.id);
    }
    //Updating infection set and updating the persons which A infected
    else if ( A .status == 'I')
    {
        I.insert(A.id) ;
			  S.erase(A.id) ;

      for(int i=0 ; i < 100 ; i++  )
      {
        // for all adjacent nodes in the graph
        if ( mat[A.id][i]  == 1)
        {
          //Checking whether the person is suceptible or not
          if ( events[i].status == 'S' ) 
          { 
            //Updating infection status
            event x;
            x.id = i;
            x.status = 'I';
		        events[i].status='I' ;
            srand(time(0)) ;
            x.timestamp = time1+1+(rand()%4);
            Q.push(x);
            
            // Updating recovery status
            event r;
            r.id = i ;
            r.status = 'R';
		        events[i].status='R' ;
            srand(time(0)) ;
            r.timestamp = x.timestamp + 1+(rand()%4);
            Q.push(r);
            

          }
        }
      }
    }
    if ( Q.top().timestamp > m) // printing status of people vs days
    {
       cout<<m<<"   " << S.size()<<"        "<<I.size()<<"         "<<R.size()<<"\n" ;
      m++;
    } 
  }
  cout<<m<<"     "<<S.size()<<"       "<<I.size()<<"        "<<R.size()<<"\n" ; // Lastday

  // Printing the shortest distance from infected person 
  cout<<"Shortest Distance from "<<fnode<<":"<<endl;

   for(int i=0;i<100;i++)
   {
    cout<<"Node "<<i<<"->"<<bfs(fnode,mat,i)<<endl;
   }  
 
  return 0;

}