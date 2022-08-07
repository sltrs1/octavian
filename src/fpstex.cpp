#include "include/fpstex.h"

FPSTex::FPSTex(std::string z_font) {
    font = TTF_OpenFont( z_font.c_str(), 28 );

    if(!font) {
        std::cout << SDL_GetError() << std::endl;
    }

    textColor = { 0, 0, 0, 255 };

    dst_rect.x = SCREEN_WIDTH / 2;
    dst_rect.y = SCREEN_HEIGHT - 50;
    dst_rect.w = 200;
    dst_rect.h = 50;

    textSurface = nullptr;

    FPSTexture = nullptr;

    frameCount = 0;

    startTime = 0.0;

}

FPSTex::~FPSTex() {

    TTF_CloseFont(font);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(FPSTexture);

}


void FPSTex::start() {
    frameCount = 0;
    startTime = SDL_GetTicks();;
}

void FPSTex::update() {

    	double FPS = frameCount / ((SDL_GetTicks() - startTime)/1000.0);
        std::string tmp = std::to_string(FPS);
        std::string rounded = tmp.substr(0, tmp.find(".")+2);
        std::string FPSstring = "FPS = " + rounded;

		textSurface = TTF_RenderText_Solid( font, FPSstring.c_str(), textColor );
        if (!textSurface) {
            std::cout << SDL_GetError() << std::endl;
        }

		FPSTexture = SDL_CreateTextureFromSurface( ren, textSurface );
        if (!FPSTexture) {
            std::cout << SDL_GetError() << std::endl;
        }

        ++frameCount;
}

void FPSTex::draw() {

    int rval = SDL_RenderCopy(ren, FPSTexture, NULL, &dst_rect);
    if (rval) {
        std::cout << SDL_GetError() << std::endl;
    }

}