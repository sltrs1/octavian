#include "include/globals.h"
#include "include/button.h"
#include "include/slot.h"
#include "include/fpstex.h"

int init = 	SDL_Init(SDL_INIT_EVERYTHING);
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
	double base_ref_rate = 300.0;
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

				case SDL_MOUSEBUTTONDOWN:
					
					spinStatus = false;

					for (auto & sl : slots) {
						if ( sl.getSpinStatus() ) {
							spinStatus = true;
							break;
						}
					}

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

		btn.update();
		btn.draw();
		
		for (auto & sl : slots) {
			if (sl.getSpinStatus()) {
				sl.update();
			}
			sl.draw();
		}

		fps.update();
		fps.draw();

		SDL_RenderPresent(ren);

		SDL_Delay(10);


	} // end main loop

	SDL_Quit();
	return 0;
}