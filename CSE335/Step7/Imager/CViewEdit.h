/*
 * Name:     CViewEdit.h
 * This is the main window we will use for editing out documents.
 *
 * Class:    CViewEdit
 * Impl:     CViewEdit.cpp
 * Created : Feb 20, 2010
 * Author :  Charles B. Owen - Initial distributed version
 */

#pragma once
#ifndef CVIEWEDIT_H_
#define CVIEWEDIT_H_

#include "CDocumentObserver.h"

class CFrame;

/** \brief A view for our pictures.
 * 
 * This class provides an image of the picture in a window with zooming.
 * It does not really do any editing, but I might add that functionality
 * at some point in the future.
 */
class CViewEdit : public wxScrolledWindow, public CDocumentObserver
{
public:
    CViewEdit(CFrame *parent);
    virtual ~CViewEdit();

    void OnPaint(wxPaintEvent &event);
    virtual void UpdateObserver();

    /** \brief Get the current zoom factor
     * \returns Zoom factor. 1.0 = 100%
     */
    double GetZoom() const {return mZoom;}

    /** \brief Set the zoom factor
     *
     * \param z The zoom factor. 1.0 = 100%
     */
    void SetZoom(double z) {mZoom = z; Refresh();}
    void FitZoom();

    // Notice:  Don't put anything between DECLARE_EVENT_TABLE() and private:
    DECLARE_EVENT_TABLE()

private:
    wxPoint mLastMouse;     //!< Saved last mouse position for user interface

    CFrame *mFrame;         //!< Pointer to the frame for this view

    double  mZoom;         //!< Current zoom factor
};

#endif /* CVIEWEDIT_H_ */
