#include "App.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "SceneMovement.h"

GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

int winWidth, winHeight;

extern bool endLoop;

static void error_callback(int error, const char* description){
	fputs(description, stderr);
	_fgetchar();
}

static void resize_callback(GLFWwindow* window, int w, int h){
	winWidth = w;
	winHeight = h;
}

bool App::Key(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}
bool App::IsMousePressed(unsigned short key) //0 - Left, 1 - Right, 2 - Middle
{
	return glfwGetMouseButton(m_window, key) != 0;
}
void App::GetCursorPos(double *xpos, double *ypos)
{
	glfwGetCursorPos(m_window, xpos, ypos);
}
int App::GetWindowWidth()
{
	return winWidth;
}
int App::GetWindowHeight()
{
	return winHeight;
}

void App::Init(){
	glfwSetErrorCallback(error_callback);

	if(!glfwInit()){
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	const GLFWvidmode* const& mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	m_window = glfwCreateWindow(mode->width, mode->height, "App Window", nullptr, nullptr);
	glfwSetWindowPos(m_window, 0, 0);
	glfwHideWindow(m_window);
	glfwMaximizeWindow(m_window);
	glfwShowWindow(m_window);
	glfwGetWindowSize(m_window, &winWidth, &winHeight);

	if(!m_window){
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(m_window);

	glfwSetWindowSizeCallback(m_window, resize_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	glfwSwapInterval(0);
}

void App::Run(){
	Scene* scene = new SceneMovement();
	scene->Init();

	static bool isTab = false;
	static bool isF1 = false;

	m_timer.startTimer();
	while(!endLoop){
		if(glfwWindowShouldClose(m_window) || Key(VK_ESCAPE)){
			endLoop = true;
		}

		scene->Update(m_timer.getElapsedTime());

		if(!isTab && Key(VK_TAB)){
			glfwGetWindowAttrib(m_window, GLFW_VISIBLE) ? glfwHideWindow(m_window) : glfwShowWindow(m_window);
			isTab = true;
		} else if(isTab && !Key(VK_TAB)){
			isTab = false;
		}
		if(!isF1 && Key(VK_F1)){
			const GLFWvidmode* const& mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			glfwSetWindowMonitor(m_window, glfwGetWindowMonitor(m_window) ?	nullptr : glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
			isF1 = true;
		} else if(isF1 && !Key(VK_F1)){
			isF1 = false;
		}

		if(glfwGetWindowAttrib(m_window, GLFW_VISIBLE)){
			glViewport(0, 0, winWidth, winHeight);
			scene->Render();
		}

		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        //m_timer.waitUntil(frameTime);

	} //Check if the ESC key had been pressed or if the window had been closed

	scene->Exit();
	delete scene;
}

void App::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}