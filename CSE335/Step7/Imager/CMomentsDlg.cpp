/*
 * Name:     CMomentsDlg.cpp
 *
 *
 * Class:    CMomentsDlg
 * Header:   CMomentsDlg.h
 * Created : Nov 14, 2011
 * Author :  Charles B. Owen
 */

#include "wx/prec.h"
#include "CMomentsDlg.h"
#include "CDocument.h"
#include "CSpeech.h"

BEGIN_EVENT_TABLE(CMomentsDlg, wxDialog)
EVT_BUTTON(ID_Ok, CMomentsDlg::OnOkButton)
EVT_BUTTON(ID_Cancel, CMomentsDlg::OnCancelButton)
EVT_IDLE(CMomentsDlg::OnIdle)
EVT_MENU(ID_ThreadDone, CMomentsDlg::OnThreadDone)
EVT_MENU(ID_Progress, CMomentsDlg::OnProgress)        
END_EVENT_TABLE();

/** \brief Constructor
 *
 * Constructor for the moments calculation dialog box
 * \param parent The parent window for the dialog box
 * \param document The document (image) we are analyzing
 */
CMomentsDlg::CMomentsDlg(wxWindow *parent, CDocument *document) : wxDialog(parent, wxID_ANY, L"Computing Image Moments",
        wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE), mDocument(document)
{
    mFirstIdle = true;

    // Create a vertical sizer so we have a top part of the box
    // for the options and a bottom part for the Ok and Cancel buttons
    wxBoxSizer* vSizer;
    vSizer = new wxBoxSizer( wxVERTICAL );

    mProgress = new CProgressCtrl(this, wxSize(400, 20));
    vSizer->Add(mProgress, 0, wxALL, 20);

    mText = new wxStaticText(this, wxID_ANY, L"Analyzing...", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    vSizer->Add(mText, 0, wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL | wxALL);

    // Create a horizontal sizer for the buttons
    wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
    vSizer->Add(hSizer, 1, wxALL| wxEXPAND);

    // Create an Ok button
    mOkButton = new wxButton( this, ID_Ok, L"Ok", wxDefaultPosition, wxDefaultSize, 0 );
    hSizer->Add(mOkButton, 1, wxALL | wxEXPAND, 10);
    mOkButton->Enable(false);
    mOkButton->SetDefault();

    // Create an Cancel button.
    mCancelButton = new wxButton( this, ID_Cancel, L"Cancel", wxDefaultPosition, wxDefaultSize, 0 );
    hSizer->Add(mCancelButton, 1, wxALL | wxEXPAND, 10);

    // Set the top level sizer and force the window to match the size
    this->SetSizer( vSizer );
    this->Layout();
    vSizer->Fit( this );
    mStopWatch.Start();
    mMoments.AnalyzeInThread(this, mDocument, ID_Progress, ID_ThreadDone);
}

/** \brief Destructor
 */
CMomentsDlg::~CMomentsDlg()
{
}



/** \brief Function called when the system is idle.
 *
 * This function is called when the window system is idle. I put
 * the processing code here so we will know the dialog box has
 * been created and displayed. It's not the best place, for sure.
 * \param event The idle event
 */
void CMomentsDlg::OnIdle(wxIdleEvent &event)
{/*
    if(mFirstIdle)
    {
        // Only do this once!
        mFirstIdle = false;
        
        // Start a stopwatch we will use for timing.
        mStopWatch.Start();
        
        // Compute the image moments
        mMoments.Thread();
        

        // We are done. Indicate the computation time
        mText->SetLabel(wxString::Format(L"%d milliseconds", (int)mStopWatch.Time()));
        
#ifdef CSPEECH
        mProgress->ShutUp();
        speak << L"Computed moments in " << (int)mStopWatch.Time() << " milliseconds" <<
                L" centroid " << mMoments.GetXCentroid() << " comma " << mMoments.GetYCentroid() <<
                L" angle " << mMoments.GetAngle() << " length " << mMoments.GetLength() <<
                L" width " << mMoments.GetWidth() << std::flush;
#endif

        // Enable the ok button
        mOkButton->Enable(true);
    }*/
}


/** \brief Handle a Cancel button press.
 * \param event The command event
 */
void CMomentsDlg::OnCancelButton(wxCommandEvent &event)
{
    mMoments.EndThread();
    EndModal(wxCANCEL);
}


/** \brief Handle on Ok button press.
 * \param event The command event
 */
void CMomentsDlg::OnOkButton(wxCommandEvent &event)
{
    // Set the moments in the document.
    mDocument->SetMoments(mMoments.GetXCentroid(), mMoments.GetYCentroid(),
            mMoments.GetAngle(), mMoments.GetLength(), mMoments.GetWidth());

    EndModal(wxOK);
}

/*! \brief Event handler called to indicate the thread has done it's work.
 * \param event The event from the thread
 */
void CMomentsDlg::OnThreadDone(wxCommandEvent &event)
{
    mText->SetLabel(wxString::Format(L"%d milliseconds", (int)mStopWatch.Time()));
    mOkButton->Enable(true);  
    Update();
}

/*! \brief Handle an indication from the thread of progress.
 * \param event The event from the thread
 */
void CMomentsDlg::OnProgress(wxCommandEvent &event)
{
    mProgress->SetProgress(double(event.GetInt()) * 0.001);
    Update();
}