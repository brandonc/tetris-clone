/*
 *  platform.h
 *  Tetris
 *
 *  Created by Brandon Croft on 11/15/08.
 *  Copyright 2008 Brandon Croft. All rights reserved.
 *
 */

#ifndef __PLATFORM_H_
#define __PLATFORM_H_

#include "game.h"
#include "timer.h"
#include "SDL.h"
#include "SDL_mixer/SDL_mixer.h"
#include "gameResources.h"

class Game;

enum EVENTS {
	EVENT_NONE = 0,
	EVENT_QUIT = 1,
	EVENT_MOVE_DOWN = 2,
	EVENT_ROTATE = 4,
	EVENT_MOVE_LEFT = 8,
	EVENT_MOVE_RIGHT = 16,
	EVENT_DROP = 32,
	EVENT_PAUSE = 64,
	EVENT_RESTART = 128
};

enum SOUNDS {
	SOUND_CLICK = 1,
	SOUND_LINE,
	SOUND_TETRIS,
	SOUND_PAUSE
};

class Platform {
public:
	static const int SIZE_TILE = 20;
	static const int FIELD_LEFT = 86;
	static const int FIELD_TOP = 0;
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;
	static const int SCREEN_BITDEPTH = 32;
	static const int SCREEN_VIDEO_MODE = (SDL_SWSURFACE | SDL_DOUBLEBUF);
	static const int LINE_ANIMATE_DELAY = 100;
	static const int NUMBER_WIDTH = 13;
	static const int NUMBER_HEIGHT = 20;
	static const int KEY_DOWN_DELAY = 330;
	static const int DELAY_SHIFT_DELAY = 60;
	static const int TILE_ANIMATE_1 = 7;
	static const int TILE_ANIMATE_2 = 0;
	static const int FRAMES_PER_SECOND_MAX = 80;
	
	void renderGame();
	int getInput();
	void playSound(int sound);
	void pauseMusic();
	void resumeMusic();
	Platform(Game* game);
	~Platform();
private:
	SDL_Surface* screen;
	
	void drawNumber(int x, int y, int number, int length);
	void drawTile(int x, int y, int tile);
	void animateLine(int line);
	Game* game;
	Timer animationTimer;
	int lastAnimateType;
	Timer frameTimer;
	int lastKeydown;
	int lastDelayShift;
};

#endif