/*
 * Name:     CProcessingDlg.cpp
 * The main image processing dialog box.
 *
 * This class creates a dialog box and dispatches images to an installed
 * image processing component.
 *
 * Class:    CProcessingDlg
 * Header:   CProcessingDlg.h
 * Created : Nov 14, 2011
 * Author :  Charles B. Owen
 */

#include "wx/prec.h"
#include "CProcessingDlg.h"
#include "CSpeech.h"

BEGIN_EVENT_TABLE(CProcessingDlg, wxDialog)
    EVT_BUTTON(ID_Ok, CProcessingDlg::OnOkButton)
    EVT_BUTTON(ID_Cancel, CProcessingDlg::OnCancelButton)
    EVT_IDLE(CProcessingDlg::OnIdle)
    EVT_MENU(ID_ThreadDone, CProcessingDlg::OnThreadDone)
    EVT_MENU(ID_Progress, CProcessingDlg::OnProgress)
END_EVENT_TABLE();

/** \brief Constructor
 * \param parent The parent window for the dialog box
 * \param processor The image processing component to use
 */
CProcessingDlg::CProcessingDlg(wxWindow *parent, CProcessor *processor) : wxDialog(parent, wxID_ANY, L"Processing",
        wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE), mProcessor(processor)
{
    mFirstIdle = true;

    // Create a vertical sizer so we have a top part of the box
    // for the options and a bottom part for the Ok and Cancel buttons
    wxBoxSizer* vSizer;
    vSizer = new wxBoxSizer( wxVERTICAL );

    mProgress = new CProgressCtrl(this, wxSize(400, 20));
    vSizer->Add(mProgress, 0, wxALL, 20);

    mText = new wxStaticText(this, wxID_ANY, L"Processing...", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    vSizer->Add(mText, 0, wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL | wxALL);

    // Create a horizontal sizer for the buttons
    wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
    vSizer->Add(hSizer, 1, wxALL| wxEXPAND);

    // Create an Ok button
    mOkButton = new wxButton( this, ID_Ok, L"Ok", wxDefaultPosition, wxDefaultSize, 0 );
    hSizer->Add(mOkButton, 1, wxALL | wxEXPAND, 10);
    mOkButton->SetDefault();
    mOkButton->Enable(false);

    // Create an Cancel button.
    mCancelButton = new wxButton( this, ID_Cancel, L"Cancel", wxDefaultPosition, wxDefaultSize, 0 );
    hSizer->Add(mCancelButton, 1, wxALL | wxEXPAND, 10);

    // Set the top level sizer and force the window to match the size
    this->SetSizer( vSizer );
    this->Layout();
    vSizer->Fit( this );
    mStopWatch.Start();
    mProcessor->AnalyzeInThread(this, ID_Progress, ID_ThreadDone);
}

/*! Destructor
 */
CProcessingDlg::~CProcessingDlg()
{
    // Destroy the processing component
    delete mProcessor;
}

/*! This function is called after the dialog box is created.
 * \param event The idle event
 */
void CProcessingDlg::OnIdle(wxIdleEvent &event)
{/*
    if(mFirstIdle)
    {
        mStopWatch.Start();
        
        mProcessor->Process();
        
        mText->SetLabel(wxString::Format(L"%d milliseconds", (int)mStopWatch.Time()));
#ifdef CSPEECH
        mProgress->ShutUp();
        speak << L"Processed in " << (int)mStopWatch.Time() << " milliseconds" << std::flush;
#endif
        
        mOkButton->Enable(true);
        mFirstIdle = false;
        
    }*/
}


/*! Handle a Cancel button press.
 * \param event The command event
 */
void CProcessingDlg::OnCancelButton(wxCommandEvent &event)
{
    mProcessor->EndThread();
    EndModal(wxCANCEL);
}


/*! Handle an Ok button press.
 * \param event The command event
 */
void CProcessingDlg::OnOkButton(wxCommandEvent &event)
{
    EndModal(wxOK);
}

/*! \brief Event handler called to indicate the thread has done it's work.
 * \param event The event from the thread
 */
void CProcessingDlg::OnThreadDone(wxCommandEvent &event)
{
    mText->SetLabel(wxString::Format(L"%d milliseconds", (int)mStopWatch.Time()));
    mOkButton->Enable(true);
    Update();
}

/*! \brief Handle an indication from the thread of progress.
 * \param event The event from the thread
 */
void CProcessingDlg::OnProgress(wxCommandEvent &event)
{
    mProgress->SetProgress(double(event.GetInt()) * 0.001);
    Update();
}