#include "SDL_Wrapper.h"

int main(int argc, char ** argv) {
	InitSystem(1800, 800, 1);

	Font bigFont = CreateFont("OpenSans-Regular.ttf", 48, White);
	Font font2 = CreateFont("OpenSans-Regular.ttf", 24, White);
	Font font3 = CreateFont("OpenSans-Regular.ttf", 12, White);


    int bird_y  = 100;
	int bird_vy  = 0;

	int pipe_x = 1000;
	int pipe_h = 350;
	int life   = 100;
	int score   = 0;
	while (!IsKeyDown(Escape)) {
        if (life > 0) {
            bird_y = bird_y + bird_vy;
            bird_vy++;

            if (WasKeyPressed(SpaceKey)) {
                // Start moving UP...
                bird_vy = -10;
            }
            // MOVE THE PIPE LEFT
            pipe_x = pipe_x - 5;
            if (pipe_x <= -100) {
                pipe_x = 1800;
                pipe_h = 100 + rand() % 500;
                score = score + 100;
            }
            bool collision = false;

             // check upper
            if (IntersectRects(80, bird_y, 80, 80,pipe_x, 0, 100, pipe_h)) {
                 //For now:
               collision = true;
            }

            // check lower
            if (IntersectRects(80, bird_y, 80, 80, pipe_x, 150 + pipe_h, 100, 650 - pipe_h)) {
                 //For now:
               collision = true;
            }
             // check too high/too low:
             if(bird_y <= 0) {
                collision = true;
             }

             if(bird_y >= 800){
                collision = true;
             }
             if (collision) {
                life--;
             }
	     }

        ClearScreen(RGB(94, 228, 70));                          // sky
        FillRect(0,550, 1800 , 250 , RGB (52, 198, 235));
              // Ocean
        FillRect(50, bird_y, 80, 50, RGB (225 , 165 , 38));    // Box bird
        FillRect(120,bird_y + 5, 15, 15, Black);// eye



        FillRect(pipe_x, 0, 100, pipe_h, RGB(50, 168, 168));        // Pipe, upper
        FillRect(pipe_x, 0, 20,  pipe_h, RGB(20, 63, 219));  // upper pipe shadow


        FillRect(pipe_x, 150 + pipe_h, 100, 650 - pipe_h, RGB(50, 168, 168));         // pipe,lower
        FillRect(pipe_x, 150 + pipe_h, 20, 650 - pipe_h, RGB(20, 63, 219)); // lower pipe shadow


        FillRect(800, 50, life * 5, 30, LightGreen);
        WriteInt(score, 50,50, bigFont);




		Refresh();
		Sleep(10);
	}
	CloseSystem();
	return 0;}


