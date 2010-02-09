/* MegaZeux
 *
 * Copyright (C) 1996 Greg Janson
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

/* Declarations for EDIT.CPP */

#ifndef __EDITOR_EDIT_H
#define __EDITOR_EDIT_H

#include "compat.h"

__M_BEGIN_DECLS

#include "../world_struct.h"

void edit_world(World *mzx_world);
int place_current_at_xy(World *mzx_world, mzx_thing id, int color,
 int param, int x, int y, Robot *copy_robot, Scroll *copy_scroll,
 Sensor *copy_sensor, int overlay_edit);

extern char debug_mode; // Debug mode
extern char debug_x; // Debug box x pos

#ifdef CONFIG_AUDIO
extern const char *mod_gdm_ext[];
#endif

#define EC_MAIN_BOX           25
#define EC_MAIN_BOX_DARK      16
#define EC_MAIN_BOX_CORNER    24
#define EC_MENU_NAME          27
#define EC_CURR_MENU_NAME     159
#define EC_MODE_STR           30
#define EC_MODE_HELP          31
#define EC_CURR_THING         31
#define EC_CURR_PARAM         23
#define EC_OPTION             26
#define EC_HIGHLIGHTED_OPTION 31
#define EC_DEBUG_BOX          DI_INPUT_BOX
#define EC_DEBUG_BOX_DARK     DI_INPUT_BOX_DARK
#define EC_DEBUG_BOX_CORNER   DI_INPUT_BOX_CORNER
#define EC_DEBUG_LABEL        DI_INPUT_BOX_LABEL
#define EC_DEBUG_NUMBER       79
#define EC_NA_FILL            1

__M_END_DECLS

#endif // __EDITOR_EDIT_H