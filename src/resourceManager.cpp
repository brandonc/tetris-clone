/*
 *  resourceManager.cpp
 *  Tetris
 *
 *  Created by Brandon Croft on 12/2/08.
 *  Copyright 2008 Brandon Croft. All rights reserved.
 *
 */

#include "resourceManager.h"

ResourceManager::ResourceManager(std::string path)
	: initialized(false), resourcePath(path)
{
}

ResourceManager::~ResourceManager() {
	std::map<std::string, SDL_RWops*>::const_iterator iter;
	for(iter = files.begin(); iter != files.end(); ++iter)
	{
		SDL_RWclose(iter->second);
	}
}

SDL_RWops* ResourceManager::getFile(std::string name) {
	if(!initialized) { populate(); initialized = true; }
	return files[name];
}

SDL_RWops* ResourceManager::createFileOps(std::string path) {
	return SDL_RWFromFile(path.c_str(), "rb");
}