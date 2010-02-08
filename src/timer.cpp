/*
 *  timer.cpp
 *  Tetris
 *
 *  Created by Brandon Croft on 11/8/08.
 *  Copyright 2008 Brandon Croft. All rights reserved.
 *
 */

#include "timer.h"

Timer::Timer()
{
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

void Timer::start()
{
	started = true;
	paused = false;
	startTicks = SDL_GetTicks();
}

void Timer::stop()
{
	started = false;
	paused = false;
}

int Timer::getSystemTime() {
	return SDL_GetTicks();
}

int Timer::getTicks()
{
	if(started) {
		if(paused) {
			return pausedTicks;
		} else {
			int result = SDL_GetTicks() - startTicks;
			return result;
		}
	}
	
	return 0;
}

void Timer::pause()
{
	if(started && !paused) {
		paused = true;
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void Timer::unpause()
{
	if(paused) {
		paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}