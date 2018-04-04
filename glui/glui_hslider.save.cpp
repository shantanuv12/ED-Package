/****************************************************************************
  
  GLUI User Interface Toolkit
  ---------------------------

     glui_hslider.cpp - GLUI_HSlider control class


          --------------------------------------------------

  Copyright (c) 1998 Paul Rademacher

  This program is freely distributable without licensing fees and is
  provided without guarantee or warrantee expressed or implied. This
  program is -not- in the public domain.

*****************************************************************************/

#include "glui.h"
#include "stdinc.h"
// #include <iostream.h>
#include <sys/types.h>
#include <time.h>
#ifdef WIN32
#include <windows.h>
#endif


static inline int round( float );


/* tolerance to hit the range selector:				*/

#define RANGETOL	3


/* find where a click landed in the control */

int   GLUI_HSlider::locate_click( int local_x, int local_y )
{
   int rend, lend;

   rend = redge_to_pixel( button_right_edge );
   lend = ledge_to_pixel( button_left_edge );
   local_x -= x_abs;
   local_y -= y_abs;

   if( local_y >= 0 && local_y < GLUI_HSLIDER_ARROW_HEIGHT )
   {
      /* if it's outside the area, hit nothing */
      if( local_x < 0 || local_x >= w ) return GLUI_HSLIDER_STATE_NONE;
      /* if it's at the left edge, hit left arrow */
      if( local_x >= 0 && local_x < GLUI_HSLIDER_ARROW_WIDTH )
         return GLUI_HSLIDER_STATE_DOWN;
      /* if it's at the right edge, hit right arrow */
      else if( local_x >= (w - GLUI_HSLIDER_ARROW_WIDTH) &&
                     local_x < w )
         return GLUI_HSLIDER_STATE_UP;
      /* if it's in the button area, it hit the button */
      else if( local_x > lend + 1 && local_x < rend - 1 )
         return GLUI_HSLIDER_STATE_BUTTON;
      /* if it's in on the left edge of the button, resize left side */
      else if( local_x >= lend - RANGETOL && local_x <= lend + RANGETOL )
         return GLUI_HSLIDER_STATE_BUTTON_LEFT;
      /* if it's in on the right edge of the button, resize right side */
      else if( local_x <= rend + RANGETOL && local_x >= rend - RANGETOL )
         return GLUI_HSLIDER_STATE_BUTTON_RIGHT;
      /* if it's outside the right edge of the button, trough right side */
      else if( local_x > rend + RANGETOL )
         return GLUI_HSLIDER_STATE_TROUGH_RIGHT;
      /* if it's outside the left edge of the button, trough left side */
      else if( local_x < lend - RANGETOL )
         return GLUI_HSLIDER_STATE_TROUGH_LEFT;
   }
   return GLUI_HSLIDER_STATE_NONE;
}

/* make sure we didn't go past any edges */
void GLUI_HSlider::reconcile_edge( void )
{
   float dx = 0.;
   if( button_left_edge < float_low )
   {
      dx = float_low - button_left_edge;
      //cerr << "bar! " << dx << endl;
   } else if( button_is_resizable && button_right_edge > float_high )
   {
      dx = float_high - button_right_edge;
   } else if( !button_is_resizable && (button_left_edge > float_high) )
   {
      dx = float_high - button_left_edge;
      //cerr << "foo! " << dx << endl;
   }

   button_left_edge += dx;
   button_right_edge += dx;

   if( button_is_resizable )
   {
      /* we may have grown past the right/left side, this checks that */
      if( button_left_edge < float_low )
      {
         button_left_edge = float_low;
      }
      if( button_right_edge > float_high )
      {
         button_right_edge = float_high;
      }
   }
}



/* at this point we've been clicked, and need to move around */
void GLUI_HSlider::do_click()
{
   float dx;

#ifdef WIN32
   last_click_time = GetTickCount();
#else
   last_click_time = clock();
#endif

   switch( state )
   {
      case GLUI_HSLIDER_STATE_DOWN:
         /* decrement by one tick */
         move_val( -.001 * ( float_high - float_low ) );
         break;

      case GLUI_HSLIDER_STATE_UP:
         /* increment by one tick */
         move_val( .001 * ( float_high - float_low ) );
         break;

      case GLUI_HSLIDER_STATE_BUTTON_LEFT:
         button_left_edge = pixel_to_ledge( new_button_center );
         if( button_left_edge > button_right_edge )
            button_left_edge = button_right_edge;
         if( button_left_edge < float_low )
            button_left_edge = float_low;
         translate_and_draw_front();
         break;

      case GLUI_HSLIDER_STATE_BUTTON_RIGHT:
         button_right_edge = pixel_to_redge( new_button_center );
         if( button_right_edge < button_left_edge )
            button_right_edge = button_left_edge;
         if( button_right_edge > float_high )
            button_right_edge = float_high;
         translate_and_draw_front();
         break;

      case GLUI_HSLIDER_STATE_BUTTON:
         move_button_pixels( new_button_center, old_button_center );
         break;

      case GLUI_HSLIDER_STATE_TROUGH_LEFT:
         /* bounce it left one width of the button */
         /*
         if( bounce_target < GLUI_HSLIDER_ARROW_WIDTH )
            bounce_target = GLUI_HSLIDER_ARROW_WIDTH;
         */

         if( bounce_target < ledge_to_pixel(button_left_edge) )
         {
            /* bounce it one width left */
            dx = button_left_edge -
               pixel_to_redge(4+redge_to_pixel(button_right_edge));
            button_left_edge += dx;
            button_right_edge += dx;

            /* make sure we didn't go over an edge */
            reconcile_edge();
            translate_and_draw_front();
         }
         break;

      case GLUI_HSLIDER_STATE_TROUGH_RIGHT:
         /* bounce it right one width of the button */
         /*
         if( bounce_target >= w - GLUI_HSLIDER_ARROW_WIDTH )
            bounce_target = w - GLUI_HSLIDER_ARROW_WIDTH - 1;
         */
         if( bounce_target > redge_to_pixel(button_right_edge) )
         {
            dx = pixel_to_redge(4+redge_to_pixel(button_right_edge))
                     - button_left_edge;
            button_left_edge += dx;
            button_right_edge += dx;

            /* make sure we didn't go over an edge */
            reconcile_edge();
            translate_and_draw_front();
         }
         break;

      case GLUI_HSLIDER_STATE_NONE:
         return;
   }

   update_slider_val();
   return;
}




/****************************** GLUI_HSlider::mouse_down_handler() **********/
int    GLUI_HSlider::mouse_down_handler( int local_x, int local_y )
{
   /* three cases: clicked on trough, clicked on up/down buttons,
      clicked on slider */

   state = locate_click( local_x, local_y );

   switch( state )
   {
      case GLUI_HSLIDER_STATE_DOWN:
      case GLUI_HSLIDER_STATE_UP:
         bneeds_idle = 1;
         break;

      case GLUI_HSLIDER_STATE_BUTTON_LEFT:
      case GLUI_HSLIDER_STATE_BUTTON_RIGHT:
         if( button_is_resizable )
         {
            glutSetCursor( GLUT_CURSOR_LEFT_RIGHT );
         } else
         {
            /* not resizable, pretend they clicked the button */
            state = GLUI_HSLIDER_STATE_BUTTON;
         }
         new_button_center = old_button_center = local_x-x_abs;
         break;

      case GLUI_HSLIDER_STATE_BUTTON:
         new_button_center = old_button_center = local_x-x_abs;
         break;

      case GLUI_HSLIDER_STATE_TROUGH_RIGHT:
      case GLUI_HSLIDER_STATE_TROUGH_LEFT:
         /* bounce it one width of the button */
         bneeds_idle = 1;
         bounce_target = local_x - x_abs;
         break;

      case GLUI_HSLIDER_STATE_NONE:
         return true;
   }

   do_click();
   return false;
}



int GLUI_HSlider::mouse_over( int entered, int x, int y )
{
   int area;

   if( ! button_is_resizable )
	return false;

   /* we're busy, call us later */
   if( state != GLUI_HSLIDER_STATE_NONE )
	return true;

   /* make sure we set it back to left arrow */
   if( !entered )
      glutSetCursor( GLUT_CURSOR_LEFT_ARROW );
   else
   {
      area = locate_click( x, y );
      if( area == GLUI_HSLIDER_STATE_BUTTON_LEFT ||
            area == GLUI_HSLIDER_STATE_BUTTON_RIGHT )
      {
         /* in the correct area, set the cursor */
         glutSetCursor( GLUT_CURSOR_LEFT_RIGHT );
      } else glutSetCursor( GLUT_CURSOR_LEFT_ARROW );
			return true;
   }

   return true;
}



int GLUI_HSlider::needs_idle()
{
   return bneeds_idle;
}



void GLUI_HSlider::idle()
{
   time_t cur_time;

   if( !bneeds_idle ) return;

#ifdef WIN32
   cur_time = GetTickCount();
   // on windows it's milliseconds, not micro
   if( cur_time - last_click_time > 50 )
#else
   cur_time = clock();
   if( cur_time - last_click_time > 50000 )
#endif
   {
      do_click();
   }
}




/****************************** GLUI_HSlider::mouse_up_handler() **********/

int    GLUI_HSlider::mouse_up_handler( int local_x, int local_y, int inside )
{
   /* redraw it, do callback? */
   local_x = local_y = inside = local_x+local_y+inside;
   bneeds_idle = 0;
   state = GLUI_HSLIDER_STATE_NONE;
   return false;
}



/****************************** GLUI_HSlider::mouse_held_down_handler() ******/

int    GLUI_HSlider::mouse_held_down_handler( int local_x, int local_y,
                    int new_inside)
{
   /* couple things here:
         when held down in the trough, keep going up in one direction until the
         mouse is let go. Don't go past the mouse area.

         when held down on an arrow, keep going in that direction until the mouse
         is let go

         when in the button state, follow the mouse horizontally until the mouse
         is let go
   */

  switch( state )
   {
      case GLUI_HSLIDER_STATE_NONE:
      case GLUI_HSLIDER_STATE_UP:
      case GLUI_HSLIDER_STATE_DOWN:
         break;

      case GLUI_HSLIDER_STATE_TROUGH_RIGHT:
      case GLUI_HSLIDER_STATE_TROUGH_LEFT:
         /* if it's still on the button, do another click */
         if( new_inside
               && locate_click(local_x, local_y) == state )
				 {
						bounce_target = local_x-x_abs;
				 }
         break;

      case GLUI_HSLIDER_STATE_BUTTON_RIGHT:
      case GLUI_HSLIDER_STATE_BUTTON_LEFT:
      case GLUI_HSLIDER_STATE_BUTTON:
         /* move button over some */
         new_button_center = local_x - x_abs;
         do_click();
         break;
   }

   return false;
}



int    GLUI_HSlider::special_handler( int key, int modifiers )
{
   key = modifiers = key+modifiers;
   return false;
}




/****************************** GLUI_HSlider::key_handler() **********/

int    GLUI_HSlider::key_handler( unsigned char key, int modifiers )
{
   key = key + 2;
   modifiers = modifiers + 2;
   return false;
}



/********************************************** GLUI_HSlider::draw() **********/

GLubyte glui_halftone[] =
{
  0xAA,  0xAA,  0xAA,  0xAA,  0x55,  0x55,  0x55,  0x55,
  0xAA,  0xAA,  0xAA,  0xAA,  0x55,  0x55,  0x55,  0x55,
  0xAA,  0xAA,  0xAA,  0xAA,  0x55,  0x55,  0x55,  0x55,
  0xAA,  0xAA,  0xAA,  0xAA,  0x55,  0x55,  0x55,  0x55,
  0xAA,  0xAA,  0xAA,  0xAA,  0x55,  0x55,  0x55,  0x55,
  0xAA,  0xAA,  0xAA,  0xAA,  0x55,  0x55,  0x55,  0x55,
  0xAA,  0xAA,  0xAA,  0xAA,  0x55,  0x55,  0x55,  0x55,
  0xAA,  0xAA,  0xAA,  0xAA,  0x55,  0x55,  0x55,  0x55,
  0xAA,  0xAA,  0xAA,  0xAA,  0x55,  0x55,  0x55,  0x55,
  0xAA,  0xAA,  0xAA,  0xAA,  0x55,  0x55,  0x55,  0x55,
  0xAA,  0xAA,  0xAA,  0xAA,  0x55,  0x55,  0x55,  0x55,
  0xAA,  0xAA,  0xAA,  0xAA,  0x55,  0x55,  0x55,  0x55,
  0xAA,  0xAA,  0xAA,  0xAA,  0x55,  0x55,  0x55,  0x55,
  0xAA,  0xAA,  0xAA,  0xAA,  0x55,  0x55,  0x55,  0x55,
  0xAA,  0xAA,  0xAA,  0xAA,  0x55,  0x55,  0x55,  0x55,
  0xAA,  0xAA,  0xAA,  0xAA,  0x55,  0x55,  0x55,  0x55,
};

void    GLUI_HSlider::draw( int x, int y )
{
   int orig, dbstate;
   int bleft, bright;

   if ( NOT can_draw() )
      return;

   if( !glui ) return;

   orig = set_to_glut_window();
   dbstate = glui->set_front_draw_buffer();

   glui->std_bitmaps.draw( GLUI_STDBITMAP_LEFT_ARROW, 0, 0 );
   glui->std_bitmaps.draw( GLUI_STDBITMAP_RIGHT_ARROW,
                                       w - GLUI_HSLIDER_ARROW_WIDTH - 1, 0 );
   glColor3ub( 192, 192, 192 );
   glBegin( GL_TRIANGLE_STRIP );
      glVertex2i( GLUI_HSLIDER_ARROW_WIDTH+1, 1 );
      glVertex2i( GLUI_HSLIDER_ARROW_WIDTH+1, h );
      glVertex2i( w - GLUI_HSLIDER_ARROW_WIDTH, 1 );
      glVertex2i( w - GLUI_HSLIDER_ARROW_WIDTH, h );
   glEnd();

   glPolygonStipple( glui_halftone );
   glEnable( GL_POLYGON_STIPPLE );
   glColor3ub( 64, 64, 64 );
   glBegin( GL_TRIANGLE_STRIP );
      glVertex2i( GLUI_HSLIDER_ARROW_WIDTH+1, 1 );
      glVertex2i( GLUI_HSLIDER_ARROW_WIDTH+1, h );
      glVertex2i( w - GLUI_HSLIDER_ARROW_WIDTH, 1 );
      glVertex2i( w - GLUI_HSLIDER_ARROW_WIDTH, h );
   glEnd();

   glDisable( GL_POLYGON_STIPPLE );

   glColor3ub( 0, 0, 0 );
   glBegin( GL_LINES );
      glVertex2i( GLUI_HSLIDER_ARROW_WIDTH+1, h );
      glVertex2i( w - GLUI_HSLIDER_ARROW_WIDTH, h );
      glVertex2i( GLUI_HSLIDER_ARROW_WIDTH+1, 1 );
      glVertex2i( w - GLUI_HSLIDER_ARROW_WIDTH, 1 );
   glEnd();

   bleft = ledge_to_pixel( button_left_edge );
   bright = redge_to_pixel( button_right_edge );


   glColor3ub( 192, 192, 192 );
   glBegin( GL_TRIANGLE_STRIP );
      glVertex2i( bleft+2, 2 );
      glVertex2i( bleft+2, h );
      glVertex2i( bright, 2 );
      glVertex2i( bright, h );
   glEnd();

   glui->draw_raised_box( bleft+1, 1, bright-bleft-1, h-1 );


/* mjb */
/* do something different to indicate this is a range slider:	*/

#define HANDLE	4

   if( button_is_resizable )
   {
     glColor3ub( 0, 0, 0 );

     glBegin( GL_TRIANGLE_STRIP );
        glVertex2i( bleft, 1 );
        glVertex2i( bleft, h );
        glVertex2i( bleft+HANDLE, 1 );
        glVertex2i( bleft+HANDLE, h );
     glEnd();

     glBegin( GL_TRIANGLE_STRIP );
        glVertex2i( bright-HANDLE, 1 );
        glVertex2i( bright-HANDLE, h );
        glVertex2i( bright, 1 );
        glVertex2i( bright, h );
     glEnd();
   }

/* mjb */

   glui->restore_draw_buffer(dbstate);
   restore_window( orig );
}



/************************************** GLUI_HSlider::update_size() **********/

void   GLUI_HSlider::update_size( void )
{
  if ( NOT glui )
    return;
}




void GLUI_HSlider::set_float_limits( float low, float high )
{
   float_low = low;
   float_high = high;

   int_low  = round( low );
   int_high = round( high );

   if( button_left_edge < float_low )
   {
      button_right_edge += button_left_edge - float_low;
      button_left_edge = float_low;
   } else if( button_left_edge > float_high )
   {
      button_right_edge += float_high - button_left_edge;
      button_left_edge = float_high;
   }

   if( button_right_edge < button_left_edge )
      button_right_edge = button_left_edge;
   if( button_right_edge > float_high )
      button_right_edge = float_high;

   translate_and_draw_front();
}



void GLUI_HSlider::set_int_limits( int low, int high )
{
	set_float_limits( (float)low, (float)high );
}



float GLUI_HSlider::get_slider_val()
{
   return button_left_edge;
}




/* finds the value closest to pct */
/* 0. <= t <= 1.		  */

float GLUI_HSlider::find_val( float t )
{
   return float_low  +  t * ( float_high - float_low );
}



static inline int round( float x )
{
   if( x >= 0. )
      return (int)( x + .5 );

   return (int)( x - .5 );
}




/* moves the value to cur + dx */

void GLUI_HSlider::move_val( float dx )
{
   button_left_edge += dx;
   button_right_edge += dx;
   reconcile_edge();
   update_slider_val();
   translate_and_draw_front();
}



int GLUI_HSlider::sync_slider()
{
   int changed = 0;
   float left, right;


   if( live_type == GLUI_LIVE_FLOAT )
      left  = ((float*)ptr_val)[0];
   else
      left  = (float) ((int*)ptr_val)[0];

   if( button_left_edge != left )
      changed = 1;
   button_left_edge  = left;


   if( button_is_resizable )
   {
      if( live_type == GLUI_LIVE_FLOAT )
         right = ((float*)ptr_val)[1];
      else
         right = (float) ((int*)ptr_val)[1];

      if( button_right_edge != right )
         changed = 1;
      button_right_edge = right;
   }

   return changed;
}



void GLUI_HSlider::update_slider_val()
{
   int changed = 0;
   float left, right;

   if( live_type == GLUI_LIVE_FLOAT )
      left  = ((float*)ptr_val)[0];
   else
      left  = (float) ((int*)ptr_val)[0];

   if( button_left_edge != left )
      changed = 1;

   if( button_is_resizable )
   {
      if( live_type == GLUI_LIVE_FLOAT )
         right = ((float*)ptr_val)[1];
      else
         right = (float) ((int*)ptr_val)[1];

      if( button_right_edge != right )
         changed = 1;

      if( live_type == GLUI_LIVE_FLOAT )
         ((float*)ptr_val)[1] = button_right_edge;
      else
         ((int*)ptr_val)[1] = round( button_right_edge );
   }

   if( live_type == GLUI_LIVE_FLOAT )
      ((float*)ptr_val)[0] = button_left_edge;
   else
      ((int*)ptr_val)[0] = round( button_left_edge );


   if ( changed )
   {
      this->execute_callback();
      // glui->post_update_main_gfx();  // MJB -- was commented out
   }
}



void GLUI_HSlider::set_slider_val( float low )
{
   button_left_edge = low;
   reconcile_edge();
}



void GLUI_HSlider::set_slider_val( float low, float high )
{
   button_left_edge = low;
   button_right_edge = high;
   reconcile_edge();
}



void GLUI_HSlider::set_slider_val( int low, int high )
{
   set_slider_val( (float)low, (float)high );
}

#define HANDLEWIDTH	6

int GLUI_HSlider::redge_to_pixel( float val )
{
   /* remove extra space between, and left arrow space */
   int pixels;
   float pct;

   pixels = w - 2*GLUI_HSLIDER_ARROW_WIDTH - 4;

   if( ! button_is_resizable )
   {
      return ledge_to_pixel( button_left_edge ) + HANDLEWIDTH;

#if 0
      /* right edge is a "constant" offset from left edge */
	/* ??? */
      xdist = pixels - float_high + float_low;
      if( xdist < 4 )
        xdist = 4;
      else
        xdist += 4;

      pixels = ledge_to_pixel( button_left_edge ) + xdist;
      return pixels;
#endif
   }

   pct = (val - float_low) / (float_high - float_low);
   return GLUI_HSLIDER_ARROW_WIDTH + 4 + round( pct*pixels );
}



int GLUI_HSlider::ledge_to_pixel( float val )
{
   /* remove extra space between, and left arrow space */
   int xdist;
   int pixels;
   float pct;

   pixels = w - 2*GLUI_HSLIDER_ARROW_WIDTH - 4;
   pct = (val - float_low) / (float_high - float_low);
   return GLUI_HSLIDER_ARROW_WIDTH + round( pct*pixels );
}




float GLUI_HSlider::pixel_to_redge( int val )
{
   int pixels;
   float pct;

   pixels = w - 2*GLUI_HSLIDER_ARROW_WIDTH - 4;
   pct = ( (float)(val - GLUI_HSLIDER_ARROW_WIDTH - 4) ) / (float)pixels;
   return find_val( pct );
}




float GLUI_HSlider::pixel_to_ledge( int val )
{
   int pixels, xdist;
   float pct;

   pixels = w - 2*GLUI_HSLIDER_ARROW_WIDTH - 4;

   if( ! button_is_resizable )
   {
      xdist = pixels - float_high + float_low;
      if( xdist > 4 )
        return val + float_low - GLUI_HSLIDER_ARROW_WIDTH;
   }

   pct = ( (float)(val - GLUI_HSLIDER_ARROW_WIDTH) ) / (float)pixels;
   return find_val( pct );
}



void GLUI_HSlider::move_button_pixels( int nval, int &oval )
{
   float dx;
   int xdist, npos;
   int pixels;

   /* nval and oval are in pixels, change them to user units:	*/

   pixels = w - 2*GLUI_HSLIDER_ARROW_WIDTH - 4;
   dx = (float)(nval - oval) * ( float_high - float_low ) / (float)pixels;
   button_left_edge  += dx;
   button_right_edge += dx;
   oval = nval;
   reconcile_edge();
   update_slider_val();
   translate_and_draw_front();
}
