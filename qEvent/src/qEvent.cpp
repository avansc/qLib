/*
 *  qEventLib
 *  qEvent.cpp
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
#include "qEvent.h"

namespace qLib
{
	namespace Event
	{
		qEvent::qEvent()
		{
		}

		qEvent::qEvent(unsigned int _param1, unsigned int _param2, event_type _type)
		{
			this->data.type = _type;
			this->data.key = EVENT_DEFAULT;
			
			switch (_type)
			{
				case EVENT_KEY:
				{
					this->data.event_data.key_d.key = _param1;
					this->data.event_data.key_d.state = _param2;
					break;
				}
				case EVENT_MOUSE:
				{
					this->data.event_data.mouse_d.x = _param1;
					this->data.event_data.mouse_d.y = _param2;
					break;
				}
				default:
					break;
			}
		}

		event_type qEvent::type()
		{
			return this->data.type;
		}

		unsigned int qEvent::key()
		{
			return this->data.key;
		}
		
		unsigned int qEvent::get_key_code()
		{
			return this->data.event_data.key_d.key;
		}
		
		unsigned int qEvent::get_key_state()
		{
			return this->data.event_data.key_d.state;
		}
		
		unsigned int qEvent::get_mouse_x()
		{
			return this->data.event_data.mouse_d.x;
		}
		
		unsigned int qEvent::get_mouse_y()
		{
			return this->data.event_data.mouse_d.y;
		}
		
		unsigned int qEvent::get_mouse_dx()
		{
			return this->data.event_data.mouse_d.dx;
		}
		
		unsigned int qEvent::get_mouse_dy()
		{
			return this->data.event_data.mouse_d.dy;
		}
		
		
		
		void qEvent::REGISTER_SCRIPTABLES(qScriptEngine *engine)
		{
			REGISTER_CLASS(engine, "qEvent", qEvent);
			
			REGISTER_METHOD(engine, "qEvent", qEvent, "uint type()", type);
			REGISTER_METHOD(engine, "qEvent", qEvent, "uint key()", key);
			REGISTER_METHOD(engine, "qEvent", qEvent, "uint get_key_code()", get_key_code);
			REGISTER_METHOD(engine, "qEvent", qEvent, "uint get_key_state()", get_key_state);
			REGISTER_METHOD(engine, "qEvent", qEvent, "uint get_mouse_x()", get_mouse_x);
			REGISTER_METHOD(engine, "qEvent", qEvent, "uint get_mouse_y()", get_mouse_y);
			REGISTER_METHOD(engine, "qEvent", qEvent, "uint get_mouse_dx()", get_mouse_dx);
			REGISTER_METHOD(engine, "qEvent", qEvent, "uint get_mouse_dy()", get_mouse_dy);
		}
	}
}