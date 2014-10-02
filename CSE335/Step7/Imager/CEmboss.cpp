/*
 * Name:     CEmboss.cpp
 * Convert an image into what looks like an embossed image on metal
 *
 * Class:    CEmboss
 * Header:   CEmboss.h
 * Created : Nov 15, 2011
 * Author :  Charles B. Owen
 */

#include "wx/prec.h"
#include "CEmboss.h"

/*! Constructor
 * \param picture The image to convert
 */
CEmboss::CEmboss(const CPicture *picture) : CProcessor(picture)
{
}


/*! Destructor
 */
CEmboss::~CEmboss()
{
}



/** \brief Actual processing of the image.
 */
void CEmboss::Process()
{
    // Get the dimensions of the image
    int hit = GetHeight();
    int wid = GetWidth();
    int progress=0;
    int nextY = 0;
    
    // Loop over the rows of the image
    #pragma omp parallel default(none) shared(hit, wid, nextY, progress)
    {
    while(true)
        {
            // Get the next available row
            int y;

            #pragma omp critical
            {
                // Get the next available row
                y = nextY;
                nextY++;
                int newProgress = (double(y) / double(GetHeight()) * 100);
                if(newProgress != progress)
                {
                    progress = newProgress;
                    Progress(progress * 0.01);
                }
            }

            if(y >= hit|| GetTerminate() )
                break;
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
}
