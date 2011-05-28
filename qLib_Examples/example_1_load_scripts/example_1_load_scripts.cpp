#include <GLUT/GLUT.h>

#include "example_base.h"

#include "qLib.h"

#include "qScriptEngine.h"
#include "qScriptModule.h"

///////////////////////////////////////////////////
static qLib::Script::qScriptEngine *engine;
static qLib::Script::qScriptModule *mod;
static qLib::Script::qScriptExec *exe;
///////////////////////////////////////////////////

static void update(float dt)
{
	exe->exec();
	exe->reset();
}

static void init(void)
{
	engine = new qLib::Script::qScriptEngine();
	
	mod = engine->pGetScriptModule("test");
	
	const char *script =
	"void test(void)										"
	"{														"
	"	Print(\"Hello from the script world!\\n\");			"
	"}														";
	
	if(mod->addSection((char*)script) < 0)
	{
		printf("Failed to get script module\n");
		return;
	}
	
	if(mod->buildScript() < 0)
	{
		printf("Failed to build script\n");
		return;
	}
	
	exe = engine->pGetScriptExec("test", "void test(void)");
}

static void destroy(void)
{
	delete exe;
	delete mod;
	delete engine;
}

qLibExample example_1_load_scripts = {
	"Load Scripts",
	init,
	update,
	destroy,
};