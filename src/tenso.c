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
#################################################################################
*****************************************************************************************************************************
# This file based on Phidgets Inc. demo code:
# - Encoder simple -
# This example simply creates an Encoder handle, hooks the event handlers, and then waits for an encoder is attached.
# Once it is attached, the program will wait for user input so that we can see the event data on the screen when using the
# encoder.
#
# Copyright 2008 Phidgets Inc.  All rights reserved.
# This work is licensed under the Creative Commons Attribution 2.5 Canada License. 
# view a copy of this license, visit http://creativecommons.org/licenses/by/2.5/ca/
*****************************************************************************************************************************/

#include "tenso.h"
#include "defs.h"
#include "meta.h"
#include "globals.h"
#include "guvcview.h"


#include <stdio.h>
#include <phidget21.h>
#include <glib.h>
#include <time.h>


#define __TENSO_MUTEX &meta->tenso_mutex
#define FREQS_SIZE 20

double bridges[FREQS_SIZE] = {0};
struct ALL_DATA *all_data;

int CCONV TensoAttachHandler(CPhidgetHandle phid, void *userptr)
{
	CPhidgetBridgeHandle bridge = (CPhidgetBridgeHandle)phid;

	CPhidgetBridge_setEnabled(bridge, 0, PTRUE);
	CPhidgetBridge_setEnabled(bridge, 1, PFALSE);
	CPhidgetBridge_setEnabled(bridge, 2, PFALSE);
	CPhidgetBridge_setEnabled(bridge, 3, PTRUE);

	CPhidgetBridge_setGain(bridge, 0, PHIDGET_BRIDGE_GAIN_16);//PHIDGET_BRIDGE_GAIN_128
	CPhidgetBridge_setGain(bridge, 1, PHIDGET_BRIDGE_GAIN_16);
	CPhidgetBridge_setGain(bridge, 2, PHIDGET_BRIDGE_GAIN_32);
	CPhidgetBridge_setGain(bridge, 3, PHIDGET_BRIDGE_GAIN_16);//PHIDGET_BRIDGE_GAIN_64
	CPhidgetBridge_setDataRate(bridge, 10);//1000

	printf("Attach handler ran!\n");
	return 0;
}

int CCONV TensoDetachHandler(CPhidgetHandle phid, void *userptr)
{
	printf("Detach handler ran!\n");
	return 0;
}

int CCONV TensoErrorHandler(CPhidgetHandle phid, void *userptr, int ErrorCode, const char *errorStr)
{
	printf("Tenso Error event: %s\n",errorStr);
	return 0;
}

int CCONV TensoData(CPhidgetBridgeHandle phid, void *userPtr, int index, double val)
{
	CPhidgetBridgeHandle bridge = (CPhidgetBridgeHandle)phid;
	
//	struct ALL_DATA *all_data = (struct ALL_DATA *) data;
	struct metaData *meta = all_data->mdata;
	TENSO *td = meta->tdata;
	struct GLOBAL *global = all_data->global;
	
	clock_t t;
	float f;
	
	t = clock();
	f = ((float)t)/CLOCKS_PER_SEC;
	
	td->tbuff->time_stamp = f;
	switch ( index )
	{
	  case 0: td->tbuff->frame->value_0 = val; break;
	  case 1: td->tbuff->frame->value_1 = val; break;
	  case 2: td->tbuff->frame->value_2 = val; break;
	  case 3: td->tbuff->frame->value_3 = val; break;
	}

	
    
	if(global->debug) g_print("Time: %f  Tenso Event (%d) %lf\n",f,index,val);

	return 0;
}


void display_generic_properties(CPhidgetHandle phid)
{
	int sernum, version;
	const char *deviceptr;
	CPhidget_getDeviceType(phid, &deviceptr);
	CPhidget_getSerialNumber(phid, &sernum);
	CPhidget_getDeviceVersion(phid, &version);

	printf("%s\n", deviceptr);
	printf("Version: %8d SerialNumber: %10d\n", version, sernum);
	return;
}

  /* run in a thread*/
void *tenso_loop(void *data)
{
    all_data = (struct ALL_DATA *) data;
    struct metaData *meta = all_data->mdata;

    gboolean signalquit = FALSE;
    
    const char *err;	
    int result;
    CPhidgetBridgeHandle bridge;

  while (1) 
  {
	    
	    CPhidgetBridge_create(&bridge);

	    CPhidget_set_OnAttach_Handler((CPhidgetHandle)bridge, TensoAttachHandler, NULL);
	    CPhidget_set_OnDetach_Handler((CPhidgetHandle)bridge, TensoDetachHandler, NULL);
	    CPhidget_set_OnError_Handler((CPhidgetHandle)bridge, TensoErrorHandler, NULL);

	    CPhidgetBridge_set_OnBridgeData_Handler(bridge, TensoData, NULL);//all_data - doesn not work

	    CPhidget_open((CPhidgetHandle)bridge, -1);

	    //Wait for 10 seconds, otherwise exit
	    if(result = CPhidget_waitForAttachment((CPhidgetHandle)bridge, 10000))
	    {

		CPhidget_getErrorDescription(result, &err);
		printf("Problem waiting for attachment: %s\n", err);

		__LOCK_MUTEX(__TENSO_MUTEX);
		meta->tenso_quite = TRUE;
		signalquit = TRUE;
		__UNLOCK_MUTEX(__TENSO_MUTEX);
	    }
	    else
	    {
	      display_generic_properties((CPhidgetHandle)bridge);
	      g_print("Tenso: Starting tenso_loop signalquit=%d\n",signalquit);
	    }
	    
	  while (signalquit == FALSE) 
	  {
	    __LOCK_MUTEX(__TENSO_MUTEX);
            signalquit = meta->tenso_quite;
	    __UNLOCK_MUTEX(__TENSO_MUTEX);
	  }
	  
	  g_print("Tenso: Stoping tenso_loop signalquit=%d\n",signalquit);
	  CPhidget_close((CPhidgetHandle)bridge);
	  CPhidget_delete((CPhidgetHandle)bridge);

	  while (signalquit == TRUE) 
	  {
	    __LOCK_MUTEX(__TENSO_MUTEX);
            signalquit = meta->tenso_quite;
	    __UNLOCK_MUTEX(__TENSO_MUTEX);
	  }
  }

}
