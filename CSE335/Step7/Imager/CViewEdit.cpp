/*
 * Name:     CViewEdit.cpp
 * The main window for editing our presentation.
 *
 * Class:    CViewEdit
 * Header:   CViewEdit.h
 * Created : Feb 20, 2010
 * Author :  Charles B. Owen - Initial distributed version
 */

#include "wx/prec.h"
#include "CViewEdit.h"
#include "CFrame.h"
#include "CDocument.h"


BEGIN_EVENT_TABLE(CViewEdit, wxScrolledWindow)
    EVT_PAINT(CViewEdit::OnPaint)
END_EVENT_TABLE();

/** \brief Constructor for an editor view.
 * \param frame The frame this view is a member of. The frame owns the document.
 */
CViewEdit::CViewEdit(CFrame *frame) :
    wxScrolledWindow(frame, wxID_ANY, wxDefaultPosition, wxSize(800, 600),
            wxHSCROLL | wxVSCROLL | wxBORDER_SUNKEN),
            CDocumentObserver(frame->GetDocument()),
            mFrame(frame)

{
    mZoom = 0.25;

    SetBackgroundColour(wxColour(128, 128, 128));
    SetVirtualSize(GetDocument()->GetSize());
    SetScrollRate(1, 1);
    mLastMouse = wxPoint(0, 0);
}


/** \brief Destructor
 */
CViewEdit::~CViewEdit()
{
}


/** \brief Force an update of this window when the document changes.
 */
void CViewEdit::UpdateObserver()
{
    Refresh();
}


/** \brief Select a zoom level that fits the image in the window.
 */
void CViewEdit::FitZoom()
{
    // This turns off the scroll bars so I know we get the client size
    // not including them.
    SetVirtualSize(wxSize(100, 100));

    wxSize dSize = GetDocument()->GetSize();
    wxSize wSize = GetClientSize();
    if(wSize.GetWidth() == 0 || wSize.GetHeight() == 0 ||
            (dSize.GetWidth() < wSize.GetWidth() && dSize.GetHeight() < wSize.GetHeight()))
    {
        mZoom = 1;
        Refresh();
        return;
    }

    double z1 = double(wSize.GetWidth()) / double(dSize.GetWidth());
    double z2 = double(wSize.GetHeight()) / double(dSize.GetHeight());

    mZoom = z1 < z2 ? z1 : z2;
    Refresh();
}


/** \brief Handle a draw request for this window.
 * \param event The draw event
 */
void CViewEdit::OnPaint(wxPaintEvent &event)
{
    // Create a device context
    wxPaintDC dc(this);
   // dc.SetClippingRegion(wxPoint(0, 0), GetDocument()->GetSize());

    wxSize dSize = GetDocument()->GetSize();
    wxSize zSize(int(dSize.GetWidth() * mZoom), int(dSize.GetHeight() * mZoom));

    SetVirtualSize(zSize);

    // Offset the device context due to any scrolling
    DoPrepareDC(dc);

    if(mZoom != 1)
        dc.SetUserScale(mZoom, mZoom);

    GetDocument()->Draw(&dc);
}



