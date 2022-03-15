#pragma once
#include <SDL_mixer.h>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

enum Sounds
{
	CANDY_CANE=0,
	BAUBLE,
	BELL,
	FirstInLineSilentPartner,
	ToasterFire,
	TOTAL_SOUNDS,
};

class SoundPlayer
{

public:
	SoundPlayer();
	void init();
	virtual ~SoundPlayer();
	void clean();

	void PlaySound(int sound, bool loop);

private:
	Mix_Music* musicPlayer;
	vector<Mix_Chunk*> soundFiles;
};

