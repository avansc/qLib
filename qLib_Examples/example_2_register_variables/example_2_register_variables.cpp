//
//  example_2_register_variables.cpp
//  qLib_Examples
//
//  Created by avansc on 5/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "example_2_register_variables.h"

#include <string.h>
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
	char data[200];
	sprintf(data, "Val = %f", val);
	drawString(10, 10, data);
}

static void init(void)
{
	engine = new qLib::Script::qScriptEngine();
	val = 0;
	
	engine->RegisterGlobalProperty("float val", &val);
	
	mod = engine->pGetScriptModule("vars");
	
	const char *script =
	"void func(void)										"
	"{														"
	"	Print(\"registers value = \" + val + \"\\n\");		"
	"	val+=0.1;											"
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
	delete exe;
	delete mod;
	delete engine;
}

qLibExample example_2_register_variables =
{
	"Register Variables",
	init,
	update,
	destroy,
};