/*
 *  gameResources.cpp
 *  Tetris
 *
 *  Created by Brandon Croft on 12/6/08.
 *  Copyright 2008 Brandon Croft. All rights reserved.
 *
 */

#include "gameResources.h"

GameResources* GameResources::singleton = NULL;

GameResources* GameResources::instance() {
	if(GameResources::singleton == NULL) {
		GameResources::singleton = new GameResources();
	}
	return GameResources::singleton;
}

GameResources::GameResources() {
#ifdef _WIN32
	this->mgr = (ResourceManager*)new ZipResourceManager("resource");
	this->music = this->mgr->getMusic("korobushka.mp3");
#elif defined(__APPLE_CC__)
	this->mgr = (ResourceManager*)new OSXResourceManager("");
	this->music = Mix_LoadMUS_RW(mgr->getFile("korobushka.mp3"));
#endif
	
	this->wav_click = Mix_LoadWAV_RW(mgr->getFile("click.wav"), 0);
	this->wav_line = Mix_LoadWAV_RW(mgr->getFile("line.wav"), 0);
	this->wav_tetris = Mix_LoadWAV_RW(mgr->getFile("tetris.wav"), 0);
	this->wav_pause = Mix_LoadWAV_RW(mgr->getFile("pause.wav"), 0);
	
	this->tiles = IMG_Load_RW(mgr->getFile("tiles.png"), 0);
	this->field = IMG_Load_RW(mgr->getFile("field.bmp"), 0);
	this->numbers = IMG_Load_RW(mgr->getFile("numbers.png"), 0);
	this->paused = IMG_Load_RW(mgr->getFile("paused.png"), 0);
	this->gameover = IMG_Load_RW(mgr->getFile("game_over.png"), 0);
}

GameResources::~GameResources() {
	SDL_FreeSurface(tiles);
	SDL_FreeSurface(field);
	SDL_FreeSurface(numbers);
	SDL_FreeSurface(paused);
	SDL_FreeSurface(gameover);
	
	Mix_FreeMusic(music);
	Mix_FreeChunk(wav_click);
	Mix_FreeChunk(wav_line);
	Mix_FreeChunk(wav_tetris);
	Mix_FreeChunk(wav_pause);
	
	delete mgr;
	delete singleton;
}