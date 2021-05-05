bool Init(){
    bool error = 0;
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		error = 1;
	}
	if (TTF_Init() < 0)
	{
		SDL_Log("%s", TTF_GetError());
		error = 1;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		printf("%s", Mix_GetError());
		error = 1;
	}
	return error;
}
bool WinAndRen(int rc){
    if(rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
    };
    return 0;
}
