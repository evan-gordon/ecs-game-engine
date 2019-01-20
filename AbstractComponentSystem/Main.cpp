//Evan Gordon

//#define SFML_DYNAMIC
#include  <windows.h>
#include <cstdlib>

#include "g_Functions.h"
#include "gameStates/StateStack.h"

using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)//*///hide window
{
	initTrig();
	StateStack game;
	bool close = false;
	do
	{
		close = game.handleEvents();
		game.update();
		game.draw();

	}while(!close);
	return 0;
}