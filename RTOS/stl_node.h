#ifndef STL_NODE_H
#define STL_NODE_H
#ifdef _WIN32
#pragma once
#endif

#include <stdlib.h>

#define RTX_STL_INIT_NODE()	next = NULL; \
							prev = NULL;

namespace rtx_stl
{
	template <typename N> class node
	{
	private:
		N * value;

	protected:
		node * next;
		node * prev;

	public:
		N * get();
		void set( N * );

		node<N> operator = ( const node<N> & );
		node<N> operator = ( const N & );

		node();
		node( const node * );
		node( const node & );
		node( const N & );
		~node();

		template <typename T> friend class stack;
		template <typename T> friend class queue;
		template <typename T> friend class pqueue;
		template <typename T> friend class list;
	};

	template <typename N> node<N> node<N>::operator = ( const node<N> & x )
	{
		*value = x.value;
	}

	template <typename N> node<N> node<N>::operator = ( const N & x )
	{
		*value = x;
	}

	template <typename N> N * node<N>::get()
	{
		return value;
	}

	template <typename N> void node<N>::set( N * x )
	{
		value = x;
	}

	template <typename N> node<N>::node() : value( NULL )
	{
		RTX_STL_INIT_NODE();
	}

	template <typename N> node<N>::node( const node<N> * x ) : value( new N )
	{
		*value = x->value;

		RTX_STL_INIT_NODE();
	}

	template <typename N> node<N>::node( const node<N> & x ) : value( new N )
	{
		*value = x.value;

		RTX_STL_INIT_NODE();
	}

	template <typename N> node<N>::node( const N & x ) : value( new N )
	{
		*value = x;

		RTX_STL_INIT_NODE();
	}

	template <typename N> node<N>::~node()
	{
	//	if ( value != NULL )
	//		delete value;
	}
}
#ifdef _WIN32
;
#endif

#endif
