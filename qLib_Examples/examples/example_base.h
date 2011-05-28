//
//  example_base.h
//  qLib_Examples
//
//  Created by avansc on 5/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef _example_base_h
#define _example_base_h

typedef void (*init_func)(void);
typedef void (*update_func)(float _dt);
typedef void (*destroy_func)(void);

typedef struct qLibExample
{
	const char *name;
	init_func init;
	update_func update;
	destroy_func destroy;
} qLibExample;

#endif