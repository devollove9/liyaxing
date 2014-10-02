/*
 * Name:     CProcessingDlg.h
 *
 * The main image processing dialog box.
 *
 * This class creates a dialog box and dispatches images to an installed
 * image processing component.
 *
 *
 * Class:    CProcessingDlg
 * Impl:     CProcessingDlg.cpp
 * Created : Nov 14, 2011
 * Author :  Charles B. Owen
 */

#pragma once
#ifndef CPROCESSINGDLG_H_
#define CPROCESSINGDLG_H_

#include "CProgressCtrl.h"
#include "CProcessor.h"

/** \brief Processing dialog box class.
 *
 * Creates a dialog box and dispatches images to an image processing component.
 */
class CProcessingDlg : public wxDialog
{
public:
    CProcessingDlg(wxWindow *parent, CProcessor *processor);
    virtual ~CProcessingDlg();

    //! Control id values
    enum Ids {ID_Cancel, ID_Ok, ID_Progress, ID_ThreadDone};

    void OnOkButton(wxCommandEvent &event);
    void OnCancelButton(wxCommandEvent &event);
    void OnIdle(wxIdleEvent &event);
    void OnThreadDone(wxCommandEvent &event);
    void OnProgress(wxCommandEvent &event);
    // Don't put anything between this line and the next
    // private, protected, or public.
    DECLARE_EVENT_TABLE()

private:
    //! The progress control
    CProgressCtrl *mProgress;

    //! The cancel button
    wxButton *mCancelButton;

    //! The OK button
    wxButton *mOkButton;

    //! A text control were we put the timing information
    wxStaticText *mText;

    //! A stopwatch to time the process
    wxStopWatch mStopWatch;

    //! The processor we are testing
    CProcessor *mProcessor;

    //! Set true for the first Idle function call
    bool mFirstIdle;
};

#endif /* CPROCESSINGDLG_H_ */
