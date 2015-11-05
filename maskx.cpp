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
////////////////////////////////////////////////////////////////////////////
//
// show_mask1 for ProcessViewServer created: mié feb 18 10:30:17 2015
//
////////////////////////////////////////////////////////////////////////////
#include "pvapp.h"

// _begin_of_generated_area_ (do not edit -> use ui2pvc) -------------------

// our mask contains the following objects
enum {
  ID_MAIN_WIDGET = 0,
  tab,
  tab_inicio,
  obj2,
  obj4,
  obj5,
  obj6,
  obj7,
  obj8,
  obj9,
  obj10,
  obj11,
  obj12,
  debug_search,
  debug_search_btn,
  debug_find,
  debug_search2,
  debug_find2,
  debug_search_btn2,
  obj3,
  console_output,
  ID_END_OF_WIDGETS
};

// our mask contains the following widget names
  static const char *widgetName[] = {
  "ID_MAIN_WIDGET",
  "tab",
  "tab_inicio",
  "obj2",
  "obj4",
  "obj5",
  "obj6",
  "obj7",
  "obj8",
  "obj9",
  "obj10",
  "obj11",
  "obj12",
  "debug_search",
  "debug_search_btn",
  "debug_find",
  "debug_search2",
  "debug_find2",
  "debug_search_btn2",
  "obj3",
  "console_output",
  "ID_END_OF_WIDGETS",
  ""};

  static const char *toolTip[] = {
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  ""};

  static const char *whatsThis[] = {
  "",
  "",
  "./images/grey.png",
  "",
  "./images/grey.png",
  "",
  "",
  "./images/grey.png",
  "",
  "",
 "./images/grey.png",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  ""};

  static const int widgetType[ID_END_OF_WIDGETS+1] = {
  0,
  TQTabWidget,
  TQWidget,
  TQWidget,
  TQImage,
  TQLabel,
  TQPushButton,
  TQImage,
  TQLabel,
  TQPushButton,
  TQImage,
  TQLabel,
  TQPushButton,
  TQLineEdit,
  TQPushButton,
  TQLineEdit,
  TQLineEdit,
  TQLineEdit,
  TQPushButton,
  TQWidget,
  TQTextBrowser,
  -1 };

static int generated_defineMask(PARAM *p)
{
  int w,h,depth;

  if(p == NULL) return 1;
  if(widgetName[0] == NULL) return 1; // suppress unused warning
  w = h = depth = strcmp(toolTip[0],whatsThis[0]);
  if(widgetType[0] == -1) return 1;
  if(w==h) depth=0; // fool the compiler
  pvStartDefinition(p,ID_END_OF_WIDGETS);

  pvQTabWidget(p,tab,0);
  pvSetGeometry(p,tab,1,1,800,640);
  pvSetFont(p,tab,"Sans Serif",9,0,0,0,0);
  pvSetWhatsThis(p,tab,pvtr("./images/grey.png"));

  pvQWidget(p,tab_inicio,tab);
  pvAddTab(p,tab,tab_inicio,pvtr("Main"));
  pvSetFont(p,tab_inicio,"Verdana",10,0,0,0,0);

  pvQWidget(p,obj2,tab);
  pvAddTab(p,tab,obj2,pvtr("Status"));
  pvSetFont(p,obj2,"Verdana",10,0,0,0,0);

  pvDownloadFile(p,"./images/grey.png");
  pvQImage(p,obj4,obj2,"./images/grey.png",&w,&h,&depth);
  pvSetGeometry(p,obj4,174,21,40,36);
  pvSetFont(p,obj4,"Sans Serif",9,0,0,0,0);
  pvSetWhatsThis(p,obj4,pvtr("./images/grey.png"));

  pvQLabel(p,obj5,obj2);
  pvSetGeometry(p,obj5,30,24,130,30);
  pvSetText(p,obj5,pvtr("Com. Modbus TCP/IP"));
  pvSetFont(p,obj5,"Sans Serif",9,0,0,0,0);

  pvQPushButton(p,obj6,obj2);
  pvSetGeometry(p,obj6,243,24,99,30);
  pvSetText(p,obj6,pvtr("Reinicializarlas"));
  pvSetFont(p,obj6,"Sans Serif",9,0,0,0,0);

  pvDownloadFile(p,"./images/grey.png");
  pvQImage(p,obj7,obj2,"./images/grey.png",&w,&h,&depth);
  pvSetGeometry(p,obj7,174,61,40,36);
  pvSetFont(p,obj7,"Sans Serif",9,0,0,0,0);
  pvSetWhatsThis(p,obj7,pvtr("./images/grey.png"));

  pvQLabel(p,obj8,obj2);
  pvSetGeometry(p,obj8,30,64,130,30);
  pvSetText(p,obj8,pvtr("Com. Modbus RTU"));
  pvSetFont(p,obj8,"Sans Serif",9,0,0,0,0);

  pvQPushButton(p,obj9,obj2);
  pvSetGeometry(p,obj9,243,64,99,30);
  pvSetText(p,obj9,pvtr("Reinicializarlas"));
  pvSetFont(p,obj9,"Sans Serif",9,0,0,0,0);

  pvDownloadFile(p,"./images/grey.png");
  pvQImage(p,obj10,obj2,"./images/grey.png",&w,&h,&depth);
  pvSetGeometry(p,obj10,174,111,40,36);
  pvSetFont(p,obj10,"Sans Serif",9,0,0,0,0);
  pvSetWhatsThis(p,obj10,pvtr("./images/grey.png"));

  pvQLabel(p,obj11,obj2);
  pvSetGeometry(p,obj11,30,114,130,30);
  pvSetText(p,obj11,pvtr("Captura MySQL"));
  pvSetFont(p,obj11,"Sans Serif",9,0,0,0,0);

  pvQPushButton(p,obj12,obj2);
  pvSetGeometry(p,obj12,243,114,99,30);
  pvSetText(p,obj12,pvtr("Reinicializarla"));
  pvSetFont(p,obj12,"Sans Serif",9,0,0,0,0);

  pvQLineEdit(p,debug_search,obj2);
  pvSetGeometry(p,debug_search,75,351,140,30);
  pvSetText(p,debug_search,pvtr("LineEdit"));
  pvSetFont(p,debug_search,"Sans Serif",9,0,0,0,0);

  pvQPushButton(p,debug_search_btn,obj2);
  pvSetGeometry(p,debug_search_btn,225,351,99,30);
  pvSetText(p,debug_search_btn,pvtr("buscar"));
  pvSetFont(p,debug_search_btn,"Sans Serif",9,0,0,0,0);

  pvQLineEdit(p,debug_find,obj2);
  pvSetGeometry(p,debug_find,132,408,140,30);
  pvSetText(p,debug_find,pvtr("LineEdit"));
  pvSetFont(p,debug_find,"Sans Serif",9,0,0,0,0);

  pvQLineEdit(p,debug_search2,obj2);
  pvSetGeometry(p,debug_search2,378,351,140,30);
  pvSetText(p,debug_search2,pvtr("LineEdit"));
  pvSetFont(p,debug_search2,"Sans Serif",9,0,0,0,0);

  pvQLineEdit(p,debug_find2,obj2);
  pvSetGeometry(p,debug_find2,429,405,140,30);
  pvSetText(p,debug_find2,pvtr("LineEdit"));
  pvSetFont(p,debug_find2,"Sans Serif",9,0,0,0,0);

  pvQPushButton(p,debug_search_btn2,obj2);
  pvSetGeometry(p,debug_search_btn2,531,351,99,30);
  pvSetText(p,debug_search_btn2,pvtr("buscar"));
  pvSetFont(p,debug_search_btn2,"Sans Serif",9,0,0,0,0);

  pvQWidget(p,obj3,tab);
  pvAddTab(p,tab,obj3,pvtr("Configuration"));
  pvSetFont(p,obj3,"Verdana",10,0,0,0,0);

  pvQTextBrowser(p,console_output,0);
  pvSetGeometry(p,console_output,1,642,1024,200);
  pvSetFont(p,console_output,"Sans Serif",9,0,0,0,0);


  pvEndDefinition(p);
  //pvTabOrder(p,tab,obj1);
  //pvTabOrder(p,obj1,label1);
  //pvTabOrder(p,label1,tab);
  //pvTabOrder(p,tab,obj4);
  return 0;
}

// _end_of_generated_area_ (do not edit -> use ui2pvc) ---------------------

#include "mask1_slots.h"

static int defineMask(PARAM *p)
{
  if(p == NULL) return 1;
  generated_defineMask(p);
  // (todo: add your code here)
  return 0;
}


static int showData(PARAM *p, DATA *d)
{
  if(p == NULL) return 1;
  if(d == NULL) return 1;
  return 0;
}

static int readData(DATA *d) // from shared memory, database or something else
{
  if(d == NULL) return 1;
  // (todo: add your code here)
  return 0;
}


int show_mask1(PARAM *p)
{
  DATA d;
  char event[MAX_EVENT_LENGTH];
  char text[MAX_EVENT_LENGTH];
  char str1[MAX_EVENT_LENGTH];
  int  i,w,h,val,x,y,button,ret;
  float xval, yval;

  defineMask(p);
  //rlSetDebugPrintf(1);
  if((ret=slotInit(p,&d)) != 0) return ret;
  readData(&d); // from shared memory, database or something else
  showData(p,&d);
  pvClearMessageQueue(p);
  while(1)
  {
    pvPollEvent(p,event);
    switch(pvParseEvent(event, &i, text))
    {
      case NULL_EVENT:
        readData(&d); // from shared memory, database or something else
        showData(p,&d);
        if((ret=slotNullEvent(p,&d)) != 0) return ret;
        break;
      case BUTTON_EVENT:
        if(trace) printf("BUTTON_EVENT id=%d\n",i);
        if((ret=slotButtonEvent(p,i,&d)) != 0) return ret;
        break;
      case BUTTON_PRESSED_EVENT:
        if(trace) printf("BUTTON_PRESSED_EVENT id=%d\n",i);
        if((ret=slotButtonPressedEvent(p,i,&d)) != 0) return ret;
        break;
      case BUTTON_RELEASED_EVENT:
        if(trace) printf("BUTTON_RELEASED_EVENT id=%d\n",i);
        if((ret=slotButtonReleasedEvent(p,i,&d)) != 0) return ret;
        break;
      case TEXT_EVENT:
        if(trace) printf("TEXT_EVENT id=%d %s\n",i,text);
        if((ret=slotTextEvent(p,i,&d,text)) != 0) return ret;
        break;
      case SLIDER_EVENT:
        sscanf(text,"(%d)",&val);
        if(trace) printf("SLIDER_EVENT val=%d\n",val);
        if((ret=slotSliderEvent(p,i,&d,val)) != 0) return ret;
        break;
      case CHECKBOX_EVENT:
        if(trace) printf("CHECKBOX_EVENT id=%d %s\n",i,text);
        if((ret=slotCheckboxEvent(p,i,&d,text)) != 0) return ret;
        break;
      case RADIOBUTTON_EVENT:
        if(trace) printf("RADIOBUTTON_EVENT id=%d %s\n",i,text);
        if((ret=slotRadioButtonEvent(p,i,&d,text)) != 0) return ret;
        break;
      case GL_INITIALIZE_EVENT:
        if(trace) printf("you have to call initializeGL()\n");
        if((ret=slotGlInitializeEvent(p,i,&d)) != 0) return ret;
        break;
      case GL_PAINT_EVENT:
        if(trace) printf("you have to call paintGL()\n");
        if((ret=slotGlPaintEvent(p,i,&d)) != 0) return ret;
        break;
      case GL_RESIZE_EVENT:
        sscanf(text,"(%d,%d)",&w,&h);
        if(trace) printf("you have to call resizeGL(w,h)\n");
        if((ret=slotGlResizeEvent(p,i,&d,w,h)) != 0) return ret;
        break;
      case GL_IDLE_EVENT:
        if((ret=slotGlIdleEvent(p,i,&d)) != 0) return ret;
        break;
      case TAB_EVENT:
        sscanf(text,"(%d)",&val);
        if(trace) printf("TAB_EVENT(%d,page=%d)\n",i,val);
        if((ret=slotTabEvent(p,i,&d,val)) != 0) return ret;
        break;
      case TABLE_TEXT_EVENT:
        sscanf(text,"(%d,%d,",&x,&y);
        pvGetText(text,str1);
        if(trace) printf("TABLE_TEXT_EVENT(%d,%d,\"%s\")\n",x,y,str1);
        if((ret=slotTableTextEvent(p,i,&d,x,y,str1)) != 0) return ret;
        break;
      case TABLE_CLICKED_EVENT:
        sscanf(text,"(%d,%d,%d)",&x,&y,&button);
        if(trace) printf("TABLE_CLICKED_EVENT(%d,%d,button=%d)\n",x,y,button);
        if((ret=slotTableClickedEvent(p,i,&d,x,y,button)) != 0) return ret;
        break;
      case SELECTION_EVENT:
        sscanf(text,"(%d,",&val);
        pvGetText(text,str1);
        if(trace) printf("SELECTION_EVENT(column=%d,\"%s\")\n",val,str1);
        if((ret=slotSelectionEvent(p,i,&d,val,str1)) != 0) return ret;
        break;
      case CLIPBOARD_EVENT:
        sscanf(text,"(%d",&val);
        if(trace) printf("CLIPBOARD_EVENT(id=%d)\n",val);
        if(trace) printf("clipboard = \n%s\n",p->clipboard);
        if((ret=slotClipboardEvent(p,i,&d,val)) != 0) return ret;
        break;
      case RIGHT_MOUSE_EVENT:
        if(trace) printf("RIGHT_MOUSE_EVENT id=%d text=%s\n",i,text);
        if((ret=slotRightMouseEvent(p,i,&d,text)) != 0) return ret;
        break;
      case KEYBOARD_EVENT:
        sscanf(text,"(%d",&val);
        if(trace) printf("KEYBOARD_EVENT modifier=%d key=%d\n",i,val);
        if((ret=slotKeyboardEvent(p,i,&d,val,i)) != 0) return ret;
        break;
      case PLOT_MOUSE_MOVED_EVENT:
        sscanf(text,"(%f,%f)",&xval,&yval);
        if(trace) printf("PLOT_MOUSE_MOVE %f %f\n",xval,yval);
        if((ret=slotMouseMovedEvent(p,i,&d,xval,yval)) != 0) return ret;
        break;
      case PLOT_MOUSE_PRESSED_EVENT:
        sscanf(text,"(%f,%f)",&xval,&yval);
        if(trace) printf("PLOT_MOUSE_PRESSED %f %f\n",xval,yval);
        if((ret=slotMousePressedEvent(p,i,&d,xval,yval)) != 0) return ret;
        break;
      case PLOT_MOUSE_RELEASED_EVENT:
        sscanf(text,"(%f,%f)",&xval,&yval);
        if(trace) printf("PLOT_MOUSE_RELEASED %f %f\n",xval,yval);
        if((ret=slotMouseReleasedEvent(p,i,&d,xval,yval)) != 0) return ret;
        break;
      case MOUSE_OVER_EVENT:
        sscanf(text,"%d",&val);
        if(trace) printf("MOUSE_OVER_EVENT %d\n",val);
        if((ret=slotMouseOverEvent(p,i,&d,val)) != 0) return ret;
        break;
      case USER_EVENT:
        if(trace) printf("USER_EVENT id=%d %s\n",i,text);
        if((ret=slotUserEvent(p,i,&d,text)) != 0) return ret;
        break;
      default:
        if(trace) printf("UNKNOWN_EVENT id=%d %s\n",i,text);
        break;
    }
  }
}
