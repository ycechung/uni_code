#ifndef STL_STACK_H
#define STL_STACK_H
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
	template <typename T> class stack
	{
	private:
		node<T> * top;
		node<T> * seek( int );
		int num;

	public:
		// Constructors.
		stack();
		~stack();

		node<T> * peek( int );
		void push( node<T> * );
		node<T> * pop();
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
#define RTX_STL_INIT_STACK()	top = NULL; \
								num = 0;

namespace rtx_stl
{
	//////////////////////////////////
	// Queue functions              //
	//////////////////////////////////

	template <typename T> stack<T>::stack()
	{
		RTX_STL_INIT_STACK();
	}

	template <typename T> stack<T>::~stack()
	{
		clear();
	}

	template <typename T> void stack<T>::clear()
	{
		node<T> * current = top;
		while ( current != NULL )
		{
			// Compiler will optimize this out.
			node<T> * successive = current;
			current = current->next;
			delete successive;
		}

		RTX_STL_INIT_STACK();
	}
	
	template <typename T> node<T> * stack<T>::seek( int position )
	{
		node<T> * current = top;
		for ( int i = 0; i < position && current != NULL; i++ )
		{
			if ( current->next == NULL )
				return current;

			current = current->next;
		}

		return current;
	}

	template <typename T> node<T> * stack<T>::peek( int position )
	{
		if ( empty() )
			throw "Stack is empty";

		if ( position < 0 || position >= num )
			throw "Out of bounds";

		return seek( position );
	}

	template <typename T> void stack<T>::push( node<T> * x )
	{
		if ( x == NULL )
			throw "Invalid data";

		x->next = NULL;
		x->prev = NULL;

		x->next = top;
		top = x;
		num++;
	}

	template <typename T> node<T> * stack<T>::pop()
	{
		if ( empty() )
			throw "Stack is empty";

		node<T> * current = top;
		top = current->next;

		num--;

		return current;
	}

	template <typename T> bool stack<T>::empty()
	{
		return top == NULL;
	}

	template <typename T> int stack<T>::size()
	{
		return num;
	}
}
#ifdef _WIN32
;
#endif

#endif
