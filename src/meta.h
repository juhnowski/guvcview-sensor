/*******************************************************************************#
#           guvcview              http://guvcview.sourceforge.net               #
#                                                                               #
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

#ifndef META_H
#define META_H
#include "defs.h"
#include <glib.h>
#include "guvcview.h"

typedef struct _XImuRecord //typedef 
{
    float gyroscope[3];
    float accelerometer[3];
    float magnetometer[3];
    float quaternion[4];
    float eulerAngles[3];
    void *next;
    void *prev;
} XImuRecord;

typedef struct _XImuBuff
{
	QWORD time_stamp;
	XImuRecord *frame;
	int bytes_used;
} XimuBuff;

typedef struct _XIMU
{
    int ximu_state;
    int id;
    char* path;
    XimuBuff* data;
    int buff_size;   //size in frames of video buffer
} XIMU;

typedef struct _EncoderRecord
{
  float position;
  int relativePosition;
  int time;
  void *next;
  void *prev;
}EncoderRecord;

typedef struct _EncoderBuff
{
  QWORD time_stamp;
  EncoderRecord *frame;
  int bytes_used;
}EncoderBuff;

typedef struct _ENCODER
{
    int id;
    char* path;
    int rate;
    EncoderBuff *ebuff;
} ENCODER;

typedef struct _TensoRecord
{
    float value_0;
    float value_1;
    float value_2;
    float value_3;
    void *next;
    void *prev;
}TensoRecord;

typedef struct _TensoBuff
{
  QWORD time_stamp;
  TensoRecord *frame;
  int bytes_used;
}TensoBuff;

typedef struct _TENSO
{
    int id;
    char* path;
    int rate;
    int channel_0;
    int channel_1;
    int channel_2;
    int channel_3;
    TensoBuff* tbuff;
}TENSO;

// main meta data interface struct
struct metaData
{
    XIMU* xdata; 	// xIMU sensor settings
    __MUTEX_TYPE ximu_mutex;
    
    ENCODER* edata; 	// Encoder sensor settings
    __MUTEX_TYPE encoder_mutex;
    gboolean encoder_quite;
    gboolean encoder_test_quite;
    
    TENSO* tdata;	// Tenso sensors settings
    __MUTEX_TYPE tenso_mutex;
    gboolean tenso_quite;
    gboolean tenso_test_quite;
};

int initMetaData(struct ALL_DATA *all_data);

int freeMetaData(struct ALL_DATA *all_data);

/*folloing functions submit values and add new empty record*/
int submit_tenso_buff(TensoBuff* buff);
int submit_encoder_buff(EncoderBuff *buff);
int submit_ximu_buff(XimuBuff* data);

/*following functions free allocated buffers*/
int free_tenso_buff(TensoBuff* buff);
int free_encoder_buff(EncoderBuff *buff);
int free_ximu_buff(XimuBuff* buff);

#endif
