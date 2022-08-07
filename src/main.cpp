/*
Тестовое задание для Октавиан.
Модель игрового автомата с пятью барабанами.
Запуск по мигающей кнопке в углу.

Могут быть некоторые проблемы с подключением заголовочных файлов в IDE.
*/

#include "include/globals.h"
#include "include/button.h"
#include "include/slot.h"
#include "include/fpstex.h"

// Рендерер и окно проще объявить глобальными, чтобы не передавать их туда-сюда.
int init = SDL_Init(SDL_INIT_EVERYTHING);
SDL_Window * win = SDL_CreateWindow("Slot_Machine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
SDL_Renderer * ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

int main( int argc, char* args[] )
{

	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	bool running = true;
	bool spinStatus = false;

	std::string tex_names[NUM_COLS];
	for (size_t i = 0; i < 5; i++) {
		tex_names[i] = "textures/texture" + std::to_string(i+1) + ".png";
	}

	Button btn;
	std::vector<Slot> slots;
	// Скорость и время вращения задается здесь.
	// Каждый следующий барабан вращается дольше и медленней.
	double base_ref_rate = 150.0;
	double ref_rate_step = 150.0;
	double base_spin_time = 4000.0;
	double spin_time_step = 500.0;

	for (size_t i = 0; i < NUM_ROWS; ++i) {

		for (size_t j = 0; j < NUM_COLS; ++j) {
			slots.emplace_back(Slot{tex_names[j], j, i, i, base_ref_rate+ref_rate_step*j, base_spin_time+spin_time_step*j});
		}
	}

	FPSTex fps(std::string("textures/courier_new.ttf"));

	fps.start();

	// main loop
	while (running) {

		SDL_Event e;

		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderClear(ren);

		// Event loop
		while (SDL_PollEvent(&e)) {

			switch (e.type)
			{
				case SDL_QUIT:
					running = false;
					break;

				// Обработку нажатия на кнопку оказалось удобнее сделать вне кнопки,
				// в цикле обработки событий.
				case SDL_MOUSEBUTTONDOWN:
					
					spinStatus = false;

					// Проверка слотов на вращение
					for (auto & sl : slots) {
						if ( sl.getSpinStatus() ) {
							spinStatus = true;
							break;
						}
					}
					
					// Если ни один слот нее вращается, 
					// то запустить все по очереди по нажатию на кнопку.
					if (!spinStatus) {
						for (auto & sl : slots) {
							sl.startSpin();
						}
					}

					break;
			
				default:
					break;
			}

		} // end event loop

		// обновление кнопки
		btn.update();
		btn.draw();
		
		// Если слот вращается, то обновить и перерисовать.
		// Если не вращается, то просто перерисовать.
		for (auto & sl : slots) {
			if (sl.getSpinStatus()) {
				sl.update();
			}
			sl.draw();
		}

		// Обновление текстуры со счетчиком ФПС
		fps.update();
		fps.draw();

		SDL_RenderPresent(ren);

		// Задержка, чтобы цменьшить ФПС и жрать поменьше процессора
		SDL_Delay(10);


	} // end main loop

	SDL_Quit();
	return 0;
}