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
@file database.cpp
*/

#include "database.h"


/*! Constructor*/
databaseAccess::databaseAccess()
{
 return;   
}


///////////////////////////////////////
///////////////////////////////////////
/*! Constructor*/
mysqlAccess::mysqlAccess()
{
  return;
}
/*! Function to initialize the whole database system needed */
int mysqlAccess::dbInit()
  {

    //initializing pointer
    pmysql = mysql_init(NULL);
    if (pmysql == NULL) 
      {
	fprintf(stderr, "%s\n", mysql_error(pmysql));
	return -1;
      }
    mysql_options(pmysql,MYSQL_OPT_LOCAL_INFILE,"1");
    //Connection to Server
    if (mysql_real_connect(pmysql, "localhost", "prointegra", "prointegra_password", 
			   "datalogger", 0, NULL, 0) == NULL) 
      {
	fprintf(stderr, "%s\n", mysql_error(pmysql));
	mysql_close(pmysql);
	return -1;
      }

    dbEnergyInit();
    dbEventsInit();
    dbIndexInit();

    return 0;
}


/*! Function to initialize the energy data table */
int mysqlAccess::dbEnergyInit()
  {
    //If the events log table doesnt exist, create the table?
    if (mysql_query(pmysql, "CREATE TABLE IF NOT EXISTS ENERGY_LOG(ID INT PRIMARY KEY AUTO_INCREMENT,COMMID INT,TAG_INDICE INT,VALOR FLOAT,HORA TIME,CICLO_DE_PROGRAMA INT,FECHA DATE)"))
      {      
	fprintf(stderr, "%s\n", mysql_error(pmysql));
	mysql_close(pmysql);
	return -1;
      }
    return 0;
  }

/*! Function to initialize the events data table */
int mysqlAccess::dbEventsInit()
  {
    //If the events log table doesnt exist, create the table?
    if (mysql_query(pmysql, "CREATE TABLE IF NOT EXISTS EVENTS_LOG(ID INT PRIMARY KEY AUTO_INCREMENT,COMMID INT, TAG_INDICE INT,VALOR FLOAT,HORA TIME,CICLO_DE_PROGRAMA INT,FECHA DATE)"))
      {      
	fprintf(stderr, "%s\n", mysql_error(pmysql));
	mysql_close(pmysql);
	return -1;
      }
    return 0;
  }

/*! Function to initialize the index table */
int mysqlAccess::dbIndexInit()
  {

    //If the indexes table doesnt exist, create the table?
    if (mysql_query(pmysql, "CREATE TABLE IF NOT EXISTS DATA_INDEX(COMMID INT,TAG_INDICE INT,TAG_NAME TEXT,COMENTARIO TEXT,TYPE TEXT,SCALE FLOAT,UNITS TEXT,EQUIP TEXT)")) 
      {      
	fprintf(stderr, "%s\n", mysql_error(pmysql));
	mysql_close(pmysql);
	return -1;
      }

    return 0;
  }

/*! Function to clear the index table */
int mysqlAccess::dbClearIndex()
{


  MYSQL_RES *result;
  unsigned int i;
  char query_def[1000];

  sprintf(query_def,"DELETE FROM DATA_INDEX");

  if(mysql_query(pmysql,query_def))
    {
      fprintf(stderr, "%s\n", mysql_error(pmysql));
      return -1;     
    }
  return 0;
}

int mysqlAccess::dbAppendIndex(char * path)
{
  char query_def[1000];

  //CREATING TEMPORAL TABLE
  if (mysql_query(pmysql, "CREATE TABLE IF NOT EXISTS DATA_INDEX_TEMP(COMMID INT,TAG_INDICE INT,TAG_NAME TEXT,COMENTARIO TEXT,TYPE TEXT,SCALE FLOAT,UNITS TEXT,EQUIP TEXT)")) 
    {      
      fprintf(stderr, "%s\n", mysql_error(pmysql));
      mysql_close(pmysql);
      return -1;
    }
  //DELETING TEMPORAL TABLE DATA
  sprintf(query_def,"DELETE FROM DATA_INDEX_TEMP");

  if(mysql_query(pmysql,query_def))
    {
      fprintf(stderr, "%s\n", mysql_error(pmysql));
      return -1;     
    }

  //IMPORTING FROM CSV
  sprintf(query_def,"LOAD DATA LOCAL INFILE '%s' INTO TABLE DATA_INDEX_TEMP FIELDS TERMINATED BY ';' OPTIONALLY ENCLOSED BY '\"' lines terminated by '\\n' IGNORE 1 ROWS",path);
  cout << "importing CSV " << endl;
  cout << query_def << endl;
  if(mysql_query(pmysql,query_def))
    {
      fprintf(stderr, "%s\n", mysql_error(pmysql));

      return -1;     
    }
  //FUSION TABLES
  sprintf(query_def,"INSERT IGNORE INTO DATA_INDEX SELECT * FROM DATA_INDEX_TEMP");
  if(mysql_query(pmysql,query_def))
    {
      fprintf(stderr, "%s\n", mysql_error(pmysql));

      return -1;     
    }
  return 0;
}

int mysqlAccess::dbSaveEnergy(int comm, int registros, mbRegData** regMatrix)
{
  char sql[1200];
  mbRegData* DATA;
  //SIN CICLOS
  int cycle = 0;
  long long value = 0;

  cout << "DEBUG: inside save energy function " << endl;
  DATA = *regMatrix;
  for(int i=0;i < registros ; i++)
    {
      switch(DATA[i].type)
	{
	case(1): //int
	  value = DATA[i].valueL;
	  break;
	case(10)://mod10
	  value = DATA[i].valueLL;
	  value = value + DATA[i].valueL * 10000;
	  value = value + DATA[i].valueH * 100000000;
	  value = value + DATA[i].valueHH * 1000000000000;
	  //  cout << "DEBUG: valores: " << DATA[i].valueLL << " , " << DATA[i].valueL << " , " << DATA[i].valueH << " , " << DATA[i].valueHH << " = " << value << endl;
	  break;
	} 
      sprintf(sql,"INSERT INTO  ENERGY_LOG(COMMID,TAG_INDICE,VALOR,HORA,FECHA) VALUES(%d,\"%d\",\"%lld\",\"%s\",\"%s\") \n",comm+1,DATA[i].index,value,DATA[i].time,DATA[i].date); 
      if (mysql_query(pmysql, sql)) 
	{
	  fprintf(stderr, "%s\n", mysql_error(pmysql));
	  //mysql_close(pDb);
	  return -1;
	}
    }
  cout << "DEBUG: outside save energy function " << endl;
  return 0;

}
