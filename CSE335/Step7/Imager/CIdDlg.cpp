/*
 * Name:     CIdDlg.cpp
 *
 *
 * Class:    CIdDlg
 * Header:   CIdDlg.h
 * Created : Oct 26, 2011
 * Author :  Charles B. Owen
 */

#include "wx/prec.h"
#include "CIdDlg.h"
#include <sstream>

using namespace std;

BEGIN_EVENT_TABLE(CIdDlg, wxDialog)
EVT_BUTTON(ID_Ok, CIdDlg::OnOkButton)
EVT_BUTTON(ID_Cancel, CIdDlg::OnCancelButton)
END_EVENT_TABLE();

/** \brief Constructor
 * \param parent The parent window
 */
CIdDlg::CIdDlg(wxWindow *parent) :
    wxDialog(parent, wxID_ANY, L"Enter user ID",
             wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE)
{
    // Create a vertical sizer so we have a top part of the box
    // for the options and a bottom part for the Ok and Cancel buttons
    wxBoxSizer* vSizer;
    vSizer = new wxBoxSizer( wxVERTICAL );

    // Create the grid sizer for the controls that edit the parameters
    wxGridSizer *gSizer = new wxGridSizer(2);
    vSizer->Add(gSizer, 0, wxALL | wxEXPAND, 20);

    //
    // User ID
    //

    wxStaticText *label1 = new wxStaticText( this, wxID_ANY, L"User ID:", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
    gSizer->Add( label1, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL);

    // Create the text control
    mIdText = new wxTextCtrl( this, ID_Id, mId.c_str(), wxDefaultPosition, wxDefaultSize, 0 );
    gSizer->Add( mIdText, 0, wxALL);

    // and add it to the vertical sizer.
    wxBoxSizer *hSizer;
    hSizer = new wxBoxSizer(wxHORIZONTAL);
    vSizer->Add(hSizer, 0, wxALL | wxEXPAND);

    // Create an Ok button and add it to the horizontal sizer.
    mOkButton = new wxButton( this, ID_Ok, L"Ok", wxDefaultPosition, wxDefaultSize, 0 );
    hSizer->Add(mOkButton, 1, wxALL | wxEXPAND);
    mOkButton->SetDefault();

    // Create a Cancel button and add to the horizontal sizer
    mCancelButton = new wxButton( this, ID_Cancel, L"Cancel", wxDefaultPosition, wxDefaultSize, 0 );
    hSizer->Add(mCancelButton, 1, wxALL | wxEXPAND);

    // Set the top level sizer and force the window to match the size
    this->SetSizer( vSizer );
    this->Layout();
    vSizer->Fit( this );

    mIdText->SetFocus();

}

/** \brief Destructor */
CIdDlg::~CIdDlg()
{
}


/** \brief Handle an Ok button press event
 * \param event The associated event for the button press.
 */
void CIdDlg::OnOkButton(wxCommandEvent &event)
{
    mId = mIdText->GetValue().Trim();
    if(mId.empty())
    {
        wxMessageBox(L"User ID must not be empty!", L"Attention");
        mIdText->SetFocus();
        return;
    }

    EndModal(wxOK);
}


/** \brief Handle a cancel button press event
 * \param event The associated event for the button press.
 */
void CIdDlg::OnCancelButton(wxCommandEvent &event)
{
    EndModal(wxCANCEL);
}








