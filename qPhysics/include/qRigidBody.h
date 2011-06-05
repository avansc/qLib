/*
 *  qPhysics
 *  qRigidBody.h
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

#ifndef _qRigidBody_h
#define _qRigidBody_h

#include <bullet/btBulletCollisionCommon.h>
#include <bullet/btBulletDynamicsCommon.h>

#include <bullet/LinearMath/btVector3.h>
#include <bullet/LinearMath/btMatrix3x3.h>
#include <bullet/LinearMath/btTransform.h>
#include <bullet/LinearMath/btQuickprof.h>
#include <bullet/LinearMath/btAlignedObjectArray.h>

class	btDynamicsWorld;
class	btRigidBody;
class	btTypedConstraint;
class	btBroadphaseInterface;
class	btCollisionShape;
class	btOverlappingPairCache;
class	btCollisionDispatcher;
class	btConstraintSolver;
struct	btCollisionAlgorithmCreateFunc;
class	btDefaultCollisionConfiguration;

#include "qComponent.h"

namespace qLib
{
	namespace Physics
	{
		class qRigidBody : public qLib::Util::qComponent
		{
		public:
			qRigidBody();
			qRigidBody(btCollisionShape *shape, btDefaultMotionState *state, btScalar mass = 0.f);
			virtual ~qRigidBody(){ delete this->body;};
			
			btRigidBody *getBody();
			btTransform getTransformation();
			
			void applyImpulse(float _x, float _y, float _z);
		//private:
			btRigidBody *body;
		};
	}
}
#endif