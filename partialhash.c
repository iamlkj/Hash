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
  Position P;
  List L;

  /* 1*/      L = T->TheLists[ Hash( Key, T->TableSize ) ];
  /* 2*/      P = L->Next;
  /* 3*/      while( P != NULL && P->Element != Key )
  /* Probably need strcmp!! */
  /* 4*/          P = P->Next;
  /* 5*/      return P;
}
//---------------------------------------------------

void
Chained_Hash_Insert(HashTable T, ElementType Key)
{
  Position Pos, NewCell;
  List L;
      
  /* 1*/      Pos = Chained_Hash_Search( T, Key );
  /* 2*/      if( Pos == NULL )   /* Key is not found */
    {
  /* 3*/          NewCell = malloc( sizeof( struct ListNode ) );
  /* 4*/          if( NewCell == NULL )
  /* 5*/              printf( "Out of space!!!\n" );
	    else
	      {
  /* 6*/  Missing statement 
  /* 7*/  Missing statement
  /* 8*/  Missing statement
  /* 9*/  Missing statement
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

  // Fill in  Missing codes
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
#define NumItems 100

main( )
{
  HashTable T;
  Position P;
  List L;
  int i;
  int CurrentSize;
  ElementType delkey;

  T = InitializeTable( CurrentSize = 13 );
  srand(time(0));
  for( i = 0; i < NumItems; i++ )
    Chained_Hash_Insert( T, rand() %100 );
  
  printf("Dump the hash table after insertions.\n");
  DumpTable (T); 
  printf("Type in the key to be deleted:\n");
  scanf("%d", &delkey);
  while ( delkey > 0)
    { Chained_Hash_Delete(T, delkey);
      DumpTable(T);
      printf("Type in the key to be deleted:\n");
      scanf("%d", &delkey);
    }
  printf( "End of program.\n" );
  return 0;
}
