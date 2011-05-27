/*
 *  qEventLib
 *  qEventHandler.cpp
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

#include "qEventHandler.h"
#include "qEvent.h"

namespace qLib
{
	namespace Event
	{
		qEventHandler::qEventHandler()
		{
		}

		void qEventHandler::ON_EVENT(const qEvent &_evt)
		{
			{
			/*switch (_evt.data.type)
			{
				case EVENT_KEY :
				{
					switch (_evt.data.event_data.key_d.state)
					{
						case KEY_DOWN :
						{
							switch(_evt.data.event_data.key_d.key)
							{
								case 'a' :
								{
									((qEntity*)this->getRoot())->x -= 0.1;
									break;
								}
								case 'd' :
								{
									((qEntity*)this->getRoot())->x += 0.1;
									break;
								}
								case 'w' :
								{
									((qEntity*)this->getRoot())->y += 0.1;
									break;
								}
								case 's' :
								{
									((qEntity*)this->getRoot())->y -= 0.1;
									break;
								}
							}
							break;
						}
						case KEY_PRESSED :
						{
							printf("KEY PRESSED : %c\n", _evt.data.event_data.key_d.key);
							break;
						}
						case KEY_RELEASED :
						{
							printf("KEY RELEASED : %c\n", _evt.data.event_data.key_d.key);
							break;
						}
							
						default:
							break;
					}
				}
					
				default:
					break;
			}*/
			//printf("default event handler\n");
			}
		}
	}
}