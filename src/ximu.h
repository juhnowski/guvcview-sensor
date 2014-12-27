/*******************************************************************************#
#           guvcview              http://guvcview.sourceforge.net               #
#                                                                               #
#           Ilya Juhnowski <juhnowski@gmail.com>                                #
#                         add ximu sensor                                       #
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

#ifndef XIMU_H
#define XIMU_H
  typedef enum {
       XIMU_STATE_INIT                      = 0,
       XIMU_STATE_ENABLE                = 1,
       XIMU_STATE_WAIT                     = 2,
       XIMU_STATE_CAPTURE_START  = 3,
       XIMU_STATE_RUN                       = 4,
       XIMU_STATE_CAPTURE_STOP    = 5,
       XIMU_STATE_CLOSE                   = 6,
       XIMU_STATE_DISABLE                = 7,
       XIMU_STATE_ERROR_INIT           = 8,
       XIMU_STATE_ERROR_WAITING   = 9,
       XIMU_STATE_ERROR_RUNNING  = 10,
       XIMU_STATE_REINIT                    = 11,
       XIMU_STATE_CALIBRATE             = 12,
       XIMU_STATE_START_CALIBRATE  = 13,
       XIMU_STATE_STOP_CALIBRATE  = 14,
       XIMU_STATE_STOP                      = 100
    } XimuStates;

#define XimuStatesCount = 16;

  typedef enum {
	PktError,
	PktCommand,
	PktReadRegister,
	PktWriteRegister,
	PktReadDateTime,
	PktWriteDateTime,
	PktRawBatteryAndThermometerData,
	PktCalBatteryAndThermometerData,
	PktRawInertialAndMagneticData,
 	PktCalInertialAndMagneticData,
	PktQuaternionData,
	PktDigitalIOdata,
	PktRawAnalogueInputData,
	PktCalAnalogueInputData,
	PktPWMoutputData,
	PktRawADXL345busData,
	PktCalADXL345busData,
  } PacketHeader;

  typedef enum {
	ErrNoError,
	ErrFactoryResetFailed,
	ErrLowBattery,
	ErrUSBreceiveBufferOverrun,
	ErrUSBtransmitBufferOverrun,
	ErrBluetoothReceiveBufferOverrun,
	ErrBluetoothTransmitBufferOverrun,
	ErrSDcardWriteBufferOverrun,
	ErrTooFewBytesInPacket,
	ErrTooManyBytesInPacket,
	ErrInvalidChecksum,
	ErrUnknownHeader,
	ErrInvalidNumBytesForPacketHeader,
	ErrInvalidRegisterAddress,
	ErrRegisterReadOnly,
	ErrInvalidRegisterValue,
	ErrInvalidCommand,
	ErrGyroscopeAxisNotAt200dps,
	ErrGyroscopeNotStationary,
	ErrAcceleroemterAxisNotAt1g,
	ErrMagnetometerSaturation,
	ErrIncorrectAuxillaryPortMode,
	ErrUARTreceiveBufferOverrun,
	ErrUARTtransmitBufferOverrun
  } ErrorCode;

  extern float gyroscope[3];
  extern float accelerometer[3];
  extern float magnetometer[3];
  extern float quaternion[4];
  extern float eulerAngles[3];

  int xIMUReceiverIsFramingChar(const unsigned char c);
  ErrorCode xIMUReceiverProcess(const unsigned char* const rxBuf, const unsigned char rxBufSize, PacketHeader* const packetHeader);

  /* run in a thread*/
  void *ximu_loop(void *data);

#endif