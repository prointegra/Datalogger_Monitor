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
@file config.c
*/

#include "config.h"


/*! Constructor*/
MonConfigurator::MonConfigurator(char* path)
{
 pugi::xml_parse_result result = doc.load_file(path);
 
 cout << "Load result: " << result.description() << ", comm1 slave number: " << doc.child("comm1").attribute("slave").value() << endl;
 return;   
}

/*!iterate example*/
int MonConfigurator::IterateComms()
{
  char buffer[100];
  ///////
  //**DISPOSITIVOS
  int i=0,j=0;
  for (pugi::xml_node comm = doc.child("comm"); comm; comm = comm.next_sibling("comm"))
    {
      i++;
    }
  ConfigSlaves = new mbSlaves[i];
  nSlaves = i;
  i=0;
  setModbusRTU(0);
  setModbusTCP(0);
  for (pugi::xml_node comm = doc.child("comm"); comm; comm = comm.next_sibling("comm"))
    {
      ConfigSlaves[i].slaveId = comm.attribute("slave").as_int();
      if(!strcmp(comm.attribute("mailbox").value(),"modbus_rtu"))
	{
	  setModbusRTU(1);
	  ConfigSlaves[i].Mailbox = new   rlDataAcquisition("../modbus_rtu.mbx","../modbus_rtu.shm",128536);
	}
      if(!strcmp(comm.attribute("mailbox").value(),"modbus_tcp"))
	{
	  ConfigSlaves[i].Mailbox = new   rlDataAcquisition("../modbus.mbx","../modbus.shm",128536);
	  setModbusTCP(1);
	}
      ConfigSlaves[i].mTime = comm.attribute("mTime").as_int();
      ConfigSlaves[i].nRegs = comm.attribute("registers").as_int(); //iniciamos  el numero de registros a leer
      ConfigSlaves[i].Registers = new mbReadData[ConfigSlaves[i].nRegs];
      i++;
    }
  ///////
  //**REGISTROS
 
  i=0;
  j=0;
 for (pugi::xml_node comm = doc.child("comm"); comm; comm = comm.next_sibling("comm"))
    {
      i=0;
      //checking type
      for(int h=0;h<ntypes;h++)
	{
	  //cout << "DEBUG: comparando entre: " << comm.attribute("Tregister").value() << " y " << stypes[h] << endl;
	  if(!strcmp(comm.attribute("Tregister").value(),stypes[h]))
	    ConfigSlaves[j].Registers[i].Datatype = itypes[h];
	}
      ConfigSlaves[j].Registers[i].address = comm.attribute("Aregister").value();	 
      for(i = 1; i <  ConfigSlaves[j].nRegs;i++)
	{
	  //cout << "slave: " << j << "register; " << i << endl;
	  //cout << "numero de registros: " <<  ConfigSlaves[j].nRegs << endl;
	  //cout << "EN EL FOR!!" << endl;
	  sprintf(buffer,"Tregister%d",i+1);
	  //cout << " DEBUG: " << comm.attribute(buffer).value() << endl;
	  //checking type
	  for(int h=0;h<ntypes;h++)
	    {
	      //cout << "DEBUG: comparando entre: " << comm.attribute(buffer).value() << " y " << stypes[h] << endl;
	      if(!strcmp(comm.attribute(buffer).value(),stypes[h]))
		ConfigSlaves[j].Registers[i].Datatype = itypes[h];
	    }
	  sprintf(buffer,"Aregister%d",i+1);
	  //cout << " DEBUG: " << comm.attribute(buffer).value() << endl;
	  ConfigSlaves[j].Registers[i].address = comm.attribute(buffer).value();

	}
      j++;
      }
  return 0;
}

/*!debug show config information*/
int MonConfigurator::RetrieveConfig()
{
  int i=0,j=0;
  cout << "number of slaves configured: " << nSlaves << endl;

  for (i=0;i<nSlaves;i++)
    {
      cout << "************************************" << endl;
      cout << "*** SLAVE "<< i+1 <<" ***" << endl;
      cout << endl;
   
      cout << " ID = " << ConfigSlaves[i].slaveId << endl;
      cout << " mTime = " << ConfigSlaves[i].mTime << endl;
      cout << " registers = " << ConfigSlaves[i].nRegs << endl;

      cout << "** REGISTROS **" << endl;
      
      for(j=0;j<ConfigSlaves[i].nRegs;j++)
	{
	   cout << " numero = " << j+1 << endl;
	   cout << " tipo = " << ConfigSlaves[i].Registers[j].Datatype << endl;
	   cout << " direccion = " << ConfigSlaves[i].Registers[j].address << endl;
	   cout << endl;
	   }
	 
    }

  return 0;
}
int MonConfigurator::getSlaveId(int id)
{
  if(id >=0 && id <nSlaves)
    return ConfigSlaves[id].slaveId;
  else
    return -1;
}
int MonConfigurator::getSlaveMailbox(int id,rlDataAcquisition **mailBox)
{
  if(id >=0 && id <nSlaves)
    *mailBox = ConfigSlaves[id].Mailbox;
  else
    return -1;
  return 0;
}
int MonConfigurator::getSlavemTime(int id)
{  
  if(id >=0 && id <nSlaves)
    return ConfigSlaves[id].mTime;
  else
    return -1;

}
int MonConfigurator::getSlavenRegs(int id)
{
  if(id >=0 && id <nSlaves)
    return ConfigSlaves[id].nRegs;
  else
    return -1;

}
int MonConfigurator::getSlaveReadData(int id,mbReadData **rData)
{
  if(id >=0 && id <nSlaves)
    *rData = ConfigSlaves[id].Registers;
  else
    return -1;
  return 0;
}

