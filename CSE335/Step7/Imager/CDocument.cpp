/*
 * Name:     CDocument.cpp
 *
 *
 * Class:    CDocument
 * Header:   CDocument.h
 * Created : Oct 7, 2011
 * Author :  Charles B. Owen
 */

#include "wx/prec.h"
#include "CDocument.h"

using namespace std;

/** \brief Constructor */
CDocument::CDocument()
{
    mHasMoments = false;
}

/** \brief Destructor */
CDocument::~CDocument()
{

}

/** Load an image file into the document.
 * \param filename Name of the file to load
 * \returns true if successful
 */
bool CDocument::LoadFile(const std::wstring &filename)
{
    bool ret = CPicture::LoadFile(filename);
    mHasMoments = false;
    UpdateObservers();
    return ret;
}


/*
 * Name :        CDocument::SetPicture()
 * Description : Set the picture in the document to another picture
 */
void CDocument::SetPicture(const CPicture *picture)
{
    CPicture::SetPicture(picture);
    mHasMoments = false;
    UpdateObservers();
}


/** \brief Sets the moments related information so we can display it.
 * \param xbar The X centroid
 * \param ybar The Y centroid
 * \param angle The fundamental angle
 * \param len The length in the fundamental direction
 * \param wid The width relative to the fundamental direction
 */
void CDocument::SetMoments(double xbar, double ybar, double angle, double len, double wid)
{
    mHasMoments = true;
    mXbar = xbar;
    mYbar = ybar;
    mAngle = angle;
    mLength = len;
    mWidth = wid;
    UpdateObservers();
}



/** \brief Draw the picture.
 * \param dc The device context
 */
void CDocument::Draw(wxDC *dc)
{
    if(IsEmpty()) 
    {
        return;
    }
    
    wxBitmap bmp(*GetImage());
    dc->DrawBitmap(bmp, 0, 0);

    if(mHasMoments)
    {
        dc->SetPen(*wxRED_PEN);

        // A vector in the orientation direction
        double ox = cos(mAngle);
        double oy = sin(mAngle);

        // A vector in the orthogonal direction
        double rx = -oy;
        double ry = ox;

        double oxl = ox * mLength / 2;
        double oyl = oy * mLength / 2;
        double rxl = rx * mWidth / 2;
        double ryl = ry * mWidth / 2;

        wxPoint p1(int(mXbar - oxl), int(mYbar - oyl));
        wxPoint p2(int(mXbar + oxl), int(mYbar + oyl));

        dc->DrawLine(p1, p2);

        wxPoint p3(int(mXbar - rxl), int(mYbar - ryl));
        wxPoint p4(int(mXbar + rxl), int(mYbar + ryl));

        dc->SetPen(*wxGREEN_PEN);
        dc->DrawLine(p3, p4);

        wxPoint p5(int(mXbar + oxl + rxl), int(mYbar + oyl + ryl));
        wxPoint p6(int(mXbar - oxl + rxl), int(mYbar - oyl + ryl));
        wxPoint p7(int(mXbar - oxl - rxl), int(mYbar - oyl - ryl));
        wxPoint p8(int(mXbar + oxl - rxl), int(mYbar + oyl - ryl));

        dc->SetPen(*wxCYAN_PEN);
        dc->DrawLine(p5, p6);
        dc->DrawLine(p6, p7);
        dc->DrawLine(p7, p8);
        dc->DrawLine(p8, p5);

        dc->SetPen(wxNullPen);
    }
}



/** \brief Add an observer to this document.
 * \param observer The observer to add
 */
void CDocument::AddObserver(CDocumentObserver *observer)
{
    mObservers.push_back(observer);
}

/** \brief Remove an observer from this document.
 * \param observer The observer to remove.
 */
void CDocument::RemoveObserver(CDocumentObserver *observer)
{
    mObservers.remove(observer);
}

/** \brief Update all observers to indicate the document has changed.
 */
void CDocument::UpdateObservers()
{
    for(list<CDocumentObserver *>::iterator o=mObservers.begin(); o!=mObservers.end(); o++)
    {
        (*o)->UpdateObserver();
    }
}


