/*
 *  ScriptLib
 *  qScriptExec.cpp
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

//#include "qScriptLibDeps.h"

#include "qScriptExec.h"

#include <assert.h>

using namespace qLib::Script;
		
qScriptExec::qScriptExec()
:	ctx(NULL),
	argc(0)
{
}

qScriptExec::qScriptExec(asIScriptContext *_ctx)
:	ctx(_ctx),
	argc(0)
{
}

qScriptExec::~qScriptExec()
{
}

int qScriptExec::exec()
{
	int r = this->ctx->Execute();
	
	if( r != asEXECUTION_FINISHED )
	{
		// The execution didn't finish as we had planned. Determine why.
		if( r == asEXECUTION_ABORTED )
			printf("The script was aborted before it could finish. Probably it timed out.\n");
		else if( r == asEXECUTION_EXCEPTION )
		{
			printf("The script ended with an exception.\n");
			
			// Write some information about the script exception
			int funcID = ctx->GetExceptionFunction();
			asIScriptFunction *func = this->ctx->GetEngine()->GetFunctionDescriptorById(funcID);
			printf("func: \n", func->GetDeclaration());
			printf("modl: \n", func->GetModuleName());
			printf("sect: \n", func->GetScriptSectionName());
			printf("line: \n", ctx->GetExceptionLineNumber());
			printf("desc: \n", ctx->GetExceptionString());
		}
		else
			printf("The script ended for some unforeseen reason (%d).\n", r);
	}
	else
	{
		// Retrieve the return value from the context
		//float returnValue = ctx->GetReturnFloat();
		//cout << "The script function returned: " << returnValue << endl;
	}
	return r;
}

int qScriptExec::reset()
{
	this->argc = 0;
	this->ctx->Prepare(this->ctx->GetExceptionFunction());
}

void qScriptExec::REGISTER_SCRIPTABLES(qScriptEngine *engine)
{
	REGISTER_CLASS(engine, "qScriptExec", qScriptExec);
}