#include <stdio.h>
#include <string.h>
#include <GLUT/GLUT.h>

#include "example_base.h"

static qLibExample *examples;
static qLibExample *current_example;
static int example_index = 0;
static int example_count = 0;

int mx;
int my;
char keys[255];

static void run_example(qLibExample *example);

static void drawString(int x, int y, float r, float g, float b, const char *str)
{
	glColor3f(r, g, b);
	glRasterPos2i(x, y);
	
	for(int i=0, len=strlen(str); i<len; i++){
		if(str[i] == '\n'){
			y -= 16;
			glRasterPos2i(x, y);
		} else {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, str[i]);
		}
	}
}

static void display(void)
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	current_example->update(1);
	
	for(int a = 0;a < example_count;a++)
	{
		char data[200];
		sprintf(data, "ex %d. %s", a+1, examples[a].name);
		
		if(a == example_index)
			drawString(15, 465 - a*16, 0, 1, 0, data);
		else
			drawString(10, 465 - a*16, 1, 1, 1, data);
	}
	
    glutSwapBuffers();
}

static void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
}

static void idle(void)
{
    glutPostRedisplay();
}

static void KeyDown(unsigned char key, int x, int y)
{
	keys[key] = 1;
	mx = x;
	my = y;
	
	
	if(key == 'n')
	{
		example_index ++;
		if(example_index >= example_count) example_index = 0;
		run_example(&examples[example_index]);
	}
	
	if(key >= '0' && key <= '9')
	{
		if(key-48 <= example_count)
		{
			example_index = key-49;
			run_example(&examples[example_index]);
		}
	}
}

static void KeyUp(unsigned char key, int x, int y)
{	
	keys[key] = 0;
	mx = x;
	my = y;
}

static void PassiveMouse(int x, int y)
{
    mx = x;
    my = y;
}

static void initGL(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	glEnableClientState(GL_VERTEX_ARRAY);
}

static void run_example(qLibExample *example)
{
	if(current_example)
		current_example->destroy();
	
	current_example = example;
	current_example->init();
	
	glutSetWindowTitle(current_example->name);
}

static void glutStuff(int argc, const char *argv[])
{
	glutInit(&argc, (char**)argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	
	glutInitWindowSize(640, 480);
	glutCreateWindow("example");
	
	initGL();
	
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	//glutTimerFunc(SLEEP_TICKS, timercall, 0);
	
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	
	glutMotionFunc(PassiveMouse);
	glutPassiveMotionFunc(PassiveMouse);
}

extern qLibExample example_1_load_scripts;
extern qLibExample example_2_register_variables;
extern qLibExample example_3_register_classes;
extern qLibExample example_4_events_native;
extern qLibExample example_5_events_script;

int main(int argc, const char **argv)
{
	qLibExample example_list[] = 
	{
		example_1_load_scripts,
		example_2_register_variables,
		example_3_register_classes,
		example_4_events_native,
		example_5_events_script
	};
	
	examples = example_list;
	
	example_count = sizeof(example_list)/sizeof(qLibExample);
	
	for(unsigned int a = 0;a < example_count;a++)
	{
		printf("%s\n", example_list[a].name);
	}
	
	glutStuff(argc, argv);
	run_example(&example_list[example_index]);
	glutMainLoop();
	
	example_list[example_index].destroy();
	
	return 0;
}

