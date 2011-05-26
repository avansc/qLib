/*
 *  ScriptLib
 *  qScriptEngine.cpp
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

#include "qScriptEngine.h"

#include <iostream>

#include <angelscript.h>

#include "qScriptAddons.h"

#include "qScriptLibrary.h"
#include "qScriptModule.h"
#include "qScriptExec.h"

using namespace qLib::Script;

qScriptEngine::qScriptEngine()
{
	this->p_engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
	this->p_engine->SetMessageCallback(asFUNCTION(qScriptEngine::MESSAGE_CALLBACK), 0, asCALL_CDECL);
	
	RegisterScriptString(this->p_engine);
	
	REGISTER_GLOBAL_FUNCTION(this, "void Print(string &in)", qScriptEngine::DEBUG_PRINT);
	
	REGISTER_GLOBAL_FUNCTION(this, "void PrintLn(string &in)", qScriptEngine::DEBUG_PRINT_LN);
	REGISTER_GLOBAL_FUNCTION(this, "void PrintInt(int &in)", qScriptEngine::DEBUG_PRINT_INT);
	
	
	this->REGISTER_SCRIPTABLES(this);
}

qScriptEngine::~qScriptEngine()
{
}


qScriptModule *qScriptEngine::pGetScriptModule(std::string mod)
{
	asIScriptModule *p_mod = this->p_engine->GetModule(mod.c_str(), asGM_CREATE_IF_NOT_EXISTS);
	if(p_mod)
		return new qScriptModule(p_mod, mod);
	else
		return NULL;
}

qScriptExec	*qScriptEngine::pGetScriptExec(std::string mod, std::string func)
{
	asIScriptContext *ctx = this->p_engine->CreateContext();
	if(ctx->Prepare(this->p_engine->GetModule(mod.c_str())->GetFunctionIdByDecl(func.c_str())) < 0)
	{
		printf("Could not get qScriptExec\n");
		return NULL;
	}
	return new qScriptExec(ctx);
}

int qScriptEngine::hasFunction(char *func)
{
	int len = this->p_engine->GetGlobalFunctionCount();
	for(int a = 0; a < len; a++)
	{
		if(strcmp_ws(func, (char*)this->p_engine->GetFunctionDescriptorById(this->p_engine->GetGlobalFunctionIdByIndex(a))->GetDeclaration()))
			return a;
	}
	return -1;
}

int qScriptEngine::hasFunctionS(string &func)
{
	return this->hasFunction((char*)func.c_str());
}

int qScriptEngine::hasProperty(char *func)
{
	int len = this->p_engine->GetGlobalPropertyCount();
	for(int a = 0; a < len; a++)
	{
		const char *name;
		this->p_engine->GetGlobalPropertyByIndex(a, &name, NULL, NULL);
		if(strcmp_ws(func, (char*)name) == 0) // changes strcmp to strcmp_ws, may cause issue.
			return a;
	}
	return -1;
}

int qScriptEngine::hasPropertyS(string &func)
{
	return this->hasProperty((char*)func.c_str());
}

int qScriptEngine::hasObjectType(const char *object)
{
	int len = this->p_engine->GetObjectTypeCount();
	for(int a = 0; a < len; a++ )
	{
		if(strcmp_ws((char*)object, (char*)this->p_engine->GetObjectTypeByIndex(a)->GetName()))
			return a;
	}
	return -1;
}
int qScriptEngine::hasObjectTypeS(string &object)
{
	return this->hasObjectType(object.c_str());
}

int qScriptEngine::objectHasMethod(const char *object ,const char *method)
{
	int o = this->hasObjectType(object);
	if(o >= 0)
	{
		int m = this->p_engine->GetObjectTypeByIndex(o)->GetMethodCount();
		for(int a = 0;a < m;a++)
		{
			//printf(":::-> %s\n", this->p_engine->GetObjectTypeByIndex(o)->GetMethodDescriptorByIndex(a, false)->GetDeclaration(false));
			if(strcmp_ws((char*)method, (char*)this->p_engine->GetObjectTypeByIndex(o)->GetMethodDescriptorByIndex(a, false)->GetDeclaration(false)))
				return a;
		}
	}
	return -1;
	
}

int	qScriptEngine::setScriptLibrary(qScriptLibrary *_p_lib)
{
	this->p_lib = _p_lib;
}

qScriptLibrary *qScriptEngine::getScriptLibrary()
{
	return this->p_lib;
}

int	qScriptEngine::exposeClass(string _class)
{
	this->p_lib->expose(this, _class);
}

void qScriptEngine::REGISTER_SCRIPTABLES(qScriptEngine *engine)
{
	REGISTER_CLASS(engine, "qScriptEngine", qScriptEngine);
	
	REGISTER_METHOD(engine, "qScriptEngine", qScriptEngine, "int exposeClass(string &in)", exposeClass);
	
	this->RegisterGlobalProperty("qScriptEngine this", this);
}

int qScriptEngine::RegisterGlobalProperty(const char *dec, void *ptr)
{
	this->p_engine->RegisterGlobalProperty(dec, ptr);
}


void qScriptEngine::DEBUG_PRINT(string &str)
{
	cout << str;
}

void qScriptEngine::DEBUG_PRINT_LN(string &str)
{
	cout << str << std::endl;
}

void qScriptEngine::DEBUG_PRINT_INT(int &val)
{
	cout << val;
}

void qScriptEngine::MESSAGE_CALLBACK(const asSMessageInfo *msg, void *param)
{
	const char *type = "ERR ";
	if( msg->type == asMSGTYPE_WARNING ) 
		type = "WARN";
	else if( msg->type == asMSGTYPE_INFORMATION ) 
		type = "INFO";
	printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
}


bool qScriptEngine::strcmp_ws(char *str1, char *str2)
{
	if(str1 == NULL || str2 == NULL) return false;
	
	char *t1 = str1;
	char *t2 = str2;
	
	while(*t1 != '\0' || *t2 != '\0')
	{
		while (*t1 == ' ') t1++;
		while (*t2 == ' ') t2++;
		if(*t1 != *t2) return false;
		if(*t1) t1++;
		if(*t2) t2++;
	}
	if(*t1 != *t2)
		return false;
	return true;
}