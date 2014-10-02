/*
 * Name:     CProcessor.h
 *
 *
 * Class:    CProcessor
 * Impl:     CProcessor.cpp
 * Created : Nov 15, 2011
 * Author :  Charles B. Owen
 */

#pragma once
#ifndef CPROCESSOR_H_
#define CPROCESSOR_H_

#include "CPicture.h"

/** \brief Abstract base class for any image processing component.
 *
 * Image processing components are derived from this class.
 */
class CProcessor
{
public:
    virtual ~CProcessor();

    /** \brief Get the result of the image processing operation
     * \returns Processed picture result. This is a new image. The original image
     * is not modified.
     */
    const CPicture *GetProcessedImage() const {return &mPicture2;}

    /** \brief Get the image width
     * \returns Image width in pixels
     */
    int GetWidth() const {return mPicture2.GetWidth();}

    /** \brief Get tjhe image height
     * \return Image height in pixels
     */
    int GetHeight() const {return mPicture2.GetHeight();}

    void GetRGB(int x, int y, int &r, int &g, int &b);
    void SetRGB(int x, int y, double r, double g, double b);
    int GetMono(int x, int y);
    void SetMono(int x, int y, double gray);
    bool IsSetBlack(int x, int y);

    /** \brief Entry point for image processing */
    virtual void Process() = 0;

    /** \brief Obtain a text name for this particular processor
     * \returns Name as an ascii string
     */
    virtual const wchar_t *Name() const = 0;

    /** \brief Obtain the filename for the input picture
     * \returns Filename
     */
    const wxFileName &GetFilename() const {return mFilename;}
    void Analyze(CPicture *picture);
    void AnalyzeInThread(wxEvtHandler *user, int progressId, int doneId);
    void EndThread();
    void Progress(double p);
protected:
    CProcessor(const CPicture *picture);
    bool GetTerminate() const {return mTerminate;}
private:
    void Thread();
    static void *ThreadEntry(void *arg);
    
    //! The user of this implementation when threaded
    wxEvtHandler *mUser;
    
    //! An id for indicating progress
    int mProgressId;

    //! An id for indicating we are done
    int mDoneId;

    //! Set true when the thread is active
    bool mActive;
    
    bool mTerminate;
    //! The thread handle
    pthread_t mThread;
    //! Disabled
    CProcessor();
    //! Disabled
    CProcessor(const CProcessor &);
    //! Disabled
    void operator=(const CProcessor &);

    CPicture mPicture1;     //!< Source picture for processing
    CPicture mPicture2;     //!< Destination for processed picture

    wxFileName mFilename;   //!< Filename for the image
};

#endif /* CPROCESSOR_H_ */
