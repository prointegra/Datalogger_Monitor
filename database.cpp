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
    // dbEventsInit();
    dbIndexInit();

    return 0;
}


/*! Function to initialize the energy data table */
int mysqlAccess::dbEnergyInit()
  {
    //If the events log table doesnt exist, create the table?
    if (mysql_query(pmysql, "CREATE TABLE IF NOT EXISTS ENERGY_LOG2(ID INT PRIMARY KEY AUTO_INCREMENT,COMMID INT,FECHA DATE,HORA TIME,TAG1_VALUE FLOAT,TAG2_VALUE FLOAT,TAG3_VALUE FLOAT,TAG4_VALUE FLOAT,TAG5_VALUE FLOAT,TAG6_VALUE FLOAT,TAG7_VALUE FLOAT,TAG8_VALUE FLOAT,TAG9_VALUE FLOAT,TAG10_VALUE FLOAT,TAG11_VALUE FLOAT,TAG12_VALUE FLOAT,TAG13_VALUE FLOAT,TAG14_VALUE FLOAT,TAG15_VALUE FLOAT,TAG16_VALUE FLOAT,TAG17_VALUE FLOAT,TAG18_VALUE FLOAT,TAG19_VALUE FLOAT,TAG20_VALUE FLOAT,TAG21_VALUE FLOAT,TAG22_VALUE FLOAT,TAG23_VALUE FLOAT,TAG24_VALUE FLOAT,TAG25_VALUE FLOAT,TAG26_VALUE FLOAT,TAG27_VALUE FLOAT,TAG28_VALUE FLOAT,TAG29_VALUE FLOAT,TAG30_VALUE FLOAT)"))
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
  sprintf(query_def,"LOAD DATA LOCAL INFILE '%s' INTO TABLE DATA_INDEX_TEMP FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '\"' lines terminated by '\\n' IGNORE 1 ROWS",path);
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
  string squery;
  ostringstream strstr;
  mbRegData* DATA;
  //SIN CICLOS
  int cycle = 0;
  long long value = 0;
  int i;
  //cout << "DEBUG: inside save energy function " << endl;
  DATA = *regMatrix;
  strstr <<  "INSERT INTO  ENERGY_LOG2(COMMID,FECHA,HORA,TAG1_VALUE,TAG2_VALUE,TAG3_VALUE,TAG4_VALUE,TAG5_VALUE,TAG6_VALUE,TAG7_VALUE,TAG8_VALUE,TAG9_VALUE,TAG10_VALUE,TAG11_VALUE,TAG12_VALUE,TAG13_VALUE,TAG14_VALUE,TAG15_VALUE,TAG16_VALUE,TAG17_VALUE,TAG18_VALUE,TAG19_VALUE,TAG20_VALUE,TAG21_VALUE,TAG22_VALUE,TAG23_VALUE,TAG24_VALUE,TAG25_VALUE,TAG26_VALUE,TAG27_VALUE,TAG28_VALUE,TAG29_VALUE,TAG30_VALUE) VALUES("<< comm << ",\"" << DATA[0].date << "\",\"" << DATA[0].time << "\",";

  for(i=0;i < registros ; i++)
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
      if(!DATA[i].err)
	{
	  if(i < 29)
	    strstr << value << ",";
	  else
	    strstr << value << ")";
	}
      else
	{
	  if(i < 29)
	    strstr << "NULL" << ",";
	  else
	    strstr << "NULL" << ")";
	}
 
    }
  if(registros < 30)
    {
      for(i=registros;i<29;i++)
	{
	  strstr << "NULL,";
	}
      strstr << "NULL)";
    }
  squery = strstr.str();
  if (mysql_query(pmysql,squery.c_str())) 
    {
      fprintf(stderr, "%s\n", mysql_error(pmysql));
      //mysql_close(pDb);
      return -1;
    }
  //cout << "DEBUG: outside save energy function " << endl;
  return 0;

}
