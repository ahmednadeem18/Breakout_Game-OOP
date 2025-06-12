#pragma once
#include "Level.h"
#include "MyStr.h"

class SaveLoadManager {
public:
    static void saveLevel(const Level& level, const char* filename);
    static void loadLevel(Level& level, const char* filename);
};