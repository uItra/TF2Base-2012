#pragma once

#include "stdafx.h"

class log_t
{
private:
	std::string _file;
public:
	void init( std::string dir, std::string name )
	{
		_file = dir + name;

		// clear the log file

		std::ofstream init;
		init.open( _file, std::ios::trunc );
		init.close();
	}
	void write( PCHAR fmt, ... )
	{
		std::ofstream out;
		out.open( _file, std::ios::app );

		if( !out.fail() )
		{
			char buf[1024];
			memset( buf, 0, 1024 );

			va_list args;			
			va_start( args, fmt );
			_vsnprintf( buf, 1024, fmt, args );
			va_end( args );

			tm* time = _util::getLocalTime();

			out << _util::formatString( "[%02d:%02d:%02d] ", time->tm_hour, time->tm_min, time->tm_sec ) << buf << std::endl;
			out.close();
		}
	}
};
