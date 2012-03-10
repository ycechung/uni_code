#include "test_suite.h"
#include "rtx.h"

using namespace rtx_stl;

void test_eugene()
{
#if 000
	node<int> cells[5] = { 1, 2, 3 , 4, 5 };
	node<int> g10[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	list <int> li;
	for ( int i = 0; i < 3; i++ )
		li.push_back( &cells[i] );
	li.push_back( &cells[3] );
	li.push_front( &cells[4] );
	// pop back
	for ( int j=0; j < 5; j++)
	{
		std::cout << "Value of " << j+1 << "th term in the list: " <<*li.pop_back()->get() << std::endl;
		std::cout << "Size of the list is now: " << li.size() << std::endl;
	}
	for (int k=0; k < 10; k++) // 9 7 5 3 1 2 4 6 8 10
	{
		if (k % 2 == 0) // if even
		{
			li.push_back( &g10[k] );
		}else{ // if odd
			li.push_front( &g10[k] );
		}
	}
	std::cout << " - - - - - - - - - - - -" << std::endl;
	for ( int m=0; m < 10; m++) // output - 9 7 5 3 1
	{
		std::cout << "Value of " << m+1 << "th term in the list: " <<*li.pop_front()->get() << std::endl;
		std::cout << "Size of the list is now: " << li.size() << std::endl;
	}
#endif
}

void test_queue()
{
#if 0

	int values[3] = { 8, 9, 10 };
	node<int> * cells[3];
	for ( int i = 0; i < 3; i++ )
		cells[i] = new node<int>( values[i] );

	queue <int> wut;
	for ( int i = 0; i < 3; i++ )
		wut.enqueue( cells[i] );



	// omg using stl, remove this before the 241nazis come get us
	std::cout << *wut.dequeue()->get() << std::endl;
	std::cout << *wut.dequeue()->get() << std::endl;
	std::cout << *wut.dequeue()->get() << std::endl;

	wut.clear();
	std::cout << wut.empty() << std::endl;
#endif
}

bool sort_wut( int * a, int * b )
{
	return *a < *b;
}

void test_pqueue()
{
	int values[3] = { 7, 3, 5 };
	node<int> * cells[3];
	for ( int i = 0; i < 3; i++ )
		cells[i] = new node<int>( values[i] );

	pqueue <int> wut( &sort_wut );
	for ( int i = 0; i < 3; i++ )
		wut.enqueue( cells[i] );



	// omg using stl, remove this before the 241nazis come get us
	std::cout << *wut.dequeue()->get() << std::endl;
	std::cout << *wut.dequeue()->get() << std::endl;
	std::cout << *wut.dequeue()->get() << std::endl;

	wut.clear();
	std::cout << wut.empty() << std::endl;
}

void test_list()
{
#if 0
	node<int> cells[3] = { 1, 2, 3 };

	list <int> wut;
	for ( int i = 0; i < 3; i++ )
		wut.push_front( &cells[i] );

	std::cout << *wut.pop_back()->get() << std::endl;
	std::cout << *wut.pop_back()->get() << std::endl;
	std::cout << *wut.pop_back()->get() << std::endl;
#endif
	//wut.push_back( 5 );
	//wut.push_front( 8 );
	//wut.push_back( 9 ); // 8 5 9
	//std::cout << wut.pop_back() << std::endl; // 9
	//std::cout << wut.pop_front() << std::endl; // 8
	//std::cout << wut.pop_back() << std::endl; // 5
}

void test_stack()
{
#if 0
	stack <int> wut;

	node<int> cells[3] = { 4, 5, 6 };

	for ( int i = 0; i < 3; i++ )
		wut.push( &cells[i] );

	std::cout << *wut.peek( 1 )->get() << std::endl; // 5
	std::cout << *wut.pop()->get() << std::endl; // 7
	std::cout << *wut.pop()->get() << std::endl; // 5
	std::cout << *wut.pop()->get() << std::endl; // 3
#endif
}

void test_memory()
{
#if 000
	MMemory * M_Memory = ( MMemory * ) MModule<MMemory>::instance();
	MMemory::init();
	char * test1 = ( char * ) M_Memory->malloc( sizeof( char ) * 64 );
	char * test2 = ( char * ) M_Memory->malloc( sizeof( char ) * 64 );
	char * test3 = ( char * ) M_Memory->malloc( sizeof( char ) * 64 );

#ifdef _WIN32
// We don't care since we're just doing static copying.
#pragma warning ( disable : 4996 )
#endif
	strcpy( test1, "wut is this" );
	strcpy( test2, "zomg hopefully no access violation" );
	strcpy( test3, "gay gay gay" );

	std::cout << test1 << std::endl;
	std::cout << test2 << std::endl;
	std::cout << test3 << std::endl;

	M_Memory->free( test1 );
	M_Memory->free( test2 );
	M_Memory->free( test3 );

	//
#endif
}


void test_queue1()
{
	/*

	node<int> cells[3] = { 1, 2, 3 };
	node<int> cells2[5] = { 1, 2, 3, 4, 5}
	queue <int> q1;
	for ( int i = 0; i < 3; i++ )
		q1.enqueue( &cells[i] );

	for ( int i = 0; i < 5; i++ )
		q1.enqueue( &cells2[i] );

	std::cout << *q1.dequeue()->get() << std::endl;
	std::cout << *q2.dequeue()->get() << std::endl;
	std::cout << *q3.dequeue()->get() << std::endl;
	*/
}
void test_queue2()
{
}
void test_queue3()
{
}
void test_queue4()
{
}
void test_queue5()
{
}
void test_queue6()
{
}
void test_queue7()
{
}
void test_queue8()
{
}
void test_queue9()
{
}
void test_queue10()
{
}
void test_list1()
{
#if 0
    node <int> * g10[10];
	int values[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	for (int x = 0; x < 10; x++)
		g10[x] = new node<int>( values[x] );

	node<int> cells[5] = { 1, 2, 3 , 4, 5 };
	list <int> li;
	for ( int i = 0; i < 3; i++ )
		li.push_back( &cells[i] );
	li.push_back( &cells[3] );
	li.push_front( &cells[4] );
	// pop back
	for ( int j=0; j < 5; j++)
	{
		std::cout << "Value of " << j+1 << "th term in the list: " <<*li.pop_back()->get() << std::endl;
		std::cout << "Size of the list is now: " << li.size() << std::endl;
	}
	for (int k=0; k < 10; k++) // 6 4 2 1 3 5
	{
		if (k % 2 == 0) // if even
		{
			li.push_back( g10[k] );
		}else{ // if odd
			li.push_front( g10[k] );
		}
	}
	std::cout << " - - - - - - - - - - - -" << std::endl;
	for ( int m=0; m < 5; m++) // output - 10 8 6 4 2
	{
		std::cout << "Value of " << m+1 << "th term in the list: " <<*li.pop_front()->get() << std::endl;
		std::cout << "Size of the list is now: " << li.size() << std::endl;
	}
	//stdio.h -> int sscanf ( const char * str, constant char * format, ...);
	/*
		expeceted output
	Value of 1th term in the list: 4
	Size of the list is now: 4
	Value of 2th term in the list: 3
	Size of the list is now: 3
	Value of 3th term in the list: 2
	Size of the list is now: 2
	Value of 4th term in the list: 1
	Size of the list is now: 1
	Value of 5th term in the list: 5
	Size of the list is now: 0
	- - - - - - - - - - - -
	Value of 1th term in the list: 10
	Size of the list is now: 9
	Value of 2th term in the list: 8
	Size of the list is now: 8
	Value of 3th term in the list: 6
	Size of the list is now: 7
	Value of 4th term in the list: 4
	Size of the list is now: 6
	Value of 5th term in the list: 2
	Size of the list is now: 5
	*/
#endif
}
void test_list2()
{
    	node<char> *cells[5];
	node<int> *g10[10];
	int value1[5] = { 'a', 'b', 'c', 'd', 'e'};
	int value2[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	for (int a = 0; a < 10; a++)
	{
		g10[a] = new node<int>( value2[a] );
		if (a < 5)
			cells[a] = new node<char>( value1[a] );
	}

	list <int> li2;
	for ( int i = 0; i < 10; i++ ) //1 2 3 4 .. 10
		li2.push_back( g10[i] );

	for ( int m=0; m < 5; m++) // output one then the characters
	{
		std::cout << "Value of " << m+1 << "th term in the list: " <<*li2.pop_front()->get() << std::endl;
		std::cout << "Size of the list is now: " << li2.size() << std::endl;
		//li2.push_front( atoi(cells[m]) );
	}

	//
	//node<T> * get( int );
	//	void insert( int, node<T> * );
	//	node<T> * remove( int );
	//	void clear();
	//	bool empty();
	//int size();
}
void test_list3()
{
}
void test_list4()
{
}
void test_list5()
{
}
void test_list6()
{
}
void test_list7()
{
}
void test_list8()
{
}
void test_list9()
{
}
void test_list10()
{
}
void test_stack1()
{
#if 0
    stack <int> s;
	node<int> g10[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	for ( int i = 0; i < 10; i++ )
	{
		s.push( &g10[i] );
		s.peek(i); // should output 10 to 1
	}

/*
		node<T> * peek( int );
		void push( node<T> * );
		node<T> * pop();
		void clear();
		bool empty();
		int size();

	std::cout << *s.peek( 1 )->get() << std::endl; // 5
	std::cout << *s.pop()->get() << std::endl; // 7
	std::cout << *s.pop()->get() << std::endl; // 5
	std::cout << *s.pop()->get() << std::endl; // 3
*/
#endif
}
void test_stack2()
{
}
void test_stack3()
{
}
void test_stack4()
{
}
void test_stack5()
{
}
void test_stack6()
{
}
void test_stack7()
{
}
void test_stack8()
{
}
void test_stack9()
{
}
void test_stack10()
{
}
void test_memory1()
{
}
void test_memory2()
{
}
void test_memory3()
{
}
void test_memory4()
{
}
void test_memory5()
{
}
void test_memory6()
{
}
void test_memory7()
{
}
void test_memory8()
{
}
void test_memory9()
{
}
void test_memory10()
{
}
