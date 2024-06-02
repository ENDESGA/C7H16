/////// /////// /////// /////// /////// /////// ///////
/////// C7H16     H   H   H   H   H   H   H
///////           |   |   |   |   |   |   |
///////       H - C - C - C - C - C - C - C - H
///////           |   |   |   |   |   |   |
///////           H   H   H   H   H   H   H
/////// (heptane) by @ENDESGA 2024 :::. MIT LICENCE

#pragma once
#define C7H16

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//

#define OS_LINUX 0
#define OS_WINDOWS 0
#define OS_MACOS 0
#define OS_OTHER 0

#if defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 ) || defined( __CYGWIN__ ) || defined( __MINGW32__ ) || defined( __WINDOWS__ ) || defined( _WIN64 )
	#undef OS_WINDOWS
	#define OS_WINDOWS 1
#elif defined( __LINUX__ ) || defined( linux ) || defined( __linux ) || defined( __linux__ )
	#undef OS_LINUX
	#define OS_LINUX 1
#elif defined( __MACOSX__ ) || defined( __APPLE__ )
	#undef OS_MACOS
	#define OS_MACOS 1
#else
	#undef OS_OTHER
	#define OS_OTHER 1
#endif

#define COMPILER_MSVC 0
#define COMPILER_TCC 0
#define COMPILER_CLANG 0
#define COMPILER_GCC 0
#define COMPILER_UNKNOWN 0

#if defined( _MSC_VER )
	#undef COMPILER_MSVC
	#define COMPILER_MSVC 1
	#define COMPILER_NAME "MSVC"
#elif defined( __TINYC__ )
	#undef COMPILER_TCC
	#define COMPILER_TCC 1
	#define COMPILER_NAME "TCC"
	#define typeof __typeof__
#elif defined( __clang__ )
	#undef COMPILER_CLANG
	#define COMPILER_CLANG 1
	#define COMPILER_NAME "CLANG"
#elif defined( __GNUC__ )
	#undef COMPILER_GCC
	#define COMPILER_GCC 1
	#define COMPILER_NAME "GCC"
#else
	#undef COMPILER_UNKNOWN
	#define COMPILER_UNKNOWN 1
	#define COMPILER_NAME "UNKNOWN"
#endif

//

#if OS_WINDOWS
	#define _CRT_SECURE_NO_WARNINGS
	#undef UNICODE
	#undef _UNICODE
	#define WIN32_LEAN_AND_MEAN
	#define VC_EXTRALEAN
	#define NOGDICAPMASKS

	#if COMPILER_TCC
		#include <winapi/windows.h>
	#else
		#if COMPILER_MSVC
			#pragma pack( push, 8 )
		#endif
		#include <windows.h>
		#if COMPILER_MSVC
			#pragma pack( pop )
		#endif
	#endif
#elif OS_LINUX
	#include <unistd.h>
	#include <pthread.h>
	#include <X11/Xlib.h>
	#include <X11/keysym.h>
	#include <X11/XKBlib.h>
	#include <X11/Xutil.h>
#else
// macOS includes
#endif

//

/////// /////// /////// /////// /////// /////// ///////

//

#define JOIN( a, ... ) a##__VA_ARGS__

#define GET_ARG0( ... )
#define GET_ARG1( a, ... ) a
#define GET_ARG2( a, b, ... ) b
#define GET_ARG3( a, b, c, ... ) c
#define GET_ARG4( a, b, c, d, ... ) d
#define GET_ARG5( a, b, c, d, e, ... ) e
#define GET_ARG6( a, b, c, d, e, f, ... ) f
#define GET_ARG7( a, b, c, d, e, f, g, ... ) g
#define GET_ARG8( a, b, c, d, e, f, g, h, ... ) h
#define GET_ARG9( a, b, c, d, e, f, g, h, i, ... ) i
#define GET_ARG10( a, b, c, d, e, f, g, h, i, j, ... ) j
#define GET_ARG11( a, b, c, d, e, f, g, h, i, j, k, ... ) k
#define GET_ARG12( a, b, c, d, e, f, g, h, i, j, k, l, ... ) l
#define GET_ARG13( a, b, c, d, e, f, g, h, i, j, k, l, m, ... ) m
#define GET_ARG14( a, b, c, d, e, f, g, h, i, j, k, l, m, n, ... ) n
#define GET_ARG15( a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, ... ) o
#define GET_ARG16( a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, ... ) p
#define GET_ARG17( a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, ... ) q

#define SKIP_ARG1( ARG, ... ) __VA_ARGS__

#define COMMA ,
#define COMMA_IF_ARGS( ... ) _COMMA_IF_ARGS( GET_ARG1( __VA_ARGS__ ) )
#define _COMMA_IF_ARGS( ... ) _COMMA_IF_ARGS_EVAL( GET_ARG1 __VA_ARGS__( COMMA ) )
#define _COMMA_IF_ARGS_EVAL( ... ) GET_ARG2( __VA_ARGS__, COMMA )

#define COUNT_ARGS( ... ) _COUNT_ARGS_EVAL( __VA_ARGS__ COMMA_IF_ARGS( __VA_ARGS__ ) )
#define _COUNT_ARGS_EVAL( ... ) GET_ARG17( __VA_ARGS__ 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 )

//

#define DEFAULTS( DEFS, ... ) _DEFAULTS_MAKE( COUNT_ARGS DEFS, DEFS, __VA_ARGS__ )
#define _DEFAULTS_MAKE( COUNT, DEFS, ... ) JOIN( _DEFAULTS_, COUNT )( DEFS, __VA_ARGS__ )
#define _DEFAULTS_PARAM( DEFS, ... ) _DEFAULTS_PARAM_EVAL( GET_ARG1 DEFS, _ COMMA_IF_ARGS( __VA_ARGS__ ) __VA_ARGS__ )
#define _DEFAULTS_PARAM_EVAL( DEF, ... ) GET_ARG2( __VA_ARGS__, DEF )
#define _DEFAULTS_0( DEFS, ... )
#define _DEFAULTS_1( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ )
#define _DEFAULTS_2( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_1( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_3( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_2( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_4( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_3( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_5( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_4( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_6( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_5( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_7( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_6( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_8( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_7( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_9( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_8( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_10( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_9( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_11( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_10( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_12( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_11( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_13( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_12( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_14( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_13( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_15( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_14( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )
#define _DEFAULTS_16( DEFS, ... ) _DEFAULTS_PARAM( DEFS, __VA_ARGS__ ), _DEFAULTS_15( ( SKIP_ARG1 DEFS ), SKIP_ARG1( __VA_ARGS__ ) )

//

#define SYMBOL_CHAIN( BEFORE, MIDDLE, AFTER, ... ) _SYMBOL_MAKE( COUNT_ARGS( __VA_ARGS__ ) )( BEFORE, MIDDLE, AFTER, __VA_ARGS__ )
#define _SYMBOL_MAKE( COUNT ) JOIN( _SYMBOL_, COUNT )
#define _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, B ) _SYMBOL_1( BEFORE, MIDDLE, AFTER, A ) MIDDLE B
#define _SYMBOL_0( BEFORE, MIDDLE, AFTER, ... ) __VA_ARGS__
#define _SYMBOL_1( BEFORE, MIDDLE, AFTER, A ) ( BEFORE( A ) AFTER )
#define _SYMBOL_2( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_1( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_3( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_2( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_4( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_3( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_5( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_4( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_6( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_5( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_7( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_6( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_8( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_7( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_9( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_8( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_10( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_9( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_11( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_10( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_12( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_11( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_13( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_12( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_14( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_13( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_15( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_14( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )
#define _SYMBOL_16( BEFORE, MIDDLE, AFTER, A, ... ) _JOIN_SYMBOL( BEFORE, MIDDLE, AFTER, A, _SYMBOL_15( BEFORE, MIDDLE, AFTER, __VA_ARGS__ ) )

//

/////// /////// /////// /////// /////// /////// ///////

//

#define _require_semicolon \
	do {                     \
	} while( no )

//

#define ref *const __restrict
#define mutable_ref *

#define ref_of( ... ) ( &__VA_ARGS__ )
#define val_of( ... ) ( *__VA_ARGS__ )
#define size_of( ... ) to_u4( sizeof( __VA_ARGS__ ) )
#define type_of( ... ) typeof( __VA_ARGS__ )

#define type_from( ... ) typedef type_of( __VA_ARGS__ )

#define to( TYPE, ... ) ( TYPE )( __VA_ARGS__ )
#define cast( TYPE, ... ) val_of( to( TYPE mutable_ref, ref_of( __VA_ARGS__ ) ) )

//

type_from( void ) _;
#define null to( _ ref, 0 )
#define print_ref( ... ) print( "%p", to( _ ref, __VA_ARGS__ ) )

// 1 byte
type_from( unsigned char ) u1;
#define to_u1( ... ) to( u1, __VA_ARGS__ )
#define u1_size ( size_of( u1 ) )
#define u1_min ( 0 )
#define u1_max ( 255 )
#define print_u1( ... ) print( "%c", to_u1( __VA_ARGS__ ) )

type_from( signed char ) s1;
#define to_s1( ... ) to( s1, __VA_ARGS__ )
#define s1_size ( size_of( s1 ) )
#define s1_min ( -128 )
#define s1_max ( 127 )
#define print_s1( ... ) print( "%hhd", to_s1( __VA_ARGS__ ) )

// 2 bytes
type_from( unsigned short ) u2;
#define to_u2( ... ) to( u2, __VA_ARGS__ )
#define u2_size ( size_of( u2 ) )
#define u2_min ( 0U )
#define u2_max ( 65535U )
#define print_u2( ... ) print( "%hu", to_u2( __VA_ARGS__ ) )

type_from( signed short ) s2;
#define to_s2( ... ) to( s2, __VA_ARGS__ )
#define s2_size ( size_of( s2 ) )
#define s2_min ( -32768 )
#define s2_max ( 32767 )
#define print_s2( ... ) print( "%hd", to_s2( __VA_ARGS__ ) )

// 4 bytes
type_from( unsigned int ) u4;
#define to_u4( ... ) to( u4, __VA_ARGS__ )
#define u4_size ( size_of( u4 ) )
#define u4_min ( 0U )
#define u4_max ( 4294967295U )
#define print_u4( ... ) print( "%u", to_u4( __VA_ARGS__ ) )

type_from( signed int ) s4;
#define to_s4( ... ) to( s4, __VA_ARGS__ )
#define s4_size ( size_of( s4 ) )
#define s4_min ( -2147483648 )
#define s4_max ( 2147483647 )
#define print_s4( ... ) print( "%d", to_s4( __VA_ARGS__ ) )

type_from( float ) f4;
#define to_f4( ... ) to( f4, __VA_ARGS__ )
#define f4_size ( size_of( f4 ) )
#define f4_min ( 1.175494351e-38f )
#define f4_max ( 3.402823466e+38f )
#define print_f4( ... ) print( "%f", to_f4( __VA_ARGS__ ) )

// 8 bytes
type_from( unsigned long long ) u8;
#define to_u8( ... ) to( u8, __VA_ARGS__ )
#define u8_size ( size_of( u8 ) )
#define u8_min ( 0ULL )
#define u8_max ( 18446744073709551615ULL )
#define print_u8( ... ) print( "%llu", to_u8( __VA_ARGS__ ) )

type_from( signed long long ) s8;
#define to_s8( ... ) to( s8, __VA_ARGS__ )
#define s8_size ( size_of( s8 ) )
#define s8_min ( to_s8( -9223372036854775808LL ) )
#define s8_max ( to_s8( 9223372036854775807LL ) )
#define print_s8( ... ) print( "%lld", to_s8( __VA_ARGS__ ) )

type_from( double ) f8;
#define to_f8( ... ) to( f8, __VA_ARGS__ )
#define f8_size ( size_of( f8 ) )
#define f8_min ( 2.2250738585072014e-308 )
#define f8_max ( 1.7976931348623158e+308 )
#define print_f8( ... ) print( "%.16lf", to_f8( __VA_ARGS__ ) )

//

type_from( u1 ) byte;
#define to_byte( ... ) to_u1( __VA_ARGS__ )
#define byte_size( ... ) u1_size( __VA_ARGS__ )
#define byte_min u1_min
#define byte_max u1_max
#define print_byte( ... ) print_u1( __VA_ARGS__ )

type_from( s1 ) flag;
#define to_flag( ... ) ( to_s1( !!( __VA_ARGS__ ) ) )
#define flag_size ( size_of( flag ) )
#define print_flag( ... ) print_s1( __VA_ARGS__ )

#define yes 1
#define maybe -1
#define no 0

//

#define not !
#define and &&
#define or ||
#define xor ^
#define mod %

#define is ==
#define isnt !=

#define loop while( yes )

#define if_all( ... ) if( SYMBOL_CHAIN(, and, , __VA_ARGS__ ) )
#define if_any( ... ) if( SYMBOL_CHAIN(, or, , __VA_ARGS__ ) )
#define if_not_all( ... ) if( SYMBOL_CHAIN( not, and, , __VA_ARGS__ ) )
#define if_not_any( ... ) if( SYMBOL_CHAIN( not, or, , __VA_ARGS__ ) )
#define if_null( ... ) if( SYMBOL_CHAIN(, and, is null, __VA_ARGS__ ) )
#define if_not_null( ... ) if( SYMBOL_CHAIN(, and, isnt null, __VA_ARGS__ ) )
#define if_zero( ... ) if( SYMBOL_CHAIN(, and, is 0, __VA_ARGS__ ) )

#define elif( ... ) else if( __VA_ARGS__ )

#define while_any( ... ) while( SYMBOL_CHAIN(, or, , __VA_ARGS__ ) )
#define while_not( ... ) while( SYMBOL_CHAIN( not, and, , __VA_ARGS__ ) )
#define while_null( ... ) while( SYMBOL_CHAIN(, and, is null, __VA_ARGS__ ) )
#define while_not_null( ... ) while( SYMBOL_CHAIN(, and, isnt null, __VA_ARGS__ ) )
#define while( ... ) while( SYMBOL_CHAIN(, and, , __VA_ARGS__ ) )
#define elwhile( ... ) else while( __VA_ARGS__ )

#define gate( ... ) __VA_ARGS__ : _require_semicolon
#define warp( ... ) goto __VA_ARGS__

//

#define temp register
#define perm static

#define fn perm inline
#define global perm volatile
#define out return
#define leave break
#define skip continue

#define select( ... ) switch( __VA_ARGS__ )
#define with( ... ) case( __VA_ARGS__ ):
#define with_other default:

//

#if COMPILER_MSVC
	#define PACKED
#else
	#define PACKED __attribute__( ( packed ) )
#endif

#define struct( ... )                                 \
	type_from( struct PACKED __VA_ARGS__ ) __VA_ARGS__; \
	struct PACKED __VA_ARGS__

#define make( STRUCT, ... ) ( ( STRUCT ){ __VA_ARGS__ } )

#define array( ... ) [] = { __VA_ARGS__ }

#define pick( IF_YES, THEN_THIS, ELSE_THIS ) ( ( IF_YES ) ? ( THEN_THIS ) : ( ELSE_THIS ) )

//

//

#define in const

//

#define print( ... ) printf( __VA_ARGS__ )

fn _ expect( in byte ref condition, in s4 line, in byte ref file )
{
	print( "!!!!!!! ------- UNEXPECTED ------- !!!!!!!\nEXPECTED \"%s\" in file: %s, at line %d\n", condition, file, line );
	abort();
}
#define expect( ... ) if_not_all( __VA_ARGS__ ) expect( to( byte ref, #__VA_ARGS__ ), __LINE__, to( byte ref, __FILE__ ) )

//

/////// /////// /////// /////// /////// /////// ///////

//

//