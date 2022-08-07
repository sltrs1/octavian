#ifndef _SLOT_H_
#define _SLOT_H_

// Класс слота. Из них собираются барабаны.
// Включает логику для имитации вращения.
// 

#include "globals.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Slot {
    public:
    /**
     * @brief Construct a new Slot object
     * 
     * @param tex_name      - строка с указанием на текстуру
     * @param col           - столбец, в котором расположен слот
     * @param row           - ряд, в котором расположен слот
     * @param start_value   - начальный кадр текстуры
     * @param r_rate        - скорость вращения
     * @param s_time        - время вращения
     */
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