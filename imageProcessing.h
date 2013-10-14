#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H
#include <iostream>
#include <QImage>
using namespace std;
QImage img(QImage &Image);
struct pixel
{
    unsigned int red;
    unsigned int green;
    unsigned int blue;
};

    void adjustIntensity(int intensity, Image &image);
    void contrast(int factor, Image &image);
    void gamma(double factor, Image &image);
    void sharpen(int factor, Image &image);
    void soften(int factor, Image &image);
    void negate(Image &image);
    void despecle(Image &image);
    void posterize(int factor, Image &image);
    void sobel(Image &image);
    void emboss(Image &image);
    void saveImage(Image &image);

    void crop(Image &image);
    void rotate(Image &image);
    void resize(Image &image);
    void cut(Image &image);
    void paste(Image &image);

    void openImage( Image &image);
    void closeImage( Image &image);

#endif // IMAGEPROCESSING_H
