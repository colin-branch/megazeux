/* MegaZeux
 *
 * Copyright (C) 2004 Gilead Kutnick <exophase@adelphia.net>
 * Copyright (C) 2007 Kevin Vance <kvance@kvance.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "event.h"
#include "platform.h"
#include "graphics.h"
#include "render_sdl.h"

#include "SDL.h"

extern struct input_status input;

static bool numlock_status_initialized;

static enum keycode convert_SDL_internal(SDL_Keycode key)
{
  switch(key)
  {
    case SDLK_BACKSPACE: return IKEY_BACKSPACE;
    case SDLK_TAB: return IKEY_TAB;
    case SDLK_RETURN: return IKEY_RETURN;
    case SDLK_ESCAPE: return IKEY_ESCAPE;
    case SDLK_SPACE: return IKEY_SPACE;
    case SDLK_QUOTE: return IKEY_QUOTE;
    case SDLK_PLUS: return IKEY_EQUALS;
    case SDLK_COMMA: return IKEY_COMMA;
    case SDLK_MINUS: return IKEY_MINUS;
    case SDLK_PERIOD: return IKEY_PERIOD;
    case SDLK_SLASH: return IKEY_SLASH;
    case SDLK_0: return IKEY_0;
    case SDLK_1: return IKEY_1;
    case SDLK_2: return IKEY_2;
    case SDLK_3: return IKEY_3;
    case SDLK_4: return IKEY_4;
    case SDLK_5: return IKEY_5;
    case SDLK_6: return IKEY_6;
    case SDLK_7: return IKEY_7;
    case SDLK_8: return IKEY_8;
    case SDLK_9: return IKEY_9;
    case SDLK_SEMICOLON: return IKEY_SEMICOLON;
    case SDLK_EQUALS: return IKEY_EQUALS;
    case SDLK_LEFTBRACKET: return IKEY_LEFTBRACKET;
    case SDLK_BACKSLASH: return IKEY_BACKSLASH;
    case SDLK_RIGHTBRACKET: return IKEY_RIGHTBRACKET;
    case SDLK_BACKQUOTE: return IKEY_BACKQUOTE;
    case SDLK_a: return IKEY_a;
    case SDLK_b: return IKEY_b;
    case SDLK_c: return IKEY_c;
    case SDLK_d: return IKEY_d;
    case SDLK_e: return IKEY_e;
    case SDLK_f: return IKEY_f;
    case SDLK_g: return IKEY_g;
    case SDLK_h: return IKEY_h;
    case SDLK_i: return IKEY_i;
    case SDLK_j: return IKEY_j;
    case SDLK_k: return IKEY_k;
    case SDLK_l: return IKEY_l;
    case SDLK_m: return IKEY_m;
    case SDLK_n: return IKEY_n;
    case SDLK_o: return IKEY_o;
    case SDLK_p: return IKEY_p;
    case SDLK_q: return IKEY_q;
    case SDLK_r: return IKEY_r;
    case SDLK_s: return IKEY_s;
    case SDLK_t: return IKEY_t;
    case SDLK_u: return IKEY_u;
    case SDLK_v: return IKEY_v;
    case SDLK_w: return IKEY_w;
    case SDLK_x: return IKEY_x;
    case SDLK_y: return IKEY_y;
    case SDLK_z: return IKEY_z;
    case SDLK_DELETE: return IKEY_DELETE;
    case SDLK_KP_0: return IKEY_KP0;
    case SDLK_KP_1: return IKEY_KP1;
    case SDLK_KP_2: return IKEY_KP2;
    case SDLK_KP_3: return IKEY_KP3;
    case SDLK_KP_4: return IKEY_KP4;
    case SDLK_KP_5: return IKEY_KP5;
    case SDLK_KP_6: return IKEY_KP6;
    case SDLK_KP_7: return IKEY_KP7;
    case SDLK_KP_8: return IKEY_KP8;
    case SDLK_KP_9: return IKEY_KP9;
    case SDLK_KP_PERIOD: return IKEY_KP_PERIOD;
    case SDLK_KP_DIVIDE: return IKEY_KP_DIVIDE;
    case SDLK_KP_MULTIPLY: return IKEY_KP_MULTIPLY;
    case SDLK_KP_MINUS: return IKEY_KP_MINUS;
    case SDLK_KP_PLUS: return IKEY_KP_PLUS;
    case SDLK_KP_ENTER: return IKEY_KP_ENTER;
    case SDLK_UP: return IKEY_UP;
    case SDLK_DOWN: return IKEY_DOWN;
    case SDLK_RIGHT: return IKEY_RIGHT;
    case SDLK_LEFT: return IKEY_LEFT;
    case SDLK_INSERT: return IKEY_INSERT;
    case SDLK_F1: return IKEY_F1;
    case SDLK_F2: return IKEY_F2;
    case SDLK_F3: return IKEY_F3;
    case SDLK_F4: return IKEY_F4;
    case SDLK_F5: return IKEY_F5;
    case SDLK_F6: return IKEY_F6;
    case SDLK_F7: return IKEY_F7;
    case SDLK_F8: return IKEY_F8;
    case SDLK_F9: return IKEY_F9;
    case SDLK_F10: return IKEY_F10;
    case SDLK_F11: return IKEY_F11;
    case SDLK_F12: return IKEY_F12;
    case SDLK_NUMLOCKCLEAR: return IKEY_NUMLOCK;
    case SDLK_CAPSLOCK: return IKEY_CAPSLOCK;
    case SDLK_SCROLLLOCK: return IKEY_SCROLLOCK;
    case SDLK_LSHIFT: return IKEY_LSHIFT;
    case SDLK_LCTRL: return IKEY_LCTRL;
    case SDLK_RALT: return IKEY_RALT;
    case SDLK_LALT: return IKEY_LALT;
    case SDLK_LGUI: return IKEY_LSUPER;
    case SDLK_RGUI: return IKEY_RSUPER;
    case SDLK_SYSREQ: return IKEY_SYSREQ;
    case SDLK_PAUSE: return IKEY_BREAK;
    case SDLK_MENU: return IKEY_MENU;
#ifndef CONFIG_PANDORA
    case SDLK_HOME: return IKEY_HOME;
    case SDLK_END: return IKEY_END;
    case SDLK_PAGEUP: return IKEY_PAGEUP;
    case SDLK_PAGEDOWN: return IKEY_PAGEDOWN;
    case SDLK_RSHIFT: return IKEY_RSHIFT;
    case SDLK_RCTRL: return IKEY_RCTRL;
#else /* CONFIG_PANDORA */
    case SDLK_HOME: return input.joystick_button_map[0][0];
    case SDLK_END: return input.joystick_button_map[0][1];
    case SDLK_PAGEUP: return input.joystick_button_map[0][2];
    case SDLK_PAGEDOWN: return input.joystick_button_map[0][3];
    case SDLK_RSHIFT: return input.joystick_button_map[0][4];
    case SDLK_RCTRL: return input.joystick_button_map[0][5];
#endif /* CONFIG_PANDORA */
    default: return IKEY_UNKNOWN;
  }
}

static bool process_event(SDL_Event *event)
{
  struct buffered_status *status = store_status();
  enum keycode ckey;

  /* SDL's numlock keyboard modifier handling seems to be broken on X11,
   * and it will only get numlock's status right on application init. We
   * can trust this value once, and then toggle based on user presses of
   * the numlock key.
   *
   * On Windows, KEYDOWN/KEYUP seem to be sent separately, to indicate
   * enabling or disabling of numlock. But on X11, both KEYDOWN/KEYUP are
   * sent for each toggle, so this must be handled differently.
   *
   * What a mess!
   */
  if(!numlock_status_initialized)
  {
    status->numlock_status = !!(SDL_GetModState() & KMOD_NUM);
    numlock_status_initialized = true;
  }

  switch(event->type)
  {
    case SDL_QUIT:
    {
      // Set the exit status
      status->exit = 1;
      break;
    }

#if SDL_VERSION_ATLEAST(2,0,0)
    case SDL_WINDOWEVENT:
    {
      switch(event->window.event)
      {
        case SDL_WINDOWEVENT_RESIZED:
        {
          resize_screen(event->window.data1, event->window.data2);
          break;
        }

        case SDL_WINDOWEVENT_FOCUS_LOST:
        {
          // Pause while minimized
          if(input.unfocus_pause)
          {
            while(1)
            {
              SDL_WaitEvent(event);

              if(event->type == SDL_WINDOWEVENT &&
                 event->window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
                break;
            }
          }
          break;
        }
      }

      break;
    }
#else // !SDL_VERSION_ATLEAST(2,0,0)
    case SDL_VIDEORESIZE:
    {
      resize_screen(event->resize.w, event->resize.h);
      break;
    }

    case SDL_ACTIVEEVENT:
    {
      if(input.unfocus_pause)
      {
        // Pause while minimized
        if(event->active.state & (SDL_APPACTIVE | SDL_APPINPUTFOCUS))
        {
          // Wait for SDL_APPACTIVE with gain of 1
          do
          {
            SDL_WaitEvent(event);
          } while((event->type != SDL_ACTIVEEVENT) ||
           (event->active.state & ~(SDL_APPACTIVE | SDL_APPINPUTFOCUS)));
        }
      }
      break;
    }
#endif // !SDL_VERSION_ATLEAST(2,0,0)

    case SDL_MOUSEMOTION:
    {
      SDL_Window *window = SDL_GetWindowFromID(sdl_window_id);
      int mx_real = event->motion.x;
      int my_real = event->motion.y;
      int mx, my, min_x, min_y, max_x, max_y;
      get_screen_coords(mx_real, my_real, &mx, &my, &min_x,
       &min_y, &max_x, &max_y);

      if(mx > 639)
        SDL_WarpMouseInWindow(window, max_x, my_real);

      if(mx < 0)
        SDL_WarpMouseInWindow(window, min_x, my_real);

      if(my > 349)
        SDL_WarpMouseInWindow(window, mx_real, max_y);

      if(my < 0)
        SDL_WarpMouseInWindow(window, mx_real, min_y);

      status->real_mouse_x = mx;
      status->real_mouse_y = my;
      status->mouse_x = mx / 8;
      status->mouse_y = my / 14;
      status->mouse_moved = true;
      break;
    }

    case SDL_MOUSEBUTTONDOWN:
    {
      status->mouse_button = event->button.button;
      status->mouse_repeat = event->button.button;
      status->mouse_button_state |= SDL_BUTTON(event->button.button);
      status->mouse_repeat_state = 1;
      status->mouse_drag_state = -1;
      status->mouse_time = SDL_GetTicks();
      break;
    }

    case SDL_MOUSEBUTTONUP:
    {
      status->mouse_button_state &= ~SDL_BUTTON(event->button.button);
      status->mouse_repeat = 0;
      status->mouse_drag_state = 0;
      status->mouse_repeat_state = 0;
      break;
    }

#if SDL_VERSION_ATLEAST(2,0,0)
    // emulate the X11-style "wheel is a button" that SDL 1.2 used
    case SDL_MOUSEWHEEL:
    {
      SDL_Event fake_event;

      fake_event.type = SDL_MOUSEBUTTONDOWN;
      fake_event.button.windowID = event->wheel.windowID;
      fake_event.button.which = event->wheel.which;
      fake_event.button.state = SDL_PRESSED;
      fake_event.button.x = 0;
      fake_event.button.y = 0;

      if(abs(event->wheel.x) > abs(event->wheel.y))
      {
        if(event->wheel.x < 0)
          fake_event.button.button = MOUSE_BUTTON_WHEELLEFT;
        else
          fake_event.button.button = MOUSE_BUTTON_WHEELRIGHT;
      }

      else
      {
        if(event->wheel.y < 0)
          fake_event.button.button = MOUSE_BUTTON_WHEELDOWN;
        else
          fake_event.button.button = MOUSE_BUTTON_WHEELUP;
      }

      SDL_PushEvent(&fake_event);

      fake_event.type = SDL_MOUSEBUTTONUP;
      fake_event.button.state = SDL_RELEASED;

      SDL_PushEvent(&fake_event);
      break;
    }
#endif // SDL_VERSION_ATLEAST(2,0,0)

    case SDL_KEYDOWN:
    {
      Uint16 unicode = 0;

#if SDL_VERSION_ATLEAST(2,0,0)
      // FIXME: SDL 2.0 finally implements proper key repeat.
      // We should probably use it instead of our hand-rolled stuff.
      if(event->key.repeat)
        break;
#endif

      ckey = convert_SDL_internal(event->key.keysym.sym);
      if(!ckey)
      {
#if !SDL_VERSION_ATLEAST(2,0,0)
        if(!event->key.keysym.unicode)
          break;
#endif
        ckey = IKEY_UNICODE;
      }

#if SDL_VERSION_ATLEAST(2,0,0)
      // SDL 2.0 sends the raw key and translated 'text' as separate events.
      // There is no longer a UNICODE mode that sends both at once.
      // Because of the way the SDL 1.2 assumption is embedded deeply in
      // the MZX event queue processor, emulate the 1.2 behaviour by waiting
      // for a TEXTINPUT event after a KEYDOWN.
      SDL_PumpEvents();
      if (SDL_PeepEvents(event, 1, SDL_GETEVENT, SDL_TEXTINPUT, SDL_TEXTINPUT)) {
        unicode = event->text.text[0] | event->text.text[1] << 8;
      }
#else
      unicode = event->key.keysym.unicode;
#endif

      if((ckey == IKEY_RETURN) &&
       get_alt_status(keycode_internal) &&
       get_ctrl_status(keycode_internal))
      {
        toggle_fullscreen();
        break;
      }

      if(ckey == IKEY_CAPSLOCK)
      {
        status->caps_status = true;
      }

      if(ckey == IKEY_NUMLOCK)
      {
#if !SDL_VERSION_ATLEAST(2,0,0) && defined(__WIN32__)
        status->numlock_status = true;
#endif
        break;
      }

      if(ckey == IKEY_F12)
      {
        dump_screen();
        break;
      }

      // Ignore alt + tab
      if((ckey == IKEY_TAB) && get_alt_status(keycode_internal))
      {
        break;
      }

      if(status->key_repeat &&
       (status->key_repeat != IKEY_LSHIFT) &&
       (status->key_repeat != IKEY_RSHIFT) &&
       (status->key_repeat != IKEY_LALT) &&
       (status->key_repeat != IKEY_RALT) &&
       (status->key_repeat != IKEY_LCTRL) &&
       (status->key_repeat != IKEY_RCTRL))
      {
        // Stack current repeat key if it isn't shift, alt, or ctrl
        if(input.repeat_stack_pointer != KEY_REPEAT_STACK_SIZE)
        {
          input.key_repeat_stack[input.repeat_stack_pointer] =
           status->key_repeat;
          input.unicode_repeat_stack[input.repeat_stack_pointer] =
           status->unicode_repeat;
          input.repeat_stack_pointer++;
        }
      }

      key_press(status, ckey, unicode);
      break;
    }

    case SDL_KEYUP:
    {
#if SDL_VERSION_ATLEAST(2,0,0)
      // FIXME: SDL 2.0 finally implements proper key repeat.
      // We should probably use it instead of our hand-rolled stuff.
      if(event->key.repeat)
        break;
#endif

      ckey = convert_SDL_internal(event->key.keysym.sym);
      if(!ckey)
      {
#if !SDL_VERSION_ATLEAST(2,0,0)
        if(!status->keymap[IKEY_UNICODE])
          break;
#endif
        ckey = IKEY_UNICODE;
      }

      if(ckey == IKEY_NUMLOCK)
      {
#if !SDL_VERSION_ATLEAST(2,0,0) && defined(__WIN32__)
        status->numlock_status = false;
#else
        status->numlock_status = !status->numlock_status;
#endif
        break;
      }

      if(ckey == IKEY_CAPSLOCK)
      {
        status->caps_status = false;
      }
      key_release(status, ckey);
      break;
    }

    case SDL_JOYAXISMOTION:
    {
      int axis_value = event->jaxis.value;
      int digital_value = -1;
      int which = event->jaxis.which;
      int axis = event->jaxis.axis;
      Sint8 last_axis = status->axis[which][axis];
      enum keycode stuffed_key;

      if(axis_value > 10000)
        digital_value = 1;
      else

      if(axis_value < -10000)
        digital_value = 0;

      if(digital_value != -1)
      {
        stuffed_key =
          input.joystick_axis_map[which][axis][digital_value];

        if(stuffed_key)
        {
          joystick_key_press(status, stuffed_key, stuffed_key);

          if(last_axis == (digital_value ^ 1))
          {
            joystick_key_release(status,
             input.joystick_axis_map[which][axis][last_axis]);
          }
        }
      }
      else if(last_axis != -1)
      {
        joystick_key_release(status,
          input.joystick_axis_map[which][axis][last_axis]);
      }

      status->axis[which][axis] = digital_value;
      break;
    }

    case SDL_JOYBUTTONDOWN:
    {
      int which = event->jbutton.which;
      int button = event->jbutton.button;
      enum keycode stuffed_key = input.joystick_button_map[which][button];

      if(stuffed_key)
        joystick_key_press(status, stuffed_key, stuffed_key);

      break;
    }

    case SDL_JOYBUTTONUP:
    {
      int which = event->jbutton.which;
      int button = event->jbutton.button;
      enum keycode stuffed_key = input.joystick_button_map[which][button];

      if(stuffed_key)
        joystick_key_release(status, stuffed_key);

      break;
    }
    
    case SDL_JOYHATMOTION:
    {
      int which = event->jhat.which;
      int dir = event->jhat.value;
      enum keycode key_up = input.joystick_hat_map[which][0];
      enum keycode key_down = input.joystick_hat_map[which][1];
      enum keycode key_left = input.joystick_hat_map[which][2];
      enum keycode key_right = input.joystick_hat_map[which][3];
      
      //if(dir & SDL_HAT_CENTERED)
      {
        joystick_key_release(status, key_up);
        joystick_key_release(status, key_down);
        joystick_key_release(status, key_left);
        joystick_key_release(status, key_right);
      }
    
      if(dir & SDL_HAT_UP)
      {
        if (key_up)
          joystick_key_press(status, key_up, key_up);
      }
      
      if(dir & SDL_HAT_DOWN)
      {
        if (key_down)
          joystick_key_press(status, key_down, key_down);
      }
      
      if(dir & SDL_HAT_LEFT)
      {
        if (key_left)
          joystick_key_press(status, key_left, key_left);
      }
      
      if(dir & SDL_HAT_RIGHT)
      {
        if (key_right)
          joystick_key_press(status, key_right, key_right);
      }
      
      break;
    }

    default:
      return false;
  }

  return true;
}

bool __update_event_status(void)
{
  Uint32 rval = false;
  SDL_Event event;

  while(SDL_PollEvent(&event))
    rval |= process_event(&event);

  return rval;
}

// This returns whether the input buffer _may_ contain a request to quit.
// Proper polling should be performed if the answer is yes.
bool __peek_exit_input(void)
{
  #if SDL_VERSION_ATLEAST(2,0,0)
  SDL_Event events[256];
  int num_events, i;
  SDL_PumpEvents();
  num_events = SDL_PeepEvents(events, 256, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
  for (i = 0; i < num_events; i++) {
    if (events[i].type == SDL_QUIT) return true;
    if (events[i].type == SDL_KEYDOWN) {
      SDL_KeyboardEvent *ev = (SDL_KeyboardEvent *) &events[i];
      if (ev->keysym.sym == SDLK_ESCAPE) return true;
      if (ev->keysym.sym == SDLK_c && ev->keysym.mod & KMOD_CTRL) return true;
      if (ev->keysym.sym == SDLK_F4 && ev->keysym.mod & KMOD_ALT) return true;
    }
  }

  #else /* !SDL_VERSION_ATLEAST(2,0,0) */

  // FIXME: SDL supports SDL_PeepEvents but the implementation is
  // different

  #endif /* SDL_VERSION_ATLEAST(2,0,0) */

  return false;
}

#if !SDL_VERSION_ATLEAST(2,0,0)
static int SDL_WaitEventTimeout(SDL_Event *event, int timeout)
{
  // SDL 1.2 doesn't have SDL_WaitEventTimeout. The suggested alternative
  // is to use timers, but this was simpler and most things won't use this
  // SDL version anyway.

  int i = timeout;
  int anyEvent = 0;

  while(timeout>0 && !anyEvent)
  {
    i--;
    delay(1);
    anyEvent = SDL_PollEvent(event);

    // If an autorepeat triggers, it needs to be processed.
    if(update_autorepeat_sdl())
      break;

    // "Fix" awful intake cursor blinking
    if(!(i&7))
      update_screen();
  }

  return anyEvent;
}
#endif

void __wait_event(int timeout)
{
  SDL_Event event;
  int anyEvent;

  // FIXME: WaitEvent with MSVC hangs the render cycle, so this is, hopefully,
  //        a short-term fix.
  #ifdef MSVC_H
    anyEvent = SDL_PollEvent(&event);
  #else
    if (!timeout) {
      anyEvent = SDL_WaitEvent(&event);
    } else {
      anyEvent = SDL_WaitEventTimeout(&event, timeout);
    }
  #endif
  if (anyEvent) process_event(&event);
}

void real_warp_mouse(Uint32 x, Uint32 y)
{
  SDL_Window *window = SDL_GetWindowFromID(sdl_window_id);
  SDL_WarpMouseInWindow(window, x, y);
}

void initialize_joysticks(void)
{
  int i, count;

  count = SDL_NumJoysticks();

  if(count > 16)
    count = 16;

  for(i = 0; i < count; i++)
  {
    SDL_JoystickOpen(i);
  }

  SDL_JoystickEventState(SDL_ENABLE);
}
