#ifndef STL_LIST_H
#define STL_LIST_H
#ifdef _WIN32
#pragma once
#endif

#include <stdlib.h>

//#include "stl_exception.h"
#include "stl_node.h"

namespace rtx_stl
{
	// Doug 9/21/2010
	//	Not tested very heavily. I don't suggest trusting this.
	//	Unlike the previously defined class (node), you
	//	are intended to use this outside of this file.
	template <typename T> class list
	{
	private:
		node<T> * head;
		node<T> * tail;
		node<T> * seek( int );
		int num;

	public:
		// Constructors.
		list();
		~list();

		node<T> * get( int );
		void insert( int, node<T> * );
		node<T> * remove( int );
		void push_front( node<T> * );
		node<T> * pop_front();
		void push_back( node<T> * );
		node<T> * pop_back();
		void clear();
		bool empty();
		int size();
	};
}
#ifdef _WIN32
;
#endif

// Doug 9/21/2010
//	MSVC is retarded and won't let you separate template declarations
//	and definitions, so we have to put the implementation in this header...
//	I separated it in case it's actually me who's retarded and we can
//	make this less horrible later.
#define RTX_STL_INIT_LIST()	head = NULL; \
							tail = NULL; \
							num = 0;

namespace rtx_stl
{
	//////////////////////////////////
	// Queue functions              //
	//////////////////////////////////

	template <typename T> list<T>::list()
	{
		RTX_STL_INIT_LIST();
	}

	template <typename T> list<T>::~list()
	{
		clear();
	}

	template <typename T> void list<T>::clear()
	{
		node<T> * current = head;
		while ( current != NULL )
		{
			// Compiler will optimize this out.
			node<T> * successive = current;
			current = current->next;
			delete successive;
		}

		RTX_STL_INIT_LIST();
	}
	
	template <typename T> node<T> * list<T>::seek( int position )
	{
		node<T> * current = head;
		for ( int i = 0; i < position && current != NULL; i++ )
		{
			if ( current->next == NULL )
				return current;

			current = current->next;
		}

		return current;
	}

	template <typename T> node<T> * list<T>::get( int position )
	{
		if ( empty() )
			throw "List is empty";

		if ( position < 0 || position >= num )
			throw "Out of bounds";

		return seek( position );
	}

	template <typename T> void list<T>::insert( int position, node<T> * x )
	{
		if ( position < 0 || position > num )
			throw "Out of bounds";

		if ( x == NULL )
			throw "Invalid data";

		x->next = NULL;
		x->prev = NULL;

		node<T> * current = seek( position );

		if ( num && position == num )
		{
			current->next = x;
			x->prev = current;
		}
		else if ( current != NULL )
		{
			x->next = current;

			if ( current->prev != NULL )
			{
				current->prev->next = x;
				x->prev = current->prev;
			}

			current->prev = x;
		}

		if ( head == NULL || position == 0 )
			head = x;

		if ( tail == NULL || position == num )
			tail = x;

		num++;
	}

	template <typename T> node<T> * list<T>::remove( int position )
	{
		if ( empty() )
			throw "List is empty";
		
		if ( position < 0 || position >= num )
			throw "Out of bounds";

		node<T> * current = seek( position );

		if ( current->next != NULL )
			current->next->prev = current->prev;

		if ( current->prev != NULL )
			current->prev->next = current->next;

		if ( current == head )
			head = current->next;

		if ( position == num - 1 )
			tail = current->prev;

		num--;

		return current;
	}

	template <typename T> void list<T>::push_front( node<T> * x )
	{
		insert( 0, x );
	}

	template <typename T> node<T> * list<T>::pop_front()
	{
		return remove( 0 );
	}

	template <typename T> void list<T>::push_back( node<T> * x )
	{
		insert( num, x );
	}

	template <typename T> node<T> * list<T>::pop_back()
	{
		return remove( num - 1 );
	}

	template <typename T> bool list<T>::empty()
	{
		return head == NULL;
	}

	template <typename T> int list<T>::size()
	{
		return num;
	}
}
#ifdef _WIN32
;
#endif

#endif
