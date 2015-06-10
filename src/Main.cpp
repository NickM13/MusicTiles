#include "game\Application.h"

int main(int argc, char* args[])
{
	Application::getInstance().init();
	Application::getInstance().destroy();
	return 0;
}
