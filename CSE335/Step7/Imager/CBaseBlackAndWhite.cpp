/*
 * Name:     CBaseBlackAndWhite.cpp
 * Converts an image from color to monochrome.
 *
 * Base version
 *
 * Class:    CBaseBlackAndWhite
 * Header:   CBaseBlackAndWhite.h
 * Created : Nov 15, 2011
 * Author :  Charles B. Owen
 */

#include "wx/prec.h"
#include "CBaseBlackAndWhite.h"

/** \brief Constructor
 * \param picture The picture we are converting
 */
CBaseBlackAndWhite::CBaseBlackAndWhite(const CPicture *picture) : CProcessor(picture)
{
}

/** \brief Destructor
 */
CBaseBlackAndWhite::~CBaseBlackAndWhite()
{
}




/** \brief Actual processing of the image.
 */
void CBaseBlackAndWhite::Process()
{
    int hit = GetHeight();
    int wid = GetWidth();

    // Loop over the rows of the image
    for(int y=0; y<hit;  y++)
    {
        // Loop over the columns of the image
        for(int x=0;  x<wid;  x++)
        {
            // Get the RGB value
            int r, g, b;
            GetRGB(x, y, r, g, b);

            // Convert RGB to gray scale
            int gray = (r + g + b) / 3;
            SetRGB(x, y, gray, gray, gray);
        }
    }
}
