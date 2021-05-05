#include "Declare.h"

void copyTex(SDL_Renderer *renderer,SDL_Texture* texture, const SDL_Rect* dsRect)
{
    SDL_RenderCopy(renderer, texture, NULL, dsRect);
}

void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32 *)p = color;
};

// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for(int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
    };
};

// draw a rectangle of size l by k
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k,Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for(i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
	};

//Draw point of block in the middle of it

void DrawPoint(SDL_Renderer *renderer, int X, int Y, int width, int number, int size) {
    std::string Text = std::to_string(number);
    int length = Text.size();
	SDL_Rect srcRect;
    SDL_Rect desRect;
    srcRect.x = 0;
    srcRect.y = 0;
	desRect.x = (X + width / 2) - length*4 - 2;
    desRect.y =  Y + width / 2 - 8;
    SDL_Color Black_txt = {0, 0, 0};
    int font_size;
    switch(size){
        case 3 :
            {
                font_size = 60;
            }
        case 4 :
            {
                font_size = 55;
            }
        case 5 :
            {
                font_size = 50;
            }
        case 6 :
            {
                font_size = 45;
            }
        case 7 :
            {
                font_size = 35;
            }
        case 8 :
            {
                font_size = 25;
            }

    }
    showText(renderer, Text,font_size,Black_txt,srcRect, desRect);

}

//draw board with all block and points

void DrawBoard(SDL_Renderer *renderer,SDL_Surface *screen, int **tab, int size, Uint32 outlineColor, Uint32 fillColor) {

	int width = (BOARD_WIDTH / size) - 2;
	int X, Y;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			X = BOARD_X + (BOARD_WIDTH / size)*i;
			Y = BOARD_Y + (BOARD_WIDTH / size)*j;

			int ColorBoard;
			switch(tab[i][j]){
                case 2048:
                {

                    ColorBoard = SDL_MapRGB(screen->format,237,196,56);
                    break;
                }
                case 1024:
                {

                    ColorBoard = SDL_MapRGB(screen->format,238,197,63);
                    break;
                }
                case 512:
                {
                    ColorBoard = SDL_MapRGB(screen->format,236,200,80);
                    break;
                }
                case 256:
                {
                    ColorBoard = SDL_MapRGB(screen->format,237,204,98);
                    break;
                }
                case 128:
                {
                    ColorBoard = SDL_MapRGB(screen->format,237,206,113);
                    break;
                }
                case 64:
                {
                    ColorBoard = SDL_MapRGB(screen->format,246,93,59);
                    break;
                }
                case 32:
                {
                    ColorBoard = SDL_MapRGB(screen->format,238,124,95);
                    break;
                }
                case 16:
                {
                    ColorBoard = SDL_MapRGB(screen->format,245,149,99);
                    break;
                }
                case 8:
                {
                    ColorBoard = SDL_MapRGB(screen->format,242,177,121);
                    break;
                }
                case 4:
                {
                    ColorBoard = SDL_MapRGB(screen->format,236,224,200);
                    break;
                }
                case 2:
                {


                    ColorBoard = SDL_MapRGB(screen->format,238,228,218);
                    break;
                }
                default:
                {
                    ColorBoard = SDL_MapRGB(screen->format,214,206,196);
                    break;
                }
			}


			DrawRectangle(screen, Y, X, width, width, outlineColor, ColorBoard);

            if(tab[i][j] != 0)
                DrawPoint(renderer, Y, X, width, tab[i][j],size);

		}

	}


}


