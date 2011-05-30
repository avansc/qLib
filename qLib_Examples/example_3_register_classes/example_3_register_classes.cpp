//
//  example_3_register_classes.cpp
//  qLib_Examples
//
//  Created by avansc on 5/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "example_3_register_classes.h"

#include <GLUT/GLUT.h>

#include "example_base.h"

#include "qLib.h"

#include "qScriptEngine.h"
#include "qScriptModule.h"

player::player()
:	x(0),
y(0),
dx(1),
dy(0)
{
}

player::player(const float &_x, const float &_y)
:	x(_x),
y(_y),
dx(1),
dy(0)
{
}

void player::move(float dt)
{
	this->x += ((float)this->dx)*dt;
	this->y += ((float)this->dy)*dt;
}

void player::setDir(int _dx, int _dy)
{
	this->dx = _dx;
	this->dy = _dy;
}


void player::REGISTER_SCRIPTABLES(qScriptEngine *engine)
{
	//deps//
	engine->RegisterScriptable<qLib::Util::qObject>();
	////////
	
	REGISTER_CLASS(engine, "player", player);
	
	
	REGISTER_METHOD(engine, "player", player, "float getX(void)", getX);
	REGISTER_METHOD(engine, "player", player, "float getY(void)", getY);
	
	REGISTER_METHOD(engine, "player", player, "int getXDir(void)", getXDir);
	REGISTER_METHOD(engine, "player", player, "int getYDir(void)", getYDir);
	
	REGISTER_METHOD(engine, "player", player, "void setX(float _x)", setX);
	REGISTER_METHOD(engine, "player", player, "void setY(float _y)", setY);
	
	REGISTER_METHOD(engine, "player", player, "void move(float _dt)", move);
	REGISTER_METHOD(engine, "player", player, "void setDir(int _dx, int _dy)", setDir);
	
	REGISTER_GLOBAL_FUNCTION(engine, "player@ player_convert(qObject@)", player::convert);
	
	//int r = engine->getEngine()->RegisterObjectMethod("player", "player@ player_convert(qObject@)", asMETHODPR(player, method2, (int, int&), void), asCALL_THISCALL); assert( r >= 0 );

}

player *player::convert(qLib::Util::qObject *ref)
{
	//&output = static_cast<player*>(&ref);
	//&output = (player*)&ref;
	return (player*)ref;
}

///////////////////////////////////////////////////

static qLib::Script::qScriptEngine *engine;
static qLib::Script::qScriptModule *mod;
static qLib::Script::qScriptExec *exe;

static int mx;
static int my;

static int px = 100;
static int py = 100;

static player *plr;

static const char *script =
"void patrol(player &plr)"
"{"
"	if(plr.getX() >= 400 && plr.getY() <= 100)"
"		plr.setDir(0,1);"
"	else if(plr.getY() >= 400  && plr.getX() >= 400)"
"		plr.setDir(-1,0);"
"	else if(plr.getX() <= 100 && plr.getY() >= 400)"
"		plr.setDir(0,-1);"
"	else if(plr.getY() <= 100 && plr.getX() <= 100)"
"		plr.setDir(1,0);"
"}";

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
	exe->ctx->SetArgObject(0, (player*)plr);
	exe->exec();
	exe->reset();
	plr->move(0.3f);
	draw(plr->getX(), plr->getY());
	
	drawString(plr->getX()-10, plr->getY()-25, "Scriptable class");
	
	char data[200];
	sprintf(data, "pos = <%f,%f>", plr->getX(), plr->getY());
	drawString(10, 10, data);
}

static void init(void)
{
	engine = new qLib::Script::qScriptEngine();
	engine->RegisterScriptable<player>();
	
	plr = new player(100, 100);
	plr->setDir(1, 1);
	
	engine->RegisterGlobalProperty("int px", &px);
	engine->RegisterGlobalProperty("int py", &py);
	
	mod = engine->pGetScriptModule("patrol_module");
	
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
	
	exe = engine->pGetScriptExec("patrol_module", "void patrol(player &plr)");
}

static void destroy(void)
{
	delete exe;
	delete mod;
	delete engine;
	delete plr;
}

qLibExample example_3_register_classes = {
	"Register Classes",
	init,
	update,
	destroy,
};