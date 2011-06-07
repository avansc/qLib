//
//  example_7_physics_script_events.h
//  qLib_Examples
//
//  Created by avansc on 6/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef _example_7_physics_script_events_h
#define _example_7_physics_script_events_h

#include "example_3_register_classes.h"

#include "qPhysicsLib.h"

class physobj : public player
{
public:
	physobj(qLib::Physics::qRigidBody *body);
	virtual ~physobj(){};
	
	void render();
	
	void REGISTER_SCRIPTABLES(qScriptEngine *engine);
};

#endif