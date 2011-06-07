/*
 *  qEventLib
 *
 *	qLib_usage_example
 *		Example on how to use qLib.
 *
 *  main.cpp
 *
 *	Copyright (c) 2001, AVS
 *	All rights reserved.
 *
 *	Redistribution and use in source and binary forms, with or without
 *	modification, are permitted provided that the following conditions are met:
 *	1.	Redistributions of source code must retain the above copyright
 *		notice, this list of conditions and the following disclaimer.
 *	2.	Redistributions in binary form must reproduce the above copyright
 *		notice, this list of conditions and the following disclaimer in the
 *		documentation and/or other materials provided with the distribution.
 *	3.	All advertising materials mentioning features or use of this software
 *		must display the following acknowledgement:
 *		This product includes software developed by the AVS.
 *	4.	Neither the name of the AVS nor the
 *		names of its contributors may be used to endorse or promote products
 *		derived from this software without specific prior written permission.
 *
 *	THIS SOFTWARE IS PROVIDED BY AVS ''AS IS'' AND ANY
 *	EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *	DISCLAIMED. IN NO EVENT SHALL AVS BE LIABLE FOR ANY
 *	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <GLUT/GLUT.h>

#include "qLib.h"

#include "qScriptEngine.h"
#include "qScriptModule.h"

class player : public qLib::Util::qObject
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
qLib::Script::qScriptEngine *engine;
qLib::Script::qScriptModule *mod;
qLib::Script::qScriptExec *exe;

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

void myTimer(int value){
	
	glutPostRedisplay();
	glutTimerFunc(1000/60, myTimer, 1);
	
}

void display(void)
{	
	//exe->push_arg_complex<player*>(plr, qLib::Script::AS_OBJECT);
	exe->ctx->SetArgObject(0, (player*)plr);
	exe->exec();
	exe->reset();
	plr->move(0.3f);
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	draw(plr->getX(), plr->getY());
	
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
}

void idle(void)
{
    glutPostRedisplay();
}


void KeyDown(unsigned char key, int x, int y)
{
}

void KeyUp(unsigned char key, int x, int y)
{	
}

void PassiveMouse(int _x, int _y)
{
    mx = _x;
    my = _y;
}

int main(int argc, char **argv)
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
		return -1;
	}
	
	if(mod->buildScript() < 0)
	{
		printf("Failed to build script\n");
		return -1;
	}
	
	exe = engine->pGetScriptExec("patrol_module", "void patrol(player &plr)");
	
	glutInit(&argc, argv);
	
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
	
    glutCreateWindow("qeventlib example");
	
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
	
    glutKeyboardFunc(KeyDown);
    glutKeyboardUpFunc(KeyUp);
    glutPassiveMotionFunc(PassiveMouse);
	
    glutMainLoop();

    return 0;
}

