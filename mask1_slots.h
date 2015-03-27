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
//###############################################################
//# mask1_slots.h for ProcessViewServer created: mié feb 18 10:30:17 2015
//# please fill out these slots
//# here you find all possible events
//# Yours: Lehrig Software Engineering
//###############################################################

// todo: uncomment me if you want to use this data aquisiton
// also uncomment this classes in main.cpp and pvapp.h
// also remember to uncomment rllib in the project file
//extern rlModbusClient     modbus;
//extern rlSiemensTCPClient siemensTCP;
//extern rlPPIClient        ppi;
extern rlDataAcquisition	modbus,modbus_rtu;
extern pid_t pidmodbusTCP,pidmodbusRTU,Daemon, Daemon2;

extern MonConfigurator *config;
extern MonCapturer *capturer;

char *search_string;
char buffd_string[100];

char *search_string2;
char buffd_string2[100];


typedef struct // (todo: define your data structure here)
{
}
DATA;

static void setState(PARAM *p, DATA *d, int value, int id, const char *IMAGEN_ON, const char * IMAGEN_OFF, const char* IMAGEN_INDEFINIDO) 
{ // helper function
  char filename[80] = "";
  if     (value == 0) strcpy(filename,IMAGEN_OFF);
  else if(value > 0) strcpy(filename,IMAGEN_ON);
  else                       strcpy(filename,IMAGEN_INDEFINIDO);
	printf("DEBUG: image set: %s , valor: %d\n",filename,value );
  pvSetImage(p,id,filename);
}


static int slotInit(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  //memset(d,0,sizeof(DATA));
  pvDownloadFile(p,"./images/green.png");
  pvDownloadFile(p,"./images/red.png");
  return 0;
}

static int slotNullEvent(PARAM *p, DATA *d)
{
   	int value;
  if(p == NULL || d == NULL) return -1;
  //checking comm
  //modbus TCP		
	pidmodbusTCP = piproc_find("../comm/modbus_client/modbus_client");
	if (pidmodbusTCP == -1)
		value = 0;
	else 
	{
		if (pidmodbusTCP>=0)
			value = 1;
		else
			value = -1;
	}
 	setState(p, d,value, obj4, "./images/green.png", "./images/red.png", "./images/grey.png");
	//deactivamos botón
	if (value == 1)
		pvSetEnabled(p,obj6,0);
	else
		pvSetEnabled(p,obj6,1);

  //modbus RTU

	pidmodbusRTU = piproc_find("../comm/modbus_rtu_client/modbus_rtu_client");
	if (pidmodbusRTU == -1)
		value = 0;
	else 
	{
		if (pidmodbusRTU>=0)
			value = 1;
		else
			value = -1;
	}
 	setState(p, d,value, obj7, "./images/green.png", "./images/red.png", "./images/grey.png");
	//deactivamos botón
	if (value == 1)
		pvSetEnabled(p,obj9,0);
	else
		pvSetEnabled(p,obj9,1);

  return 0;
}

static int slotButtonEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotButtonPressedEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotButtonReleasedEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
	//restart modbus TCP
 	if(id  == obj6)
	{
		Daemon = fork();
  		if(Daemon == 0)//child
    		{
			launchDaemonMBTCP();
    		}
		pvSetEnabled(p,obj6,0);
	}
	//restart modbus RTU
 	if(id  == obj9)
	{
		Daemon2 = fork();
  		if(Daemon2 == 0)//child
    		{
			launchDaemonMBRTU();
    		}
		pvSetEnabled(p,obj9,0);
	}
	if(id == debug_search_btn)
	{
		pvText (p,debug_search);
		sprintf(buffd_string,"%s -> %d",search_string,modbus.intValue(search_string));
		//pvSetValue(p,debug_find,modbus.intValue(search_string));
		pvSetText(p,debug_find,buffd_string);
	}
	if(id == debug_search_btn2)
	{
		pvText (p,debug_search2);
		sprintf(buffd_string2,"%s -> %d",search_string2,modbus_rtu.intValue(search_string2));
		//pvSetValue(p,debug_find,modbus.intValue(search_string));
		pvSetText(p,debug_find2,buffd_string2);
	}
  return 0;
}

static int slotTextEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
	if(id == debug_search)
	{
		if (search_string != NULL)
			free(search_string);
		search_string = (char*) malloc(sizeof(char)*(strlen(text)+1));
		strcpy(search_string,text);
	}
	if(id == debug_search2)
	{
		if (search_string2 != NULL)
			free(search_string2);
		search_string2 = (char*) malloc(sizeof(char)*(strlen(text)+1));
		strcpy(search_string2,text);
	}
  return 0;
}

static int slotSliderEvent(PARAM *p, int id, DATA *d, int val)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000) return -1;
  return 0;
}

static int slotCheckboxEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  return 0;
}

static int slotRadioButtonEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  return 0;
}

static int slotGlInitializeEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotGlPaintEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotGlResizeEvent(PARAM *p, int id, DATA *d, int width, int height)
{
  if(p == NULL || id == 0 || d == NULL || width < 0 || height < 0) return -1;
  return 0;
}

static int slotGlIdleEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotTabEvent(PARAM *p, int id, DATA *d, int val)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000) return -1;
  return 0;
}

static int slotTableTextEvent(PARAM *p, int id, DATA *d, int x, int y, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000 || text == NULL) return -1;
  return 0;
}

static int slotTableClickedEvent(PARAM *p, int id, DATA *d, int x, int y, int button)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000 || button < 0) return -1;
  return 0;
}

static int slotSelectionEvent(PARAM *p, int id, DATA *d, int val, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000 || text == NULL) return -1;
  return 0;
}

static int slotClipboardEvent(PARAM *p, int id, DATA *d, int val)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000) return -1;
  return 0;
}

static int slotRightMouseEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  //pvPopupMenu(p,-1,"Menu1,Menu2,,Menu3");
  return 0;
}

static int slotKeyboardEvent(PARAM *p, int id, DATA *d, int val, int modifier)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000 || modifier < -1000) return -1;
  return 0;
}

static int slotMouseMovedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  return 0;
}

static int slotMousePressedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  return 0;
}

static int slotMouseReleasedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  return 0;
}

static int slotMouseOverEvent(PARAM *p, int id, DATA *d, int enter)
{
  if(p == NULL || id == 0 || d == NULL || enter < -1000) return -1;
  return 0;
}

static int slotUserEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  return 0;
}
