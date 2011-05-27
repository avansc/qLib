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

qLib::Script::qScriptEngine *engine;
qLib::Script::qScriptModule *mod;
qLib::Script::qScriptExec *exe;

int mx;
int my;

int px = 100;
int py = 100;

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
	exe->exec();
	exe->reset();
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	draw(px, py);
	
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
	
	//REGISTER_GLOBAL_PROPERTY(engine, "int@ global_int_script", &global_int_native);
	engine->RegisterGlobalProperty("int px", &px);
	engine->RegisterGlobalProperty("int py", &py);
	
	mod = engine->pGetScriptModule("test");
	
	const char *script =
	"int state = 0;									"
	"void test()									"
	"{												"
	"	switch(state)								"
	"	{											"
	"		case 0 : px++; break;					"
	"		case 1 : py++; break;					"
	"		case 2 : px--; break;					"
	"		case 3 : py--; break;					"
	"	}											"
	"	if(state == 0 && px == 400) state++;		"
	"	else if(state == 1 && py == 400) state++;	"
	"	else if(state == 2 && px == 100) state++;	"
	"	else if(state == 3 && py == 100) state=0;	"
	"}												";
	
	int res = mod->addSection((char*)script);
	
	if(mod->buildScript() < 0)
	{
		printf("Failed to build script\n");
		return -1;
	}
	
	exe = engine->pGetScriptExec("test", "void test()");
	
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

