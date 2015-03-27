/*
 * 	Prointegra Datalogger, Monitor
 *
 *  Copyright 2014-2015 by it's authors. 
 *
 *  Some rights reserved. See COPYING, AUTHORS.
 *  This file may be used under the terms of the GNU General Public
 *  License version 3.0 as published by the Free Software Foundation
 *  and appearing in the file COPYING included in the packaging of
 *  this file.
 *
 *  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 *  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */
/*!
@File capture.h
*/
#ifndef _CAPTURE_
#define _CAPTURE_
#include "../lib/pugixml-1.5/src/pugixml.hpp"
#include <iostream>
#include <stdio.h>
#include <sstream>
#include "config.h"
#include <time.h>
#include "database.h"
//#include "piMysql.h"
//#include "piCsv.h"








class MonCaptureDevice 
{
 public:
  MonCaptureDevice();
  //
  int captureDataDevice(time_t);
  int getDataMailbox(time_t);
  int saveRegister(int);
  int saveDate(int reg,time_t now);

  //
  int setId(int data){slaveId = data; return 0;}
  int getId(){return slaveId;}
  int setmTime(int data){mTime = data; return 0;}
  int getmTime(){return mTime;}
  int setnRegs(int data){nRegs = data; return 0;}
  int getnRegs(){return nRegs;}
  int setMailBox(rlDataAcquisition** data){mailbox = *data; return 0;}
  int getMailBox(rlDataAcquisition** data){*data = mailbox; return 0;}
  int setRegisters(int num){if (num >= 0){ registers = new mbReadData[num]; return 0;}else return -1;}
  int freeRegisters(){ delete(registers); return 0;}
  int setRegisterType(int num, int type){if (num >= 0 && num < nRegs){registers[num].Datatype = type;  return 0;}else return -1;}
  int setRegisterAddress(int num, string addr){if (num >= 0 && num < nRegs){registers[num].address = addr; return 0;}else return -1;}

  time_t getLastTime(){return lastTime;}
  int setLastTime(time_t newTime){lastTime = newTime; return 0; }
  ////
  int getRegisterT(int reg);
  const char * getRegisterA(int reg);
  ////
  int printRegister(int reg);
  int getReadRegisters(mbRegData** rData){*rData = readData; return 0;}
  ////
  int addAddress_n(int,int);
 private:
  int slaveId;
  rlDataAcquisition* mailbox;//!rl Data adquisitio instance, used to retrieve data from modbus
  int mTime;
  int nRegs;
  mbReadData* registers;
  mbRegData* readData;
  time_t lastTime;
  

};

class MonCapturer 
{
 public:
  /*!constructor*/
  MonCapturer();
  /*!load configuration from config interfaz*/
  int initFromConfig(MonConfigurator** OrigConfig);
  /*!show config loaded, for debugging*/
  int showConfig();
  int  captureData();
  int captureDB(int);
  int showCapturedData();
  // int IterateComms();
  int getDevices(MonCaptureDevice** interfaz){ *interfaz = devicesInterf; return 0;}
  //database functions
  int initDatabase();
 private:
  // IniRecip();
  // CloseRecip();

  pugi::xml_document doc;

  void *pRecip;
  int id;
  int type;
  int lastPackCaptured;
  int CaptureType;

  databaseAccess *database;
  MonCaptureDevice* devicesInterf;
  int devices;
  
};


#endif
