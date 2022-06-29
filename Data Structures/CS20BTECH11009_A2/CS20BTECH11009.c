#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct bstnode bstnode ;
typedef bstnode* bst ;
typedef bstnode Node ;
typedef struct avlnode avlnode ;
typedef avlnode* avl ;
typedef struct QueueNode QueueNode ;
typedef QueueNode* Queue ;
typedef struct StackNode StackNode ;
typedef StackNode*  Stack ;

// struct to represent queue node
struct QueueNode{
    char songs[100] ;
    Queue Next ;
} ;

// struct to repesent stack node
struct StackNode{
    char songs[100] ;
    Stack Next ;
} ;

// struct to repesent bst node
struct bstnode{
   
   char data[10] ;
   bstnode* left ;
   bstnode*right ;

};
// struct to repesent avl node
struct avlnode{
    char data[10] ;
    avlnode* left ;
    avlnode* right ;
    int height ;
} ;

// Function which returns maximum between 2 numbers
int max(int x,int y)
{
    if(x>=y)
        return x ;
    else
        return y ;
}
// Function to compare lexicographic order between 2 strings
int compare_songs(char s1[],char s2[])
{
    
    if(strcmp(s1,s2)>0)
    {
        return 1 ;
    }
    else if(strcmp(s1,s2)<0)
    {
        return 2 ;
    }
    else
        return 3 ;
}

// Function to create a new node for bst
bst create_node(char data[])
{
    bst node=(bst)malloc(sizeof(bstnode)) ;
    strcpy(node->data,data) ;
    node->left=NULL ;
    node->right=NULL ;
    return node ;
}
// Function to create a new node for avl
avl create_avlnode(char data[])
{
    avl node=(avl)malloc(sizeof(avlnode)) ;
    strcpy(node->data,data) ;
    node->left=NULL ;
    node->right=NULL ;
    node->height=1 ;
    return node ;
}
//Function to get height of a node in AVL tree
int get_height(avl root)
{
    if(root==NULL)
        return 0 ;
    else
        return root->height ;
}
//Recursive insertion in BST Tree
bst insert(bst root,char data[])
{
   if(root==NULL)
   {
     root=(bst)malloc(sizeof(bstnode)) ;
     strcpy(root->data,data) ;
     root->left=NULL ;
     root->right=NULL ;
   }
   else
   {
       if(compare_songs(root->data,data)==1)
        root->left=insert(root->left,data) ;
       else if(compare_songs(root->data,data)==2)
        root->right=insert(root->right,data) ;
   }
   return root ;

}
// function to left rotate at the given node 

avl left_rot(avl root)
{
    avl node1=root->right ;
    avl node2=node1->left ;
    node1->left=root ;
    root->right=node2 ;
    root->height=max(get_height(root->left),get_height(root->right))+1 ;
    node1->height=max(get_height(node1->left),get_height(node1->right))+1 ;
    return node1 ;
}
// function to Right rotate at the given node

avl right_rot(avl root)
{
    avl node1=root->left ;
    avl node2=node1->right ;
    node1->right=root ;
    root->left=node2 ;
    root->height=max(get_height(root->left),get_height(root->right))+1 ;
    node1->height=max(get_height(node1->left),get_height(node1->right))+1 ;
    return node1 ;
}
// Function for recursive insertion and Balancing the height 

avl insert_avlnode(avl root,char data[])
{
    avl node=create_avlnode(data) ;
    if(root==NULL)
    {
        return node ;
    }

    if(compare_songs(root->data,data)==1)
    {
        root->left=insert_avlnode(root->left,data) ;
    }
    else if(compare_songs(root->data,data)==2)
    {
        root->right=insert_avlnode(root->right,data) ;
    }
    else
        return node ;
    // getting the height of the node from subtrees
    root->height=max(get_height(root->left),get_height(root->right))+1 ;
    int balance ;
    //here we have 4 cases
    if(root!=NULL)
    balance=get_height(root->left)-get_height(root->right) ;
    else
        balance=0 ;
    //Left-Left case    
    if(root->left&&balance>1&&compare_songs(root->left->data,data)==1)
    {
        return right_rot(root) ;
    }
    //Right-Right case
    if(root->right&&balance<-1&&compare_songs(root->right->data,data)==2)
    {
        return left_rot(root) ;
    }
    //Left-Right case    
    if(root->left&&balance>1&&compare_songs(root->left->data,data)==2)
    {
        root->left=left_rot(root->left) ;
        return right_rot(root) ;
    }
    //Right-Left case
    if(root->right&&balance<-1&&compare_songs(root->right->data,data)==1)
    {
        root->right=right_rot(root->right) ;
        return left_rot(root) ;
    }

    return root ;

}

//This function deletes the node with given data from bst tree and returns new root
bst delete(bst root,char data[])
{
    if(root==NULL)
        return root ;

    if(compare_songs(root->data,data)==1)
    {
        root->left=delete(root->left,data) ;
    }
    else if(compare_songs(root->data,data)==2)
    {
        root->right=delete(root->right,data) ;
    }
    else
    {
        if(root->left==NULL)
        {
            struct bstnode* temp=root->right ;
            free(root) ;
            return temp ;
        }
        else if(root->right==NULL)
        {
            struct bstnode* temp=root->left ;
            free(root) ;
            return temp ;
        }
        struct bstnode* curr=root->right ;
        while(curr&&curr->left)
        {
            curr=curr->left ;
        }
        strcpy(root->data,curr->data) ;
        root->right=delete(root->right,curr->data) ;
    }
    return root ;
}

// Function for searching a data in Bst tree
bst bst_search(bst root,char data[])
{
    if(root==NULL||strcmp(data,root->data)==0)
    {
        return root ;
    }

    if(compare_songs(root->data,data)==1)
    {
        bst_search(root->left,data) ;
    }
    else
        bst_search(root->right,data) ;
}
//Constucting a bst from preorder transversal
bst construct_tree(char* songs_list[],int* index1,int l,int r,int num_songs)
{
    if(*index1>num_songs||l>r)
        return NULL ;

    bst node=create_node(songs_list[*index1]) ;
    *index1=*index1+1 ;
    if(l==r)
    {
        return node ;
    }
    int index2=r ; // index2 contains the index of next largest song than the song in node
    for(int i=l;i<=r;i++)
    {
        if(compare_songs(songs_list[i],node->data)==1)
        {
            index2=i ;
            break ;
        }
    }
    node->left=construct_tree(songs_list,index1,*index1,index2-1,num_songs) ; // all the indices lesser than index2 belong to left subtree
    node->right=construct_tree(songs_list,index1,index2,r,num_songs) ; // all the indices greater than index2 belong to right subtree
    return node ;
}
// deletes the node for given data from avl tree and return new root

avl delete_avlnode(avl root,char data[])
{
    if(root==NULL)
        return NULL ;

    if(compare_songs(root->data,data)==1)
    {
        root->left=delete_avlnode(root->left,data) ;
    }
    else if(compare_songs(root->data,data)==2)
    {
        root->right=delete_avlnode(root->right,data) ;
    }
    else
    {
        if(root->left==NULL||root->right==NULL)
        {
            avl temp ;
            if(root->left)
            {
                temp=root->left ;
            }
            else
                temp=root->right ;
            if(!temp)
            {
                temp=root ;
                root=NULL ;
            }
            else
                *root=*temp ;
            free(temp) ;
        }
        else
        {
            avl temp=root->right ;
            while(temp!=NULL&&temp->left!=NULL)
            {
                temp=temp->left ;
            }
            strcpy(root->data,temp->data) ;
            root->right=delete_avlnode(root->right,temp->data) ;
        }
    }
    if(root==NULL)
        return NULL ;
    root->height=1+max(get_height(root->left),get_height(root->right)) ;
    int balance=0 ;
    if(root!=NULL)
    balance=get_height(root->left)-get_height(root->right) ;
    //Left-Left case

    if(root->left&&balance>1&&compare_songs(root->left->data,data)==1)
    {
        return right_rot(root) ;
    }
    //Right-Right case
    if(root->right&&balance<-1&&compare_songs(root->right->data,data)==2)
    {
        return left_rot(root) ;
    } 
    //Left-Right case  
    if(root->left&&balance>1&&compare_songs(root->left->data,data)==2)
    {
        root->left=left_rot(root->left) ;
        return right_rot(root) ;
    }
    //Right-Left case
    if(root->right&&balance<-1&&compare_songs(root->right->data,data)==1)
    {
        root->right=right_rot(root->right) ;
        return left_rot(root) ;
    }

    return root ;
}  
//Function for Adding data to Queues
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
//Function for Removing data from Queue

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
//Function for Adding data to Stacks

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
//Function for Removing data from Stack

Stack Pop(Stack S)
{
    if(S==NULL)
        return NULL ;
    
   Stack P=S ;
   S=S->Next ;
   free(P) ;
   return S ;
}
//Function for adding the elements of the inorder transversal into Queue for playing next songs 

Queue avl_inorder(avl root,Queue Q)
{
    if(root==NULL)
    {
        return Q ;
    }
    else
    {
        Q=avl_inorder(root->left,Q) ;
        Q=Push_Q(Q,root->data) ;
        Q=avl_inorder(root->right,Q) ;
        return Q ;        
    }
}


int main(void)
{
    //Code for reading the data frm file
    FILE* fp=fopen("file.txt","r") ;
    char songs[100000] ;
    fgets(songs,100000,fp) ;
    char* songs_list[10000] ;
    int num_songs=0 ;
    char* song=strtok(songs,":") ;
    while(song)
    {
        songs_list[num_songs++]=song ;
        song=strtok(NULL,":") ;
    }
    //adding all the songs into bst tree from given preorder .this will be our new library
    int index1 ;
    bst library=construct_tree(songs_list,&index1,0,num_songs-1,num_songs) ;
    printf("All songs entered!\n") ;
    
    //running a while loop 
    while(1)
    {
        char song_name[1000] ;
        //deleting the songs from library which you hate 
        printf("Enter the song which you want to delete from library/Enter -1 if you don't want to delete the song\n") ;
        scanf("%s",song_name) ;
        if(strcmp(song_name,"-1")==0)
        {
            break ;
        }
        else
        {
            library=delete(library,song_name) ;
            printf("%s deleted from library!\n",song_name) ;
        }
    }
    
    avl playlist=NULL ;
    //after deletion songs from library , adding songs into playlist which is an AVL tree
    while(1)
    {
        char song_name[1000] ;
        printf("Enter the song which you want to insert into playlist/Enter -1 if you don't want to insert the song in Playlist\n") ;
        scanf("%s",song_name) ;
        if(strcmp(song_name,"-1")==0)
        {
            break ;
        }
        else
        {
            bst node=bst_search(library,song_name) ;
            if(node==NULL)
            {
                printf("Song not found in library\n") ;
            }
            else
            {
                playlist=insert_avlnode(playlist,song_name) ;
                printf("%s is inserted in playlist\n",song_name) ;
            }
        }
    }
    while(1)
    {
        char song_name[1000] ;
        //deleting the songs from playlist  
        printf("Enter the song which you want to delete from Playlist/Enter -1 if you don't want to delete the song\n") ;
        scanf("%s",song_name) ;
        if(strcmp(song_name,"-1")==0)
        {
            break ;
        }
        else
        {
            playlist=delete_avlnode(playlist,song_name) ;
            printf("%s deleted from playlist!\n",song_name) ;
        }
    }    
    Queue Q =NULL ;
    //recent songs stack
    Stack S=NULL ;
    //Adding the songs into queue which we got from inorder transversal of AVL Playlist
    Q=avl_inorder(playlist,Q) ;
    while(1)
    {
        
        printf("Play next song, previous songs or end? n/p:k/e\n") ;
        char input[100] ;
        scanf("%s",input) ;
        //playing the next song by dequeing the queue and adding them into recent songs stack
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
        //playing previous k songs by poping from recent songs stack and enquing into temporary queue
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
        //when you want to leave the playlist
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