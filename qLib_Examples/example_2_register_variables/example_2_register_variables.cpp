//
//  example_2_register_variables.cpp
//  qLib_Examples
//
//  Created by avansc on 5/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "example_2_register_variables.h"

#include <GLUT/GLUT.h>

#include "example_base.h"

#include "qLib.h"

#include "qScriptEngine.h"
#include "qScriptModule.h"

///////////////////////////////////////////////////
static qLib::Script::qScriptEngine *engine;
static qLib::Script::qScriptModule *mod;
static qLib::Script::qScriptExec *exe;

float val = 0;

///////////////////////////////////////////////////

static void draw(int x, int y)
{
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
	exe->exec();
	exe->reset();
}

static void init(void)
{
	engine = new qLib::Script::qScriptEngine();
	
	engine->RegisterGlobalProperty("float val", &val);
	
	mod = engine->pGetScriptModule("vars");
	
	const char *script =
	"void func(void)										"
	"{														"
	"}														";
	
	if(mod->addSection((char*)script) < 0)
	{
		printf("Failed to get script module\n");
		return;
	}
	
	if(mod->buildScript() < 0)
	{
		printf("Failed to build script\n");
		return;
	}
	
	exe = engine->pGetScriptExec("vars", "void func(void)");
}

static void destroy(void)
{
}

qLibExample example_2_register_variables =
{
	"Register Variables",
	init,
	update,
	destroy,
};