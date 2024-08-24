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
// canvas

object( canvas )
{
	byte ref data;
	u2 width;
	u2 height;
};

embed canvas new_canvas( in u2 width, in u2 height )
{
	temp canvas c = new_object( canvas );
	c->width = width;
	c->height = height;
	set_new_ref( c->data, (c->width * c->height) * 3 );
	out c;
}

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
	_ mutable_ref hwnd;
#else
	_ mutable_ref display;
	_ mutable_ref window;
	_ mutable_ref gc;
	_ mutable_ref image;
#endif
};

global window main_window = null;
global list window_list = null;

window new_window( in text name, in u2 width, in u2 height, in window_fn update, in window_fn render )
{
	temp window w = new_object( window );
	w->title = name;
	set_ref( w->pixels, new_canvas( width, height ) );
	w->update = update;
	w->render = render;
	out w;
}
