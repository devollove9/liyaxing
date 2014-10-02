/*
 * Name:     CBlackAndWhite.cpp
 * Converts an image from color to monochrome.
 *
 * Class:    CBlackAndWhite
 * Header:   CBlackAndWhite.h
 * Created : Nov 15, 2011
 * Author :  Charles B. Owen
 */

#include "wx/prec.h"
#include "CBlackAndWhite.h"

/*! Constructor
 * \param picture The picture we are converting
 */
CBlackAndWhite::CBlackAndWhite(const CPicture *picture) : CProcessor(picture)
{
}

/*! Destructor
 */
CBlackAndWhite::~CBlackAndWhite()
{
}




/*! Actual processing of the image.
 */
void CBlackAndWhite::Process()
{
    int hit = GetHeight();
    int wid = GetWidth();
    int progress=0;
    int nextY = 0;
    
    // Loop over the rows of the image
    #pragma omp parallel default(none) shared(hit, wid, nextY, progress)
    {
    // Loop over the rows of the image
    
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

        

        // Loop over the columns of the image
        // Loop over the columns of the image
        for(int x=0;  x<wid;  x++)
        {
            // Get the RGB value
            int r, g, b;
            GetRGB(x, y, r, g, b);
            //if (a<0.99) a+=0.001;
            // Convert RGB to gray scale
            int gray = (r + g + b) / 3;
            SetRGB(x, y, gray, gray, gray);
            //if (a<0.99) a+=0.001;
            
        }
        
    }
    }
    //if (a<1) Progress(1.0);
}
