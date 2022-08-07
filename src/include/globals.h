#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

const int BUTTON_W = 64;
const int BUTTON_H = 64;
const int BUTTON_TEX_SIZE = 64;
const int NUM_BUTTON_STATES = 2;

const int SLOT_W = 128;
const int SLOT_H = 128;
const int NUM_SLOT_STATES = 7;
const int START_SLOT_X = 100;
const int START_SLOT_Y = 50;

const int NUM_ROWS = 3;
const int NUM_COLS = 5;

extern SDL_Window * win;
extern SDL_Renderer * ren;


#endif