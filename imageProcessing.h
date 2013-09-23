#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

using namespace std;

struct pixel
{
    unsigned int red;
    unsigned int green;
    unsigned int blue;
};

class image
{
public:
    int imageWidth();
    int imageHeight();
  //Drop down functions
    void adjustIntensity(int intensity, Image &image);
    void contrast(int factor, Image &image);
    void gamma(double factor, Image &image);
    void sharpen(int factor, Image &image);
    void soften(int factor, Image &image);
    void negate(Image &image);
    void medianFilter(Image &image);
    void poserize(int factor, Image &image);
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

private:
    void setRed(int red);
    void setGreen(int green);
    void setBlue(int blue);
    void setIntensity(int intensity);
};

#endif // IMAGEPROCESSING_H
