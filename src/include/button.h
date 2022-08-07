#ifndef _BUTTON_H_
#define _BUTTON_H_

// Класс кноки, по которой запускаются барабаны.
// На самом деле, просто обертка над текстурой,
// обеспечивающая мигание.
// Обработка нажатия происходит в цикле обработки 
// событий в main.

#include "globals.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Button {
    public:
    Button();
    ~Button();

    void draw();
    void update();

    private:
    SDL_Texture * tex;
    SDL_Rect src_rect[2];
    SDL_Rect dst_rect;
    size_t tex_cnt;
    double refreshRate;
    double lastRefreshTime;
};


#endif