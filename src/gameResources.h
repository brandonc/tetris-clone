/*
 *  gameResources.h
 *  Tetris
 *
 *  Created by Brandon Croft on 12/6/08.
 *  Copyright 2008 Brandon Croft. All rights reserved.
 *
 */

#include "SDL.h"
#include "SDL_mixer/SDL_mixer.h"
#include "SDL_image/SDL_image.h"

#ifdef _WIN32
#include "zipResourceManager.h"
#elif defined(__APPLE_CC__)
#include "osx/OSXResourceManager.h"
#endif

class GameResources {
public:
	static GameResources* instance();
	
	SDL_Surface* tiles;
	SDL_Surface* field;
	SDL_Surface* numbers;
	SDL_Surface* paused;
	SDL_Surface* gameover;
	
	Mix_Music* music;
	Mix_Chunk* wav_click;
	Mix_Chunk* wav_line;
	Mix_Chunk* wav_tetris;
	Mix_Chunk* wav_pause;
	
	~GameResources();
private:
	static GameResources* singleton;
	ResourceManager* mgr;
	GameResources();
};