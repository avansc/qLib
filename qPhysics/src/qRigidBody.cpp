/*
 *  qPhysics
 *  qRigidBody.cpp
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

#include "qRigidBody.h"

namespace qLib
{
	namespace Physics
	{
		qRigidBody::qRigidBody()
		{
			btCollisionShape* shape = new btSphereShape(1);
			btDefaultMotionState* state = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,50,0)));
			btScalar mass = 1;
			btVector3 fallInertia(0,0,0);
			shape->calculateLocalInertia(mass,fallInertia);
			btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,state,shape,fallInertia);
			this->body = new btRigidBody(fallRigidBodyCI);
		}
		
		qRigidBody::qRigidBody(btCollisionShape *shape, btDefaultMotionState *state, btScalar mass)
		{
			btVector3 fallInertia(0,0,0);
			if(mass > 0)
			{
				shape->calculateLocalInertia(mass,fallInertia);
			}
			btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,state,shape,fallInertia);
			this->body = new btRigidBody(fallRigidBodyCI);
		}
		
		btRigidBody *qRigidBody::getBody()
		{
			return this->body;
		}
		
		btTransform qRigidBody::getTransformation()
		{
			btTransform trans;
			this->body->getMotionState()->getWorldTransform(trans);
			return trans;
		}
		
		void qRigidBody::applyImpulse(float _x, float _y, float _z)
		{
			//this->body->applyImpulse(
			btTransform trans;
			this->body->getMotionState()->getWorldTransform(trans);
			//this->body->applyForce(btVector3(_x, _y, _z), trans.getOrigin());
			//this->body->applyImpulse(btVector3(_x, _y, _z), trans.getOrigin());
			
			btVector3 t(_x,_y,_z);
			//t.rotate(btVector3(1,1,1), 15);
			
			this->body->applyCentralForce(t);
			 
		}
		
		bool qRigidBody::isActive()
		{
			return this->body->isActive();
		}
		
		qRigidBody *qRigidBody::convert(qLib::Util::qObject *ref)
		{
			//&output = static_cast<player*>(&ref);
			//&output = (player*)&ref;
			return (qRigidBody*)ref;
		}
		
		void qRigidBody::REGISTER_SCRIPTABLES(qScriptEngine *engine)
		{
			
			engine->RegisterScriptable<qObject>();
			
			REGISTER_CLASS(engine, "qRigidBody", qRigidBody);
			
			REGISTER_METHOD(engine, "qRigidBody", qRigidBody, "void applyImpulse(float x, float y, float z)", applyImpulse);
			
			REGISTER_METHOD(engine, "qRigidBody", qRigidBody, "bool isActive()", isActive);
			
			REGISTER_GLOBAL_FUNCTION(engine, "qRigidBody@ qRigidBody_convert(qObject@)", qRigidBody::convert);
		}
		
	}
}