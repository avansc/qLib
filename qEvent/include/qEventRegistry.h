/*
 *  qEventLib
 *  qEventRegistry.h
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

#ifndef _qEventRegistry_h
#define _qEventRegistry_h

#include <map>
#include <vector>

//#include "qComponent.h"

#include "qEvent.h"

using namespace std;

namespace qLib
{
	namespace Util
	{
	//	class qComponent;
	}
	
	namespace Event
	{
		class qEventListener;
		class qEventHandler;
		//typedef multimap<unsigned int , multimap<unsigned int, qEventListener*> > listener_multimap;

		typedef multimap<unsigned int, qEventListener*> listener_multimap;
		typedef multimap<unsigned int, qEventListener*> monitor_multimap;
		typedef multimap<unsigned int, multimap<unsigned int, qEventListener*> >listener_multi_map;

		const unsigned int EVENT_BUFFER_MAX = 100;

		class qEventRegistry
		{
		public:
			qEventRegistry();
			bool push_event(const qEvent &_evt);
			
			void process_events();
			
			bool register_pair(qEventListener *L, qEventHandler *H, qLib::Util::qObject *comp);

		private:
			listener_multimap listeners;
			listener_multi_map listener_map;
			monitor_multimap monitor_map;
			//multimap<unsigned int, qEventListener*> listeners;
			vector<qEvent> event_queue;
			qEvent event_buffer[EVENT_BUFFER_MAX];
			unsigned int buffer_count;
			
		};
	}
}

#endif