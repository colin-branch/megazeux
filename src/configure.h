/* MegaZeux
 *
 * Copyright (C) 2004 Gilead Kutnick <exophase@adelphia.net>
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

#ifndef __CONFIGURE_H
#define __CONFIGURE_H

#include "compat.h"

__M_BEGIN_DECLS

#define OPTION_NAME_LEN 33

enum ratio_type
{
  RATIO_CLASSIC_4_3,
  RATIO_MODERN_64_35,
  RATIO_STRETCH
};

struct config_info
{
  // Video options
  bool fullscreen;
  int resolution_width;
  int resolution_height;
  int window_width;
  int window_height;
  bool allow_resize;
  char video_output[16];
  int force_bpp;
  enum ratio_type video_ratio;
  char gl_filter_method[16];
  int gl_vsync;

  // Audio options
  int output_frequency;
  int buffer_size;
  int oversampling_on;
  int resample_mode;
  int modplug_resample_mode;
  int music_volume;
  int sam_volume;
  int pc_speaker_volume;
  int music_on;
  int pc_speaker_on;

  // Game options
  char startup_path[256];
  char startup_file[256];
  char default_save_name[256];
  int mzx_speed;
  int disassemble_extras;
  int disassemble_base;
  int startup_editor;
  int standalone_mode;
  int no_titlescreen;

  // Misc options
  int mask_midchars;
  bool system_mouse;
    
  // Network layer options
#ifdef CONFIG_NETWORK    
  bool network_enabled;
  char socks_host[256];
  int socks_port;
#endif
    
#ifdef CONFIG_UPDATER
  int update_host_count;
  char **update_hosts;
  char update_branch_pin[256];
#endif
};

typedef void (* config_function)(struct config_info *conf,
 char *name, char *value, char *extended_data);

CORE_LIBSPEC void set_config_from_file(struct config_info *conf,
 const char *conf_file_name);
CORE_LIBSPEC void set_config_from_file_startup(struct config_info *conf,
 const char *conf_file_name);
CORE_LIBSPEC void default_config(struct config_info *conf);
CORE_LIBSPEC void set_config_from_command_line(struct config_info *conf,
 int *argc, char *argv[]);
CORE_LIBSPEC void free_config(struct config_info *conf);

typedef void (* find_change_option)(void *conf, char *name, char *value,
 char *extended_data);

#ifdef CONFIG_EDITOR

CORE_LIBSPEC void __set_config_from_file(find_change_option find_change_handler,
 void *conf, const char *conf_file_name);
CORE_LIBSPEC void __set_config_from_command_line(
 find_change_option find_change_handler, void *conf, int *argc, char *argv[]);

#endif // CONFIG_EDITOR

__M_END_DECLS

#endif // __CONFIGURE_H
