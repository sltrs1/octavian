#include "include/slot.h"

Slot::Slot(std::string tex_name, size_t col, size_t row, size_t start_value, double r_rate, double s_time) {

    tex = IMG_LoadTexture(ren, tex_name.c_str());

    if (!tex) {
        std::cout << SDL_GetError() << std::endl;
    }

    for (size_t i = 0; i < NUM_SLOT_STATES; i++) {

        src_rect[i].x = 0;
        src_rect[i].y = SLOT_H * i;
        src_rect[i].h = SLOT_H;
        src_rect[i].w = SLOT_W;
    }

    dst_rect.x = START_SLOT_X + SLOT_W * col;
    dst_rect.y = START_SLOT_Y + SLOT_H * row;
    dst_rect.h = SLOT_H;
    dst_rect.w = SLOT_W;

    tex_cnt = start_value;

    refreshRate = r_rate;

    spinningTime = s_time;

    startSpinningTime = 0.0;

    lastRefreshTime = 0.0;

    isSpinning = false;

}

Slot::~Slot() {

}

void Slot::update() {

    double currentTime = SDL_GetTicks();

    if (isSpinning) {

        if ( currentTime - lastRefreshTime > refreshRate ) {
            tex_cnt = (tex_cnt + 1)%NUM_SLOT_STATES;
            lastRefreshTime = currentTime;
        }

        if (currentTime - startSpinningTime > spinningTime) {
            stopSpin();
        }
    }
}

void Slot::draw() {

    int rval = SDL_RenderCopy(ren, tex, &src_rect[tex_cnt], &dst_rect);

    if (rval) {
        std::cout << SDL_GetError() << std::endl;
    }

}

void Slot::startSpin() {
    isSpinning = true;
    startSpinningTime = SDL_GetTicks();
    lastRefreshTime = startSpinningTime;
}

void Slot::stopSpin() {
    isSpinning = false;
}

bool Slot::getSpinStatus() {
    return isSpinning;
}