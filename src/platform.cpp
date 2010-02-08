/*
 *  platform.cpp
 *  Tetris
 *
 *  Created by Brandon Croft on 11/15/08.
 *  Copyright 2008 Brandon Croft. All rights reserved.
 *
 */

#include "platform.h"

Platform::Platform(Game* game) {
	this->game = game;
	this->lastAnimateType = TILE1;
	this->lastKeydown = 0;
	this->lastDelayShift = 0;

	SDL_Init(SDL_INIT_VIDEO);
	this->screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BITDEPTH, SCREEN_VIDEO_MODE);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 512);
	Mix_PlayMusic(GameResources::instance()->music, -1);
	SDL_WM_SetCaption("Tetris", NULL);
}

Platform::~Platform() {
	Mix_HaltMusic();
	Mix_CloseAudio();
	
	SDL_FreeSurface(screen);
	
	SDL_Quit();
}

void Platform::pauseMusic() {
	Mix_PauseMusic();
}

void Platform::resumeMusic() {
	Mix_ResumeMusic();
}

void Platform::playSound(int sound) {
	int result = 0;
	switch(sound) {
		case SOUND_CLICK:
			result = Mix_PlayChannel(-1, GameResources::instance()->wav_click, 0);
			break;
		case SOUND_LINE:
			result = Mix_PlayChannel(-1, GameResources::instance()->wav_line, 0);
			break;
		case SOUND_TETRIS:
			result = Mix_PlayChannel(-1, GameResources::instance()->wav_tetris, 0);
			break;
		case SOUND_PAUSE:
			result = Mix_PlayChannel(-1, GameResources::instance()->wav_pause, 0);
			break;
	}
}

void Platform::drawNumber(int x, int y, int number, int length) {
    SDL_Rect recDest;
    SDL_Rect recSource;
    int pos;
	
    recSource.y = 0;
    recSource.w = NUMBER_WIDTH;
    recSource.h = NUMBER_HEIGHT;
    recDest.y = y;
	
    pos = 0;
    do {
        recDest.x = x + NUMBER_WIDTH * (length - pos);
        recSource.x = NUMBER_WIDTH * (number % 10);
		
		if(number > 0) {
			SDL_BlitSurface(GameResources::instance()->numbers, &recSource, screen, &recDest);
		}
        number /= 10;
    } while (++pos < length);
}


void Platform::drawTile(int x, int y, int tile) {
	SDL_Rect recDest;
    SDL_Rect recSource;
	
    recDest.x = x;
    recDest.y = y;
    recSource.x = SIZE_TILE * (tile - 1);
    recSource.y = 0;
    recSource.w = SIZE_TILE;
    recSource.h = SIZE_TILE;
	
    SDL_BlitSurface(GameResources::instance()->tiles, &recSource, this->screen, &recDest);
}

void Platform::renderGame() {
	if(!this->frameTimer.isStarted()) {
		this->frameTimer.start();
	}
	if(!this->animationTimer.isStarted()) {
		this->animationTimer.start();
	}
	// Draw field
	SDL_BlitSurface(GameResources::instance()->field, NULL, screen, NULL);
	
	if(!this->game->isPaused()) {
		// Draw matrix
		for(int row = 2; row < Game::NUMBER_ROWS; row++) {
			if(this->game->isCollapsing(row)) {
				animateLine(row);
			} else {
				for(int col = 0; col < Game::NUMBER_COLUMNS; col++) {
					switch(game->field[col][row]) {
						case NO_TILE:
							// NOP
							break;
						default:
							drawTile(col * SIZE_TILE + FIELD_LEFT,
									 row * SIZE_TILE + FIELD_TOP,
									 this->game->field[col][row]);
					}
				}
			}
		}
		
		if(game->getFallingBlock()) {
			// Draw fallingBlock
			for(int col = 0; col < 4; col++) {
				for(int row = 0; row < 4; row++) {
					if(game->getFallingBlock()->y() + row > 1 && game->getFallingBlock()->tiles[col][row]) {
						drawTile(col * SIZE_TILE + FIELD_LEFT + (SIZE_TILE * game->getFallingBlock()->x()),
								 row * SIZE_TILE + FIELD_TOP + (SIZE_TILE * game->getFallingBlock()->y()),
								 game->getFallingBlock()->type());
					}
				}
			}
		}
	} else if(!this->game->isOver()) {
		// Game is paused
		SDL_Rect recDest;
		recDest.x = 103;
		recDest.y = 213;
		SDL_BlitSurface(GameResources::instance()->paused, NULL, this->screen, &recDest);
	}
	
	// Draw next block
	for(int col = 0; col < 4; col++) {
		for(int row = 0; row < 4; row++) {
			if(game->getNextBlock()->tiles[col][row]) {
				drawTile(col * SIZE_TILE + 383, row * SIZE_TILE + 390, game->getNextBlock()->type());
			}
		}
	}
	
	// Draw stats
	drawNumber(447, 53, game->getStats()->score(), 10);
	drawNumber(447, 177, game->getStats()->level(), 4);
	drawNumber(447, 114, game->getStats()->lines(), 4);
	drawNumber(447, 287, game->getStats()->highscore(), 10);
	
	if(this->game->isOver()) {
		SDL_Rect recDest;
		recDest.x = 80;
		recDest.y = 213;
		SDL_BlitSurface(GameResources::instance()->gameover, NULL, this->screen, &recDest);
	}
	
	SDL_Flip(screen);

	if(!this->frameTimer.hasElapsed(1000 / FRAMES_PER_SECOND_MAX)) {
		SDL_Delay(1000 / FRAMES_PER_SECOND_MAX - this->frameTimer.getTicks());
	}

	this->frameTimer.start(); //resets
}

void Platform::animateLine(int line) {
	for(int col = 0; col < Game::NUMBER_COLUMNS; col++) {
		drawTile(col * SIZE_TILE + FIELD_LEFT, line * SIZE_TILE + FIELD_TOP, lastAnimateType);
	}
	
	if(animationTimer.hasElapsed(LINE_ANIMATE_DELAY)) {
		if(lastAnimateType == TILE_ANIMATE_1) { lastAnimateType = TILE_ANIMATE_2; } else { lastAnimateType = TILE_ANIMATE_1; }
		animationTimer.start();	// resets
	}
}

int Platform::getInput() {
	SDL_Event event;
	
	int result = EVENT_NONE;
    /* Grab events in the queue */
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
				/* On quit game */
			case SDL_QUIT:
				result |= EVENT_QUIT;
				break;
			case SDL_KEYDOWN:
				lastKeydown = Timer::getSystemTime();
				switch(event.key.keysym.sym) {
					case SDLK_ESCAPE:
						result |= EVENT_QUIT;
						break;
					case SDLK_s:
					case SDLK_DOWN:
						result |= EVENT_MOVE_DOWN;
						break;
					case SDLK_w:
					case SDLK_UP:
						result |= EVENT_ROTATE;
						break;
					case SDLK_a:
					case SDLK_LEFT:
						result |= EVENT_MOVE_LEFT;
						break;
					case SDLK_d:
					case SDLK_RIGHT:
						result |= EVENT_MOVE_RIGHT;
						break;
					case SDLK_SPACE:
						result |= EVENT_DROP;
						break;
					case SDLK_p:
						result |= EVENT_PAUSE;
						break;
					case SDLK_r:
						result |= EVENT_RESTART;
						break;
				}
				break;
        }
    }
	
	if(Timer::getSystemTime() - lastKeydown >= KEY_DOWN_DELAY && Timer::getSystemTime() - lastDelayShift >= DELAY_SHIFT_DELAY) {
		lastDelayShift = Timer::getSystemTime();
		if(SDL_GetKeyState(NULL)[SDLK_LEFT] || SDL_GetKeyState(NULL)[SDLK_a]) {
			result |= EVENT_MOVE_LEFT;
		} else if(SDL_GetKeyState(NULL)[SDLK_RIGHT] || SDL_GetKeyState(NULL)[SDLK_d]) {
			result |= EVENT_MOVE_RIGHT;
		} else if(SDL_GetKeyState(NULL)[SDLK_DOWN] || SDL_GetKeyState(NULL)[SDLK_s]) {
			result |= EVENT_MOVE_DOWN;
		}
	}
	
	return result;
}
