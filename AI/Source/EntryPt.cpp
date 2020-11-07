#include "App.h"

#include <crtdbg.h>
#include <thread>

bool endLoop;

void MainProcess(){
	App& app = App::GetInstance();
	app.Init();
	app.Run();
	app.Exit();
}

int main(const int&, const char* const* const&){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	std::thread worker(&MainProcess);

	while(!endLoop){
		if(App::IsKeyPressed(VK_ESCAPE)){
			endLoop = true;
			break;
		}
	}

	worker.join();
}