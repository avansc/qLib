/*
 *  qEventLib
 *  qEventRegistry.cpp
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

#include "qEventRegistry.h"
#include "qEventListener.h"

#include "qComponent.h"

namespace qLib
{
	namespace Event
	{
		qEventRegistry::qEventRegistry()
		:	buffer_count(0)
		{
		}

		bool qEventRegistry::push_event(const qEvent &_evt)
		{
			if(this->buffer_count >= EVENT_BUFFER_MAX)
			{
				printf("EVENT BUFFER FULL!\n");
				return false;
			}
			
			this->event_buffer[this->buffer_count] = _evt;
			this->buffer_count++;
			
			return true;
		}

		void qEventRegistry::process_events()
		{
			// loop over all the events in our buffer
			for(unsigned int e_itr = 0;e_itr < this->buffer_count;e_itr++)
			{
				// iterator over entire multimap
				pair<listener_multi_map::iterator, listener_multi_map::iterator> l_main_itr;
				
				// only get listeners(really a multimaps) of event type (KEY, MOUSE, GAME, ...)
				l_main_itr = this->listener_map.equal_range(this->event_buffer[e_itr].type());
				
				// loop over all listeners(really multimaps) of that type
				for(listener_multi_map::iterator l_main_itr2 = l_main_itr.first;
					l_main_itr2 != l_main_itr.second; l_main_itr2++)
				{
					// iterator over inner multimap
					pair<listener_multimap::iterator, listener_multimap::iterator> l_itr;
					
					// only get listeners with defined key (anything the user specified, 0 by default)
					l_itr = l_main_itr2->second.equal_range(this->event_buffer[e_itr].key());
					
					// loop over listeners with same key type.
					for(listener_multimap::iterator l_itr2 = l_itr.first;
						l_itr2 != l_itr.second; l_itr2++)
					{
						// call listener, which in turn will call the event handler.
						l_itr2->second->ON_EVENT(this->event_buffer[e_itr]);
					}
				}
			}
			
			// reset buffer.
			this->buffer_count = 0;
		}

		bool qEventRegistry::register_pair(qEventListener *L, qEventHandler *H, qLib::Util::qComponent *comp)
		{
			// set the root of the listener and handler to the listening object
			((qLib::Util::qComponent*)L)->setRoot(comp);
			((qLib::Util::qComponent*)H)->setRoot(comp);
			// add listener and handler as components to the listening object
			comp->addComp("event_listener", (qLib::Util::qComponent*)L);
			comp->addComp("event_handler", (qLib::Util::qComponent*)H);
			
			// get multimap with type of the listener
			multimap<unsigned int, qEventListener*> t = this->listener_map.find(L->listener_type())->second;
			// insert the new listener with its key type
			t.insert(pair<unsigned int, qEventListener*>(L->listener_key(), L));
			// insert multimap back into main listener nested multimap
			this->listener_map.insert(pair<unsigned int, multimap<unsigned int, qEventListener*> >(L->listener_type(), t));
			
			return true;
		}
	}
}