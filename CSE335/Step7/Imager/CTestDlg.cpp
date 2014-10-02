/*
 * Name:     CTestDlg.cpp
 *
 *
 * Class:    CTestDlg
 * Header:   CTestDlg.h
 * Created : Nov 14, 2011
 * Author :  Charles B. Owen
 */

#include "wx/prec.h"
#include "CTestDlg.h"
#include "CSpeech.h"

BEGIN_EVENT_TABLE(CTestDlg, wxDialog)
EVT_BUTTON(ID_Ok, CTestDlg::OnOkButton)
EVT_INIT_DIALOG(CTestDlg::OnInitDialog)
EVT_IDLE(CTestDlg::OnIdle)
END_EVENT_TABLE();

/** \brief Constructor
 * \param parent The parent window
 * \param processor1 The base processor to compare against
 * \param processor2 The processor under test
 */
CTestDlg::CTestDlg(wxWindow *parent, CProcessor *processor1, CProcessor *processor2) :
        wxDialog(parent, wxID_ANY, L"Processor Test",
        wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE),
        mProcessor1(processor1), mProcessor2(processor2)
{
    mFirstIdle = true;

    // Create a vertical sizer so we have a top part of the box
    // for the options and a bottom part for the Ok and Cancel buttons
    wxBoxSizer* vSizer;
    vSizer = new wxBoxSizer( wxVERTICAL );

    mProgress = new CProgressCtrl(this, wxSize(400, 20));
    vSizer->Add(mProgress, 0, wxALL, 20);

    mSuccess = new wxStaticText(this, wxID_ANY, L"", wxDefaultPosition, wxDefaultSize,
            wxALIGN_CENTRE);
    vSizer->Add(mSuccess, 0, wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL | wxALL);

    mText = new wxStaticText(this, wxID_ANY, L"Processing...", wxDefaultPosition, wxDefaultSize,
            wxALIGN_CENTER);
    vSizer->Add(mText, 0, wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL | wxALL);

    // Create a horizontal sizer for the buttons
    wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
    vSizer->Add(hSizer, 1, wxALL| wxEXPAND);

    // Create an Ok button
    mOkButton = new wxButton( this, ID_Ok, L"Ok", wxDefaultPosition, wxDefaultSize, 0 );
    hSizer->Add(mOkButton, 1, wxALL | wxEXPAND, 10);
    mOkButton->SetDefault();

    // Set the top level sizer and force the window to match the size
    this->SetSizer( vSizer );
    this->Layout();
    vSizer->Fit( this );
}

/** \brief Destructor */
CTestDlg::~CTestDlg()
{
    delete mProcessor1;
    delete mProcessor2;
}

/** \brief Idle event handler */
void CTestDlg::OnIdle(wxIdleEvent &event)
{
    if(mFirstIdle)
    {
        mFirstIdle = false;
        mText->SetLabel(L"Base processor processing...");
#ifdef CSPEECH
        speak << mText->GetLabel() << std::flush;
#endif
        this->Layout();
        Update();

        mProcessor1->Process();

        mText->SetLabel(L"Modified processor processing...");
#ifdef CSPEECH
        speak << mText->GetLabel() << std::flush;
#endif
        mProgress->SetProgress(0.5);
        this->Layout();
        Update();

        mProcessor2->Process();
        mProgress->SetProgress(1.0);

        // Compare the results
        const CPicture *p1 = mProcessor1->GetProcessedImage();
        const CPicture *p2 = mProcessor2->GetProcessedImage();

#ifdef CSPEECH
        mProgress->ShutUp();
#endif
        // Are they the same size?
        bool fail = true;
        int cnt;
        if(p1->GetWidth() != p2->GetWidth())
        {
            mText->SetLabel(wxString::Format(L"Images are not the same width!  Is %d, should be %d", p2->GetWidth(), p1->GetWidth()));
#ifdef CSPEECH
        speak << mText->GetLabel() << L" fail" << std::flush;
#endif
        }
        else if(p1->GetHeight() != p2->GetHeight())
        {
            mText->SetLabel(wxString::Format(L"Images are not the same height!  Is %d, should be %d", p2->GetHeight(), p1->GetHeight()));
#ifdef CSPEECH
        speak << mText->GetLabel() << L" fail" << std::flush;
#endif
        }
        else if((cnt = p1->Compare(p2)) > 0)
        {
            mText->SetLabel(wxString::Format(L"Images are not the same!  They differ in %d pixels", cnt));
#ifdef CSPEECH
        speak << mText->GetLabel() << L" fail" << std::flush;
#endif
        }
        else
        {
            fail = false;
            mText->SetLabel(L"The processors produced identical images");
#ifdef CSPEECH
        speak << mText->GetLabel() << L" success" << std::flush;
#endif
        }


        if(fail)
            mSuccess->SetLabel(L"FAIL!");
        else
            mSuccess->SetLabel(L"Success!");
        this->Layout();
    }
}



/** \brief Handle an Ok button press.
 * \param event The command event
 */
void CTestDlg::OnOkButton(wxCommandEvent &event)
{
    EndModal(wxOK);
}

