void copyTex(SDL_Texture* texture, const SDL_Rect* dsRect)
{
    SDL_RenderCopy(m_renderer, texture, NULL, dsRect);
}


void Number(SDL_Renderer* renderer,const int &so, const int &y, const int &x)
{
    SDL_Surface* image = NULL;
    SDL_Texture* last = nullptr;
    int h_w = dienTich - 2;  // -2 để ko che viền ô
    SDL_Rect rect;
    rect.x =
    rect.y =
    rect.w =
    rect.h =
     = setRect(leTrai + dienTich * x + 1, leTren + dienTich * y + 1, h_w, h_w) ;
    switch(so)
    {
    case 2:
        {
            image = IMG_Load("picture//2.jpg");
            break;
        }
    case 4:
        {
            image = IMG_Load("picture//4.jpg");
            break;
        }
    case 8:
        {
            image = IMG_Load("picture//8.jpg");
            break;
        }
    case 16:
        {
            image = IMG_Load("picture//16.jpg");
            break;
        }
    case 32:
        {
            image = IMG_Load("picture//32.jpg");
            break;
        }
    case 64:
        {
            image = IMG_Load("picture//64.jpg");
            break;
        }
    case 128:
        {
            image = IMG_Load("picture//128.jpg");
            break;
        }
    case 256:
        {
            image = IMG_Load("picture//256.jpg");
            break;
        }
    case 512:
        {
            image = IMG_Load("picture//512.jpg");
            break;
        }
    case 1024:
        {
            image = IMG_Load("picture//1024.jpg");
            break;
        }
    case 2048:
        {
            image = IMG_Load("picture//2048.jpg");
            break;
        }
    }

    last = SDL_CreateTextureFromSurface(renderer,image);

    // đưa ảnh từ texture vào màn hình, ảnh co dãn theo kich thuoc
    copyTex(last, &rect);
    //hủy texture
    SDL_DestroyTexture(last);
    SDL_FreeSurface(image);
}
