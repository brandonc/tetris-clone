/*
 *  resourceManager.h
 *  Tetris
 *
 *  Created by Brandon Croft on 12/2/08.
 *  Copyright 2008 Brandon Croft. All rights reserved.
 *
 */

#ifndef __RESOURCEMANAGER_H_
#define __RESOURCEMANAGER_H_

#include <string>
#include <map>
#include "SDL.h"
#include "SDL_mixer/SDL_mixer.h"

class ResourceManager {
public:
	ResourceManager(std::string path);
	virtual ~ResourceManager();
	
	SDL_RWops* getFile(std::string name);
	virtual Mix_Music* getMusic(std::string name) = 0;
protected:
	virtual void populate() = 0;
	virtual SDL_RWops* createFileOps(std::string path);
	std::map<std::string, SDL_RWops*> files;
	std::string resourcePath;

private:
	bool initialized;
};

#endif