#include "iostream"
#include "imagesubwindow.h"
#include "mainwindow.h"

ImageSubwindow::ImageSubwindow() :
    QMdiSubWindow()
{
    setWidget(&ScrollArea);
    ScrollArea.setWidget(&Label);

    //curFile = NULL;
}

ImageSubwindow::ImageSubwindow(QWidget *parent) :
    QMdiSubWindow(parent)
{
    setWidget(&ScrollArea);
    ScrollArea.setWidget(&Label);

    parentMW = parent;

    //curFile = NULL;
}

void ImageSubwindow::focusInEvent(QFocusEvent *fIE)
{
    cout<<currentFile().toStdString();
    ((MainWindow*)parentMW)->currentChild = this;
}

void ImageSubwindow::fitToPixmap()
{
    this->resize(Pixmap.width(), Pixmap.height());
}

void ImageSubwindow::fitToMainWindow()
{
    int mainWidth = ((MainWindow*)parent())->width();
    int mainHeight = ((MainWindow*)parent())->height();


    if(width() > mainWidth)
        this->resize(mainWidth, height());
    if(height() > mainHeight)
        this->resize(width(), mainHeight);
}

void ImageSubwindow::resizeFrame()
{
    ScrollArea.adjustSize();
    ScrollArea.resize(this->width(), this->height());

    Label.adjustSize();
    Label.resize(this->width(), this->height());

}

bool ImageSubwindow::loadFile(const QString &fileName)
{
    if (!Pixmap.load(fileName, 0, Qt::AutoColor)) {
            QMessageBox::warning(this, tr("MDI"),
                                 tr("Cannot read file %1.")
                                 .arg(fileName));
            return false;
        }
        image = Pixmap.toImage();
        fitToPixmap(); //fits the whole subwindow's size to be the size of the pixmap
        resizeFrame(); //fits the contents of the subwindow to match the subwindow's size
        fitToMainWindow(); //makes sure that huge files don't go waay off of the window

        //now, assign the pixmap to the label
        Label.setPixmap(Pixmap);

        Label.show();
        this->show();

        //set the current file
        setCurrentFile(fileName);

        return true;
}

void ImageSubwindow::setCurrentFile(QString fileName)
{
    curFile = fileName;
}

QString ImageSubwindow::currentFile()
{
    return curFile;
}

bool ImageSubwindow::save()
{
    QString temp;
    temp = currentFile();
    cout<<temp.toStdString();
    cout.flush();
    if(Pixmap.save(curFile,0,-1))
    {
        cout<<" saved succesfully.\n";
        return true;
    }

    cout<<" could not save succesfully. \n";
    return false;
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
bool ImageSubwindow::median()
{
    //QImage image = Pixmap.toImage();
    int size = 3;
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
                      local_hist[qGray(temp.pixel(y,x))]++;
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
          image.setPixel(y, x, qRgb(i, i, i));
        }
       this->Label.setPixmap(QPixmap::fromImage(image));
       this->Label.show();
      return true;
}

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
bool ImageSubwindow::emboss()
{
    if( image.isNull() )
        return false;
    int x, y, gradient;

    QImage temp = image;
    for( x = 0; x < image.width()-1; x++ )
        for( y = 1; y < image.height(); y++ )
        {
            gradient = (qGray(temp.pixel(x,y))
                        - qGray(temp.pixel(x+1,y-1)))/2+128;
            image.setPixel(x,y, qRgb(gradient, gradient, gradient));
        }
    this->Label.setPixmap(QPixmap::fromImage(image));
    this->Label.show();
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
bool ImageSubwindow::sobelEdgeDetect()
{
    if(image.isNull())
        return false;

    int UpL, Up, UpR, L, R, BotL, Bot, BotR;
    int X, Y, x, y, m; // x is horizontal gradient
                       // y is vertical gradient
                       // m is magnitude
    QImage temp = image;
    for(x = 1; x < temp.width() - 1; x++)
        for(y = 1; y < temp.height() - 1; y++)
        {
            UpL = qGray(temp.pixel(x-1,y+1));
            Up = qGray(temp.pixel(x,y+1));
            UpR = qGray(temp.pixel(x+1,y+1));
            L = qGray(temp.pixel(x-1,y));
            R = qGray(temp.pixel(x+1,y));
            BotL = qGray(temp.pixel(x-1,y-1));
            Bot = qGray(temp.pixel(x,y-1));
            BotR = qGray(temp.pixel(x+1,y-1));

            X = -UpL-2*L-BotL+UpR+2*R+BotR;

            Y = -UpL-2*Up-UpR+BotL+2*Bot+BotR;

            m = sqrt(double(X*X)+double(Y*Y));
            image.setPixel(x, y, qRgb(m, m, m));
        }
    this->Label.setPixmap(QPixmap::fromImage(image));
    this->Label.show();
    return true;
}

/****************************************************************//**
 * @author Benjamin Sherman
 *
 * @par Description:
 * This function uses the gamma power transformation
 * function and applies it to the image accordingly.
 *
 * @param[in][out] image - variable that contains the image
 * to be manipulated.
 *
 * @returns true - functioned sucessfully.
 * @returns false - user canceled execution of this
 * process
  *******************************************************************/
bool ImageSubwindow::gamma(double sigma)
{
    int LookUpTable[256] = {0}, i, x, y;
    double temp_table;

    for( i = 0; i < 256; i++ )
    {
        if( sigma > 0 )
            LookUpTable[i] = 255.0 * pow( double(i)/255.0, sigma );

        else if( sigma < 0 )
        {
            temp_table = 255.0 * pow( double(i)/255.0, -1.0*sigma );
            LookUpTable[i] = 1.0/temp_table;
        }

        else
            break;
        if( LookUpTable[i] > 255.0 )
            LookUpTable[i] = 255;
        if( LookUpTable[i] < 0 )
            LookUpTable[i] = 0;
    }

    QRgb rgb;
    for( x = 0; x < image.width(); x++ )
        for( y = 0; y < image.height(); y++ )
        {
            //clr = image.pixel(r,c);
            //clr(image.pixel(r,c));
            rgb = image.pixel(x,y);
            rgb = qRgb(LookUpTable[qRed(rgb)], LookUpTable[qGreen(rgb)], LookUpTable[qBlue(rgb)]);
            image.setPixel(x, y, rgb);
        }
    this->Label.setPixmap(QPixmap::fromImage(image));
    this->Label.show();
    return true;
}

bool ImageSubwindow::posterize(int levels)
{
    // handle invalid parameters
    if(levels < 1 || levels > 255)
        return false;

//    if(levels == 1)
//        ; // set image all black, make new black copy, same size

    int LookUpTable[256] = {0}, i;

    for(i = 1; i <= 256; i++ )
        LookUpTable[i] = int(double(i)/double(levels)/256.0)*(256/levels);
    //int nrows = image.height(), ncols = image.width(), r, c;
    int x, y;
    QRgb rgb, pixel;
    for( x = 0; x < image.width(); x++ )
        for( y = 0; y < image.height(); y++ )
        {
            rgb = image.pixel(x, y);
            pixel = qRgb(LookUpTable[qRed(rgb)], LookUpTable[qGreen(rgb)], LookUpTable[qBlue(rgb)]);
            image.setPixel(x, y, pixel);
        }
    this->Label.setPixmap(QPixmap::fromImage(image));
    this->Label.show();
    //Exit the function successfully
    return true;
}

void ImageSubwindow::negate()
{
    if(image.isNull())
        return;
    image.invertPixels();

    this->Label.setPixmap(QPixmap::fromImage(image));
    this->Label.show();
}

/****************************************************************//*
 * @author Benjamin Sherman
 *
 * @par Description:
 * This is the function prompts the user for a value
 * between -255 and 255 which the function will then
 * add to the image intensity consequently brightening
 * or darkening it.
 *
 * @param[in][out] image - variable that contains the image
 * to be manipulated.
 *
 * @returns true - functioned sucessfully.
 * @returns false - user canceled execution of this
 * process
  *******************************************************************/
void ImageSubwindow::adjustIntensity(int intChange)
{
    if( image.isNull() )
        return;

    int x, y,
    LookUpTable[256] = {0}, i;

    for( i = 0; i < 256; i++ )
    {
        if( (i + intChange) < 0 )
            LookUpTable[i] = 0;
        else if( (i + intChange) > 255 )
            LookUpTable[i] = 255;
        else
            LookUpTable[i] = i + intChange;
    }

    QRgb pixel, rgb;
    for( x = 0; x < image.width(); x++ )
        for( y = 0; y < image.height(); y++ )
        {
            rgb = image.pixel(x,y);
            pixel = qRgb(LookUpTable[qRed(rgb)], LookUpTable[qGreen(rgb)], LookUpTable[qBlue(rgb)]);
            image.setPixel(x,y,pixel);
        }

    this->Label.setPixmap(QPixmap::fromImage(image));
    this->Label.show();
}

/*****************************************************************//*
 * @author Benjamin Sherman
 *
 * @par Description:  This function uses a 3x3 averaging mask to
 * smooth the input image.
 *
 * @par Note: I average all colorbands as using intensity
 * gives poor results.
 *
 * @param[in][out] Image &image - The image to be manipulated.
 *
 * @returns true  - The image negative was successfully computed
 *          false - The function end prematurely, due to an error.
 *******************************************************************/
void ImageSubwindow::smooth()
{
    if( image.isNull() )
        return;
    int x, y;
    QRgb upL, up, upR, L, C, R, lowL, low, lowR;
    QImage temp = image;
    QRgb pixel;
    int red_pix_total, green_pix_total, blue_pix_total;
    for( x = 1; x < temp.width()-1; x++ )
        for( y = 1; y < temp.height()-1; y++ )
        {
            upL = temp.pixel(x-1,y+1);
            up = temp.pixel(x,y+1);
            upR = temp.pixel(x+1,y+1);
            L = temp.pixel(x-1,y);
            C = temp.pixel(x,y);
            R = temp.pixel(x+1,y);
            lowL = temp.pixel(x-1,y-1);
            low = temp.pixel(x,y-1);
            lowR = temp.pixel(x+1,y-1);
            red_pix_total = qRed(upL)+ qRed(up)+ qRed(upR)+ qRed(L)
                    + qRed(C)+ qRed(R)+ qRed(lowL)+ qRed(low)+ qRed(lowR);
            green_pix_total = qGreen(upL)+ qGreen(up)+ qGreen(upR)+ qGreen(L)
                    + qGreen(C)+ qGreen(R)+ qGreen(lowL)+ qGreen(low)+ qGreen(lowR);
            blue_pix_total = qBlue(upL)+ qBlue(up)+ qBlue(upR)+ qBlue(L)
                    + qBlue(C)+ qBlue(R)+ qBlue(lowL)+ qBlue(low)+ qBlue(lowR);

            pixel = qRgb(red_pix_total/9, green_pix_total/9, blue_pix_total/9);

            image.setPixel(x, y, pixel);
        }
    this->Label.setPixmap(QPixmap::fromImage(image));
    this->Label.show();
}
