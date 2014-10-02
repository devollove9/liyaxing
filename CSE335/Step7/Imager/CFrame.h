/* Name:     CFrame.h
 *
 *
 * Class:    CFrame
 * Impl:     CFrame.cpp
 * Created : Feb 20, 2010
 * Author :  Charles B. Owen - Initial distributed version
 */

#pragma once
#ifndef CFRAME_H_
#define CFRAME_H_

#include "CViewEdit.h"
#include "CDocument.h"

class CProcessor;

/** \brief Main application frame class.
 *
 * This is the application main frame. All other windows are children
 * of this window.
 */
class CFrame : public wxFrame
{
public:
    CFrame();
    virtual ~CFrame();

    /** \brief The ID values for menu options */
    enum Ids {ID_Exit=1, ID_None, ID_About, ID_FileOpen,
        ID_AnalyzeMoments,
        ID_BaseBW, ID_BaseEmboss, ID_BaseCanny,
        ID_ModifiedBW, ID_ModifiedEmboss, ID_ModifiedCanny,
        ID_TestBW, ID_TestEmboss, ID_TestCanny,
        ID_BenchmarkBW, ID_BenchmarkEmboss, ID_BenchmarkCanny,
        ID_Zoom25, ID_Zoom50, ID_Zoom100, ID_ZoomFit};

    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnFileOpen(wxCommandEvent& event);
    void OnAnalyzeMoments(wxCommandEvent &event);

    void OnBase(wxCommandEvent &event);
    void OnModified(wxCommandEvent &event);
    void OnTest(wxCommandEvent &event);
    void OnBenchmark(wxCommandEvent &event);

    void OnZoom25(wxCommandEvent &event);
    void OnZoom50(wxCommandEvent &event);
    void OnZoom100(wxCommandEvent &event);
    void OnZoomFit(wxCommandEvent &event);

    /** \brief Get the document associated with this frame.
     * \returns Document pointer.
     */
    CDocument *GetDocument() {return &mDocument;}

    DECLARE_EVENT_TABLE()

private:
    void Process(CProcessor *processor);

    //! The document containing the image we are editing
    CDocument  mDocument;

    //! The editing child window
    CViewEdit *mViewEdit;
};

#endif /* CFRAME_H_ */
