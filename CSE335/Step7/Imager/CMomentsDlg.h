/*
 * Name:     CMomentsDlg.h
 * Dialog box class for the image moments computation.
 *
 * Class:    CMomentsDlg
 * Impl:     CMomentsDlg.cpp
 * Created : Nov 14, 2011
 * Author :  Charles B. Owen
 */

#pragma once
#ifndef CMOMENTSDLG_H_
#define CMOMENTSDLG_H_

#include "CProgressCtrl.h"
#include "CProcessor.h"
#include "CMoments.h"

class CDocument;

/** \brief Moments calculation dialog box
 * 
 * This dialog box dispatches the picture to the moments calculation
 * component of type CMoments.
 */
class CMomentsDlg : public wxDialog
{
public:
    CMomentsDlg(wxWindow *parent, CDocument *document);
    virtual ~CMomentsDlg();

    //! The control id values
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
    CProgressCtrl *mProgress;   //!< The progress indicator control
    wxButton *mCancelButton;    //!< Cancel button control
    wxButton *mOkButton;        //!< OK button control
    wxStaticText *mText;        //!< Text to display control
    wxStopWatch mStopWatch;     //!< Stopwatch to support timing

    CDocument *mDocument;       //!< The document we are working on
    CMoments mMoments;          //!< The moments calculator class

    bool mFirstIdle;           //!< Flag indicating the first time idle is called
};

#endif /* CMOMENTSDLG_H_ */
