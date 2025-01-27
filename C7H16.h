/////// /////// /////// /////// /////// /////// ///////
///  C7H16    H   H   H   H   H   H   H
///           |   |   |   |   |   |   |
///       H - C - C - C - C - C - C - C - H
///           |   |   |   |   |   |   |
///           H   H   H   H   H   H   H
/////// (hept render) by @ENDESGA 2024 :::.

/////// /////// /////// /////// /////// /////// ///////
///////  only define once
#ifndef HEPT_RENDER
#define HEPT_RENDER

/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
/// check operating system

#define OS_LINUX 0
#define OS_WINDOWS 0
#define OS_MACOS 0
#define OS_UNKNOWN 0

#if defined( __linux__ )
#undef OS_LINUX
#define OS_LINUX 1
#define OS_NAME "Linux"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
//
#elif defined( _WIN32 )
#undef OS_WINDOWS
#define OS_WINDOWS 1
#define OS_NAME "Windows"
#undef UNICODE
#undef _UNICODE
#define WINDOWS_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#define NOGDICAPMASKS
#define NOMINMAX
#pragma pack( push, 8 )
#include <windows.h>
#undef near
#undef far
#pragma pack( pop )
//
#elif defined( __APPLE__ )
#undef OS_MACOS
#define OS_MACOS 1
#define OS_NAME "macOS"
//
#else
#undef OS_UNKNOWN
#define OS_UNKNOWN 1
#define OS_NAME "unknown"
#endif

/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

#include "H_new.h"

/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

// // // // // // //
// print to terminal

fn _print( in byte ref bytes, in u2 size )
{
#if OS_LINUX
	write( 1, bytes, pick( size is 0, measure_bytes( bytes ), size ) );
#elif OS_WINDOWS
	perm HANDLE console = null;
	do_once console = GetStdHandle( STD_OUTPUT_HANDLE );
	WriteConsoleA( console, bytes,
		pick( size is 0, measure_bytes( bytes ), size ), NULL, NULL );
#endif
}

#define print( BYTES, ... ) _print( BYTES, DEFAULTS( ( 0 ), __VA_ARGS__ ) )

#define print_nl( ... ) print( "\n", 1 )

fn print_format( in byte ref in_bytes, ... )
{
	if_null( in_bytes ) out;
	//
	args_start( in_bytes );
	perm byte buffer[1024] = { 0 };
	format_bytes( in_bytes, buffer, _args );
	print( buffer );
}

// // // // // // //
// print type functions

#define print_byte( ... ) print_format( "|b", byte( __VA_ARGS__ ) )
#define print_u1( ... ) print_format( "|u1", u1( __VA_ARGS__ ) )
#define print_u1_2d( _2d ) print_format( "|u1, |u1", u1( _2d.x ), u1( _2d.y ) )
#define print_u1_3d( _3d ) \
	print_format( "|u1, |u1, |u1", u1( _3d.x ), u1( _3d.y ), u1( _3d.z ) )
#define print_u1_4d( _4d ) \
	print_format( \
		"|u1, |u1, |u1, |u1", u1( _4d.x ), u1( _4d.y ), u1( _4d.z ), u1( _4d.w ) )

#define print_s1( ... ) print_format( "|s1", s1( __VA_ARGS__ ) )
#define print_s1_2d( _2d ) print_format( "|s1, |s1", s1( _2d.x ), s1( _2d.y ) )
#define print_s1_3d( _3d ) \
	print_format( "|s1, |s1, |s1", s1( _3d.x ), s1( _3d.y ), s1( _3d.z ) )
#define print_s1_4d( _4d ) \
	print_format( \
		"|s1, |s1, |s1, |s1", s1( _4d.x ), s1( _4d.y ), s1( _4d.z ), s1( _4d.w ) )

#define print_u2( ... ) print_format( "|u2", u2( __VA_ARGS__ ) )
#define print_u2_2d( _2d ) print_format( "|u2, |u2", u2( _2d.x ), u2( _2d.y ) )
#define print_u2_3d( _3d ) \
	print_format( "|u2, |u2, |u2", u2( _3d.x ), u2( _3d.y ), u2( _3d.z ) )
#define print_u2_4d( _4d ) \
	print_format( \
		"|u2, |u2, |u2, |u2", u2( _4d.x ), u2( _4d.y ), u2( _4d.z ), u2( _4d.w ) )

#define print_s2( ... ) print_format( "|s2", s2( __VA_ARGS__ ) )
#define print_s2_2d( _2d ) print_format( "|s2, |s2", s2( _2d.x ), s2( _2d.y ) )
#define print_s2_3d( _3d ) \
	print_format( "|s2, |s2, |s2", s2( _3d.x ), s2( _3d.y ), s2( _3d.z ) )
#define print_s2_4d( _4d ) \
	print_format( \
		"|s2, |s2, |s2, |s2", s2( _4d.x ), s2( _4d.y ), s2( _4d.z ), s2( _4d.w ) )

#define print_u4( ... ) print_format( "|u4", u4( __VA_ARGS__ ) )
#define print_u4_2d( _2d ) \
	print_format( "{|u4, |u4}", u4( _2d.x ), u4( _2d.y ) )
#define print_u4_3d( _3d ) \
	print_format( "{|u4, |u4, |u4}", u4( _3d.x ), u4( _3d.y ), u4( _3d.z ) )
#define print_u4_4d( _4d ) \
	print_format( "{|u4, |u4, |u4, |u4}", u4( _4d.x ), u4( _4d.y ), u4( _4d.z ), \
		u4( _4d.w ) )

#define print_s4( ... ) print_format( "|s4", s4( __VA_ARGS__ ) )
#define print_s4_2d( _2d ) print_format( "|s4, |s4", s4( _2d.x ), s4( _2d.y ) )
#define print_s4_3d( _3d ) \
	print_format( "|s4, |s4, |s4", s4( _3d.x ), s4( _3d.y ), s4( _3d.z ) )
#define print_s4_4d( _4d ) \
	print_format( \
		"|s4, |s4, |s4, |s4", s4( _4d.x ), s4( _4d.y ), s4( _4d.z ), s4( _4d.w ) )

#define print_f4( ... ) print_format( "|f4", f4( __VA_ARGS__ ) )
#define print_f4_2d( _2d ) print_format( "|f4, |f4", f4( _2d.x ), f4( _2d.y ) )
#define print_f4_3d( _3d ) \
	print_format( "|f4, |f4, |f4", f4( _3d.x ), f4( _3d.y ), f4( _3d.z ) )
#define print_f4_4d( _4d ) \
	print_format( \
		"|f4, |f4, |f4, |f4", f4( _4d.x ), f4( _4d.y ), f4( _4d.z ), f4( _4d.w ) )

#define print_u8( ... ) print_format( "|u8", u8( __VA_ARGS__ ) )
#define print_u8_2d( _2d ) print_format( "|u8, |u8", u8( _2d.x ), u8( _2d.y ) )
#define print_u8_3d( _3d ) \
	print_format( "|u8, |u8, |u8", u8( _3d.x ), u8( _3d.y ), u8( _3d.z ) )
#define print_u8_4d( _4d ) \
	print_format( \
		"|u8, |u8, |u8, |u8", u8( _4d.x ), u8( _4d.y ), u8( _4d.z ), u8( _4d.w ) )

#define print_s8( ... ) print_format( "|s8", s8( __VA_ARGS__ ) )
#define print_s8_2d( _2d ) print_format( "|s8, |s8", s8( _2d.x ), s8( _2d.y ) )
#define print_s8_3d( _3d ) \
	print_format( "|s8, |s8, |s8", s8( _3d.x ), s8( _3d.y ), s8( _3d.z ) )
#define print_s8_4d( _4d ) \
	print_format( \
		"|s8, |s8, |s8, |s8", s8( _4d.x ), s8( _4d.y ), s8( _4d.z ), s8( _4d.w ) )

#define print_f8( ... ) print_format( "|f8", f8( __VA_ARGS__ ) )
#define print_f8_2d( _2d ) print_format( "|f8, |f8", f8( _2d.x ), f8( _2d.y ) )
#define print_f8_3d( _3d ) \
	print_format( "|f8, |f8, |f8", f8( _3d.x ), f8( _3d.y ), f8( _3d.z ) )
#define print_f8_4d( _4d ) \
	print_format( \
		"|f8, |f8, |f8, |f8", f8( _4d.x ), f8( _4d.y ), f8( _4d.z ), f8( _4d.w ) )

// // // // // // //

#define print_list( LIST, TYPE, PRINT_FN ) \
	DEF_START \
	print( "[" ); \
	for( u4 i = 0; i < ( LIST )->size; ++i ) \
	{ \
		if( i ) print( ", " ); \
		PRINT_FN( list_get( LIST, TYPE, i ) ); \
	} \
	print( "]\n" ); \
	DEF_END

#define print_pile( PILE, TYPE, PRINT_FN, SKIP_IF ) \
	DEF_START \
	print_byte( '{' ); \
	temp u4 comma = 0; \
	iter_pile( PILE, i ) \
	{ \
		temp const u4 pos = i_data_pos; \
		get_pile_iter( TYPE, val, i, SKIP_IF ); \
		if( comma ) print( ", " ); \
		print( "<" ); \
		print_u4( pos ); \
		print( ">" ); \
		PRINT_FN( val ); \
		comma = 1; \
	} \
	print_byte( '}' ); \
	DEF_END

#define print_text( TEXT ) print( ( TEXT )->data )

/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
#endif // HEPT_RENDER
/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///