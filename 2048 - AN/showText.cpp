void showText(SDL_Renderer* renderer,std::string msg,const int size,SDL_Color color,SDL_Rect srcRect,SDL_Rect desRect){
    TTF_Font *font = TTF_OpenFont("Font/MYRIADPRO-BOLDSEMICN_0.OTF",size);

    SDL_Surface *textSurface = TTF_RenderText_Solid(font,msg.c_str(),color);
    SDL_Texture *Text = SDL_CreateTextureFromSurface(renderer,textSurface);

    TTF_SizeText(font,msg.c_str(), &srcRect.w,& srcRect.h);
    SDL_FreeSurface(textSurface);

    desRect.w = srcRect.w;
    desRect.h = srcRect.h;
    SDL_RenderCopy(renderer, Text, &srcRect, &desRect);
    SDL_DestroyTexture(Text);
    TTF_CloseFont(font);

    Text = nullptr;
    textSurface = nullptr;
    font = nullptr;

}
