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
//***************************************************************************
//                          main.cpp  -  description
//                             -------------------
//  begin            : mié feb 18 10:30:17 2015
//  generated by     : pvdevelop (C) Lehrig Software Engineering
//  email            : lehrig@t-online.de
//***************************************************************************
#include "pvapp.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

pid_t Daemon,Daemon2, pidmodbusTCP,pidmodbusRTU, CaptureData;

MonConfigurator *config;
MonCapturer *capturer;

// todo: comment me out. you can insert these objects as extern in your masks.
//rlModbusClient     modbus(modbusdaemon_MAILBOX,modbusdaemon_SHARED_MEMORY,modbusdaemon_SHARED_MEMORY_SIZE);
rlDataAcquisition	modbus("../modbus.mbx","../modbus.shm",128536);
rlDataAcquisition	modbus_rtu("../modbus_rtu.mbx","../modbus_rtu.shm",128536);
//rlSiemensTCPClient siemensTCP(siemensdaemon_MAILBOX,siemensdaemon_SHARED_MEMORY,siemensdaemon_SHARED_MEMORY_SIZE);
//rlPPIClient        ppi(ppidaemon_MAILBOX,ppidaemon_SHARED_MEMORY,ppidaemon_SHARED_MEMORY_SIZE);

/*! function to check if a process is running
 only  under Gnu/Linux*/
pid_t piproc_find(const char* name) 
{
    DIR* dir;
    struct dirent* ent;
    char* endptr;
    char buf[512];

    if (!(dir = opendir("/proc"))) {
        perror("can't open /proc");
        return -1;
    }

    while((ent = readdir(dir)) != NULL) {
        /* if endptr is not a null character, the directory is not
         * entirely numeric, so ignore it */
        long lpid = strtol(ent->d_name, &endptr, 10);
        if (*endptr != '\0') {
            continue;
        }

        /* try to open the cmdline file */
        snprintf(buf, sizeof(buf), "/proc/%ld/cmdline", lpid);
        FILE* fp = fopen(buf, "r");

        if (fp) {
            if (fgets(buf, sizeof(buf), fp) != NULL) {
                /* check the first token in the file, the program name */
                char* first = strtok(buf, " ");
                if (!strcmp(first, name)) {
                    fclose(fp);
                    closedir(dir);
                    return (pid_t)lpid;
                }
            }
            fclose(fp);
        }

    }

    closedir(dir);
    return -1;
}

/*! it executes the modbus TCP IP daemon with no parameters, could be improved the path to daemon personalized, a .ini file choosable, etc.*/
int launchDaemonMBTCP()//path configurable? .ini to use, etc.
{

  char line[128]; //should be IMPROVED
  FILE *file;
  FILE *fout; // out file

  rename("MBdaemon.log", "MBdaemon_old.log");
  fout = fopen("MBdaemon.log","w");
  
  //execute pipe
  file = popen("../comm/modbus_client/modbus_client ../comm/modbus_client/config.ini", "r");
  if (!file) 
    { 
      fprintf(stderr,"ERROR: bad command to execute modbus tcp ip daemon\n");
      perror(".daemon_log"); 
      return -1;        
  }
  //show output
  while (fgets(line, 128, file) != NULL) //buffer can be improved IMPROVE
    {
      fprintf(fout,"%s", line);

    }
  pclose(file);
  pclose(fout); 
  return 0;    

}

/*! it executes the modbus RTU daemon with no parameters, could be improved the path to daemon personalized, a .ini file choosable, etc.*/
int launchDaemonMBRTU()//path configurable? .ini to use, etc.
{

  char line[128]; //should be IMPROVED
  FILE *file;
  FILE *fout; // out file

  rename("MBRTUdaemon.log", "MBRTUdaemon_old.log");
  fout = fopen("MBRTUdaemon.log","w");
  
  //execute pipe
  file = popen("../comm/modbus_rtu_client/modbus_rtu_client ../comm/modbus_rtu_client/config_rtu.ini", "r");
  if (!file) 
    { 
      fprintf(stderr,"ERROR: bad command to execute modbus rtu daemon\n");
      perror(".daemon_log"); 
      return -1;        
  }
  //show output
  while (fgets(line, 128, file) != NULL) //buffer can be improved IMPROVE
    {
      fprintf(fout,"%s", line);

    }
  pclose(file);
  pclose(fout); 
  return 0;    

}

/*! it executes the capture to Database program */
int launchDaemonCAPTURE()//path configurable? .ini to use, etc.
{

  char line[128]; //should be IMPROVED
  FILE *file;
  FILE *fout; // out file

  rename("CAPTUREdaemon.log", "CAPTUREdaemon_old.log");
  fout = fopen("CAPTUREdaemon.log","w");
  
  //execute pipe
  file = popen("../capture/MtoDB", "r");
  if (!file) 
    { 
      fprintf(stderr,"ERROR: bad command to execute capture daemon\n");
      perror(".daemon_log"); 
      return -1;        
  }
  //show output
  while (fgets(line, 128, file) != NULL) //buffer can be improved IMPROVE
    {
      fprintf(fout,"%s", line);

    }
  pclose(file);
  pclose(fout); 
  return 0;    
}

int pvMain(PARAM *p)
{
int ret;

  pvSendVersion(p);
  pvSetCaption(p,"pvs");
  pvResize(p,0,1280,1024);
  //pvScreenHint(p,1024,768); // this may be used to automatically set the zoomfactor
  ret = 1;
  pvGetInitialMask(p);
  if(strcmp(p->initial_mask,"mask1") == 0) ret = 1;
  pidmodbusTCP = piproc_find("../comm/modbus_client/modbus_client");
  pidmodbusRTU = piproc_find("../comm/modbus_rtu_client/modbus_rtu_client");
  CaptureData = piproc_find("../capture/MtoDB");
  while(1)
  {
    if(trace) printf("show_mask%d\n", ret);
    switch(ret)
    {
      case 2:
        pvStatusMessage(p,-1,-1,-1,"mask2");
        ret = show_mask2(p);
        break;
      case 1:
        pvStatusMessage(p,-1,-1,-1,"mask1");
        ret = show_mask1(p);
        break;
      default:
        return 0;
    }
  }
}

#ifdef USE_INETD
int main(int ac, char **av)
{
PARAM p;

  pvInit(ac,av,&p);
  /* here you may interpret ac,av and set p->user to your data */
  pvMain(&p);
  return 0;
}


#else  // multi threaded server
int main(int ac, char **av)
{
PARAM p;
int   s;
int error;

  pvInit(ac,av,&p);
  /* here you may interpret ac,av and set p->user to your data */
//CARGAMOS CONFIGURACIÓN
config = new MonConfigurator("config.xml");
config->IterateComms();
//DEBUG: MUESTRA LA CONFIGURACIÓN CARGADA
config->RetrieveConfig();
//QUÉ/ COMO LANZAMOS LAS COMUNICACIONES
//QUÉ/ COMO LANZAMOS EL ALMACENAJE
capturer = new MonCapturer;
//CAPTURAMOS LA CONFIGURACIÓN EN MEMORIA
capturer->initFromConfig(&config);
capturer->showConfig();
//INICIAMOS DATABASE
capturer->initDatabase();
//
  pidmodbusTCP = -1;
//  Daemon = fork();
//  if(Daemon == 0)//child
 //   {
//	launchDaemonMBTCP();
//    }
  pidmodbusRTU = -1;
  Daemon2 = fork();
  if(Daemon2 == 0)//child
    {
	launchDaemonMBRTU();
    }

  CaptureData = -1;
  Daemon = fork();  
  if(Daemon == 0)//child
   {

	while(1)
	{
	  printf("forked\n");
	  capturer->captureData();
	  //DEBUG 
	  //capturer->showCapturedData();
	  sleep(1);
	  //launchDaemonCAPTURE();
	}
   }

  while(1)
  {
    s = pvAccept(&p);
    if(s != -1) pvCreateThread(&p,s);
    else        break;
  }
  return 0;
}
#endif
