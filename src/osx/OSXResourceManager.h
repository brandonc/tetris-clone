/*
 *  OSXResourceManager.h
 *  Tetris
 *
 *  Created by Brandon Croft on 12/2/08.
 *  Copyright 2008 Brandon Croft. All rights reserved.
 *
 */

#ifndef __OSXRESOURCEMANAGER_H_
#define __OSXRESOURCEMANAGER_H_

#include "../resourceManager.h"
#include "SDL_mixer/SDL_mixer.h"

#ifdef __APPLE_CC__
#include <CoreFoundation/CoreFoundation.h>
#endif

class OSXResourceManager : public ResourceManager {
public:
	OSXResourceManager(std::string path) : ResourceManager(path) {}
	Mix_Music* getMusic(std::string name);
protected:
	void populate();
private:
	std::string getBundlePath();
};

#endif