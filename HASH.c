#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MinTableSize (10)

typedef int ElementType;
typedef unsigned int Index;

struct ListNode;
typedef struct ListNode *Position;
struct HashTbl;
typedef struct HashTbl *HashTable;
ElementType s[200000];
struct ListNode
{
  ElementType Element;
  Position    Next;
};

typedef Position List;

/* List *TheList will be an array of lists, allocated later */
/* The lists use headers (for simplicity), */
/* though this wastes space */

struct HashTbl
{
  int TableSize;
  List *TheLists;
};

//---------------------------------
/* Hash function for ints */

Index
Hash( ElementType Key, int TableSize )
{
  return Key % TableSize;
}

//---------------------------------
HashTable
InitializeTable( int TableSize )
{
  HashTable T;
  int i;

  if( TableSize < MinTableSize )
    {
      printf( "Table size too small.\n" );
      return NULL;
    }

  /* Allocate table */
  T = malloc( sizeof( struct HashTbl ) );
  if( T == NULL )
    printf( "Out of space!!!\n" );
  
  T->TableSize = TableSize ;

  /* Allocate array of lists */
  T->TheLists = malloc( sizeof( List ) * T->TableSize );
  if( T->TheLists == NULL )
    printf( "Out of space!!!\n" );

  /* Allocate list headers */
  for( i = 0; i < T->TableSize; i++ )
    {
      T->TheLists[ i ] = malloc( sizeof( struct ListNode ) );
      if( T->TheLists[ i ] == NULL )
	printf( "Out of space!!!\n" );
      else
	T->TheLists[ i ]->Next = NULL;
    }
  return T;
}
//---------------------------------------------------
Position
Chained_Hash_Search(HashTable T, ElementType Key)
{
  Position P,ppast;
  List L;

  /* 1*/      L = T->TheLists[ Hash( Key, T->TableSize ) ];
  /* 2*/      P = L->Next;
              ppast=L;
  /* 3*/      while( P != NULL && P->Element != Key )
				{
				  ppast=P;
  /* 4*/          P = P->Next;
				}
  /* 5*/      return ppast;
}
//---------------------------------------------------

void
Chained_Hash_Insert(HashTable T, ElementType Key)
{
  Position Pos, NewCell;
  List L;
      
  /* 1*/      Pos = Chained_Hash_Search( T, Key );
  /* 2*/      if( Pos->Next == NULL )   /* Key is not found */
    {
  /* 3*/          NewCell = malloc( sizeof( struct ListNode ) );
  /* 4*/          if( NewCell == NULL )
  /* 5*/              printf( "Out of space!!!\n" );
	    else
	      {
				NewCell->Element=Key;
				NewCell->Next=NULL;
				Pos->Next= NewCell;
	}
    }
}
//-----------------------------------------------------

ElementType
Retrieve( Position P )
{
  return P->Element;
}

//-----------------------------------------------------
void
Chained_Hash_Delete( HashTable T, ElementType Key )
{
  List L;
  Position P, PreP;
	PreP = Chained_Hash_Search( T, Key );
	P=PreP->Next;
	if(P!=NULL)
	{
		PreP->Next=P->Next;
		free(P);
	}
//	else printf("FUCK OFF!!\n");
  
}

//----------------------------------------------------
// Inspect the hash table.

void
DumpTable (HashTable T)
{ Position P;
  List L;
  int i;

  for( i = 0 ; i < T->TableSize; i++ )
    { L = T->TheLists[i ];
      P = L->Next;
      printf("%4d:", i);
      while( P != NULL )
	{ printf(" %4d  ", Retrieve(P));
	  P = P->Next;
	}
      printf("\n");
    }
}

//----------------------------------------------------
//#define NumItems 100

ElementType compare (const void * a, const void * b)
{
  return ( *(ElementType*)a - *(ElementType*)b );
}

void FUCKSORT(HashTable T)
{
	Position P;
	List L;
	int i;
	int c=0;
	for( i = 0 ; i < T->TableSize; i++ )
    { 
	  L = T->TheLists[i ];
      P = L->Next;
		while( P != NULL )
		{ 
		s[c]=Retrieve(P);
		c++;
		P = P->Next;
		}
    }
	qsort (s,c, sizeof(ElementType), compare);
	printf("%d\n",c);
	for(i=0;i<c;i++)
	{
		printf("%d\n",s[i]);
	}
}
main( )
{
  HashTable T;
  Position P;
  List L;
  int i;
  int CurrentSize,Delsize,NumItems;
  ElementType delkey,insertKey;
	scanf("%d",&NumItems);
  T = InitializeTable( CurrentSize=1023);
  //srand(time(0));
  for( i = 0; i < NumItems; i++ )
  {
		scanf("%d",&insertKey);
      Chained_Hash_Insert( T, insertKey);
	  
  }
  //printf("Dump the hash table after insertions.\n");
  //DumpTable (T); 
  //printf("Type in the key to be deleted:\n");
  
  scanf("%d", &Delsize);
  for(i=0;i<Delsize;i++)
    {
		scanf("%d",&delkey);
		Chained_Hash_Delete(T, delkey);
      //DumpTable(T);
      //printf("Type in the key to be deleted:\n");
      
    }
    FUCKSORT(T);
  //printf( "End of program.\n" );
  //system("pause");
  return 0;
}
