#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
typedef struct QueueNode QueueNode ;
typedef QueueNode* Queue ;
typedef struct StackNode StackNode ;
typedef StackNode*  Stack ;
typedef struct ListNode ListNode;
typedef ListNode* List ;

struct QueueNode{
	char songs[100] ;
	Queue Next ;
} ;

struct StackNode{
	char songs[100] ;
	Stack Next ;
} ;

struct ListNode{
	char songs[100] ;
	List Next ;
} ;

Queue Push_Q(Queue Q,char songs[])
{
   Queue P=(Queue)malloc(sizeof(QueueNode)) ;
   strcpy(P->songs,songs) ;
   P->Next=NULL ;

   if(Q==NULL)
   	Q=P ;
   else
   {
   	  Queue Q1=Q ;

   	  while(Q1->Next!=NULL)
   	  	Q1=Q1->Next ;

   	   Q1->Next=P ;
   }
   return Q ;
}

Queue Pop_Q(Queue Q)
{
   if(Q==NULL)
   	return NULL ;

   Queue P ;
   P=Q ;
   Q=Q->Next ;
   free(P) ;
   return Q ;

}



Stack Push(Stack S,char songs[])
{
   Stack P=(Stack)malloc(sizeof(StackNode)) ;
   strcpy(P->songs,songs) ;
   P->Next=NULL ;

   if(S==NULL)
   	S=P ;
   else
   {
   	  P->Next=S ;
   	  S=P ;
   }
   return S ;
}


Stack Pop(Stack S)
{
	if(S==NULL)
		return NULL ;
	
   Stack P=S ;
   S=S->Next ;
   free(P) ;
   return S ;
}

List Insert(List L,char songs[])
{
	List P=(List)malloc(sizeof(ListNode)) ;
	strcpy(P->songs,songs) ;
	P->Next=NULL ;

	if(L==NULL)
	{
		L=P ;
	}
	else
	{
   	   List L1=L ;

   	  while(L1->Next!=NULL)
   	  	L1=L1->Next ;

   	   L1->Next=P;	
	}
	return L ;
}

int FindLast(List L,char songs[])
{
	if(L==NULL)
	{
		return -1 ;
	}
	else if(strcmp(L->songs,songs)==0)
	{
		return 0 ;
	}
	List P=L->Next ;
	int index=0 ;
	int ans=-1 ;
	while(P!=NULL&&P->Next!=NULL)
	{
		if(strcmp(P->songs,songs)==0)
		{
           ans=index;
		}
		index++ ;
		P=P->Next ;
	}
	if(strcmp(P->songs,songs)==0)
	{
		ans=index ;
	}
	return ans ;
}
int main(void)
{
	printf("Enter all songs (as strings),End with -1\n") ;
	char input[100] ;
	scanf("%s",input) ;
	List L=NULL ;
	while(strcmp(input,"-1")!=0)
	{
		L=Insert(L,input) ;
		memset(input,'\0',100) ;
		scanf("%s",input) ;
	}
	printf("All songs entered!\n") ;
	printf("Create Playlist, end with -1\n") ;
	memset(input,'\0',100) ;
	scanf("%s",input) ;
	Stack S=NULL ;
	Queue Q=NULL ;
	while(strcmp(input,"-1")!=0)
	{
		bool found=false ;
		if(FindLast(L,input)==-1)
		{
			printf("Not Found in the song library\n") ;
		}
		else
		{
			Q=Push_Q(Q,input) ;
			printf("Found Enqueud\n") ;
		}
		memset(input,'\0',100) ;
		scanf("%s",input) ;
	}
	printf("Playlist Ready!\n") ;
	while(1)
	{
		printf("Play next song, previous songs or end? n/p:k/e\n") ;
		memset(input,'\0',100) ;
		scanf("%s",input) ;
		if(strcmp(input,"n")==0)
		{
			if(Q==NULL)
			{
				printf("There is no next song in the Playlist\n") ;
				continue ;
			}
			else
			{
				printf("Playing %s\n",Q->songs) ;
				S=Push(S,Q->songs) ;
				Q=Pop_Q(Q) ;
			}
		}
		else if(input[0]=='p')
		{
			Queue Temporary_Queue=NULL ;
			int n=atoi(input+2) ;
			int cnt=0 ;
			for(int i=0;i<n;i++)
			{
				if(S==NULL)
				{
					printf("There aren't %d previous songs\n",n) ;
					break ;
				}
				else
				{
					printf("Playing %s\n",S->songs) ;
					Temporary_Queue= Push_Q(Temporary_Queue,S->songs) ;
					S=Pop(S) ;
					cnt++ ;
				}
			}
			for(int i=0;i<cnt;i++)
			{
				S=Push(S,Temporary_Queue->songs) ;
				Temporary_Queue=Pop_Q(Temporary_Queue) ;
			}
		}
		else if(strcmp(input,"e")==0)
		{
			printf("Bye\n") ;
			return 0 ;
		}
		else
		{
			printf("Invalid command!\n") ;
		}

	}
}