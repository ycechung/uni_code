#ifndef STL_QUEUE_H
#define STL_QUEUE_H
#ifdef _WIN32
#pragma once
#endif

#include <stdlib.h>

#include "stl_node.h"

namespace rtx_stl
{
	// Doug 9/21/2010
	//	Not tested very heavily. I don't suggest trusting this.
	//	Unlike the previously defined class (node), you
	//	are intended to use this outside of this file.
	template <typename T> class queue
	{
	private:
		node<T> * head;
		node<T> * tail;
		int num;

		node<T> * seek( int );

	public:
		// Constructors.
		queue();
		~queue();

		void enqueue( node<T> * );
		node<T> * dequeue();
		node<T> * peek( int );
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
#define RTX_STL_INIT_QUEUE()	head = NULL; \
								tail = NULL; \
								num = 0;

namespace rtx_stl
{
	//////////////////////////////////
	// Queue functions              //
	//////////////////////////////////

	template <typename T> queue<T>::queue()
	{
		RTX_STL_INIT_QUEUE();
	}

	template <typename T> queue<T>::~queue()
	{
		clear();
	}

	template <typename T> void queue<T>::clear()
	{
		node<T> * current = head;
		while ( current != NULL )
		{
			// Compiler will optimize this out.
			node<T> * del = current;
			current = current->next;
			delete del;
		}

		RTX_STL_INIT_QUEUE();
	}

	template <typename T> node<T> * queue<T>::peek( int position )
	{
		if ( empty() )
			throw "Queue is empty";

		if ( position < 0 || position >= num )
			throw "Out of bounds";

		return seek( position );
	}

	template <typename T> node<T> * queue<T>::seek( int position )
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

	template <typename T> void queue<T>::enqueue( node<T> * x )
	{
		if ( x == NULL )
			throw "Invalid data";

		x->next = NULL;
		x->prev = NULL;

		if ( head == NULL )
			head = x;

		if ( tail != NULL )
			tail->next = x;

		tail = x;

		num++;
	}

	template <typename T> node<T> * queue<T>::dequeue()
	{
		if ( empty() )
			throw "Queue is empty";

		node<T> * current = head;
		head = head->next;

		if ( current == tail )
			tail = NULL;

		num--;

		return current;
	}

	template <typename T> bool queue<T>::empty()
	{
		return num ? false : true;
	}

	template <typename T> int queue<T>::size()
	{
		return num;
	}
}
#ifdef _WIN32
;
#endif

#endif
