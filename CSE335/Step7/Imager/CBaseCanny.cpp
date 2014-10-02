/*
 * Name:     CBaseCanny.cpp
 * Implements Canny edge detection on an image creating a
 * false color edge image.
 *
 * Base Version
 *
 * Class:    CBaseCanny
 * Header:   CBaseCanny.h
 * Created : Nov 15, 2011
 * Author :  Charles B. Owen
 */

#include "wx/prec.h"
#include "CBaseCanny.h"

using namespace std;


/** \brief Constructor
 * \param picture The image to process
 */
CBaseCanny::CBaseCanny(const CPicture *picture) : CProcessor(picture)
{
    // Canny uses two thresholds to determine where edges are.
    // These are the default values for those thresholds
    mThresholdHigh = 100;
    mThresholdLow = 2;
}

/** \brief Destructor
 */
CBaseCanny::~CBaseCanny()
{
}




/** \brief Actual processing of the image.
 */
void CBaseCanny::Process()
{
    int hit = GetHeight();
    int wid = GetWidth();

    //
    // Step 1: Gaussian filter
    //

    CArray2D<double> gaussianFiltered;
    GaussianFilter(gaussianFiltered);

    //
    // Step 2: Sobel filter to determine gradient and orientation
    //

    CArray2D<Directions> directions;
    CArray2D<double> gradient;
    DetermineGradient(gaussianFiltered, gradient, directions);

    //
    // Step 3: Non-maximum suppression
    //

    CArray2D<double> gradientNM;
    NonMaximumSuppression(gradient, directions, gradientNM);

    //
    // Step 4: Trace the edges
    //

    list<wxPoint> edges;
    TraceEdges(gradientNM, edges);

    //
    // Clear the result image to black
    //

    for(int y=0; y<hit;  y++)
    {
        for(int x=0;  x<wid;  x++)
        {
            // Non-edge pixels we be set to black
            SetRGB(x, y, 0, 0, 0);
        }
    }

    //
    // Final step: draw the located edges into a color
    // output image we display.
    //

    for(std::list<wxPoint>::iterator p=edges.begin(); p!=edges.end(); p++)
    {
        // If this assert fails, you have a race condition
        assert(IsSetBlack(p->x, p->y));

        // The color we set is determined by the edge direction
        switch(directions.Get(p->x, p->y))
        {
        case D0:
            SetRGB(p->x, p->y, 255, 0, 0);
            break;

        case D45:
            SetRGB(p->x, p->y, 0, 255, 0);
            break;

        case D90:
            SetRGB(p->x, p->y, 0, 0, 255);
            break;

        case D135:
            SetRGB(p->x, p->y, 255, 0, 255);
            break;
        }

    }

}



/*! \brief Filter the input image using a Gaussian filter of size 5x5.
 * Filter the input image using a Gaussian filter of size 5x5,
 * creating the output image in gaussianFiltered
 * \param gaussianFiltered The 2D output image
 */
void CBaseCanny::GaussianFilter(CArray2D<double> &gaussianFiltered)
{
    // Image size
    int hit = GetHeight();
    int wid = GetWidth();

    // A filter kernel is a 1D array of values we will
    // use to filter the image. They create a weighted average
    // of a neighborhood of pixels.
    static const int Size = 5;
    static const int Size2 = 2;     // Floor of Size / 2
    static const double sigma = 1.4;
    double gaussian[Size];
    ComputeGaussianKernel(Size, sigma, gaussian);

    //
    // First we filter the rows into the intermediate array rowsFiltered
    //

    CArray2D<double> rowsFiltered(wid, hit);

    for(int y=0;  y<hit; y++)
    {
        for(int x=0;  x<wid;  x++)
        {
            double sum = 0;
            for(int i=0;  i<Size;  i++)
            {
                sum += GetMono(x + i - Size2, y) * gaussian[i];
            }

            rowsFiltered.Set(x, y, sum);
        }
    }

    //
    // Then we filter the columns into the output array gaussianFiltered
    //

    gaussianFiltered.SetSize(wid, hit);

    for(int y=0;  y<hit; y++)
    {
        for(int x=0;  x<wid;  x++)
        {
            double sum = 0;
            for(int i=0;  i<Size;  i++)
            {
                sum += rowsFiltered.Get(x, y + i - Size2) * gaussian[i];
            }

            gaussianFiltered.Set(x, y, sum);
        }
    }

}


/** \brief Compute the gradient image and directions.
 * Apply the Sobel gradient estimation operator to the image
 * to determine the image gradient at each pixel. We apply both
 * the horizontal and vertical operator here.
 * \param gaussian The input array after Gaussian filtering
 * \param gradient The output array with the magnitude of the gradient at each pixel squared
 * \param directions An output array with a direction code for the edge at each pixel.
 */
void CBaseCanny::DetermineGradient(CArray2D<double> &gaussian, CArray2D<double> &gradient,
        CArray2D<CBaseCanny::Directions> &directions)
{
    int hit = gaussian.GetHit();
    int wid = gaussian.GetWid();

    // Make the output arrays the same size as the input array
    gradient.SetSize(wid, hit);
    directions.SetSize(wid, hit);

    // Loop over the rows and columns of the image
    for(int y=0;  y<hit;  y++)
    {
        for(int x=0;  x<wid;  x++)
        {
            // What are the eight neighbors of this pixel?
            double p1 = gaussian.Get(x-1, y-1);
            double p2 = gaussian.Get(x, y-1);
            double p3 = gaussian.Get(x+1, y-1);
            double p4 = gaussian.Get(x-1, y);
            double p5 = gaussian.Get(x+1, y);
            double p6 = gaussian.Get(x-1, y+1);
            double p7 = gaussian.Get(x, y+1);
            double p8 = gaussian.Get(x+1, y+1);

            // Compute the horizontal and vertical gradients
            double gx = -p1 - 2 * p4 - p6 + p3 + 2 * p5 + p8;
            double gy = -p1 - 2 * p2 - p3 + p6 + 2 * p7 + p8;

            // Compute the magnitude of the 2d value squared
            double g = gx * gx + gy * gy;   // Actually, the intensity squared
            gradient.Set(x, y, g);          // Set in the output image

            // If we have any gradient there at all...
            if(g > 0)
            {
                // Compute the angle at the location using atan2
                double angle = atan2(gy, gx);
                if(angle < 0)
                    angle += M_PI;

                // Round the angle to four possible values: 0, 45, 90, and 135 degrees
                angle += (M_PI / 8);
                if(angle >= M_PI)
                    angle = 0;

                // Set the angle in the output image
                directions.Set(x, y, (Directions)(angle / (M_PI / 4)));
            }
            else
            {
                // If no gradient, we can't set an angle, so just use 0 degrees
                directions.Set(x, y, D0);
            }
        }
    }

}

/** \brief Perform non-maximum suppression.
 * An edge will have gradient in a range around
 * it. This function looks at each pixel and keeps
 * only those gradients that are the largest in the
 * edge direction. This makes the edges thin.
 * \param gradient The gradient image (input)
 * \param directions The directions image (input)
 * \param gradientNM The output gradient image with non-maximum suppression
 */
void CBaseCanny::NonMaximumSuppression(CArray2D<double> &gradient, CArray2D<CBaseCanny::Directions> &directions, CArray2D<double> &gradientNM)
{
    int hit = gradient.GetHit();
    int wid = gradient.GetWid();

    // Set output image to same size
    gradientNM.SetSize(wid, hit);

    // Loop over the rows and columns
    for(int y=0;  y<hit;  y++)
    {
        for(int x=0;  x<wid;  x++)
        {
            // Current location
            double g = gradient.Get(x, y);

            // Our two neighbors
            double n1 = 0;
            double n2 = 0;

            switch(directions.Get(x, y))
            {
            case D0:
                // Look in the east and west directions
                n1 = gradient.Get(x-1, y);
                n2 = gradient.Get(x+1, y);
                break;

            case D45:
                // Look in the northeast and southwest directions
                n1 = gradient.Get(x-1, y-1);
                n2 = gradient.Get(x+1, y+1);
                break;

            case D90:
                // Look in the north and south directions
                n1 = gradient.Get(x, y-1);
                n2 = gradient.Get(x, y+1);
                break;

            case D135:
                // Look in the northwest and southeast directions
                n1 = gradient.Get(x-1, y+1);
                n2 = gradient.Get(x+1, y-1);
                break;
            }

            if(g > n1 && g > n2)
            {
                // We are the maximum of the three. Write the gradient
                gradientNM.Set(x, y, g);
            }
            else
            {
                // We are not maximum, so we are suppressed.
                gradientNM.Set(x, y, 0);
            }
        }
    }
}


/*! \brief Compute a list of edge pixels.
 * Finding starting points in the gradient image where the gradient is high,
 * this function follows the edge using a lower threshold to trace out the edge
 * continuity. It calls the recursive function Trace that does the actually tracing.
 *
 * Notice: This process destroys the gradient image.
 *
 * Parallelizing this function will be much harder than the other
 * functions.
 *
 * \param gradient The gradient image after non-maximum suppression
 * \param edges The output edge pixels that have been traced.
 */
void CBaseCanny::TraceEdges(CArray2D<double> &gradient, std::list<wxPoint> &edges)
{
    int hit = gradient.GetHit();
    int wid = gradient.GetWid();

    double usethreshold = mThresholdHigh * mThresholdHigh;

    for(int y=0; y<hit;  y++)
    {
        for(int x=0;  x<wid;  x++)
        {
            double g = gradient.Get(x, y);
            if(g > usethreshold)
            {
                Trace(x, y, gradient, edges);
            }
        }
    }
}


/** \brief Trace an edge recursively from a starting point
 * This function follows the edge using a lower threshold to trace out the edge
 * continuity. It calls the recursive function Trace that does the actually tracing.
 *
 * Notice :      This process destroys the gradient image.
 *               This function is recursive!
 *
 * \param x Starting x location for the recursive trace
 * \param y Starting y location for the recursive trace
 * \param gradient The gradient image after non-maximum suppression
 * \param edges The output edge pixels that have been traced.
 */
void CBaseCanny::Trace(int x, int y, CArray2D<double> &gradient, std::list<wxPoint> &edges)
{
    // Indicate that this pixel is an edge pixel in the output image
    edges.push_back(wxPoint(x, y));

    // This assertion must be true. If it is not, you have a race condition
    assert(gradient.Get(x, y) > 0);

    // Clear this pixel in the input image so we don't test it again later
    gradient.Set(x, y, 0);

    // Every pixel has 8 neighbors. These are the locations of those neighbors
    int neighbors[][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};

    // We need the square of the threshold
    double threshold = mThresholdLow * mThresholdLow;

    // Test all neighbors to see if they are on the edge
    for(int i=0;  i<8;  i++)
    {
        // The x,y location of the neighbor
        int xn = x+neighbors[i][0];
        int yn = y + neighbors[i][1];

        // If it is above the threshold, it is part of this edge
        if(gradient.Get(xn, yn) > threshold)
        {
            // If part of this edge, continue tracing from there
            Trace(xn, yn, gradient, edges);
        }
    }
}



/** \brief Compute a 1D Gaussian filter kernel.
 * Compute the appropriate 1D Gaussian filter kernel
 * for a specified size and sigma. For small values of size,
 * there will be no advantage to parallelizing this function.
 * \param size Kernel will be size by size
 * \param sigma The kernel sigma value
 * \param gaussian Output result
 * \param gaussian Kernel is returned in an array pointed to by this parameter.
 */
void CBaseCanny::ComputeGaussianKernel(int size, double sigma, double *gaussian)
{
    // Compute the Gaussian filter kernel
    double sum = 0;
    for(int i=0;  i<size;  i++)
    {
        // Offset 0 to size-1 i, j to -size/2 to size/2
        double io = i - size/2;
        double h = 1 / (sigma * 2.506628) * exp(-(io * io) / (2 * sigma * sigma));
        sum += h;
        gaussian[i] = h;
    }

    // Normalize the filter kernel
    for(int i=0;  i<size;  i++)
    {
        gaussian[i] /= sum;
    }
}

