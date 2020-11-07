#include "App.h"
#include <crtdbg.h>

int main( void ){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	App &app = App::GetInstance();
	app.Init();
	app.Run();
	app.Exit();
}