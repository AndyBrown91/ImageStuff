#pragma once

class PerPixelOperation
{
public:
  PerPixelOperation()
  {
  }
  
  void perform(SDL_Surface* surface)
  {
    for (int y = 0; y < surface->h; y++)
    {
      for (int x = 0; x < surface->w; x++)
      {
        Uint32 col = GetPixel(surface, x, y);
        Uint8 r, g, b, a;
        
        SDL_GetRGBA(col, surface->format, &r, &g, &b, &a);
        getValue(r, g, b);
        
        Uint32 newCol = SDL_MapRGBA(surface->format, Uint8(r), Uint8(g), Uint8(b), a);
        SetPixel(surface, x, y, newCol);
      }
    }
  }
  
  inline virtual void getValue(uint8_t& r, uint8_t& g, uint8_t& b) = 0;
};
