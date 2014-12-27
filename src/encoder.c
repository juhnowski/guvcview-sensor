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
#include <stdio.h>
#include <phidget21.h>


#define __ENCODER_MUTEX &meta->encoder_mutex
struct ALL_DATA *all_data;

int CCONV EncoderAttachHandler(CPhidgetHandle ENC, void *userptr)
{
        int serialNo;
        CPhidget_DeviceID deviceID;
        int i, inputcount;

        CPhidget_getSerialNumber(ENC, &serialNo);

        //Retrieve the device ID and number of encoders so that we can set the enables if needed
        CPhidget_getDeviceID(ENC, &deviceID);
        CPhidgetEncoder_getEncoderCount((CPhidgetEncoderHandle)ENC, &inputcount);
        printf("Encoder %10d attached! \n", serialNo);

        //the 1047 requires enabling of the encoder inputs, so enable them if this is a 1047    
        if (deviceID == PHIDID_ENCODER_HS_4ENCODER_4INPUT)
        {
                printf("Encoder requires Enable. Enabling inputs....\n");
                for (i = 0 ; i < inputcount ; i++)
                        CPhidgetEncoder_setEnabled((CPhidgetEncoderHandle)ENC, i, 1);
        }
        return 0;
}


int CCONV EncoderDetachHandler(CPhidgetHandle ENC, void *userptr)
{
	int serialNo;
	CPhidget_getSerialNumber(ENC, &serialNo);
	printf("Encoder %10d detached! \n", serialNo);

	return 0;
}

int CCONV EncoderErrorHandler(CPhidgetHandle ENC, void *userptr, int ErrorCode, const char *Description)
{
	printf("Error handled. %d - %s \n", ErrorCode, Description);

	return 0;
}

int CCONV EncoderInputChangeHandler(CPhidgetEncoderHandle ENC, void *usrptr, int Index, int State)
{
	printf("Input #%i - State: %i \n", Index, State);

	return 0;
}

int CCONV EncoderPositionChangeHandler(CPhidgetEncoderHandle ENC, void *usrptr, int Index, int Time, int RelativePosition)
{
	clock_t t;
	float f;
	int Position;
	CPhidgetEncoder_getPosition(ENC, Index, &Position);
	
	t = clock();
	f = ((float)t)/CLOCKS_PER_SEC;
	
	
	struct metaData *meta = all_data->mdata;
	ENCODER *ed = meta->edata;
	EncoderBuff *eb = ed->ebuff;
	struct GLOBAL *global = all_data->global;
	
	eb->time_stamp = f;
	eb->frame->position = Position;
	eb->frame->relativePosition = RelativePosition;
	eb->frame->time = Time;
	
	if(global->debug) g_print("Time: %f Encoder #%i - Position: %5d -- Relative Change %2d -- Elapsed Time: %5d \n",f, Index, Position, RelativePosition, Time);
	
	return 0;
}

//Display the properties of the attached phidget to the screen.  We will be displaying the name, serial number and version of the attached device.
//Will also display the number of inputs and encoders on this device
int display_properties(CPhidgetEncoderHandle phid)
{
	int serialNo, version, num_inputs, num_encoders;
	const char* ptr;

	CPhidget_getDeviceType((CPhidgetHandle)phid, &ptr);
	CPhidget_getSerialNumber((CPhidgetHandle)phid, &serialNo);
	CPhidget_getDeviceVersion((CPhidgetHandle)phid, &version);

	CPhidgetEncoder_getInputCount(phid, &num_inputs);
	CPhidgetEncoder_getEncoderCount(phid, &num_encoders);

	printf("%s\n", ptr);
	printf("Serial Number: %10d\nVersion: %8d\n", serialNo, version);
	printf("Num Encoders: %d\nNum Inputs: %d\n", num_encoders, num_inputs);

	return 0;
}

void *encoder_loop(void *data)
{
    all_data = (struct ALL_DATA *) data; //struct ALL_DATA *
    struct metaData *meta = all_data->mdata;
    
    gboolean signalquit = FALSE;
    
	int result;
	const char *err;

	//Declare an encoder handle
	CPhidgetEncoderHandle encoder = 0;

  while (1) 
  {
	//create the encoder object
	CPhidgetEncoder_create(&encoder);

	//Set the handlers to be run when the device is plugged in or opened from software, unplugged or closed from software, or generates an error.
	CPhidget_set_OnAttach_Handler((CPhidgetHandle)encoder, EncoderAttachHandler, NULL);
	CPhidget_set_OnDetach_Handler((CPhidgetHandle)encoder, EncoderDetachHandler, NULL);
	CPhidget_set_OnError_Handler((CPhidgetHandle)encoder, EncoderErrorHandler, NULL);

	//Registers a callback that will run if an input changes.
	//Requires the handle for the Phidget, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
	CPhidgetEncoder_set_OnInputChange_Handler(encoder, EncoderInputChangeHandler, NULL);

	//Registers a callback that will run if the encoder changes.
	//Requires the handle for the Encoder, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
	CPhidgetEncoder_set_OnPositionChange_Handler (encoder, EncoderPositionChangeHandler, NULL);

	CPhidget_open((CPhidgetHandle)encoder, -1);

	//get the program to wait for an encoder device to be attached
	printf("Waiting for encoder to be attached....");
	if((result = CPhidget_waitForAttachment((CPhidgetHandle)encoder, 10000)))
	{
		CPhidget_getErrorDescription(result, &err);
		printf("Problem waiting for attachment: %s\n", err);
		__LOCK_MUTEX(__ENCODER_MUTEX);
		meta->encoder_quite = TRUE;
		signalquit = TRUE;
		__UNLOCK_MUTEX(__ENCODER_MUTEX);
	}
	else
	{
	  //Display the properties of the attached encoder device
	  display_properties(encoder);
	}
	
	while (signalquit == FALSE) 
	  {
	    __LOCK_MUTEX(__ENCODER_MUTEX);
            signalquit = meta->encoder_quite;
	    __UNLOCK_MUTEX(__ENCODER_MUTEX);
	  }

	CPhidget_close((CPhidgetHandle)encoder);
	CPhidget_delete((CPhidgetHandle)encoder);

	while (signalquit == TRUE) 
	  {
	    __LOCK_MUTEX(__ENCODER_MUTEX);
            signalquit = meta->encoder_quite;
	    __UNLOCK_MUTEX(__ENCODER_MUTEX);
	  }

  }
}
