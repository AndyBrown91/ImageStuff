#pragma once

class FastPosterise : public PerPixelOperation
{
public: 
  FastPosterise(SDL_Surface* surface, int colours) : colours(colours)
  {
    margin = 256 / colours;
    perform(surface);
  }
  
  inline void getValue(uint8_t& r, uint8_t& g, uint8_t& b)
  {
    bool foundR = false, foundG = false, foundB = false;
    
    //Find closest palette
    for (int m = 0; m < colours; m++)
    {
      double dvalue = m * margin;
      double nvalue = m < colours - 1 ? (m + 1) * margin : 256;
      
      if (r >= dvalue && r < nvalue)
      {
        if (foundR != true)
        {
          r = Uint8(m * margin + (margin / 2));
          foundR = true;
        }
      }
      
      if (g >= dvalue && g < nvalue)
      {
        if (foundG != true)
        {
          g = Uint8(m * margin + (margin / 2));
          foundG = true;
        }
      }
      
      
      if (b >= dvalue && b < nvalue)
      {
        if (foundB != true)
        {
          b = Uint8(m * margin + (margin / 2));
          foundB = true;
        }
      }
    }
    
    if (r < 0) r = 0; else if (r > 255) r = 255;
    if (g < 0) g = 0; else if (g > 255) g = 255;
    if (b < 0) b = 0; else if (b > 255) b = 255;
    
    if (foundR != true || foundG != true || foundB != true)
      std::cout << "Failed to calculate\n";//at X: " << x << " Y: " << y << endl;
  }
  
private:
  int colours;
  int margin;
};
