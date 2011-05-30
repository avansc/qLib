//
//  example_3_register_classes.h
//  qLib_Examples
//
//  Created by avansc on 5/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef _example_3_register_classes_h
#define _example_3_register_classes_h

#include "qLib.h"

class player : public qLib::Util::qComponent
{
public:
	player();
	player(const float &_x, const float &_y);
	virtual ~player(){};
	
	float getX() { return this->x; }
	float getY() { return this->y; }
	
	int getXDir() { return this->dx; }
	int getYDir() { return this->dy; }
	
	void setX(float _x) { this->x = _x; }
	void setY(float _y) { this->y = _y; }
	
	void move(float dt);
	void setDir(int _dx, int _dy);
	
	virtual void REGISTER_SCRIPTABLES(qScriptEngine *engine);
private:
	float x,y;
	int dx, dy;
};

#endif