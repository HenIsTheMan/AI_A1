#ifndef App_H
#define App_H

#include "timer.h"

class App
{
public:
	static App& GetInstance()
	{
		static App app;
		return app;
	}
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	static bool IsMousePressed(unsigned short key);
	static void GetCursorPos(double *xpos, double *ypos);
	static int GetWindowWidth();
	static int GetWindowHeight();

private:
	App();
	~App();

	//Declare a window object
	StopWatch m_timer;
};

#endif