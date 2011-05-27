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

#include "qLib.h"

#include "qScriptEngine.h"
#include "qScriptModule.h"

qLib::Script::qScriptEngine *engine;
qLib::Script::qScriptModule *mod;
qLib::Script::qScriptExec *exe;

int global_int_native = 0;

int main (int argc, const char * argv[])
{
	engine = new qLib::Script::qScriptEngine();
	
	//REGISTER_GLOBAL_PROPERTY(engine, "int@ global_int_script", &global_int_native);
	engine->RegisterGlobalProperty("int global_int_script", &global_int_native);
	
	mod = engine->pGetScriptModule("test");
	
	const char *script =
	"void test()								"
	"{											"
	"	Print(\"Hello from the script, count : \" + global_int_script + \"\\n\");	"
	"	global_int_script++;					"
	"}											";
	
	int res = mod->addSection((char*)script);
	
	if(mod->buildScript() < 0)
	{
		printf("Failed to build script\n");
		return -1;
	}
	
	exe = engine->pGetScriptExec("test", "void test()");
	
	for(unsigned int a = 0;a < 100000;a++)
	{
		//printf("Hello from C++, count : %d\n", global_int_native);
		a++;
		exe->exec();
		exe->reset();
	}
	
    return 0;
}

