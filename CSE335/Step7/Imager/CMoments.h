/*
 * Name:     CMoments.h
 *
 *
 * Class:    CMoments
 * Impl:     CMoments.cpp
 * Created : Nov 18, 2011
 * Author :  Charles B. Owen
 */

#pragma once
#ifndef CMOMENTS_H_
#define CMOMENTS_H_
#include <pthread.h>
class CPicture;

/** \brief Class that calculates image moments
 *
 * Analyze a picture, determining the moments information.
 * There is a nice description of what this does at:
 * http://www.mukimuki.fr/flashblog/2009/05/20/magic-moments/
 */
class CMoments
{
public:
    CMoments();
    virtual ~CMoments();

    /** \brief The X centroid for the image
     * \returns X centroid
     */
    double GetXCentroid() const {return mXbar;}

    /** \brief The Y centroid for the image
     * \returns Y centroid
     */
    double GetYCentroid() const {return mYbar;}

    /** \brief The image fundamental angle
     * \returns The angle in radians
     */
    double GetAngle() const {return mAngle;}

    /** \brief The image length
     * \returns The length of the image in the fundamental direction
     */
    double GetLength() const {return mLength;}

    /** \brief The image width
     * \returns The width of the image relative to the fundamental direction
     */
    double GetWidth() const {return mWidth;}

    void Analyze(CPicture *picture);
    void AnalyzeInThread(wxEvtHandler *user, CPicture *picture, int progressId, int doneId);
    void EndThread();
    void Progress(double p);
private:
    double Moment(CPicture *picture, int i, int j);
    void Thread();
    static void *ThreadEntry(void *arg);
    
    //! The user of this implementation when threaded
    wxEvtHandler *mUser;

    //! The picture to analyze
    CPicture *mPicture;

    //! An id for indicating progress
    int mProgressId;

    //! An id for indicating we are done
    int mDoneId;

    //! Set true when the thread is active
    bool mActive;
    
    //! The thread handle
    pthread_t mThread;
    
    double mXbar;       //!< X centroid for the image
    double mYbar;       //!< Y centroid for the image
    double mAngle;      //!< The image fundamental angle
    double mLength;     //!< Shape length
    double mWidth;      //!< Shape width

    // Temporary values used by Moment()
    double mX0;         //!< Temporary X0
    double mY0;         //!< Temporary Y0
    double mSize;       //!< Temporary size holder
    
    
};

#endif /* CMOMENTS_H_ */
