#ifndef _SLOT_H_
#define _SLOT_H_

#include "globals.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Slot {
    public:
        Slot(std::string tex_name, size_t col, size_t row, size_t start_value, double r_rate, double s_time);
        ~Slot();
        void update();
        void draw();
        void startSpin();
        void stopSpin();
        bool getSpinStatus();

    private:
    SDL_Texture * tex;
    SDL_Rect src_rect[NUM_SLOT_STATES];
    SDL_Rect dst_rect;
    size_t tex_cnt;
    double refreshRate;
    double spinningTime;
    double lastRefreshTime;
    double startSpinningTime;
    bool isSpinning;

};


#endif