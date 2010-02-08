/*
 *  resourceManagerFactory.h
 *  Tetris
 *
 *  Created by Brandon Croft on 12/2/08.
 *  Copyright 2008 Brandon Croft. All rights reserved.
 *
 */

#ifndef __RESOURCEMANAGERFACTORY_H_
#define __RESOURCEMANAGERFACTORY_H_

#ifdef WIN32
#include "win32ResourceManager.h"
#endif

class ResourceManagerFactory {
public:
	static ResourceManager* instance() {
		if(ResourceManagerFactory::singleton == NULL) {
#ifdef WIN32
			ResourceManagerFactory::singleton = new Win32ResourceManager("resource");
#endif
		}
		return ResourceManagerFactory::singleton;
	}
private:
	static ResourceManager* singleton = NULL;
};

#endif