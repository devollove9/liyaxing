/*
 * Name:     CApp.cpp
 * Main application class
 *
 * Class:    CApp
 * Header:   CApp.h
 * Created : Feb 20, 2010
 * Author :  Charles B. Owen - Initial distributed version
 */

#include "wx/prec.h"
#include "CApp.h"
#include "CFrame.h"

IMPLEMENT_APP(CApp)

CApp::CApp()
{
    // TODO Auto-generated constructor stub

}

CApp::~CApp()
{
    // TODO Auto-generated destructor stub
}


/*
 * Name :  CApp::OnInit()
 *
 * This function is called once when the
 * application is started. It creates the main frame for
 * the program and displays it.
 *
 */
bool CApp::OnInit()
{
    wxInitAllImageHandlers();
    CFrame *frame = new CFrame();
    frame->Show(true);
    SetTopWindow(frame);
    return true;
}
