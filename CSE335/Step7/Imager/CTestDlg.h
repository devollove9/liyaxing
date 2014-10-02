/*
 * Name:     CTestDlg.h
 *
 *
 * Class:    CTestDlg
 * Impl:     CTestDlg.cpp
 * Created : Nov 14, 2011
 * Author :  Charles B. Owen
 */

#pragma once
#ifndef CTESTDLG_H_
#define CTESTDLG_H_

#include "CProgressCtrl.h"
#include "CProcessor.h"

/** \brief Testing dialog box
 * 
 * This box accepts a base image processor and a version under test and
 * compares the output to ensure the test version is working identically
 * to the original.
 */
class CTestDlg : public wxDialog
{
public:
    CTestDlg(wxWindow *parent, CProcessor *processor1, CProcessor *processor2);
    virtual ~CTestDlg();

    //! Id values for controls
    enum Ids {ID_Cancel, ID_Ok};

    void OnOkButton(wxCommandEvent &event);
    void OnIdle(wxIdleEvent &event);

    // Don't put anything between this line and the next
    // private, protected, or public.
    DECLARE_EVENT_TABLE()

private:
    CProgressCtrl *mProgress;       //!< Progress indicator control
    wxButton *mOkButton;            //!< Okay button control
    wxStaticText *mSuccess;         //!< Success indicator control
    wxStaticText *mText;            //!< Text indicator control

    CProcessor *mProcessor1;        //!< First processor to test
    CProcessor *mProcessor2;        //!< Second processor to test

    bool mFirstIdle;                //!< Bool to determine the first call to the idle routine
};

#endif /* CTESTDLG_H_ */
