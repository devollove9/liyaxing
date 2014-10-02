/*
 * Name:     CProgressCtrl.h
 *
 *
 * Class:    CProgressCtrl
 * Impl:     CProgressCtrl.cpp
 * Created : Nov 14, 2011
 * Author :  Charles B. Owen
 */

#pragma once
#ifndef CPROGRESSCTRL_H_
#define CPROGRESSCTRL_H_

/** \brief A simple progress control for dialog boxes
 * 
 * This displays the progress of an operation as a horizontal thermometer bar
 */
class CProgressCtrl : public wxWindow
{
public:
    CProgressCtrl(wxWindow *parent, wxSize size);

    virtual ~CProgressCtrl();

    //! Control id values
    enum Ids {ID_Timer = 1};

    /** \brief Get the set progress value
     * \returns Progress in the range 0 to 1
     */
    double GetProgress() const {return mProgress;}

    /** \brief Set the progress value
     *
     * \param p The progres value in the range 0 to 1
     */
    void SetProgress(double p) {mProgress = p; Refresh();}
    
    /** \brief Turn off the spoken progress */
    void ShutUp() {mQuiet = true;}

    // Don't put anything between this line and the next
    // private, protected, or public.
    DECLARE_EVENT_TABLE()

private:
    CProgressCtrl();

    void OnPaint(wxPaintEvent &event);
    void OnTimer(wxTimerEvent &event);

    double mProgress;       //!< Current progress value 0-1
    wxTimer mTimer;          //!< A timer to support progress animation
    wxStopWatch mStopwatch;  //!< A stopwatch to control the animation speed

    int mLastTime;          //!< The time of the last stopwatch reading
    double mBarPos;         //!< Position of the progress bar
    double mHandPos;        //!< Position of the hand in the progress bar

    wxBitmap mBar;           //!< Bitmap image for the progress bar
    wxBitmap mHand;          //!< Bitmap image for the hand
    
    int mSpeakCount;         //!< Variable to support speaking the progress
    bool mQuiet;             //!< Support for turning the spoken progress off
};

#endif /* CPROGRESSCTRL_H_ */
