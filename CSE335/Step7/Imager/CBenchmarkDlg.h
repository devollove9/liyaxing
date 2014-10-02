/*
 * Name:     CBenchmarkDlg.h
 *
 *
 * Class:    CBenchmarkDlg
 * Impl:     CBenchmarkDlg.cpp
 * Created : Nov 14, 2011
 * Author :  Charles B. Owen
 */

#pragma once
#ifndef CBENCHMARKDLG_H_
#define CBENCHMARKDLG_H_

#include "CProgressCtrl.h"
#include "CProcessor.h"

/** \brief Dialog box for benchmarking parallel implementations
 * 
 * This dialog box accepts a base (reference) implementation and a parallelized
 * implementation and compares the two by running them 10 times each.
 */
class CBenchmarkDlg : public wxDialog
{
public:
    CBenchmarkDlg(wxWindow *parent, CProcessor *processor1, CProcessor *processor2);
    virtual ~CBenchmarkDlg();

    //! The control id values
    enum Ids {ID_Cancel, ID_Ok, ID_Submit};

    void OnOkButton(wxCommandEvent &event);
    void OnSubmitButton(wxCommandEvent &event);
    void OnIdle(wxIdleEvent &event);

    // Don't put anything between this line and the next
    // private, protected, or public.
    DECLARE_EVENT_TABLE()

private:
    CProgressCtrl *mProgress;   //!< The progress control
    wxButton *mOkButton;        //!< Okay button control
    wxButton *mSubmitButton;    //!< Submit button control
    wxStaticText *mSuccess;     //!< Success indicator
    wxStaticText *mText;        //!< Display text
    wxStaticText *mText2;       //!< Second line of display text

    int         mIterations;    //!< Iterations counter

    CProcessor *mProcessor1;    //!< Base processor to compare against
    CProcessor *mProcessor2;    //!< New processor we are benchmarking

    double mScore;              //!< Computed score

    bool mFirstIdle;            //!< Indication of first call it idle
};

#endif /* CBENCHMARKDLG_H_ */
