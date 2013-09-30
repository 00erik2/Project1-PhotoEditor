#include <QImage>
#include <iostream>

using namespace std;

QImage gamma(QImage &image, double sigma);
QImage posterize(QImage &Image);

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
QImage gamma(QImage &image , double sigma)
{
    if( image.isNull() )
        return false;
    int LookUpTable[256] = {0}, i, r, c, nrows, ncols;
    double temp_table;
    nrows = image.height();
    ncols = image.width();

    if ( !getParams( sigma ) )
        return false;
    for( i = 0; i < 256; i++ )
    {
        if( gamma > 0 )
            LookUpTable[i] = 255.0 * pow( double(i)/255.0, gamma );


        else if( gamma < 0 )
        {
            temp_table = 255.0 * pow( double(i)/255.0, -1.0*gamma );
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
    QColor clr;
    for( r = 0; r < nrows; r++ )
        for( c = 0; c < ncols; c++ )
        {
            //clr = image.pixel(r,c);
            clr(image.pixel(r,c));
            rgb = image.pixel(r,c);
            rgb = qRgb(LookUpTable[qRed(rgb)], LookUpTable[qGreen(rgb)], LookUpTable[qBlue(rgb)]);
            image.setPixel(r, c, rgb);
        }
    return true;
}

bool posterize(QImage &image, int levels)
{
    // handle invalid parameters
    if(levels < 1 || levels > 255)
        return false;

    if(levels == 1)
        ; // set image all black, make new black copy, same size

    int LookUpTable[256] = {0}, i, j;

    for(i = 1; i <= 256; i++ )
        LookUpTable[i] = int(double(i)/double(levels)/256.0)(256/levels);

    QRgb rgb;
    QColor clr;
    for( r = 0; r < nrows; r++ )
        for( c = 0; c < ncols; c++ )
        {
            rgb = image.pixel(r,c);
            rgb = QRgb(LookUpTable[qRed(rgb)], LookUpTable[qGreen(rgb)], LookUpTable[qBlue(rgb)]);
            image.setPixel(r, c, rgb);
        }
    //Exit the function successfully
    return true;
}
