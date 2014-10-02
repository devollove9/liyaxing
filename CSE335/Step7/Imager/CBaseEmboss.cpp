/*
 * Name:     CBaseEmboss.cpp
 * Convert an image into what looks like an embossed image on metal
 *
 * Base Version
 *
 * Class:    CBaseEmboss
 * Header:   CBaseEmboss.h
 * Created : Nov 15, 2011
 * Author :  Charles B. Owen
 */

#include "wx/prec.h"
#include "CBaseEmboss.h"

/*! Constructor
 * \param picture The image to convert
 */
CBaseEmboss::CBaseEmboss(const CPicture *picture) : CProcessor(picture)
{
}


/*! Destructor
 */
CBaseEmboss::~CBaseEmboss()
{
}



/** \brief Actual processing of the image.
 */
void CBaseEmboss::Process()
{
    // Get the dimensions of the image
    int hit = GetHeight();
    int wid = GetWidth();

    // Loop over the rows of the image
    for(int y=0; y<hit;  y++)
    {
        // Loop over the columns of the image
        for(int x=0;  x<wid;  x++)
        {
            // Compute a horizontal Sobel operator
            double sobel = -GetMono(x-1, y-1) - 2 * GetMono(x-1, y) - GetMono(x-1, y+1) +
                    GetMono(x+1, y-1) + 2 * GetMono(x+1, y) + GetMono(x+1, y+1);

            // This is a value from -1024 to + 1024.
            // Make into a value with an average of 128
            sobel = sobel + 128;

            // Write this as the monochrome pixel value
            SetMono(x, y, sobel);
        }
    }
}
