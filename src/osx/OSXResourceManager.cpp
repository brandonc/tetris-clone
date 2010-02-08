/*
 *  OSXResourceManager.cpp
 *  Tetris
 *
 *  Created by Brandon Croft on 12/2/08.
 *  Copyright 2008 Brandon Croft. All rights reserved.
 *
 */

#include "OSXResourceManager.h"
#include "dirent.h"

void OSXResourceManager::populate() {
	std::string bundlepath = getBundlePath() + "/" + resourcePath;
	if(bundlepath.substr(bundlepath.size() - 1, 1) != "/")
		bundlepath += "/";
	
	DIR* dir = opendir(bundlepath.c_str());
	struct dirent* dp;
	while((dp = readdir(dir)) != NULL) {
		std::string name = std::string(dp->d_name);
		if(name == "." || name == "..") {
			continue;
		}
		files[name] = createFileOps(bundlepath + name);
	}
}

Mix_Music* OSXResourceManager::getMusic(std::string name) {
	return Mix_LoadMUS((getBundlePath() + "/" + name).c_str());
}

std::string OSXResourceManager::getBundlePath() {
	char path[1024];
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    assert(mainBundle);
	
    CFURLRef mainBundleURL = CFBundleCopyBundleURL(mainBundle);
    assert(mainBundleURL);
	
    CFStringRef cfStringRef = CFURLCopyFileSystemPath(mainBundleURL, kCFURLPOSIXPathStyle);
    assert(cfStringRef);
	
    CFStringGetCString(cfStringRef, path, 1024, kCFStringEncodingASCII);
	
    CFRelease(mainBundleURL);
    CFRelease(cfStringRef);
	
    return std::string(path) + "/Contents/Resources";
}