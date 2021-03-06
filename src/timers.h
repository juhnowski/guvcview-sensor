/*******************************************************************************#
#           guvcview              http://guvcview.sourceforge.net               #
#                                                                               #
#           Paulo Assis <pj.assis@gmail.com>                                    #
#           Ilya Juhnowski <juhnowski@gmail.com>                                #
#                                                                               #
# This program is free software; you can redistribute it and/or modify          #
# it under the terms of the GNU General Public License as published by          #
# the Free Software Foundation; either version 2 of the License, or             #
# (at your option) any later version.                                           #
#                                                                               #
# This program is distributed in the hope that it will be useful,               #
# but WITHOUT ANY WARRANTY; without even the implied warranty of                #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 #
# GNU General Public License for more details.                                  #
#                                                                               #
# You should have received a copy of the GNU General Public License             #
# along with this program; if not, write to the Free Software                   #
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA     #
#                                                                               #
********************************************************************************/

#ifndef TIMERS_H
#define TIMERS_H

#include <glib.h>

gboolean
shutd_timer(gpointer data);

gboolean
timer_callback(gpointer data);

gboolean
Image_capture_timer(gpointer data);

gboolean 
FpsCount_callback(gpointer data);

gboolean
ximu_timer_callback(gpointer data);

gboolean
tenso_timer_callback(gpointer data);

gboolean
encoder_timer_callback(gpointer data);

/*
 * Not a timer callback
 * Regular function to determine if enought free space is available
 * returns TRUE if still enough free space left on disk
 * FALSE otherwise
 */
gboolean
DiskSupervisor(gpointer data);

/* called by video capture every 10 sec for checking disk free space*/
gboolean 
FreeDiskCheck_timer(gpointer data);

/* check for udev events for v4l2 devices*/
gboolean 
check_v4l2_udev_events(gpointer data);

#endif
