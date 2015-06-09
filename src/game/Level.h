#pragma once
#include <string>

class Level
{
public:
	void loadLevel(std::string);
	int readByte();
	int* generateRandom(int);
	int getByte();
	int getSize();

private:
	int* leveldata = NULL;
	int levelsize = 0;
	int bytesread = 0;

};
