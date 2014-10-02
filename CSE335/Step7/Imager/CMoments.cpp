/*
 * Name:     CMoments.cpp
 *
 *
 * Class:    CMoments
 * Header:   CMoments.h
 * Created : Nov 18, 2011
 * Author :  Charles B. Owen
 */

#include "wx/prec.h"
#include "CMoments.h"
#include "CPicture.h"

/** \brief Constructor */
CMoments::CMoments()
{
    // Until we compute anything
    mXbar = 0;
    mYbar = 0;
    mAngle = 0;
    mWidth = 0;
    mLength = 0;
    mUser = NULL;
    mPicture = NULL;
    mProgressId = 0;
    mDoneId = 0;
    mActive=false;
    mThread=0;
}

/** \brief Destructor */
CMoments::~CMoments()
{
}




/** \brief Compute the moment for an image.
 *
 * This function computes the i, y statistical moment for an
 * image. The computation is based on a gray scale equivalent of the
 * image. See : http://en.wikipedia.org/wiki/Image_moment
 * \param picture The picture we are analyzing
 * \param i The x'th moment we want to compute
 * \param j The y'th moment we want to compute
 * \returns The computed moment
 */
double CMoments::Moment(CPicture *picture, int i, int j)
{
    // Compute the moment
    double mij = 0;
    for(int y=0; y<mSize;  y++)
    {
        for(int x=0;  x<mSize;  x++)
        {
            int r, g, b;
            picture->GetRGB(x+mX0, y+mY0, r, g, b);
            double gray = (r + g + b) / (3.0 * 255.0);
            mij += pow(x, i) * pow(y, j) * gray;
        }
    }

    return mij;
}



/** \brief Analyze a picture, determining the moments information.
 *
 * There is a nice description of what this does at:
 * http://www.mukimuki.fr/flashblog/2009/05/20/magic-moments/
 * \param picture The picture to analyze
 * \returns No direct return value, but computed results are stored
 * as member variables.
 */
void CMoments::Analyze(CPicture *picture)
{
    // This only really works right for square images
    // So I'm going to determine the range we use in
    // each dimension to take a square subset
    int h = picture->GetHeight();
    int w = picture->GetWidth();
    mX0 = 0;
    mY0 = 0;
    if(w > h)
    {
        mX0 = (w - h) / 2;
        mSize = h;
    }
    else
    {
        mY0 = (h - w) / 2;
        mSize = w;
    }

    // Sum of all gray level values
    double m00 = Moment(picture, 0, 0);
    Progress(0.166);
  //  Update();
    // The x and y centroids for the image
    double xbar = Moment(picture, 1, 0) / m00;
    Progress(0.333);
    double ybar = Moment(picture, 0, 1) / m00;
    Progress(0.5);
    // Moments 20, 02, and 11
    double m20 = Moment(picture, 2, 0);
    Progress(0.667);
    double m02 = Moment(picture, 0, 2);
    Progress(0.833);
    double m11 = Moment(picture, 1, 1);
    Progress(1.0);

    double mu20p = m20 / m00 - xbar * xbar;
    double mu02p = m02 / m00 - ybar * ybar;
    double mu11p = m11 / m00 - xbar * ybar;

    mAngle = atan2(2 * mu11p, mu20p - mu02p) / 2;

    double avgmup = (mu20p + mu02p) / 2;
    double factor = sqrt(4 * mu11p * mu11p + (mu20p - mu02p)*(mu20p - mu02p)) / 2;

    mXbar = xbar + mX0;
    mYbar = ybar + mY0;
    mLength = 4 * sqrt(avgmup + factor);
    mWidth = 4 * sqrt(avgmup - factor);
}

/*!  \brief Start the moments computation thread
 *
 * Do the moment analysis in a thread instead of
 *  in the main thread.
 * \param user An event handler that is using this functionality.
 * \param picture The image we are analyzing
 * \param progressId An id for a progress indication
 * \param  doneId An id for a done indication
 */
void CMoments::AnalyzeInThread(wxEvtHandler *user, CPicture *picture, int progressId, int doneId)
{
    mUser = user;
    mPicture = picture;
    mProgressId = progressId;
    mDoneId = doneId;

    mActive = true;
    pthread_create(&mThread, NULL, ThreadEntry, (void *)this);
}

/*!  \brief The entry point in the class for the thread.
 */
void CMoments::Thread()
{
    Analyze(mPicture);
    
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
void *CMoments::ThreadEntry(void *arg)
{
    CMoments *obj = (CMoments *)arg;
    obj->Thread();
    return NULL;
}

/*! \brief End the thread if it is active.
 */
void CMoments::EndThread()
{
    if(mActive)
    {
        pthread_join(mThread, NULL);
    }
}

/*! \brief Set the current progress in the calling program.
 * \param p The progress as a value from 0 to 1
 */
void CMoments::Progress(double p)
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