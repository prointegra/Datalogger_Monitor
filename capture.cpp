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

/**
@file capture.c
*/

#include "capture.h"


/*! Constructor*/
MonCaptureDevice::MonCaptureDevice()
{
  errCount = 0;
 return;   
}

int MonCaptureDevice::getRegisterT(int reg)
{
  if(reg >= 0 && reg < nRegs)
    return registers[reg].Datatype;
  else
    return -1;
}
const char * MonCaptureDevice::getRegisterA(int reg)
{

  if(reg >= 0 && reg < nRegs)
    return registers[reg].address.c_str();
  else
    return NULL; 
}
/*! Capture Data to device*/
int MonCaptureDevice::captureDataDevice(time_t time)
{
  double seconds =  difftime(time,lastTime);
  
  if(mTime <= 0)
    {
      // cout << "CONTINOUS MONITORING NOT IMPLEMENTED YET" << endl;
      return 0;
    }
  if(seconds > (double) mTime)
    {
      cout << "INFO: capturando esclavo nº:" << slaveId << endl;
      if(!getDataMailbox(time))
	lastTime = time;
      else
	cout << "ERROR: getting data from mailbox" << endl;
      // cout <<"DEBUG: out from capturedatadevice" << endl;
      return 0;
    }
      
 return -1;   
}

/*! Capture Data to device*///deberemos ahcerlo distinto si son eventos a si son por tiempo
int MonCaptureDevice::getDataMailbox(time_t now)
{
  int i=0;

  cout << "DEBUG: in getDataMailbox " << endl;
  if(readData)
    delete readData;
  readData = new mbRegData[nRegs];

  for(i=0;i<nRegs; i++)
    {
      saveRegister(i);
      saveDate(i, now);
    }

  return 0;
}
/*! save register from mailbox*/
int MonCaptureDevice::saveRegister(int reg)
{
  //typedef struct 
  //{
  //int index;
  //char tag_name[12];
  //int valueLL;
  //int valueL;
  //int valueH;
  //int valueHH;
  //char date[12];
  //char time[10];
  //int cycle;
  //char comment[100];
  //char type[10];
  //} mbRegData;
  //que tipo de registro es?
  cout << "DEBUG: in saveRegister " << endl;
  readData[reg].type = registers[reg].Datatype;
  switch(readData[reg].type)
    {
    case(1): //TIPO INT
      readData[reg].valueL = mailbox->intValue(registers[reg].address.c_str());
      //ERROR?
      if(readData[reg].valueL == DAQ_ERROR)
	readData[reg].err = 1;
      else
	readData[reg].err = 0;
      /////////
      readData[reg].index = reg+1;

      break;
    case(10): //TIPO MOD10
      if(!addAddress_n(reg,3))//add 3 addresses to register reg
	{
	  //cout <<"DEBUG:" << endl << registers[reg].address.c_str() << endl;
	  //cout <<registers[reg].addressH << endl;
	  //cout <<registers[reg].addressHH << endl;
	  // cout <<registers[reg].addressHHH << endl;
	  readData[reg].valueLL = mailbox->intValue(registers[reg].address.c_str());	  
	  readData[reg].valueL = mailbox->intValue(registers[reg].addressH.c_str());
	  readData[reg].valueH = mailbox->intValue(registers[reg].addressHH.c_str());	  
	  readData[reg].valueHH = mailbox->intValue(registers[reg].addressHHH.c_str());
	  //ERROR?
	  if((readData[reg].valueL == DAQ_ERROR) || (readData[reg].valueLL == DAQ_ERROR) || (readData[reg].valueH == DAQ_ERROR)|| (readData[reg].valueHH == DAQ_ERROR))
	    readData[reg].err = 1;
	  else
	    readData[reg].err = 0;
	  /////////
	}
      else
	{
	  readData[reg].valueL = mailbox->intValue(registers[reg].address.c_str());
	}
	  
	  
      readData[reg].index = reg+1;
      
      break;
    default:
      return 1;
    }
  cout << "DEBUG: out from save register" << endl;
  return 0;
}
/*! save register date from mailbox*/
int MonCaptureDevice::saveDate(int reg,time_t now)
{
  //typedef struct 
  //{
  //int index;
  //char tag_name[12];
  //int valueLL;
  //int valueL;
  //int valueH;
  //int valueHH;
  //char date[12];
  //char time[10];
  //int cycle;
  //char comment[100];
  //char type[10];
  //} mbRegData;
  time_t rnow;
  string date,hours;
  

  time(&rnow);
  struct tm *timeinfo;
  
  cout << "DEBUG: in saveDate " << endl;
  timeinfo = localtime(&rnow);

  cout << "DEBUG: en los sprintfs" << endl;
  sprintf(readData[reg].date,"%d-%d-%d",timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday);
  sprintf(readData[reg].time,"%d:%d:%d",timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
  
 
  cout << "DEBUG: out from save date" << endl;
  return 0;
}

/*! print register data, for debug purposes*/
int MonCaptureDevice::printRegister(int reg)
{
  cout <<"**DEBUG**" << endl;
  cout << "register: " << reg+1 << endl;
  cout << "index: " << readData[reg].index << endl;
  cout << "value: " << readData[reg].valueL << endl;
  cout << "date: "  << readData[reg].date << endl;
  cout << "time: "  << readData[reg].time << endl;
  cout <<"**END DEBUG**" << endl;
}
/*! print register data, for debug purposes*/
int MonCaptureDevice::addAddress_n(int reg, int n)
{//SOLO MODBUS
  string backreg;
  size_t found,found2;
  string nregister;
  int number;
  char buff[100];
  
  if(n> 0)
    {
      found = registers[reg].address.rfind(",");
      found2 = registers[reg].address.rfind(")");
      nregister = registers[reg].address.substr(found+1,found2-found);
      stringstream(nregister) >> number;
      if(number >= 0)
	number++;
      registers[reg].addressH = registers[reg].address.substr(0,found+1); 
      sprintf(buff,"%s%d)",registers[reg].addressH.c_str(),number);
      registers[reg].addressH = buff;
    }
  if(n>1)
    {
      number++;
      registers[reg].addressHH = registers[reg].address.substr(0,found+1); 
      sprintf(buff,"%s%d)",registers[reg].addressHH.c_str(),number);
      registers[reg].addressHH = buff;
    }
  if(n>2)
    {
      number++;
      registers[reg].addressHHH = registers[reg].address.substr(0,found+1); 
      sprintf(buff,"%s%d)",registers[reg].addressHHH.c_str(),number);
      registers[reg].addressHHH = buff;
    }
  return 0;

}





///////////////////////////////////////
///////////////////////////////////////
/*!iterate example*/
MonCapturer::MonCapturer()
{
  return;
}
/*!load configuration to memory for working*/
int MonCapturer::initFromConfig(MonConfigurator** OrigConfig)
{
  MonConfigurator* config;
  int i,j;
  rlDataAcquisition* tMailbox;//!rl Data adquisitio instance, used to retrieve data from modbus
  mbReadData* tRegisters;
  //cout << "INSIDE INIT FROM CONFIG " << endl;
  config = *OrigConfig;
  //number of capture devices and saving memory for
  devices = config->getnumSlaves(); 
  //cout << "DEVICES = " << devices << endl;
  if (devicesInterf)
    delete(devicesInterf);
  devicesInterf = new MonCaptureDevice[devices];
  //
  //populating devices data
  //cout << "MEMORY DATA!!" << endl;
  for (i=0; i<devices ;i++)
    {
      //cout << "************************************" << endl;
      //cout << "*** SLAVE "<< i+1 <<" ***" << endl;
      cout << endl;

      devicesInterf[i].setId(config->getSlaveId(i));
      //substract 1, to have the capture finished in the smaple time, and not started (it fihishes one second later then)
      devicesInterf[i].setmTime(config->getSlavemTime(i) -1);
      devicesInterf[i].setnRegs(config->getSlavenRegs(i));

      //cout << " ID = " << devicesInterf[i].getId() << endl;
      //cout << " mTime = " << devicesInterf[i].getmTime() << endl;
      //cout << " registers = " << devicesInterf[i].getnRegs() << endl;
 
      config->getSlaveMailbox(i,&tMailbox);
      devicesInterf[i].setMailBox(&tMailbox);
      
      // cout << "** REGISTROS **" << endl;
      config-> getSlaveReadData(i,&tRegisters);
      devicesInterf[i].setRegisters(devicesInterf[i].getnRegs());
           
      for(j=0;j<devicesInterf[i].getnRegs();j++)
	{
	  //	  cout << " numero = " << j+1 <<  endl;
	  devicesInterf[i].setRegisterType(j, tRegisters[j].Datatype);
	  devicesInterf[i].setRegisterAddress(j, tRegisters[j].address);
	  //cout << " tipo = " << devicesInterf[i].getRegisterT(j) << endl;
	  //cout << " direccion = " << devicesInterf[i].getRegisterA(j)  << endl;
	  cout << endl;
	}
      
    }
  
  return 0;
}
/*!function for showing what are we getting from configuration layer*/
int MonCapturer::showConfig()
{

  int i,j;

  cout << "MEMORY DATA!!" << endl;
  cout << "DEVICES LOADED = " << devices << endl;
  for (i=0; i<devices ;i++)
    {
      cout << "************************************" << endl;
      cout << "*** SLAVE "<< i+1 <<" ***" << endl;
      cout << endl;

      cout << " ID = " << devicesInterf[i].getId() << endl;
      cout << " mTime = " << devicesInterf[i].getmTime() << endl;
      cout << " registers = " << devicesInterf[i].getnRegs() << endl;
 

      
      cout << "** REGISTROS **" << endl;

           
      for(j=0;j<devicesInterf[i].getnRegs();j++)
	{
	  cout << " numero = " << j+1 <<  endl;
	  cout << " tipo = " << devicesInterf[i].getRegisterT(j) << endl;
	  cout << " direccion = " << devicesInterf[i].getRegisterA(j)  << endl;
	  cout << endl;
	}
      
    }
  
  return 0;
}
/*!function to capture data from all devices*/
int MonCapturer::captureData()
{

  int i,j;
  time_t now;
  double seconds;
  time(&now);
  for(i = 0; i <devices ; i++)
    {
      //time(&now); BUG: accumulative time error
      if(!devicesInterf[i].captureDataDevice(now))
	captureDB(i);
    }
  // cout << "DEBUG: out from captureData" << endl;
  return 0;
}

/*!function to capture data from all devices*/
int MonCapturer::showCapturedData()
{

  int i,j;
 

  for(i = 0; i <devices ; i++)
    {
      for(j=0;j<devicesInterf[i].getnRegs();j++)
	{
	  try
	    {
	      cout << "DEBUG: PRINTING SLAVE: " << i << "REGISTER: " << j << endl;
	      devicesInterf[i].printRegister(j);
	      throw 0;
	    }
	  catch(int e)
	    {
	      cout << "ERROR: slave: " << i+1 << " has no register: " << j+1 << " saved" << endl;
	      //return 1;
	    }
	}
    }
 
  return 0;
}
/*!function to save device data to database*/
int MonCapturer::initDatabase()
{
  //INICIAMOS DATABASE
  if(database != NULL)
    delete(database);
  database = new mysqlAccess;

  database->dbInit();
  database->dbClearIndex();
  //INSERTING ALL INTERFACES, IMPROVE
  database->dbAppendIndex("../comm/modbus_rtu_client/rtu.csv");
  //database->dbAppendIndex("../comm/modbus_client/tcp.csv");
  return 0;
}
/*!function to save device data to database*/


int MonCapturer::captureDB(int comm)
{
  //  cout << "DEBUG: inside  captureDB" << endl;
  mbRegData *tData;
  if(comm >= 0)
    {
      //    cout << "DEBUG: getmtime" << devicesInterf[comm].getmTime() <<  endl;
      if(devicesInterf[comm].getmTime()> 0)
	{
	  //getting registers from comm to store
	  devicesInterf[comm].getReadRegisters(&tData);
	  //store registers to db
	  database->dbSaveEnergy(comm,devicesInterf[comm].getnRegs(),&tData);
	}
      else //EVENTS?
	return 1;
      //database->dbSaveEvents(&);
    }
  // cout << "DEBUG: outside  captureDB" << endl;
  return 0;
}
