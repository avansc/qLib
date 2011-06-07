//
//  example_7_physics_script_events.cpp
//  qLib_Examples
//
//  Created by avansc on 6/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "example_3_register_classes.h"

#include "example_7_physics_script_events.h"

#include <GLUT/GLUT.h>

#include "example_base.h"

#include "qLib.h"

#include "qPhysicsLib.h"
#include <mach/mach_time.h>

#include <list>

typedef struct mach_timebase_info	*mach_timebase_info_t;
typedef struct mach_timebase_info	mach_timebase_info_data_t;

///////////////////////////////////////////////////
static qLib::Event::qEventRegistry *evt_reg;

static qLib::Physics::qWorld *world;
static qLib::Physics::qRigidBody *plane;
static qLib::Physics::qRigidBody *ball;

static physobj *obj;

static qLib::Script::qScriptEngine *engine;
static qLib::Script::qScriptModule *mod;
static qLib::Script::qScriptExec *exe;

static player *plr;

static const char *script =
"void ON_EVENT(qEvent &evt, qObject &obj)		"
"{												"
"	qObject@ it = obj.getComp(\"rigid_body\");"
//"	qRigidBody@ ref = qRigidBody_convert();	"
//"	if(!ref.isActive())							"
//"		ref.AddRef(); "
//"		ref.applyImpulse(100,100,0);				"
"}		";

static int mx;
static int my;

static int px = 100;
static int py = 100;

extern char keys[255];

static int t = 0;

static uint64_t timer = 0;

static std::list<qLib::Physics::qRigidBody*> body_list;

///////////////////////////////////////////////////


physobj::physobj(qLib::Physics::qRigidBody *body)
{
	this->addComp("rigid_body", body);
}

void physobj::render()
{
	std::string t("rigid_body");
	qLib::Physics::qRigidBody *body = (qLib::Physics::qRigidBody*)this->getComp(t);
	
	btTransform trans;
	body->getBody()->getMotionState()->getWorldTransform(trans);
	
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

void physobj::REGISTER_SCRIPTABLES(qScriptEngine *engine)
{
	REGISTER_CLASS(engine, "physobj", physobj);
	
	REGISTER_METHOD(engine, "physobj", physobj, "void render()", getX);
	REGISTER_METHOD(engine, "physobj", physobj, "void AddRef()", Addref);
	//Addref
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

	if(keys['w'] == 1)
	{
		ball->body->activate();
		ball->applyImpulse(0, 100, 0);
	}
	/*
	if(keys['q'] == 1)
	{
		//evt_reg->push_event(qLib::Event::qEvent(a, qLib::Event::KEY_DOWN, qLib::Event::EVENT_KEY));
		qLib::Physics::qRigidBody *t  = new qLib::Physics::qRigidBody(new btBoxShape(btVector3(10.f,10.f,10.f)),
																	  new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(100,300,0))),
																	  1.0f);
		
		t->getBody()->setLinearFactor(btVector3(1,1,0));
		t->getBody()->setAngularFactor(btVector3(0,0,1));
		world->m_dynamicsWorld->addRigidBody(t->getBody());
		body_list.push_back(t);
		
	}*/
	
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

static void draw_bounding_sphere(btVector3 &center, btScalar &rad)
{
	glColor3f(1.0f, 0.0f, 1.0f);
	glPushMatrix();
	glScaled(1.1, 1.1, 1);
	glTranslatef(center.getX(), center.getY(),0);
    glBegin(GL_QUADS);
    glVertex2f(-10, -10);
    glVertex2f(10, -10);
    glVertex2f(10, 10);
    glVertex2f(-10, 10);
    glEnd();
	//glutWireSphere(rad, 10, 10);
	glPopMatrix();
}

static void update(float dt)
{
	//glPushMatrix();
	uint64_t res =  mach_absolute_time() - timer;
	world->update(res/1000.0f);
	timer = mach_absolute_time();
	
	proc_events();
	
	obj->render();
	
	/*
	btTransform trans;
	btVector3 center;
	btScalar rad;
	const int	numObjects=world->m_dynamicsWorld->getNumCollisionObjects();
	btVector3 wireColor(1,0,0);
	for(int i=4;i<numObjects;i++)
	{
		btCollisionObject*	colObj=world->m_dynamicsWorld->getCollisionObjectArray()[i];
		printf("%f\n", center.getX());
		btRigidBody*		body=btRigidBody::upcast(colObj);
		body->getMotionState()->getWorldTransform(trans);
		//glRotatef(15, 0,0,1);
		//glRotatef(15, 0,0,1);
		glPushMatrix();
		//trans.getRotation().getAxis();
		//glTranslatef(trans.getOrigin().getX(), trans.getOrigin().getY(), 0);
		draw(trans);
		draw_bounding_sphere(center, rad);
		glPopMatrix();
		//char data[200];
		//sprintf(data, "pos = <%f,%f>", plr->getX(), plr->getY());
		//drawString(10, 10, data);
	}
	*/
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
	
	plane = new qLib::Physics::qRigidBody(new btStaticPlaneShape(btVector3(-1,0,0),1),
										  new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(600,0,0))));
	world->m_dynamicsWorld->addRigidBody(plane->getBody());
	
	plane = new qLib::Physics::qRigidBody(new btStaticPlaneShape(btVector3(1,0,0),1),
										  new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(10,0,0))));
	world->m_dynamicsWorld->addRigidBody(plane->getBody());
	
	//----
	
	ball = new qLib::Physics::qRigidBody(new btBoxShape(btVector3(10.f,10.f,10.f)),
										 new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(100,300,0))),
										 1.0f);
	
	ball->getBody()->setLinearFactor(btVector3(1,1,0));
	ball->getBody()->setAngularFactor(btVector3(0,0,1));
	
	obj = new physobj(ball);
	
	world->m_dynamicsWorld->addRigidBody(ball->getBody());
	timer =	mach_absolute_time();
	
	
	engine = new qLib::Script::qScriptEngine();
	engine->RegisterScriptable<qLib::Util::qObject>();
	engine->RegisterScriptable<qLib::Physics::qRigidBody>();
	engine->RegisterScriptable<qLib::Event::qEvent>();
	
	mod = engine->pGetScriptModule("event");
	
	if(mod->addSectionFromFile("script.as") < 0)
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
	
	evt_reg = new qLib::Event::qEventRegistry();
	qLib::Event::qEventListener *L = new qLib::Event::qKeyEventListener();
	qLib::Event::qEventHandler *H = new qLib::Event::qScriptEventHandler();
	((qLib::Event::qScriptEventHandler*)H)->set_script_exe(exe);
	
	evt_reg->register_pair(L, H, obj);
	
}

static void destroy(void)
{
	std::list<qLib::Physics::qRigidBody*>::iterator it;
	for(it = body_list.begin();it != body_list.end();it++)
	{
		delete *it;
	}
	body_list.clear();
	delete world;
}

qLibExample example_7_physics_script_events = {
	"Physics Script Events",
	init,
	update,
	destroy,
};