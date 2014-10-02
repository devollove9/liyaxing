/*
 * Name:     CIdDlg.h
 * This dialog box supports the entry of a user id if running under
 * the student account.
 *
 * Class:    CIdDlg
 * Impl:     CIdDlg.cpp
 * Created : Oct 26, 2011
 * Author :  Charles B. Owen
 */

#pragma once
#ifndef CIDDLG_H_
#define CIDDLG_H_

#include <string>

/**
 * \brief Dialog box for entry of a user id
 *
 * This dialog box is used when the user ID for the system comes up
 * as "student", which is the case for the virtual machine. It allows
 * the student to enter an actual user ID.
 * 
 */
class CIdDlg : public wxDialog
{
public:
    CIdDlg(wxWindow *parent);

    virtual ~CIdDlg();

    //! Id values for our controls
    enum Ids {ID_Ok, ID_Cancel, ID_Id};

    void OnOkButton(wxCommandEvent &event);
    void OnCancelButton(wxCommandEvent &event);

    /** Set the id string
     * \param str New id to set
     */
    void SetId(const std::wstring &str) {mId = str;}

    /** Get the id string
     * \returns Current id string
     */
    const std::wstring &GetId() const {return mId;}

    // Don't put anything between this line and the next
    // private, protected, or public.
    DECLARE_EVENT_TABLE()

private:
    CIdDlg();

    std::wstring    mId;        //!< Entered id value

    wxTextCtrl *mIdText;        //!< Text control
    wxButton *mOkButton;        //!< Ok button control
    wxButton *mCancelButton;    //!< Cancel button control
};

#endif /* CIDDLG_H_ */
