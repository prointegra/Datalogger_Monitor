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
@File database.h
*/
#ifndef _DATABASE_
#define _DATABASE_

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <mysql.h>
#include "config.h"



class databaseAccess
{
 public:
  databaseAccess();
  virtual int dbInit() =0;
  //
  virtual int dbClearIndex() =0;
  virtual int dbAppendIndex(char *) =0;
  //
  virtual int dbSaveEnergy(int comm, int registros, mbRegData** regMatrix) = 0;
 protected:
  MYSQL * pmysql;
  //MonCaptureDevice* devicesInterf;
 
};

class mysqlAccess : public databaseAccess 
{
 public:
  /*!constructor*/
   mysqlAccess();
   /*!database initialization*/
   int dbInit();
   int dbEnergyInit();
   int dbEventsInit();
   int dbIndexInit();
   //
   int dbClearIndex();
   //   int dbClearEvents();
   //int dbClearEnergy();   
   int dbAppendIndex(char * path);
   //capture
   // int dbSaveEvents(int comm,int registros, mbRegData** regMatrix);
   int dbSaveEnergy(int comm, int registros, mbRegData** regMatrix);
 private:
 
};


#endif
