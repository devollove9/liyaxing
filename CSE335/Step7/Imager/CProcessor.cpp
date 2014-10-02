/*
 * Name:     CProcessor.cpp
 *
 *
 * Class:    CProcessor
 * Header:   CProcessor.h
 * Created : Nov 15, 2011
 * Author :  Charles B. Owen
 */

#include "wx/prec.h"
#include "CProcessor.h"

/** \cond */
/*
 * Name :        ByteRange(double d)
 * Description : Force the value of d to be in the range 0 - 255 as an integer.
 * Parameters :  d - Value that may be out of range
 * Returns :     Bounded value as an integer
 */
inline int ByteRange(double d)
{
    int b;
    if(d < 0)
        b = 0;
    else if(d > 255)
        b = 255;
    else
        b = int(d);

    return b;
}
/** \endcond */


/** \brief Constructor
 *
 * This is the constructor to use. The default constructor is disabled.
 * \param picture The image to process. This is the input to the processor and
 * is not changed in the processing.
 */
CProcessor::CProcessor(const CPicture *picture)
{
    // Copy the original to the local mPicture1
    mPicture1.SetPicture(picture);

    mFilename = picture->GetFilename();

    // Create the second picture the same size
    mPicture2.Create(picture->GetSize());
    
    mUser = NULL;
    mProgressId = 0;
    mDoneId = 0;
    mActive=false;
    mThread=0;
    mTerminate=false;
}

/** \brief Destructor */
CProcessor::~CProcessor()
{
}

/** \brief Get the RGB value of a pixel in the input image.
 * Get the RGB value of a pixel at location x,y. This function returns
 * black if x,y is outside the bounds of the picture.
 * \param x X location (column) in the image
 * \param y Y location (row) in the image. The top row is row 0
 * \param r Red output result
 * \param g Green output result
 * \param b Blue output result
 */
void CProcessor::GetRGB(int x, int y, int &r, int &g, int &b)
{
    if(x < 0 || x >= GetWidth() || y < 0 || y >= GetHeight())
    {
        r = 0;
        g = 0;
        b = 0;
        return;
    }

    mPicture1.GetRGB(x, y, r, g, b);
}

/** \brief Set the RGB value of a pixel in the output image.
 * Set the RGB value of a pixel at location x,y in the output image.
 * \param x X location (column) in the image
 * \param y Y location (row) in the image. The top row is row 0
 * \param r Red value to set
 * \param g Green value to set
 * \param b Blue value to set
  */
void CProcessor::SetRGB(int x, int y, double r, double g, double b)
{
    if(x < 0 || x >= GetWidth() || y < 0 || y >= GetHeight())
    {
        return;
    }

    mPicture2.SetRGB(x, y, ByteRange(r), ByteRange(g), ByteRange(b));
}


/** \brief Ensure a pixel in the output image is set to black.
 * This function will test that a pixel in the output image is
 * set to black. It is used mainly to test for potential race
 * conditions.
 * \param x X location (column) in the image
 * \param y Y location (row) in the image
 * \returns true if the pixel is black
 */
bool CProcessor::IsSetBlack(int x, int y)
{
    int r, g, b;
    mPicture2.GetRGB(x, y, r, g, b);
    return r == 0 && g == 0 && b == 0;
}




/** \brief Get the monochrome value of a pixel in the input image
 * Safe access to a pixel as monochrome. This function returns
 * black if x,y is outside the bounds of the picture.
 * \param x X location (column) in the image
 * \param y Y location (row) in the image. The top row is row 0
 * \returns Monochrome pixel at location (x, y)
 */
int CProcessor::GetMono(int x, int y)
{
    int r, g, b;
    GetRGB(x, y, r, g, b);
    return (r + g + b) / 3;
}


/** \brief Set the monochrome value of a pixel in the input image.
 * This is identical to calling SetRGB with the r, g, b values the same.
 * \param x X location (column) in the image
 * \param y Y location (row) in the image. The top row is row 0
 * \param gray Color to set. 0-255, but is clamped to that range.
 */
void CProcessor::SetMono(int x, int y, double gray)
{
    int igray = ByteRange(gray);
    SetRGB(x, y, igray, igray, igray);
}

/*!  \brief The entry point in the class for the thread.
 */

/*!  \brief Start the moments computation thread
 *
 * Do the moment analysis in a thread instead of
 *  in the main thread.
 * \param user An event handler that is using this functionality.
 * \param picture The image we are analyzing
 * \param progressId An id for a progress indication
 * \param  doneId An id for a done indication
 */
void CProcessor::AnalyzeInThread(wxEvtHandler *user, int progressId, int doneId)
{
    mUser = user;
    
    mProgressId = progressId;
    mDoneId = doneId;

    mActive = true;
    pthread_create(&mThread, NULL, ThreadEntry, (void *)this);
}

/*!  \brief The entry point in the class for the thread.
 */
void CProcessor::Thread()
{
    this->Process();
   
    // Create an event to indicate we are done
    wxCommandEvent event( wxEVT_COMMAND_MENU_SELECTED, mDoneId );
    
    // send in a thread-safe way
    wxPostEvent(mUser, event );
    
    mActive = false;
    pthread_exit(NULL);
}

/*! \brief This is the static entry point for the thread.
 * \param arg An anonymized pointer to this object
 * \returns NULL 
 */
void *CProcessor::ThreadEntry(void *arg)
{
    CProcessor *obj = (CProcessor *)arg;
    obj->Thread();
    return NULL;
}

/*! \brief End the thread if it is active.
 */
void CProcessor::EndThread()
{
    if(mActive)
    {
        pthread_join(mThread, NULL);
    }
}

/*! \brief Set the current progress in the calling program.
 * \param p The progress as a value from 0 to 1
 */
void CProcessor::Progress(double p)
{
    // We only do this if we have a user for this object.
    // This allows us to continue to use the object without
    // the thread as we did before when we add progress indicators.
    if(mUser != NULL)
    {
        // Create an event to indicate we are done
        wxCommandEvent event( wxEVT_COMMAND_MENU_SELECTED, mProgressId );
        event.SetInt(int(p * 1000));

        // send in a thread-safe way
        wxPostEvent(mUser, event );

    }
}
