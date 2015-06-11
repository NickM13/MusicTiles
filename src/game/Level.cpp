#include "game\Level.h"
#include <vector>
#include <SDL.h>

void Level::loadLevel(std::string filename)
{

}

int Level::readByte()
{
	if (bytesread < levelsize)
	{
		bytesread++;
		return leveldata[bytesread-1];
	}
	return NULL;
}

void Level::reload()
{
	bytesread = 0;
}

int* Level::generateRandom(int length)
{
	bytesread = 0;
	std::vector<int> rlevel_;
	int rlength_, row_, rrow_;
	
	printf("Generating random level\n");
	for (int i = 0; i < length; i++)
	{
		rlength_ = abs(rand() % 100);
		if (rlength_ < 0) rlength_ = 0;
		else if (rlength_ < 75) rlength_ = 1;
		else if(rlength_ < 85) rlength_ = 2;
		else if (rlength_ < 97) rlength_ = 3;
		else rlength_ = 4;

		row_ = 0;
		rlevel_.push_back(rlength_);
		for (int j = 0; j < rlength_;)
		{
			rrow_ = rand() % 10;
			if ((row_ >> rrow_) % 2 & 1)
				continue;
			row_ += (int)pow(2, rrow_);
			rlevel_.push_back(rrow_);

			j++;
		}
	}
	if (leveldata != NULL) {
		delete[] leveldata;
	}
	levelsize = rlevel_.size();
	leveldata = new int[levelsize];
	printf("Replacing old level...\n");
	for (unsigned int i = 0; i < rlevel_.size(); i++)
	{
		leveldata[i] = rlevel_[i];
	}
	printf("Random level generated, Size: %i\n", levelsize);
	printf("Exitting random level generator\n");
	return leveldata;
}

int Level::getByte()
{
	return bytesread;
}

int Level::getSize()
{
	return levelsize;
}
