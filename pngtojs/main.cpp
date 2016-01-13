#include <iostream>
#include <limits>
#include <cmath>
#include <cstdint>
#include <cstdarg>

#include <visp/vpImageIo.h>

template <typename T>
inline T min(T const& a, T const& b)
{
    return (a < b)? a : b;
}

int main()
{
    unsigned int const nb_layers = 16;

    vpImage<unsigned char> img;
    vpImageIo::read(img, "../textures/heightmap.png");

    unsigned int width(img.getWidth()), height(img.getHeight());
    //*
    std::cout << "var heightMapArray;" << std::endl;
    std::cout << "var distanceMapArray;" << std::endl;
    std::cout << std::endl;
    std::cout << "var heightMapWidth = " << width << ";" << std::endl;
    std::cout << "var heightMapHeight = " << height << ";" << std::endl;
    std::cout << "heightMapArray = [";
    for(unsigned int i = 0; i < height; ++i)
    {
        std::cout << "[";
        for(unsigned int j = 0; j < width; ++j)
        {
            std::cout << (int)img[i][j];
            if(j != width - 1)
                std::cout << ", ";
        }
        std::cout << "]";
        if(i != height - 1)
            std::cout << ", ";
    }
    std::cout << "];" << std::endl;

    std::cout << "//ok" << std::endl;
    //*/

    uint8_t * L[nb_layers];
    for(unsigned int h = 0; h < nb_layers; ++h)
    {
        L[h] = new uint8_t[height*width];
        for(unsigned int i = 0; i < height*width; ++i)
            L[h][i] = std::numeric_limits<uint8_t>::max();
    }

    for(unsigned int i = 0; i < height; ++i)
        for(unsigned int j = 0; j < width; ++j)
        {
            unsigned int h_max = (uint8_t) floor((double) img[i][j] * (double) nb_layers / 255.0);
            for(unsigned int h = 0; h < h_max; ++h)
                L[h][i*width+j] = 0;
        }

    for(unsigned int h = 0; h < nb_layers; ++h)
        for(unsigned int i = 0; i < height; ++i)
            for(unsigned int j = 0; j < width; ++j)
            {
                uint8_t val = L[h][i*width + j];
                uint8_t valh = (h > 0)? L[h-1][i*width+j] + 1 : val;
                uint8_t valj = (j > 0)? L[h][i*width+(j-1)] + 1 : val;
                uint8_t vali = (i > 0)? L[h][(i-1)*width+j] + 1 : val;

                L[h][i*width + j] = min(min(val, valh), min(valj, vali));
            }

    for(int h = nb_layers - 1; h >= 0; --h)
        for(int i = height - 1; i >= 0; --i)
            for(int j = width - 1; j >= 0; --j)
            {
                uint8_t val = L[h][i*width + j];
                uint8_t valh = (h < nb_layers - 1)? L[h+1][i*width+j] + 1 : val;
                uint8_t valj = (j < width - 1)? L[h][i*width + (j+1)] + 1 : val;
                uint8_t vali = (i < height - 1)? L[h][(i+1)*width+ j] + 1 : val;

                L[h][i*width + j] = min(min(val, valh), min(valj, vali));
            }

    //populating done
    std::cout << "distanceMapArray = [";
    for(unsigned int h = 0; h < nb_layers; ++h)
    {
        std::cout << "[";
        for(unsigned int i = 0; i < height * width; ++i)
        {
            std::cout << (unsigned int) L[h][i];
            if(i != height * width - 1)
                std::cout << ", ";
        }
        std::cout << "]";
        if(h != nb_layers - 1)
            std::cout << ", ";
    }
    std::cout << "];" << std::endl;

    for(unsigned int h = 0; h < nb_layers; ++h)
        delete L[h];
}
