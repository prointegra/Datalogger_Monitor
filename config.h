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
@File config.h
*/
#ifndef _CONFIG_
#define _CONFIG_
#include "../lib/pugixml-1.5/src/pugixml.hpp"
#include <iostream>
#include <stdio.h>
#include "rldataacquisition.h"

using namespace std;


//members
/*!register to save*/
typedef struct 
{
  int index;
  char tag_name[12];
  int valueLL;
  int valueL;
  int valueH;
  int valueHH;
  char date[20];
  char time[20];
  int cycle;
  char comment[100];
  int type;
} mbRegData;

//members
/*!register trnasmitted*/
typedef struct 
{
  int Datatype;
  string address;
  string addressH;
  string addressHH;
  string addressHHH;
} mbReadData;

//members
/*!slaves to communicate with*/
typedef struct 
{
  int slaveId;
  rlDataAcquisition* Mailbox;//!rl Data adquisitio instance, used to retrieve data from modbus
  int mTime;
  mbReadData* Registers;
  int nRegs;
} mbSlaves;


class MonConfigurator 
{
 public:
  MonConfigurator (char *);

  int IterateComms();
  int RetrieveConfig();
  int getnumSlaves(){return nSlaves;}
  int getSlaveId(int id);
  int getSlaveMailbox(int id,rlDataAcquisition **);
  int getSlavemTime(int id);
  int getSlavenRegs(int id); 
  int getSlaveReadData(int id,mbReadData **);

 private:
  pugi::xml_document doc;
  //number of slaves and type
  mbSlaves* ConfigSlaves;
  int nSlaves;

  const char* stypes[2] = {"INT","MOD10"};
  const int itypes[2]= {1,10};
  const int ntypes = 2;
};




#endif
