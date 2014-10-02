/*
 * Name:     CFrame.cpp
 * This is the main program frame. It owns the menus and all child windows.
 * In this application it also owns the document.
 *
 * Class:    CFrame
 * Header:   CFrame.h
 * Created : Feb 20, 2010
 * Author :  Charles B. Owen - Initial distributed version
 */

#include "wx/prec.h"
#include <string>
#include <unistd.h>

#include "CFrame.h"
#include "CDocument.h"
#include "CMomentsDlg.h"
#include "CProcessingDlg.h"
#include "CTestDlg.h"
#include "CBaseBlackAndWhite.h"
#include "CBaseEmboss.h"
#include "CBaseCanny.h"
#include "CBlackAndWhite.h"
#include "CEmboss.h"
#include "CCanny.h"
#include "CBenchmarkDlg.h"
#include "CSpeech.h"

using namespace std;

BEGIN_EVENT_TABLE(CFrame, wxFrame)
    EVT_MENU(ID_Exit, CFrame::OnExit)
    EVT_MENU(ID_About, CFrame::OnAbout)
    EVT_MENU(ID_FileOpen, CFrame::OnFileOpen)
    EVT_MENU(ID_AnalyzeMoments, CFrame::OnAnalyzeMoments)
    EVT_MENU(ID_BaseBW, CFrame::OnBase)
    EVT_MENU(ID_BaseEmboss, CFrame::OnBase)
    EVT_MENU(ID_BaseCanny, CFrame::OnBase)

    EVT_MENU(ID_ModifiedBW, CFrame::OnModified)
    EVT_MENU(ID_ModifiedEmboss, CFrame::OnModified)
    EVT_MENU(ID_ModifiedCanny, CFrame::OnModified)

    EVT_MENU(ID_TestBW, CFrame::OnTest)
    EVT_MENU(ID_TestEmboss, CFrame::OnTest)
    EVT_MENU(ID_TestCanny, CFrame::OnTest)

    EVT_MENU(ID_BenchmarkBW, CFrame::OnBenchmark)
    EVT_MENU(ID_BenchmarkEmboss, CFrame::OnBenchmark)
    EVT_MENU(ID_BenchmarkCanny, CFrame::OnBenchmark)

    EVT_MENU(ID_Zoom25, CFrame::OnZoom25)
    EVT_MENU(ID_Zoom50, CFrame::OnZoom50)
    EVT_MENU(ID_Zoom100, CFrame::OnZoom100)
    EVT_MENU(ID_ZoomFit, CFrame::OnZoomFit)
END_EVENT_TABLE();

/** \brief Constructor for frame.
 */
CFrame::CFrame() : wxFrame( NULL, -1, L"Imager Picture Editing Application",
        wxPoint(100, 100), wxDefaultSize)
{
    //
    // File menu
    //

    wxMenu *menuFile = new wxMenu;

    menuFile->Append(ID_FileOpen, L"&Open");
    menuFile->Append(ID_About, L"&About");
    menuFile->AppendSeparator();
    wxMenuItem *exitItem = menuFile->Append( ID_Exit, L"E&xit" );
    exitItem->SetHelp(L"Exit the program");

    //
    // Zoom menu
    //

    wxMenu *menuZoom = new wxMenu;
    menuZoom->Append(ID_ZoomFit, L"&Fit");
    menuZoom->AppendSeparator();
    menuZoom->Append(ID_Zoom100, L"&100%");
    menuZoom->Append(ID_Zoom50, L"&50%");
    menuZoom->Append(ID_Zoom25, L"&25%");

    //
    // Analyze menu
    //

    wxMenu *menuAnalyze = new wxMenu;
    menuAnalyze->Append(ID_AnalyzeMoments, L"&Moments");

    //
    // Base menu
    //

    wxMenu *menuProcess = new wxMenu;
    menuProcess->Append(ID_BaseBW, L"&Black and White");
    menuProcess->Append(ID_BaseEmboss, L"&Emboss");
    menuProcess->Append(ID_BaseCanny, L"&Canny");

    //
    // Modified menu
    //

    wxMenu *menuModified = new wxMenu;
    menuModified->Append(ID_ModifiedBW, L"&Black and White");
    menuModified->Append(ID_ModifiedEmboss, L"&Emboss");
    menuModified->Append(ID_ModifiedCanny, L"&Canny");

    //
    // Test menu
    //

    wxMenu *menuTest = new wxMenu;
    menuTest->Append(ID_TestBW, L"&Black and White");
    menuTest->Append(ID_TestEmboss, L"&Emboss");
    menuTest->Append(ID_TestCanny, L"&Canny");

    //
    // Benchmark menu
    //

    wxMenu *menuBenchmark = new wxMenu;
    menuBenchmark->Append(ID_BenchmarkBW, L"&Black and White");
    menuBenchmark->Append(ID_BenchmarkEmboss, L"&Emboss");
    menuBenchmark->Append(ID_BenchmarkCanny, L"&Canny");

    //
    // Menu Bar
    //

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, L"&File");
    menuBar->Append( menuZoom, L"&Zoom");
    menuBar->Append(menuAnalyze, L"&Analyze");
    menuBar->Append(menuProcess, L"&Base");
    menuBar->Append(menuModified, L"&Modified");
    menuBar->Append(menuTest, L"&Test");
    menuBar->Append(menuBenchmark, L"&Benchmark");

    SetMenuBar( menuBar );

    //
    // Create a status bar
    //

    CreateStatusBar();
    SetStatusText(L"");

    //
    // Create the child windows
    //

    mViewEdit = new CViewEdit(this);

    //
    // Create the sizers
    //

    // A vertical sizer so we an put two windows on top of each other
    wxBoxSizer *vertSizer = new wxBoxSizer(wxVERTICAL);

    vertSizer->Add(mViewEdit, 1, wxEXPAND | wxALL, 0);     // Add edit view as second in horzSizer

    SetSizer(vertSizer);
    vertSizer->Fit(this);
    mViewEdit->SetMinSize(wxSize(100, 100));

    //
    // Determine number of cores
    //

    int c = sysconf(_SC_NPROCESSORS_ONLN);
    if(c < 2)
    {
        wxMessageDialog dlg(this, L"Your system only has one available core. This assignment must be completed on a machine with at least two cores.", L"Insufficient Cores", wxOK | wxICON_HAND);
        dlg.ShowModal();
    }
    
#ifdef CSPEECH
    CSpeech::Get().AddMenu(this);
#endif
}

/** \brief CFrame destructor.
 *
 * Destroys anything this class owns.
 */
CFrame::~CFrame()
{
    DestroyChildren();

}



/** \brief Select a 25% zoom factor */
void CFrame::OnZoom25(wxCommandEvent &event)
{
    mViewEdit->SetZoom(0.25);
}

/** \brief Select a 50% zoom factor */
void CFrame::OnZoom50(wxCommandEvent &event)
{
    mViewEdit->SetZoom(0.5);

}

/** \brief Select a 100% zoom factor */
void CFrame::OnZoom100(wxCommandEvent &event)
{
    mViewEdit->SetZoom(1);

}

/** \brief Select a zoom factor that fits the window. */
void CFrame::OnZoomFit(wxCommandEvent &event)
{
    mViewEdit->FitZoom();
}




/** \brief This function is called when an the file open option is selected.
 * \param event An object that describes the event.
 */
void CFrame::OnFileOpen(wxCommandEvent& event)
{
    wxFileDialog dlg(this, L"Open JPEG File", L"", L"", L"JPEG files (*.jpg;*.JPG)|*.jpg;*.JPG", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    dlg.SetDirectory(L"images");
    if(dlg.ShowModal() != wxID_OK)
        return;

    wstring filename = dlg.GetPath().wc_str();
    if(!mDocument.LoadFile(filename))
    {
        wxMessageBox(L"Unable to load image file",
                L"Imager error",
                wxOK | wxICON_INFORMATION, this);
    }
    else
    {
        mViewEdit->FitZoom();
    }
}


/** \brief Handler for the Analyze/Moments menu option
 * \param event An object that describes the event
 */
void CFrame::OnAnalyzeMoments(wxCommandEvent &event)
{
    // Create the moments calculation dialog box
    CMomentsDlg dlg(this, GetDocument());
    dlg.ShowModal();
}

/** \brief Handler for Base menu options
 *
 * Handle any menu selection from the Base menu
 * \param event An object that describes the event
 */
void CFrame::OnBase(wxCommandEvent &event)
{
    // Create a processor to use
    CProcessor *processor = NULL;
    switch(event.GetId())
    {
    case ID_BaseBW:
        processor = new CBaseBlackAndWhite(GetDocument());
        break;

    case ID_BaseEmboss:
        processor = new CBaseEmboss(GetDocument());
        break;

    case ID_BaseCanny:
        processor = new CBaseCanny(GetDocument());
        break;
    }

    Process(processor);
}


/** \brief Handler for the Modified menu options
 *
 * Handle any menu selection from the Modified menu
 * \param event An object that describes the event
 */
void CFrame::OnModified(wxCommandEvent &event)
{
    // Create a processor to use
    CProcessor *processor = NULL;
    switch(event.GetId())
    {
    case ID_ModifiedBW:
        processor = new CBlackAndWhite(GetDocument());
        break;

    case ID_ModifiedEmboss:
        processor = new CEmboss(GetDocument());
        break;

    case ID_ModifiedCanny:
        processor = new CCanny(GetDocument());
        break;
    }

    Process(processor);
}


/** \brief Handler for Test menu options
 *
 * Handle any menu selection from the Test menu
 * \param event An object that describes the event
 */
void CFrame::OnTest(wxCommandEvent &event)
{
    // Create the processors to use
    CProcessor *processor1 = NULL;
    CProcessor *processor2 = NULL;
    switch(event.GetId())
    {
    case ID_TestBW:
        processor1 = new CBaseBlackAndWhite(GetDocument());
        processor2 = new CBlackAndWhite(GetDocument());
        break;

    case ID_TestEmboss:
        processor1 = new CBaseEmboss(GetDocument());
        processor2 = new CEmboss(GetDocument());
        break;

    case ID_TestCanny:
        processor1 = new CBaseCanny(GetDocument());
        processor2 = new CCanny(GetDocument());
        break;
    }

    // Create the processing dialog box
    CTestDlg dlg(this, processor1, processor2);

    // Display the dialog box
    dlg.ShowModal();
}


/** \brief Handler for the Benchmark menu options
 *
 * Handle any menu selection from the Benchmark menu
 * \param event An object that describes the event
 */
void CFrame::OnBenchmark(wxCommandEvent &event)
{
    // Create the processors to use
    CProcessor *processor1 = NULL;
    CProcessor *processor2 = NULL;
    switch(event.GetId())
    {
    case ID_BenchmarkBW:
        processor1 = new CBaseBlackAndWhite(GetDocument());
        processor2 = new CBlackAndWhite(GetDocument());
        break;

    case ID_BenchmarkEmboss:
        processor1 = new CBaseEmboss(GetDocument());
        processor2 = new CEmboss(GetDocument());
        break;

    case ID_BenchmarkCanny:
        processor1 = new CBaseCanny(GetDocument());
        processor2 = new CCanny(GetDocument());
        break;
    }

    // Create the processing dialog box
    CBenchmarkDlg dlg(this, processor1, processor2);

    // Display the dialog box
    dlg.ShowModal();
}



/** Given a processor to use, create the dialog box
 * and pass it the processor to use.
 * \param processor The processor to use
 */
void CFrame::Process(CProcessor *processor)
{
    // Create the processing dialog box
    CProcessingDlg dlg(this, processor);

    // Display the dialog box
    if(dlg.ShowModal() == wxOK)
    {
        GetDocument()->SetPicture(processor->GetProcessedImage());
    }
}




/** \brief Called on exit
 *
 * This function is called when an exit menu item is selected.
 * It closes the main window, which ends the program.
 * \param event An object that describes the event.
 */
void CFrame::OnExit(wxCommandEvent& event)
{
    Close(TRUE);
}


/** \brief File/About menu option
 *
 * Menu handler for File/About menu option
 * \param event The menu event
 */
void CFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"Imager is a Doc Owen Production",
            L"About Imager",
            wxOK | wxICON_INFORMATION, this);
}


