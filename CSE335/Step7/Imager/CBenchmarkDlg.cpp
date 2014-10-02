/*
 * Name:     CBenchmarkDlg.cpp
 *
 *
 * Class:    CBenchmarkDlg
 * Header:   CBenchmarkDlg.h
 * Created : Nov 14, 2011
 * Author :  Charles B. Owen
 */

#include "wx/prec.h"
#include "CBenchmarkDlg.h"
#include <unistd.h>
#include <cstdlib>
#include "wx/protocol/http.h"
#include "CIdDlg.h"
#include "CSpeech.h"

BEGIN_EVENT_TABLE(CBenchmarkDlg, wxDialog)
EVT_BUTTON(ID_Ok, CBenchmarkDlg::OnOkButton)
EVT_BUTTON(ID_Submit, CBenchmarkDlg::OnSubmitButton)
EVT_INIT_DIALOG(CBenchmarkDlg::OnInitDialog)
EVT_IDLE(CBenchmarkDlg::OnIdle)
END_EVENT_TABLE();

/** \brief Constructor
 * \param parent The parent window
 * \param processor1 The base (reference) processor
 * \param processor2 The processor to test
 */
CBenchmarkDlg::CBenchmarkDlg(wxWindow *parent, CProcessor *processor1, CProcessor *processor2) :
        wxDialog(parent, wxID_ANY, L"Processor Benchmark",
        wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE),
        mProcessor1(processor1), mProcessor2(processor2)
{
    mFirstIdle = true;
    mIterations = 10;

    // Create a vertical sizer so we have a top part of the box
    // for the options and a bottom part for the Ok and Cancel buttons
    wxBoxSizer* vSizer;
    vSizer = new wxBoxSizer( wxVERTICAL );

    mProgress = new CProgressCtrl(this, wxSize(400, 20));
    vSizer->Add(mProgress, 0, wxALL, 20);

    mSuccess = new wxStaticText(this, wxID_ANY, L"", wxDefaultPosition, wxDefaultSize,
            wxALIGN_CENTRE);
    vSizer->Add(mSuccess, 0, wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL | wxALL);

    mText = new wxStaticText(this, wxID_ANY, L"                                                                  ",
            wxDefaultPosition, wxDefaultSize,
            wxALIGN_CENTER);
    vSizer->Add(mText, 0, wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL | wxALL);

    mText2 = new wxStaticText(this, wxID_ANY, L"", wxDefaultPosition, wxDefaultSize,
            wxALIGN_CENTER);
    vSizer->Add(mText2, 0, wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL | wxALL);

    // Create a horizontal sizer for the buttons
    wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
    vSizer->Add(hSizer, 1, wxALL| wxEXPAND);

    // Create an Ok button
    mOkButton = new wxButton( this, ID_Ok, L"Ok", wxDefaultPosition, wxDefaultSize, 0 );
    hSizer->Add(mOkButton, 1, wxALL | wxEXPAND, 10);
    mOkButton->SetDefault();

    mSubmitButton = new wxButton( this, ID_Submit, L"Submit", wxDefaultPosition, wxDefaultSize, 0 );
    hSizer->Add(mSubmitButton, 1, wxALL | wxEXPAND, 10);
    mSubmitButton->Enable(false);

    // Set the top level sizer and force the window to match the size
    this->SetSizer( vSizer );
    this->Layout();
    vSizer->Fit( this );
}

/** \brief Destructor */
CBenchmarkDlg::~CBenchmarkDlg()
{
    delete mProcessor1;
    delete mProcessor2;
}

/** \brief Handle the idle event.
 *
 * All actual processing is done in the idle event to ensure
 * the dialog box has been created and is displayed.
 * \param event The idle event
 */
void CBenchmarkDlg::OnIdle(wxIdleEvent &event)
{
    if(mFirstIdle)
    {
        mFirstIdle = false;

        wxStopWatch baseTime;
        baseTime.Start();
        baseTime.Pause();
        
        long bestBase = 1000000000;

        wxStopWatch modTime;
        modTime.Start();
        modTime.Pause();
        
        long bestMod = 1000000000;

        for(int i=0;  i<mIterations;  i++)
        {
            mText->SetLabel(L"Base processor processing...");
#ifdef CSPEECH
        speak << L"Base processor processing..." << std::flush;
#endif
            this->Layout();
            Update();

            baseTime.Start();
            mProcessor1->Process();
            long t = baseTime.Time();
            if(t < bestBase)
            {
                bestBase = t;
            }

            mText->SetLabel(L"Modified processor processing...");
#ifdef CSPEECH
        speak << L"Modified processor processing..." << std::flush;
#endif
            mProgress->SetProgress(double(i) / double(mIterations));
            this->Layout();
            Update();

            modTime.Start();
            mProcessor2->Process();
            t = modTime.Time();
            if(t < bestMod)
            {
                bestMod = t;
            }

            mProgress->SetProgress(double(i * 2 + 1) / double(mIterations * 2));
            this->Layout();
            Update();

            // Compare the results
            const CPicture *p1 = mProcessor1->GetProcessedImage();
            const CPicture *p2 = mProcessor2->GetProcessedImage();

            // Are they the same size?
            bool fail = true;
            int cnt;
            if(p1->GetWidth() != p2->GetWidth())
            {
                mText->SetLabel(wxString::Format(L"Images are not the same width!  Is %d, should be %d", p2->GetWidth(), p1->GetWidth()));
#ifdef CSPEECH
        speak << mText->GetLabel() << std::flush;
#endif
            }
            else if(p1->GetHeight() != p2->GetHeight())
            {
                mText->SetLabel(wxString::Format(L"Images are not the same height!  Is %d, should be %d", p2->GetHeight(), p1->GetHeight()));
#ifdef CSPEECH
        speak << mText->GetLabel() << std::flush;
#endif
            }
            else if((cnt = p1->Compare(p2)) > 0)
            {
                mText->SetLabel(wxString::Format(L"Images are not the same!  They differ in %d pixels", cnt));
#ifdef CSPEECH
        speak << mText->GetLabel() << std::flush;
#endif
            }
            else
            {
                fail = false;
            }

            if(fail)
            {
                mSuccess->SetLabel(L"FAIL!");
                mProgress->SetProgress(0);
                return;
            }
        }
        
#ifdef CSPEECH
        mProgress->ShutUp();
#endif

        double t1 = bestBase * 0.001;
        double t2 = bestMod * 0.001;

        // Determine number of cores
        int c = sysconf(_SC_NPROCESSORS_ONLN);

        double factor = (t2 * c) / t1;
        mScore = factor;

        mText->SetLabel(wxString::Format(L"Base time: %g/Modified time: %g", t1, t2));
        mText2->SetLabel(wxString::Format(L"Number of processors: %d, Benchmark factor: %g", c, factor));
#ifdef CSPEECH
        speak << mText->GetLabel() << L" " << mText2->GetLabel() << " success" << std::flush;
#endif

        mSubmitButton->Enable(true);

        mSuccess->SetLabel(L"Success!");
        mProgress->SetProgress(1);
        Update();
        this->Layout();
    }
}



/** \brief Handle an Ok button press.
 * \param event The command event
 */
void CBenchmarkDlg::OnOkButton(wxCommandEvent &event)
{
    EndModal(wxOK);
}



/** \brief Handle an Ok button press.
 * \param event The command event
 */
void CBenchmarkDlg::OnSubmitButton(wxCommandEvent &event)
{
    wxString user = wxString::FromAscii(getenv("USER"));
    if(user == L"student")
    {
        CIdDlg dlg(this);
        if(dlg.ShowModal() != wxOK)
        {
            return;
        }

        user = dlg.GetId();
    }

    // Get the information we need into a get string
    wxString hostSys=L"www.cse.msu.edu";
    wxString url = L"/~cbowen/335/contest.php?";
    url += L"user=";
    url += user;

    char host[100];
    gethostname(host, sizeof(host));
    url += L"&host=";
    url += wxString::FromAscii(host);

    url += L"&file=";
    url += mProcessor1->GetFilename().GetFullName();

    int c = sysconf(_SC_NPROCESSORS_ONLN);
    url += wxString::Format(L"&cores=%d&score=%g&magic=335ma&proc=", c, mScore);
    url += mProcessor1->Name();

    mSubmitButton->Enable(false);

    wxHTTP http;
    http.SetHeader(_T("Content-type"), _T("text/html; charset=utf-8"));
    if(!http.Connect(hostSys))
    {
        wxMessageBox(L"Unable to connect to contest server", L"Failure");
    }

    http.GetInputStream(url);
    if(http.GetError() != wxPROTO_NOERR)
    {
        wxMessageBox(L"Unable to communicate with contest server", L"Failure");
    }
}


