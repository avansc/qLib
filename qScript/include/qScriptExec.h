/*
 *  ScriptLib
 *  qScriptExec.h
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

#ifndef _qScriptExec_h
#define _qScriptExec_h

#include <angelscript.h>

//#include "qScriptLibDeps.h"

#include "qScriptEngine.h"

namespace qLib
{
	namespace Script
	{
		enum AS_ARG_TYPE { AS_BYTE = 0, AS_WORD, AS_DWORD, AS_QWORD, AS_FLOAT, AS_DOUBLE, AS_ADDRESS, AS_OBJECT };
		

		class qScriptExec : public iScriptable<qScriptExec>
		{
		public:
			qScriptExec();
			qScriptExec(asIScriptContext *_ctx);
			virtual ~qScriptExec();
			
			int exec();
			
			template<typename T>
			T exec();
			
			int reset();
			
			template<typename T>
			int push_arg(T data, AS_ARG_TYPE type);
			
			template<typename T>
			int push_arg_primitive(T data, AS_ARG_TYPE type);
			
			template<typename T>
			int push_arg_complex(T data, AS_ARG_TYPE type);
			
			template<typename T>
			T get_arg(AS_ARG_TYPE type);
			
			void REGISTER_SCRIPTABLES(qScriptEngine *engine);
			
		//private:
			asIScriptContext *ctx;
			int argc;
		};


		template<typename T>
		T qScriptExec::exec()
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
			//T ret = (T)this->ctx->GetAddressOfReturnValue();
			//this->reset();
			return (T)this->ctx->GetAddressOfReturnValue();
			
		}

		template<typename T>
		int qScriptExec::push_arg(T data, AS_ARG_TYPE type)
		{
			switch(type)
			{
				case AS_BYTE :
				case AS_WORD :
				case AS_DWORD :
				case AS_QWORD :
				case AS_FLOAT :
				case AS_DOUBLE :
				{
					this->push_arg_primitive(data, type);
					break;
				}
				case AS_ADDRESS :
				case AS_OBJECT :
				{
					this->push_arg_complex(data, type);
					break;
				}
				default:
					break;
			}
			return -1;
		}

		template<typename T>
		int qScriptExec::push_arg_primitive(T data, AS_ARG_TYPE type)
		{
			switch(type)
			{
				case AS_BYTE :
				{
					this->argc++;
					return this->ctx->SetArgByte(this->argc-1, data);
				}
				case AS_WORD :
				{
					this->argc++;
					return this->ctx->SetArgWord(this->argc-1, data);
				}
				case AS_DWORD :
				{
					this->argc++;
					return this->ctx->SetArgDWord(this->argc-1, data);
				}
				case AS_QWORD :
				{
					this->argc++;
					return this->ctx->SetArgQWord(this->argc-1, data);
				}
				case AS_FLOAT :
				{
					this->argc++;
					return this->ctx->SetArgFloat(this->argc-1, data);
				}
				case AS_DOUBLE :
				{
					this->argc++;
					return this->ctx->SetArgDouble(this->argc-1, data);
				}
				default:
					break;
			}
			return -1;
		}

		template<typename T>
		int qScriptExec::push_arg_complex(T data, AS_ARG_TYPE type)
		{
			switch(type)
			{
				case AS_ADDRESS :
				{
					this->argc++;
					return this->ctx->SetArgAddress(this->argc-1, data);
				}
				case AS_OBJECT :
				{
					this->argc++;
					return this->ctx->SetArgObject(this->argc-1, data);
				}
				default:
					break;
			}
			return -1;
		}


		template<typename T>
		T qScriptExec::get_arg(AS_ARG_TYPE type)
		{
			switch(type)
			{
				case AS_BYTE :
				{
					return this->ctx->GetReturnByte();
				}
				case AS_WORD :
				{
					return this->ctx->GetReturnWord();
				}
				case AS_DWORD :
				{
					return this->ctx->GetReturnDWord();
				}
				case AS_QWORD :
				{
					return this->ctx->GetReturnQWord();
				}
				case AS_FLOAT :
				{
					return (T)this->ctx->GetReturnFloat();
				}
				case AS_DOUBLE :
				{
					return this->ctx->GetReturnDouble();
				}
				case AS_ADDRESS :
				{
					return *((T*)this->ctx->GetReturnAddress());
				}
				case AS_OBJECT :
				{
					return *((T*)this->ctx->GetReturnObject());
				}
				default:
					break;
			}
				
			return (T)0;
		}
	}
}
#endif