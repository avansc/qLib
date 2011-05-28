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

class player : public qLib::Util::qComponent
{
public:
	player();
	player(const float &_x, const float &_y);
	virtual ~player(){};
	
	float getX() { return this->x; }
	float getY() { return this->y; }
	
	int getXDir() { return this->dx; }
	int getYDir() { return this->dy; }
	
	void setX(float _x) { this->x = _x; }
	void setY(float _y) { this->y = _y; }
	
	void move(float dt);
	void setDir(int _dx, int _dy);
	
	virtual void REGISTER_SCRIPTABLES(qScriptEngine *engine);
private:
	float x,y;
	int dx, dy;
};

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
	REGISTER_CLASS(engine, "player", player);
	
	
	REGISTER_METHOD(engine, "player", player, "float getX(void)", getX);
	REGISTER_METHOD(engine, "player", player, "float getY(void)", getY);
	
	REGISTER_METHOD(engine, "player", player, "int getXDir(void)", getXDir);
	REGISTER_METHOD(engine, "player", player, "int getYDir(void)", getYDir);
	
	REGISTER_METHOD(engine, "player", player, "void setX(float _x)", setX);
	REGISTER_METHOD(engine, "player", player, "void setY(float _y)", setY);
	
	REGISTER_METHOD(engine, "player", player, "void move(float _dt)", move);
	REGISTER_METHOD(engine, "player", player, "void setDir(int _dx, int _dy)", setDir);
}

///////////////////////////////////////////////////
static qLib::Script::qScriptEngine *engine;
static qLib::Script::qScriptModule *mod;
static qLib::Script::qScriptExec *exe;

int mx;
int my;

int px = 100;
int py = 100;

player *plr;
///////////////////////////////////////////////////

void draw(int x, int y)
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
	exe->ctx->SetArgObject(0, (player*)plr);
	exe->exec();
	exe->reset();
	plr->move(0.3f);
	draw(plr->getX(), plr->getY());
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
	
	const char *script =
	"void patrol(player &plr)								"
	"{														"
	"	if(plr.getX() >= 400 && plr.getY() <= 100)			"
	"		plr.setDir(0,1);								"
	"	else if(plr.getY() >= 400  && plr.getX() >= 400)	"
	"		plr.setDir(-1,0);								"
	"	else if(plr.getX() <= 100 && plr.getY() >= 400)		"
	"		plr.setDir(0,-1);								"
	"	else if(plr.getY() <= 100 && plr.getX() <= 100)		"
	"		plr.setDir(1,0);								"
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
	
	exe = engine->pGetScriptExec("patrol_module", "void patrol(player &plr)");
}

static void destroy(void)
{
}

qLibExample example_3_register_classes = {
	"Register Classes",
	init,
	update,
	destroy,
};