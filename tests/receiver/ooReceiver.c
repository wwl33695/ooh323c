/*
 * Copyright (C) 2004 by Objective Systems, Inc.
 *
 * This software is furnished under an open source license and may be
 * used and copied only in accordance with the terms of this license.
 * The text of the license may generally be found in the root
 * directory of this installation in the COPYING file.  It
 * can also be viewed online at the following URL:
 *
 *   http://www.obj-sys.com/open/license.html
 *
 * Any redistributions of this file including modified versions must
 * maintain this copyright notice.
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>



#include "ooReceiver.h"
#include "H323-MESSAGES.h"
#include "ooasn1.h"
#include "ooh323ep.h"

#include "oo.h"
#include "ooports.h"
#include "ooStackCmds.h"
#include "oosndrtp.h"

#ifndef _OOCHANNELS_H_
#include "oochannels.h"
#endif
#ifndef _WIN32
#include <pthread.h>
#endif

int osEpOnCallCleared(ooCallData* call );

char callToken[20];
int isCallActive;
int main(int argc, char ** argv)
{
  int ret=0;

   H245AudioCapability audioCap;
#ifdef _WIN32
   HANDLE threadHdl;
#else
   pthread_t threadHdl;
#endif

#ifdef _WIN32
   ooSocketsInit (); /*Initialize the windows socket api  */
#endif

   ret = ooInitializeH323Ep("receiver.log", 0, 0, 28, 9, 0, 61, "obj-sys",
                      "Version 0.3", T_H225CallType_pointToPoint, 1720,
                      "objsyscall", "receiver", 0);
   if(ret != OO_OK)
   {
      printf("Failed to initialize H.323 Endpoint\n");
      return -1;
   }
   audioCap.t = T_H245AudioCapability_g711Ulaw64k;
   audioCap.u.g711Ulaw64k = 240;
   ooAddAudioCapability(audioCap, OO_RXTX_CAP,
                             &osEpStartReceiveChannel, NULL,
                             &osEpStopReceiveChannel, NULL);
   ooH323EpRegisterCallbacks(&osEpOnIncomingCall, NULL, NULL, &osEpOnCallCleared, NULL);
   /* Load plug-in*/
#ifdef _WIN32
   ret = ooLoadSndRTPPlugin("oomedia.dll");
   if(ret != OO_OK)
   {
      printf("\n Failed to load the media plug-in library - oomedia.dll\n");
      exit(0);
   }
#else
   ret = ooLoadSndRTPPlugin("liboomedia.so");
   if(ret != OO_OK)
   {
      printf("\n Failed to load the media plug-in library - liboomedia.so\n");
      exit(0);
   }
#endif
  
  /* Create H.323 Listener */
   ret = ooCreateH323Listener();
   if(ret != OO_OK)
   {
      OOTRACEERR1("Failed to Create H.323 Listener");
      return -1;
   }
   /* This thread is created to monitor user input on stdin while stack is
      monitoring sockets. Required for windows as windows does not allow
      file handles(i.e. stdin in this case) to be monitored by select.
   */
#ifdef _WIN32
   threadHdl = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)osEpHandleCommand,
                            0, 0, 0);
#else
   pthread_create(&threadHdl, NULL, osEpHandleCommand, NULL);
#endif
   /*Monitor channels for incoming messages*/
   ooMonitorChannels();

   return ASN_OK;
}

int osEpStartReceiveChannel(ooCallData *call)
{
   printf("Starting receive channel %s:%d\n", call->localIP, call->localRtpPort);
   ooCreateReceiveRTPChannel(call->localIP,
                              call->localRtpPort);
   ooStartReceiveAudioAndPlayback();
   return OO_OK;
}

int osEpStopReceiveChannel(ooCallData *call)
{
   printf("Stopping Receive Channel\n");
   ooStopReceiveAudioAndPlayback();
   return OO_OK;
}


/* This function handles used commands. This function is basically used
   as a callback function on linux as we can monitor stdin with sockets
   on linux. On windows, however, this function is used as a separate
  thread monitoring user activity.
*/  
void* osEpHandleCommand(void* dummy)
{
   int ret;
   char command[20];
   printf("Hit <ENTER> to hang call\n");
   memset(command, 0, sizeof(command));
   fgets(command, 20, stdin);
   if(isCallActive)
   {
      printf("Hanging up call\n");
      ret = ooHangCall(callToken);
      printf("Hit <ENTER> to quit\n");
      fgets(command, 20, stdin);
   }
   else{
      printf("No active call\n");
   }
   printf("Closing stack\n");
   ret = ooStopMonitor();
   return dummy;
}

int osEpOnIncomingCall(ooCallData* call )
{
   strcpy(callToken, call->callToken);
   isCallActive = 1;
   return OO_OK;
}

int osEpOnCallCleared(ooCallData* call )
{
   printf("Call Ended\n");
   isCallActive = 0;
   return OO_OK;
}
