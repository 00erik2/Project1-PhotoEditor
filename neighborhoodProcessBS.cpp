#include <QImage>
#include <iostream>
#include <cmath>

bool emboss(QImage &image);
bool median(QImage &image, int size);
bool sobelEdgeDetect(QImage &image);
/*****************************************************************//*
 * @author Benjamin Sherman
 *
 * @verbatim
 * 0  0  0
 * 0  1  0
 * 0  0 -1
 * @endverbatim
 * @par Description:  The mask above is applied to every pixel
 * in an image. This function is a type of edge detector. It
 * isn't typically used to find edges, it is more used to
 * give an image a 3 dimensional effect or embossed effect.
 *
 * @param[in][out] Image &imageimage - The image to be manipulated.
 *
 * @returns true  - The image negative was successfully computed
 *          false - The function end prematurely, due to an error.
 *******************************************************************/
bool emboss(QImage &image)
{
    if( image.isNull() )
        return false;
    int nrows = image.height(), ncols = image.width(), x, y, gradient;

    QImage temp = image;
    for( x = 0; x < image.width()-1; x++ )
        for( y = 1; y < image.height()-1; x++ )
        {
            gradient = (qGray(temp.pixel(x,y))
                        - qGray(temp.pixel(x+1,y-1)))/2+128;
            image.setPixel(x,y, qRgb(gradient, gradient, gradient));
        }
    return true;
}


/*****************************************************************//*
 * @author Benjamin Sherman
 *
 * @par Description:  This function prompts the user for a
 * neighborhood size (NxN box around the pixel being processed)
 * distance.  This is scaled to an odd number and if it is less than
 * 3 it is scaled to 3. Next, this distance is divided by 2 to scale
 * to a Chebyshev distnace from center pixel.  Once the distance of
 * pixels Chebyshev radius is derived, this function
 * will then read in all the values with the Chebyshev radius around
 * a pixel are processed (this happens for every pixel in theQImage
 * excluding edge pixels). The mean of intensites is derived from
 * the pixels within the Chebyshev radius of pixels.
 *
 * @par Note:
 * The neighborhood intensities are not sorted, rather the
 * frequency of intensities are stored in a local histogram
 * and there is no need of sorting. Once the sum of the frequencies
 * going left to right in the histogram is equal to
 * neighborhood size/2 + 1 the intensity index is the mean.
 * The intensity index is then written to the image.
 *
 *
 * @param[in][out] Image &imageimage - The image to be manipulated.
 *
 * @returns true  - The image negative was successfully computed
 *          false - The function end prematurely, due to an error.
 *******************************************************************/
bool median(QImage &image, int size)
{
    if(image.isNull() )
        return false;
  int nrows = image.height(), ncols = image.width(), x, y, i, j;
  int COL, ROW, size_sqr, place, mean_index;

  // handle out of range neighborhood parameters
  if( size%2 == 0 )
      size += 1;
  if( size < 3 )
      size = 3;
  size_sqr = size * size;
  // mean index is the number of pixels in the median filter
  // neighborhood size. When these are sorted, they
  mean_index = size_sqr/2 + 1;
 QImage temp = image;

  for( x = size/2; x < nrows - size/2; x++ )
      for( y = size/2; y < ncols - size/2; y++ )
      {
          std::vector <int> local_hist (256, 0);
          ROW = y - size/2;
          COL = x - size/2;

              for( i = ROW; i < ROW + size; i++ )
              {
                  for( j = COL; j < COL + size; j++ )
                  {
                      local_hist[qGray(temp.pixel(x,y))]++;
                  }

              }

          place = 0; // the intensity of the sorted middle neighborhood
          // pixel is initializede to 0
          for( i = 0; i < 256; i++ )
              {
                  place += local_hist[i];

                  // once half-way through the sorted elements in the
                  // neighborhood, break and set intensity of pixel
                  if( place >= mean_index )
                      break;
              }
          image.setPixel(x, y, qRgb(i, i, i));
        }

      return true;
}


/*****************************************************************//*
 * @author Bejamin Sherman
 *
 * @par Description:  Outputs the Sobel filter magnitude, which is
 *                    the square root of the x (horizontal) direction
 *                    squared and
 *                    the y (verticle) direction squared (sqrt(x^2+y^2).
 *                    The x coordinate of the Sobel filter is:
 *                                              | -1  0  1 |
 *                          Sobel,x:  h(x,y) =  | -2  0  2 |
 *                                              | -1  0  1 |
 *                    The y coordinate of the Sobel filter is:
 *                                              | -1 -2 -1 |
 *                          Sobel,y:  h(x,y) =  |  0  0  0 |
 *                                              |  1  2  1 |
 *
 * @param[in/out] QImage &image - The pixmap to be manipulated.
 *
 * @returns true  - The Sobel magnitude was successfully applied.
 *          false - The function end prematurely, due to an error.
 *******************************************************************/
bool sobelEdgeDetect(QImage &image)
{
    if(image.isNull())
        return false;

    int UpL, Up, UpR, L, R, BotL, Bot, BotR;
    int r, c, x, y, m; // x is horizontal gradient
                       // y is vertical gradient
                       // m is magnitude

    for(r = 1; r < image.height() - 1; r++)
        for(c = 1; c < image.width() - 1; c++)
        {
            UpL = qGray(image.pixel(r-1,c-1));
            Up = qGray(image.pixel(r-1,c));
            UpR = qGray(image.pixel(r-c,c+1));
            L = qGray(image.pixel(r,c-1));
            R = qGray(image.pixel(r,c+1));
            BotL = qGray(image.pixel(r+1,c-1));
            Bot = qGray(image.pixel(r+1,c));
            BotR = qGray(image.pixel(r+1,c+1));

            x = -UpL-2*L-BotL+UpR+2*R+BotR;

            y = -UpL-2*Up-UpR+BotL+2*Bot+BotR;

            m = sqrt(double(x*x)+double(y*y));
            image.setPixel(c, r, qRgb(m, m, m));
        }
    return true;
}

