#pragma once

enum class GrayscaleType { GrayAverage, GrayLuminance, GrayLightness, GrayRed, GrayGreen, GrayBlue };

template <GrayscaleType type>
class FastGrayscale : public PerPixelOperation
{
public:
  FastGrayscale(SDL_Surface* surface) : PerPixelOperation()
  {
    perform(surface);
  }
  
  inline void getValue(uint8_t& r, uint8_t& g, uint8_t& b);
};

template<>
inline void FastGrayscale<GrayscaleType::GrayAverage>::getValue(uint8_t& r, uint8_t& g,
                                                                uint8_t& b)
{
  r = (int(r) + int(g) + int(b)) / 3;
  g = r;
  b = r;
}

template<>
inline void FastGrayscale<GrayscaleType::GrayLuminance>::getValue(uint8_t& r, uint8_t& g,
                                                                  uint8_t& b)
{
  r = (int(r)*0.72) + (int(g)*0.21) + (int(b)*0.07);
  g = r;
  b = r;
}

template<>
inline void FastGrayscale<GrayscaleType::GrayLightness>::getValue(uint8_t& r, uint8_t& g,
                                                                  uint8_t& b)
{
  r = (std::min(int(r), std::min(int(g), int(b))) + std::max(int(r), std::max(int(g), int(b)))) / 2;
  g = r;
  b = r;
}

template<>
inline void FastGrayscale<GrayscaleType::GrayRed>::getValue(uint8_t& r, uint8_t& g,
                                                            uint8_t& b)
{
  g = r;
  b = r;
}

template<>
inline void FastGrayscale<GrayscaleType::GrayGreen>::getValue(uint8_t& r, uint8_t& g,
                                                            uint8_t& b)
{
  r = g;
  b = g;
}

template<>
inline void FastGrayscale<GrayscaleType::GrayBlue>::getValue(uint8_t& r, uint8_t& g,
                                                            uint8_t& b)
{
  r = b;
  g = b;
}
