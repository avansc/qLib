/*
 *  ScriptLib
 *  qScriptModule.cpp
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

#include "qScriptModule.h"

#include <stdio.h>

#include <angelscript.h>

using namespace qLib::Script;

qScriptModule::qScriptModule()
{
}

qScriptModule::qScriptModule(asIScriptModule *_mod, std::string _name)
:	mod(_mod),
	name(_name)
{
}

qScriptModule::~qScriptModule()
{
}

int qScriptModule::addSection(char *_script)
{
	int r = this->mod->AddScriptSection(this->name.c_str(), _script, strlen(_script));
	if( r < 0 ) 
	{
		printf("AddScriptSection() failed\n");
		return -1;
	}
	
	return r;
}

int qScriptModule::addSectionFromFile(char *_file)
{
	int r;
	
	// We will load the script from a file on the disk.
	FILE *f = fopen(_file, "rb");
	if( f == 0 )
	{
		printf("Failed to open the script file '%s'.\n", _file);
		free(_file);
		return -1;
	}
	
	// Determine the size of the file	
	fseek(f, 0, SEEK_END);
	int len = ftell(f);
	fseek(f, 0, SEEK_SET);
	
	// On Win32 it is possible to do the following instead
	// int len = _filelength(_fileno(f));
	
	// Read the entire file
	string script;
	script.resize(len);
	int c =	fread(&script[0], len, 1, f);
	fclose(f);
	free(_file);
	
	if( c == 0 ) 
	{
		printf("Failed to load script file.\n");
		return -1;
	}
	
	//printf("%s\n", &script[0]);
	r = mod->AddScriptSection(this->name.c_str(), &script[0], len);
	if( r < 0 ) 
	{
		printf("AddScriptSection() failed\n");
		return -1;
	}
}

int qScriptModule::buildScript()
{
	
	//this->mod->
	int r = this->mod->Build();
	if( r < 0 )
	{
		printf("Build() failed\n");
		return -1;
	}
	return r;
}

void qScriptModule::REGISTER_SCRIPTABLES(qScriptEngine *engine)
{
}