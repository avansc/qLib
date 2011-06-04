//
//  example_6_physics_simple.cpp
//  qLib_Examples
//
//  Created by avansc on 6/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include "example_6_physics_simple.h"

#include <GLUT/GLUT.h>

#include "example_base.h"

#include "qLib.h"

#include "qPhysicsLib.h"

///////////////////////////////////////////////////

static int mx;
static int my;

static int px = 100;
static int py = 100;


extern char keys[255];

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
	
	//char data[200];
	//sprintf(data, "pos = <%f,%f>", plr->getX(), plr->getY());
	//drawString(10, 10, data);
}

static void init(void)
{	
}

static void destroy(void)
{
}

qLibExample example_6_physics_simple = {
	"Simple Physics",
	init,
	update,
	destroy,
};