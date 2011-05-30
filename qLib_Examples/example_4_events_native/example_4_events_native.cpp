//
//  example_4_events_native.cpp
//  qLib_Examples
//
//  Created by avansc on 5/30/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "example_4_events_native.h"

#include <GLUT/GLUT.h>

#include "example_base.h"

#include "qLib.h"

#include "qEventHandler.h"

//reuse class from example_3_register_classes
#include "example_3_register_classes.h"

///////////////////////////////////////////////////

static qLib::Event::qEventRegistry *evt_reg;

static int mx;
static int my;

static int px = 100;
static int py = 100;

player *plr;

extern char keys[255];


static void native_event(const qLib::Event::qEvent &_evt, const qLib::Util::qObject &_obj)
{
	if(_evt.data.type == qLib::Event::EVENT_KEY)
	{
		switch(_evt.data.event_data.key_d.key)
		{
			case 'a' :
			{
				((player*)&_obj)->setDir(-1, 0);
				plr->move(1);
				break;
			}
			case 'd' :
			{
				((player*)&_obj)->setDir(1, 0);
				plr->move(1);
				break;
			}
			case 'w' :
			{
				((player*)&_obj)->setDir(0, 1);
				plr->move(1);
				break;
			}
			case 's' :
			{
				((player*)&_obj)->setDir(0, -1);
				plr->move(1);
				break;
			}
		}
	}
}

static void proc_events()
{	
	for(uint8_t a = 0;a < 255;a++)
	{
		if(keys[a] == 1)
		{
			evt_reg->push_event(qLib::Event::qEvent(a, qLib::Event::KEY_DOWN, qLib::Event::EVENT_KEY));
		}
	}
	
	evt_reg->process_events();
}

///////////////////////////////////////////////////

static void drawString(int x, int y, const char *str)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2i(x, y);
	
	for(int i=0, len=strlen(str); i<len; i++){
		if(str[i] == '\n'){
			y -= 16;
			glRasterPos2i(x, y);
		} else {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, str[i]);
		}
	}
}

static void draw(int x, int y)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
    glTranslatef(x, y, 0);
    glBegin(GL_QUADS);
    glVertex2f(-10, -10);
    glVertex2f(10, -10);
    glVertex2f(10, 10);
    glVertex2f(-10, 10);
    glEnd();
    glPopMatrix();
}

static void update(float dt)
{
	proc_events();
	
	draw(plr->getX(), plr->getY());
	
	char data[200];
	sprintf(data, "pos = <%f,%f>", plr->getX(), plr->getY());
	drawString(10, 10, data);
}

static void init(void)
{	
	plr = new player(100, 100);
	plr->setDir(1, 1);
	
	evt_reg = new qLib::Event::qEventRegistry();
	qLib::Event::qEventListener *L = new qLib::Event::qKeyEventListener();
	qLib::Event::qEventHandler *H = new qLib::Event::qNativeEventHandler();
	((qLib::Event::qNativeEventHandler*)(H))->set_event_ptr(native_event);
	
	evt_reg->register_pair(L, H, plr);
	
}

static void destroy(void)
{
	delete plr;
}

qLibExample example_4_events_native = {
	"Native Events",
	init,
	update,
	destroy,
};