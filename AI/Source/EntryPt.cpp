#include "App.h"

#include <crtdbg.h>
#include <thread>
#include <string>

#ifndef SLN_CONFIG
	#ifdef _DEBUG
		#define SLN_CONFIG (std::string)"Debug"
	#else
		#define SLN_CONFIG (std::string)"Release"
	#endif
#endif

#ifndef SLN_PLAT
	#ifdef _WIN64
		#define SLN_PLAT (std::string)"x64"
	#else
		#define SLN_PLAT (std::string)"x86"
	#endif
#endif

bool endLoop;

void MainProcess(){
	App& app = App::GetInstance();
	app.Init();
	app.Run();
	app.Exit();
}

int main(const int&, const char* const* const&){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SetLayeredWindowAttributes(GetConsoleWindow(), NULL, 230, LWA_ALPHA);
	SetConsoleTitleA(((std::string)"Console Window (" + SLN_CONFIG + ' ' + SLN_PLAT + ')').c_str());

	std::thread worker(&MainProcess);

	while(!endLoop){
		if(App::IsKeyPressed(VK_ESCAPE)){
			endLoop = true;
			break;
		}
	}

	worker.join();
}