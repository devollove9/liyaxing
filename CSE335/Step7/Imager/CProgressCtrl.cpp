/*
 * Name:     CProgressCtrl.cpp
 *
 *
 * Class:    CProgressCtrl
 * Header:   CProgressCtrl.h
 * Created : Nov 14, 2011
 * Author :  Charles B. Owen
 */

#include "wx/prec.h"
#include "CProgressCtrl.h"
#include "CSpeech.h"

BEGIN_EVENT_TABLE(CProgressCtrl, wxWindow)
   EVT_PAINT(CProgressCtrl::OnPaint)
   EVT_TIMER(ID_Timer, CProgressCtrl::OnTimer)
END_EVENT_TABLE();

const double BarSpeed = 40;
const double HandSpeed = 200;
const int HandExtra = 100;

/** \brief Constructor
 * \param parent The parent window
 * \param size The size of the control
 */
CProgressCtrl::CProgressCtrl(wxWindow *parent, wxSize size) :
    wxWindow(parent, wxID_ANY, wxDefaultPosition, size, wxBORDER_SUNKEN), mTimer(this, ID_Timer)
{
    mProgress = 0;
    mTimer.Start(30);
    mStopwatch.Start();
    mLastTime = 0;
    mQuiet = false;
    
    bool ok = mBar.LoadFile(L"progress/bar.png", wxBITMAP_TYPE_PNG);
    assert(ok);

    ok = mHand.LoadFile(L"progress/handsmall.png", wxBITMAP_TYPE_PNG);
    assert(ok);

    mBarPos = 0;
    mHandPos = -mHand.GetWidth();
    mSpeakCount = 0;
}

/** \brief Destructor */
CProgressCtrl::~CProgressCtrl()
{
}

/*! \brief Handle timer events
 * \param event The timer event
 */
void CProgressCtrl::OnTimer(wxTimerEvent &event)
{
    Refresh();

#ifdef CSPEECH    
    mSpeakCount++;
    if(!mQuiet && mSpeakCount > 15) 
    {
        mSpeakCount = 0;
        speak << "progress" << std::flush;
    }
#endif
}

/** \brief Handle a draw request for this window
 * \param event The draw event
 */
void CProgressCtrl::OnPaint(wxPaintEvent &event)
{
    wxSize size = GetSize();

    // Elapsed time:
    int newTime = mStopwatch.Time();
    double delta = (newTime - mLastTime) * 0.001;
    mLastTime = newTime;

    mBarPos += BarSpeed * delta;
    while(mBarPos > (mBar.GetHeight() - size.GetHeight()))
    {
        mBarPos -= mBar.GetHeight() - size.GetHeight();
    }

    mHandPos += HandSpeed * delta;
    double maxHand = size.GetWidth() + HandExtra;
    if(mHandPos > maxHand)
    {
        mHandPos = -mHand.GetWidth();
    }

    // Create a device context
    wxPaintDC dc(this);

    int x = int(mProgress * size.GetWidth());

    dc.DrawBitmap(mBar, x - mBar.GetWidth(), -int(mBarPos));

    dc.SetPen(*wxTRANSPARENT_PEN);

    dc.SetBrush(*wxWHITE_BRUSH);
    dc.DrawRectangle(x, 0, size.GetWidth() - x, size.GetHeight());

    dc.DrawBitmap(mHand, int(mHandPos), 0, true);

    dc.SetPen(wxNullPen);
    dc.SetBrush(wxNullBrush);
    dc.SetFont(wxNullFont);
}
