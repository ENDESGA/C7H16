/////// /////// /////// /////// /////// /////// ///////
/////// C7H16     H   H   H   H   H   H   H
///////           |   |   |   |   |   |   |
///////       H - C - C - C - C - C - C - C - H
///////           |   |   |   |   |   |   |
///////           H   H   H   H   H   H   H
/////// (heptane) by @ENDESGA 2024 :::. MIT LICENCE

#pragma once
#define INCLUDED_C7H16

#include "H.h"

// // // // // // //
// window

fn_type() window_fn;

object( window )
{
	text title;
	canvas pixels;
	s4 keys[ 256 ], modif, x, y, mouse;
	window_fn update;
	window_fn render;

#if OS_WINDOWS
	HWND hwnd;
#else
	byte mutable_ref display;
	byte mutable_ref window;
	byte mutable_ref gc;
	byte mutable_ref image;
#endif
};

global window main_window = null;
global list window_list = null;

window new_window( in text name, in u2 width, in u2 height, in window_fn update, in window_fn render )
{
	temp window w = new_object( window );
	w->title = name;
	w->pixels = new_canvas( rgb3, width, height );
	w->update = update;
	w->render = render;
	out w;
}

// // // // // // //
// render

#define render_pixel( CANVAS, X, Y, RGB ) cast( struct rgb3 mutable_ref, CANVAS.data )[ ( X ) + ( ( Y ) * CANVAS.width ) ] = RGB
//#define render_pixel( CANVAS, X, Y, RGB ) to(struct rgb mutable_ref, CANVAS->data)[ ( ( Y ) * CANVAS->width ) + ( X ) ] = RGB

#if OS_WINDOWS
embed LRESULT CALLBACK render_wndproc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	struct window mutable_ref r = null;

	if( msg is WM_CREATE )
	{
		CREATESTRUCT ref cs = to( CREATESTRUCT ref, lParam );
		SetWindowLongPtr( hwnd, GWLP_USERDATA, ( LONG_PTR )cs->lpCreateParams );
	}
	else
	{
		r = to( struct window mutable_ref, GetWindowLongPtr( hwnd, GWLP_USERDATA ) );
	}

	select( msg )
	{
		with( WM_PAINT )
		{
			if_not_null( r )
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint( hwnd, ref_of( ps ) );
				BITMAPINFO bmi = {
					{ size_of( BITMAPINFOHEADER ), r->pixels.width, -r->pixels.height, 1, 24, BI_RGB }
				};
				SetDIBitsToDevice( hdc, 0, 0, r->pixels.width, r->pixels.height, 0, 0, 0, r->pixels.height, r->pixels.data, ref_of( bmi ), DIB_RGB_COLORS );
				EndPaint( hwnd, ref_of( ps ) );
			}
			leave;
		}
		with(WM_ERASEBKGND)
		{
			out 1;
		}
		with( WM_CLOSE )
		{
			DestroyWindow( hwnd );
			leave;
		}
		with( WM_DESTROY )
		{
			PostQuitMessage( 0 );
			leave;
		}
		with( WM_LBUTTONDOWN, WM_LBUTTONUP )
		{
			if_not_null( r ) r->mouse = ( msg is WM_LBUTTONDOWN );
			leave;
		}
		with( WM_MOUSEMOVE )
		{
			if_not_null( r )
			{
				r->x = LOWORD( lParam );
				r->y = HIWORD( lParam );
			}
			leave;
		}
		with( WM_KEYDOWN, WM_KEYUP )
		{
			if_not_null( r )
			{
				s4 vk = to( s4, wParam );
				r->keys[ vk ] = ( msg is WM_KEYDOWN );
				r->modif = ( GetKeyState( VK_CONTROL ) < 0 ? 1 : 0 ) |
					( GetKeyState( VK_SHIFT ) < 0 ? 2 : 0 ) |
					( GetKeyState( VK_MENU ) < 0 ? 4 : 0 ) |
					( ( GetKeyState( VK_LWIN ) < 0 or GetKeyState( VK_RWIN ) < 0 ) ? 8 : 0 );
			}
			leave;
		}
		with_other
		{
			out DefWindowProc( hwnd, msg, wParam, lParam );
		}
	}
	out 0;
}

#else
perm struct
{
	s4 x11;
	s4 common;
} keymap[] = {
	{		XK_BackSpace,	8},
	{				 XK_Tab,	9},
	{			XK_Return, 10},
	{			XK_Escape, 27},
	{				XK_Left, 20},
	{			 XK_Right, 19},
	{					XK_Up, 17},
	{				XK_Down, 18},
	{			 XK_space, 32},
	{	XK_apostrophe, 39},
	{			 XK_comma, 44},
	{			 XK_minus, 45},
	{			XK_period, 46},
	{			 XK_slash, 47},
	{		XK_semicolon, 59},
	{			 XK_equal, 61},
	{ XK_bracketleft, 91},
	{		XK_backslash, 92},
	{XK_bracketright, 93},
	{			 XK_grave, 96}
};
#endif

embed s4 render_open( window r )
{
#if OS_WINDOWS
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = render_wndproc;
	wc.hInstance = GetModuleHandle( NULL );
	wc.lpszClassName = r->title->bytes;
	RegisterClass( ref_of( wc ) );
	r->hwnd = CreateWindow( r->title->bytes, r->title->bytes, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, r->pixels.width, r->pixels.height, NULL, NULL, wc.hInstance, NULL );
	SetWindowLongPtr( r->hwnd, GWLP_USERDATA, ( LONG_PTR )r );
	ShowWindow( r->hwnd, SW_SHOW );
#else
	r->display = XOpenDisplay( NULL );
	r->window = XCreateSimpleWindow( r->display, DefaultRootWindow( r->display ), 0, 0, r->width, r->height, 1, BlackPixel( r->display, DefaultScreen( r->display ) ), WhitePixel( r->display, DefaultScreen( r->display ) ) );
	XSelectInput( r->display, r->window, ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask );
	XMapWindow( r->display, r->window );
	r->gc = XCreateGC( r->display, r->window, 0, NULL );
	r->image = XCreateImage( r->display, DefaultVisual( r->display, DefaultScreen( r->display ) ), 24, ZPixmap, 0, to( byte ref, r->buf ), r->width, r->height, 32, 0 );
#endif
	out 0;
}

embed s4 render_loop( window r )
{
#if OS_WINDOWS
	MSG msg;
	while( PeekMessage( ref_of( msg ), NULL, 0, 0, PM_REMOVE ) )
	{
		if( msg.message is WM_QUIT ) out - 1;
		TranslateMessage( ref_of( msg ) );
		DispatchMessage( ref_of( msg ) );
	}
	InvalidateRect( r->hwnd, NULL, no );
#else
	XPutImage( r->display, r->window, r->gc, r->image, 0, 0, 0, 0, r->width, r->height );
	XFlush( r->display );
	while( XPending( r->display ) )
	{
		XEvent event;
		XNextEvent( r->display, ref_of( event ) );
		warp( event.type )
		{
		gate( ButtonPress )
			gate() ButtonRelease)
			r->mouse = ( event.type is ButtonPress );
		leave;
		gate( MotionNotify )
			r->x = event.xmotion.x;
		r->y = event.xmotion.y;
		leave;
		gate( KeyPress )
			gate( KeyRelease )
		{
			s4 keysym = XLookupKeysym( ref_of( event.xkey ), 0 );
			iter( i, size_of( keymap ) / size_of( keymap[ 0 ] ) )
			{
				if( keymap[ i ].x11 is keysym )
				{
					r->keys[ keymap[ i ].common ] = ( event.type is KeyPress );
					leave;
				}
			}
			r->modif = ( ( event.xkey.state & ControlMask ) ? 1 : 0 ) |
				( ( event.xkey.state & ShiftMask ) ? 2 : 0 ) |
				( ( event.xkey.state & Mod1Mask ) ? 4 : 0 ) |
				( ( event.xkey.state & Mod4Mask ) ? 8 : 0 );
			leave;
		}
		}
	}
#endif
	out 0;
}

fn render_close( window r )
{
#if OS_WINDOWS
	DestroyWindow( r->hwnd );
#else
	XDestroyWindow( r->display, r->window );
	XCloseDisplay( r->display );
#endif
}