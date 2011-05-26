/*
 *  ScriptLib
 *  qScriptEngine.h
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

#ifndef _qScriptEngine_h
#define _qScriptEngine_h

#include <angelscript.h>

#include <assert.h>

#include <string>

using namespace std;

#include "qScriptLibDeps.h"

namespace qLib
{
	namespace Script
	{
		template<typename T>
		class iScriptable
		{
		public:
			iScriptable();
			iScriptable(const T &other);
			~iScriptable();
			
			virtual void REGISTER_SCRIPTABLES(qScriptEngine *engine) = 0;
			
			void Addref();
			void Release();
			T typeOf() { return T(); }
			T &operator=(const T &other);
			
			static void constructor(void *mem);
			static void destructor(void *mem);
			static void *Factory();
			static T *CopyFactory(const T &other);
			
			
			static void regit(qScriptEngine *engine);
			
		protected:
			int RefCount;
			
		};
		
		template<typename T>
		iScriptable<T>::iScriptable()
		:	RefCount(1)
		{
		}
		template<typename T>
		iScriptable<T>::iScriptable(const T &other)
		:	RefCount(1)
		{
		}
		
		template<typename T>
		iScriptable<T>::~iScriptable()
		{
		}
		
		template<typename T>
		void iScriptable<T>::Addref()
		{
			this->RefCount++;
		}
		
		template<typename T>
		void iScriptable<T>::Release()
		{
			if(--RefCount == 0)
				delete this;
		}
		
		template<typename T>
		T &iScriptable<T>::operator=(const T &other)
		{
			// Copy only the data, not the reference counter
			// ex. buffer = other.buffer;
			
			// Return a reference to this object
			return *this;
		}
		
		
		template<typename T>
		void iScriptable<T>::constructor(void *mem)
		{
			new(mem) T();
		}  
		
		template<typename T>
		void iScriptable<T>::destructor(void *mem)
		{
			((T*)mem)->~T();
		}
		
		template<typename T>
		void *iScriptable<T>::Factory()
		{
			return new T();
		}
		template<typename T>
		T *iScriptable<T>::CopyFactory(const T &other)
		{
			return new T(other);
		}
		
		template<typename T>
		void iScriptable<T>::regit(qScriptEngine *engine)
		{
			T::LIBRARY_REGISTER_SCRIPTABLES(engine);
		}
		
		class qScriptEngine : public iScriptable<qScriptEngine>
		{
		public:
			qScriptEngine();
			~qScriptEngine();
			
			//// iteration 0 ////
			
			qScriptModule	*pGetScriptModule(std::string mod);
			qScriptExec		*pGetScriptExec(std::string mod, std::string func);
			
			int				hasFunctionS(string &func);
			int				hasFunction(char *func);
			int				hasPropertyS(string &func);
			int				hasProperty(char *func);
			int				hasObjectType(const char *object);
			int				hasObjectTypeS(string &object);
			int				objectHasMethod(const char *object, const char *method);
			int				setScriptLibrary(qScriptLibrary *_p_lib);
			qScriptLibrary	*getScriptLibrary();
			int				exposeClass(string _class);
			int				RegisterGlobalProperty(const char *dec, void *ptr);
			template<typename T>
			void			RegisterScriptable();
			
			asIScriptEngine *getEngine() { return this->p_engine; }
			
			static void		DEBUG_PRINT(string &str);
			static void		DEBUG_PRINT_LN(string &str);
			static void		DEBUG_PRINT_INT(int &val);
			static void		MESSAGE_CALLBACK(const asSMessageInfo *msg, void *param);
			
			/////////////////////
			
			void			REGISTER_SCRIPTABLES(qScriptEngine *engine);
			
			static bool		strcmp_ws(char *str1, char *str2);
			
		private:
			asIScriptEngine *p_engine;
			qScriptLibrary *p_lib;
		};
		
		template<typename T>
		void qScriptEngine::RegisterScriptable()
		{
			T bla;
			bla.REGISTER_SCRIPTABLES(this);
		}
	}
}

#endif