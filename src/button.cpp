#include "include/button.h"

Button::Button() {

    tex = IMG_LoadTexture(ren, "textures/button.png");
    
    if(!tex) {
        std::cout << SDL_GetError() << std::endl;
    }

    src_rect[0].x = 0;
	src_rect[0].y = 0;
	src_rect[0].h = BUTTON_H;
	src_rect[0].w = BUTTON_W;
	
	src_rect[1].x = 0;
	src_rect[1].y = BUTTON_TEX_SIZE;
	src_rect[1].h = BUTTON_H;
	src_rect[1].w = BUTTON_W;

	dst_rect.x = SCREEN_WIDTH - BUTTON_TEX_SIZE;
	dst_rect.y = 0;
	dst_rect.h = BUTTON_H;
	dst_rect.w = BUTTON_W;

    tex_cnt = 0;

    refreshRate = 500.0;
    lastRefreshTime = SDL_GetTicks();
}

Button::~Button() {
    SDL_DestroyTexture(tex);
}

void Button::update(){

    if ( SDL_GetTicks() - lastRefreshTime > refreshRate ) {
        tex_cnt = (tex_cnt + 1)%NUM_BUTTON_STATES;
        lastRefreshTime = SDL_GetTicks();
    }
}

void Button::draw() {

    int rval = SDL_RenderCopy(ren, tex, &src_rect[tex_cnt], &dst_rect);
    if (rval) {
        std::cout << SDL_GetError() << std::endl;
    }
}