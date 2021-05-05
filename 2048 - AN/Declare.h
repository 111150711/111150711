
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT	= 480;

const int BOARD_SIZE = 4;

const int BOARD_WIDTH = 400;
const int BOARD_X = 50;
const int BOARD_Y = 10;

	int size = 4;
	bool getStart = 0;
	unsigned int score = 0;
	unsigned int backScore = score;
	int showSize = 0;

	int** tab;
	int** backtab;
	int fileSize = 0;


	int t1, t2, rc;
	int quit = 0, frames = 0 , Move = 0, Back_Move;
	double delta;
	double worldTime = 0, fpsTimer = 0, fps = 0, distance = 0, etiSpeed = 0;

	SDL_Event event;
	SDL_Surface *screen = NULL;
	SDL_Surface *charset = NULL;
	SDL_Texture *scrtex = NULL;
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	//Sound Effect
	Mix_Chunk* chunk = NULL;
	//Background Music
	Mix_Music* music = NULL;



	SDL_Rect srcRect;
    SDL_Rect desRect;

    TTF_Font* font = NULL;
