/*
 *  qEventLib
 *  qEvent.h
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

#ifndef _qEvent_h
#define _qEvent_h

namespace qLib
{
	namespace Event
	{
		enum event_type
		{
			EVENT_DEFAULT = 0,
			EVENT_KEY,
			EVENT_MOUSE,
			EVENT_GAME,
			EVENT_USER,
			EVENT_MONITOR
		};

		enum key_state
		{
			KEY_UP = 0,
			KEY_PRESSED,
			KEY_DOWN,
			KEY_RELEASED
		};

		struct key_data
		{
			unsigned int key;
			unsigned int state;
		};

		struct mouse_data
		{
			float x;
			float y;
			float dx;
			float dy;
		};

		struct default_data
		{
			void *data;
		};

		typedef struct event_data
		{
			event_type type;
			unsigned int key;
			union data
			{
				default_data default_d;
				key_data key_d;
				mouse_data mouse_d; 
				default_data game_d;
				default_data user_d;
			};
			data event_data;
			
		} event_data;

		class qEvent
		{
		public:
			qEvent();
			qEvent(unsigned int _param1, unsigned int _param2, event_type _type);
			event_type type();
			unsigned int key();
			
			unsigned int get_key_code();
			unsigned int get_key_state();
			unsigned int get_mouse_x();
			unsigned int get_mouse_y();
			unsigned int get_mouse_dx();
			unsigned int get_mouse_dy();
			void *get_game_data();
			void *get_user_data();
			
		//private:
			event_data data;
		};
	}
}

#endif