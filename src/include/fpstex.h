#ifndef _FPSTEX_H_
#define _FPSTEX_H_

// Кдасс, совмещающий счетчик ФПС с текстурой,
// на которой он рисуется.

#include "globals.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class FPSTex {
    public:
    /**
     * @brief Construct a new FPSTex object
     * 
     * @param z_font - строка с указанием на шрифт
     */
    FPSTex(std::string z_font);
    ~FPSTex();

    void start();
    void update();
    void draw();

    private:
    SDL_Rect dst_rect;
    TTF_Font * font;
    SDL_Color textColor;
    SDL_Surface * textSurface;
    SDL_Texture * FPSTexture;

    double frameCount;
    double startTime;

};


#endif