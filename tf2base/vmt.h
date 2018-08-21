#pragma once

#include "stdafx.h"

class vmt_t
{
private:
	void ***_inst, **_old, **_new;
	int _size;
	bool _hook;
public:
	vmt_t( const void* inst )
	{
		_hook	= false;
		_inst	= ( void*** )( inst );
		_old	= *_inst;
		_size	= this->countVMT( _old );
		_new	= new void*[_size + 3];
		_new[2]	= _old[-1];
		
		for( int i = 0; i < _size; ++i ) _new[i + 3] = _old[i];
	}
	~vmt_t()
	{
		if( this->unHook() )
		{
			_inst = 0;
			delete [] _new;
		}
	}

	__forceinline void* getInst()
	{
		return _inst;
	}
	template< typename T > __forceinline T getMethod( int index )
	{
		return ( index < 0 || index > _size || !_old ) ? 0 : ( T )( _old[index] );
	}

	bool reHook()
	{
		if( _inst && !_hook )
		{
			*_inst = _new + 3;
			_hook = true;

			return true;
		}

		return false;
	}
	bool unHook()
	{
		if( _inst )
		{
			if( _hook )
			{
				*_inst = _old;
				_hook = false;
			}

			return true;
		}

		return false;
	}
	void hookMethod( void* newFn, int index )
	{
		if( index < 0 || index > _size || !_new ) return;

		_new[index + 3] = newFn;
	}

	static int countVMT( void** in )
	{
		int count = -1;
		for( ; !IsBadCodePtr( ( FARPROC )( in[count] ) ); ++count );

		return count;
	}
};
