#pragma once

enum class ThresholdType { ThresholdRed, ThresholdGreen, ThresholdBlue };

template <ThresholdType type>
class FastThreshold : public PerPixelOperation
{
public:
  FastThreshold(SDL_Surface* surface, int max) : PerPixelOperation(), max(max)
  {
    perform(surface);
  }
  
  inline void getValue(uint8_t& r, uint8_t& g, uint8_t& b);
  
private:
  int max;
};

template<>
inline void FastThreshold<ThresholdType::ThresholdRed>::getValue(uint8_t& r, uint8_t& g,
                                                                uint8_t& b)
{
  if (int(r) < max)
    r = 0;
  else if (int(r) >= max)
    r = 255;
  
  g = r;
  b = r;
}

template<>
inline void FastThreshold<ThresholdType::ThresholdGreen>::getValue(uint8_t& r, uint8_t& g,
                                                                 uint8_t& b)
{
  if (int(g) < max)
    g = 0;
  else if (int(g) >= max)
    g = 255;
  
  r = g;
  b = g;
}

template<>
inline void FastThreshold<ThresholdType::ThresholdBlue>::getValue(uint8_t& r, uint8_t& g,
                                                                 uint8_t& b)
{
  if (int(b) < max)
    b = 0;
  else if (int(b) >= max)
    b = 255;
  
  r = b;
  g = b;
}
