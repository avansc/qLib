//
//  example_8_example_game.cpp
//  qLib_Examples
//
//  Created by avansc on 6/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "example_8_example_game.h"


#include <GLUT/GLUT.h>

#include "example_base.h"

#include "qLib.h"

#include "qEventHandler.h"
#include "qScriptEngine.h"
#include "qScriptModule.h"

//reuse class from example_3_register_classes
#include "example_3_register_classes.h"

///////////////////////////////////////////////////

static qLib::Event::qEventRegistry *evt_reg;

static int mx;
static int my;

static int px = 100;
static int py = 100;

static player *plr;

extern char keys[255];

static qLib::Script::qScriptEngine *engine;
static qLib::Script::qScriptModule *mod;
static qLib::Script::qScriptExec *exe;

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
}

static void init(void)
{	
	evt_reg = new qLib::Event::qEventRegistry();
	/*
	engine = new qLib::Script::qScriptEngine();
	engine->RegisterScriptable<player>();
	engine->RegisterScriptable<qLib::Util::qObject>();
	engine->RegisterScriptable<qLib::Event::qEvent>();
	
	mod = engine->pGetScriptModule("event");
	
	if(mod->addSection((char*)script) < 0)
	{
		printf("Failed to get script module\n");
		exit(-1);
	}
	
	if(mod->buildScript() < 0)
	{
		printf("Failed to build script\n");
		exit(-1);
	}
	
	exe = engine->pGetScriptExec("event", "void ON_EVENT(qEvent &evt, qObject &obj)");
	
	plr = new player(100, 100);
	plr->setDir(1, 1);
	
	qLib::Event::qEventListener *L = new qLib::Event::qKeyEventListener();
	qLib::Event::qEventHandler *H = new qLib::Event::qScriptEventHandler();
	((qLib::Event::qScriptEventHandler*)H)->set_script_exe(exe);
	
	evt_reg->register_pair(L, H, plr);
	*/
	
}

static void destroy(void)
{
	//delete plr;
}

qLibExample example_8_example_game = {
	"Example Game",
	init,
	update,
	destroy,
};