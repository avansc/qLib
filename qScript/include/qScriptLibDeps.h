/*
 *  qScriptLib
 *  qScriptLibDeps.h
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

#ifndef _ScriptLibDeps_h
#define _ScriptLibDeps_h

/*#include <angelscript.h>

#include <string>
#include <map>
#include <iostream>
#include <new.h>
#include <assert.h>

#include "../add_on/scriptstring/scriptstring.h"
#include "../add_on/scriptany/scriptany.h"
#include "../add_on/scriptarray/scriptarray.h"
#include "../add_on/scriptdictionary/scriptdictionary.h"*/

/*namespace qLib
{
	namespace Script
	{
		template<typename T> class iScriptable;
		
		class qScriptEngine;
		class qScriptExec;
		class qScriptModule;
		class qScriptLibrary;		
		
		typedef iScriptable<qScriptEngine> qScriptEngine_td;
		typedef iScriptable<qScriptExec> qScriptExec_td;
		typedef iScriptable<qScriptModule> qScriptModule_td;
		typedef iScriptable<qScriptLibrary> qScriptLibrary_td;
		
		typedef void(*pREG_FUNC)(qScriptEngine*);
	}
}

#define scriptable_class(name) class (name) : public iScriptable<(name)> 

#define REGISTER_CLASS(ENGINE, NAME, CLASS)																									\
if(ENGINE->hasObjectType(NAME) < 0)																											\
{																																			\
assert(ENGINE->getEngine()->RegisterObjectType(NAME, sizeof(CLASS), asOBJ_REF) >= 0);													\
assert(ENGINE->getEngine()->RegisterObjectBehaviour(NAME, asBEHAVE_FACTORY, NAME" @f()", asFUNCTION(Factory), asCALL_CDECL) >= 0);		\
\
assert(ENGINE->getEngine()->RegisterObjectBehaviour(NAME, asBEHAVE_FACTORY, NAME" @f(const "NAME"&in)", asFUNCTION(CopyFactory), asCALL_CDECL) >= 0);		\
\
assert(ENGINE->getEngine()->RegisterObjectBehaviour(NAME, asBEHAVE_ADDREF, "void f()", asMETHOD(CLASS,Addref), asCALL_THISCALL) >= 0);	\
assert(ENGINE->getEngine()->RegisterObjectBehaviour(NAME, asBEHAVE_RELEASE, "void f()", asMETHOD(CLASS,Release), asCALL_THISCALL) >= 0);\
}else																																		\
{																																			\
printf("Class name '%s' is already defined.\n", NAME);																					\
}																																			\


#define REGISTER_METHOD(ENGINE, NAME, CLASS, PROTO, FUNC)														\
if(ENGINE->objectHasMethod(NAME, PROTO) < 0)																	\
assert(ENGINE->getEngine()->RegisterObjectMethod(NAME, PROTO, asMETHOD(CLASS,FUNC), asCALL_THISCALL) >= 0);	\
else																											\
printf("Method name '%s' for class '%s' is already defined.\n", PROTO, NAME);								\


#define REGISTER_GLOBAL_FUNCTION(ENGINE, PROTO, FUNC)												\
if(ENGINE->hasFunction(PROTO) < 0)																	\
assert(ENGINE->getEngine()->RegisterGlobalFunction(PROTO, asFUNCTION(FUNC), asCALL_CDECL) >= 0);\
else																								\
printf("Global function '%s' is already defined.\n", PROTO);											\


#define REGISTER_GLOBAL_PROPERTY(ENGINE, DECLARATION, PROPERTY)						\
if(ENGINE->hasProperty(DECLARATION) < 0)											\
assert(ENGINE->getEngine()->RegisterGlobalProperty(DECLARATION, PROPERTY) >= 0);\
else																				\
printf("Global property '%s' is already defined.\n", DECLARATION);							\

#define REGISTER_TO_LIBRARY(ENGINE, NAME, FUNCTION)		\
ENGINE->getScriptLibrary()->add(NAME, FUNCTION);		\

 */

/*#include "qScriptLib.h"*/


#endif