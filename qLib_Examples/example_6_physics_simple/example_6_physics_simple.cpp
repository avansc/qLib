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
#include <mach/mach_time.h>

typedef struct mach_timebase_info	*mach_timebase_info_t;
typedef struct mach_timebase_info	mach_timebase_info_data_t;

///////////////////////////////////////////////////
qLib::Physics::qWorld *world;
qLib::Physics::qRigidBody *ball;
qLib::Physics::qRigidBody *plane;

static int mx;
static int my;

static int px = 100;
static int py = 100;

extern char keys[255];

static int t = 0;

uint64_t timer = 0;

///////////////////////////////////////////////////


static void proc_events()
{	
	if(keys['q'] == 1)
	{
		//evt_reg->push_event(qLib::Event::qEvent(a, qLib::Event::KEY_DOWN, qLib::Event::EVENT_KEY));
		qLib::Physics::qRigidBody *t  = new qLib::Physics::qRigidBody(new btBoxShape(btVector3(10.f,10.f,10.f)),
																			 new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(100,300,0))),
																			 1.0f);
		
		t->getBody()->setLinearFactor(btVector3(1,1,0));
		t->getBody()->setAngularFactor(btVector3(0,0,1));
		world->m_dynamicsWorld->addRigidBody(t->getBody());
		
	}
	
	//evt_reg->process_events();
}

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

static void draw(btTransform trans)
{
	//temp->
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	//glScaled(0.3f, 0.3f, 1);
    glTranslatef(trans.getOrigin().getX(), trans.getOrigin().getY(), 0);
	btScalar yaw, pitch, roll;
	trans.getBasis().getEulerYPR(yaw, pitch, roll);
	glRotatef(yaw*180/3.14159265358979f, 0,0,1);
    glBegin(GL_QUADS);
    glVertex2f(-10, -10);
    glVertex2f(10, -10);
    glVertex2f(10, 10);
    glVertex2f(-10, 10);
    glEnd();
    glPopMatrix();
}

static void draw(int x, int y)
{
	//temp->
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	
    glTranslatef(x, y, 0);
	glRotatef(15, 0,0,1);
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
	//glPushMatrix();
	uint64_t res =  mach_absolute_time() - timer;
	world->update(res/10000.0f);
	timer = mach_absolute_time();
	
	proc_events();
	
	btTransform trans;
	const int	numObjects=world->m_dynamicsWorld->getNumCollisionObjects();
	btVector3 wireColor(1,0,0);
	for(int i=0;i<numObjects;i++)
	{
		btCollisionObject*	colObj=world->m_dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody*		body=btRigidBody::upcast(colObj);
		body->getMotionState()->getWorldTransform(trans);
	
		//glRotatef(15, 0,0,1);
		//glRotatef(15, 0,0,1);
		glPushMatrix();
		//trans.getRotation().getAxis();
		//glTranslatef(trans.getOrigin().getX(), trans.getOrigin().getY(), 0);
		draw(trans);
		glPopMatrix();
		//char data[200];
		//sprintf(data, "pos = <%f,%f>", plr->getX(), plr->getY());
		//drawString(10, 10, data);
	}
	
	//glPopMatrix();
}

static void init(void)
{
	world = new qLib::Physics::qWorld();
	
	plane = new qLib::Physics::qRigidBody(new btStaticPlaneShape(btVector3(0,1,0),1),
										  new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,10,0))));
	world->m_dynamicsWorld->addRigidBody(plane->getBody());
	
	plane = new qLib::Physics::qRigidBody(new btStaticPlaneShape(btVector3(0,-1,0),1),
										  new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,500,0))));
	world->m_dynamicsWorld->addRigidBody(plane->getBody());
	
	/*plane = new qLib::Physics::qRigidBody(new btStaticPlaneShape(btVector3(0,1,0),1),
										  new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0))));
	world->m_dynamicsWorld->addRigidBody(plane->getBody());
	
	plane = new qLib::Physics::qRigidBody(new btStaticPlaneShape(btVector3(0,1,0),1),
										  new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0))));
	world->m_dynamicsWorld->addRigidBody(plane->getBody());*/
	
	//----
	
	/*ball = new qLib::Physics::qRigidBody(new btBoxShape(btVector3(5.f,5.f,5.f)),
										 new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(100,300,0))),
										 1.0f);
	
	ball->getBody()->setLinearFactor(btVector3(1,1,0));
	ball->getBody()->setAngularFactor(btVector3(0,0,1));
	
	world->m_dynamicsWorld->addRigidBody(ball->getBody());*/
	timer =	mach_absolute_time();

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