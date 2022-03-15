#include "SoundPlayer.h"
#include "stdafx.h"


SoundPlayer::SoundPlayer()
{
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1)
	{
		printf("Audio Mixer could not be created! SDL_Error %\n", SDL_GetError());
	}

	for (int i = 0; i < TOTAL_SOUNDS; i++)
	{
		stringstream name;
		name << "assets\\";
		name << i;
		name << ".wav";
		cout <<  name.str();
		Mix_Chunk* sound = Mix_LoadWAV(name.str().c_str());
		soundFiles.push_back(sound);
	}
}

void SoundPlayer::init()
{
	Mix_Chunk* sound = NULL;

	sound = Mix_LoadWAV("Juno In The Space Maze - Loopop");
	if (sound == NULL) {
		fprintf(stderr, "Unable to load WAV file: %s\n", Mix_GetError());
	}
	soundFiles.push_back(sound);
	sound = Mix_LoadWAV("assets\\2.wav");
	if (sound == NULL) {
		fprintf(stderr, "Unable to load WAV file: %s\n", Mix_GetError());
	}
	soundFiles.push_back(sound);
}

SoundPlayer::~SoundPlayer()
{
	for (auto& sound : soundFiles)
	{
		Mix_FreeChunk(sound);
	}

	cout << "soundClean?";
	Mix_FreeMusic(musicPlayer);
}

void SoundPlayer::PlaySound(int sound, bool loop)
{
	std::cout << "sound play request";
	int i = 0;
	if (loop)
	{
		i = -1;
	}

	Mix_PlayChannel(-1, soundFiles[sound], i);
}


