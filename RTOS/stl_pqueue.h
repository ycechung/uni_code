#ifndef STL_PQUEUE_H
#define STL_PQUEUE_H
#ifdef _WIN32
#pragma once
#endif

#include <stdlib.h>

#include "stl_node.h"

namespace rtx_stl
{
	// Doug 11/3/2010
	//	Sort function works like this:
	//	A "current" and "new" TC are passed into the sort function.
	//	The function's responsibility is to provide a return value.
	//	Returning "false" indicates that "new" is not greater than
	//	"current". This stops sorting and places it there. The sort
	//	function is only called on enqueue. Note that the prototype
	//	is arranged in such a way that it should be easier to figure
	//	out what's going on. The "current" TC is first, and the "new"
	//	TC is after it. If this is the correct order, true is returned,
	//	otherwise false is returned.
	template <typename T> class pqueue
	{
	private:
		node<T> * head;
		node<T> * seek( int );
		bool ( * sort )( T *, T * );
		int num;

	public:
		// Constructors.
		pqueue();
		pqueue( bool ( * )( T *, T * ) );
		~pqueue();

		void set_sort( bool ( * )( T *, T * ) );

		node<T> * peek( int );
		void enqueue( node<T> * );
		node<T> * dequeue();
		void clear();
		int size();
		bool empty();
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
#define RTX_STL_INIT_PQUEUE()	head = NULL; \
								num = 0;

namespace rtx_stl
{
	//////////////////////////////////
	// Queue functions              //
	//////////////////////////////////

	template <typename T> pqueue<T>::pqueue()
	{
		RTX_STL_INIT_PQUEUE();
	}

	template <typename T> pqueue<T>::pqueue( bool ( *sort_function )( T *, T * ) ) : sort( sort_function )
	{
		RTX_STL_INIT_PQUEUE();
	}

	template <typename T> pqueue<T>::~pqueue()
	{
		clear();
	}

	template <typename T> void pqueue<T>::set_sort( bool ( *sort_function )( T *, T * ) )
	{
		sort = sort_function;
	}

	template <typename T> void pqueue<T>::clear()
	{
		node<T> * current = head;
		while ( current != NULL )
		{
			// Compiler will optimize this out.
			node<T> * del = current;
			current = current->next;
			delete del;
		}

		RTX_STL_INIT_PQUEUE();
	}

	template <typename T> node<T> * pqueue<T>::peek( int position )
	{
		if ( empty() )
			throw "Pqueue is empty";

		if ( position < 0 || position >= num )
			throw "Out of bounds";

		return seek( position );
	}

	template <typename T> node<T> * pqueue<T>::seek( int position )
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

	template <typename T> void pqueue<T>::enqueue( node<T> * x )
	{
		if ( x == NULL )
			throw "Invalid data";

		if ( sort == NULL )
			throw "Sort function undefined";

		x->next = NULL;
		x->prev = NULL;

		node<T> * current = head, * previous = NULL;
		while ( !empty() && current != NULL )
		{
			if ( !sort( current->get(), x->get() ) )
				break;

			previous = current;
			current = current->next;
		}

		if ( empty() || previous == NULL )
		{
			head = x;
			if ( current != NULL )
				x->next = current;
		}

		if ( previous != NULL )
		{
			x->next = previous->next;
			previous->next = x;
		}

		num++;
	}

	template <typename T> node<T> * pqueue<T>::dequeue()
	{
		if ( empty() )
			throw "Pqueue is empty";

		node <T> * current = head;
		head = head->next;

		num--;

		return current;
	}

	template <typename T> bool pqueue<T>::empty()
	{
		return num ? false : true;
	}

	template <typename T> int pqueue<T>::size()
	{
		return num;
	}
}
#ifdef _WIN32
;
#endif

#endif
