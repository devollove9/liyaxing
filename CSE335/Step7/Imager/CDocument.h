/*
 * Name:     CDocument.h
 *
 *
 * Class:    CDocument
 * Impl:     CDocument.cpp
 * Created : Oct 7, 2011
 * Author :  Charles B. Owen
 */

#pragma once
#ifndef CDOCUMENT_H_
#define CDOCUMENT_H_

#include <list>
#include <string>
#include "CDocumentObserver.h"
#include "CPicture.h"

/** \brief A document that holds a single image we will be processing
 *
 * This class is derived from CPicture, so it is a picture with additional functionality
 * to support drawing and display of moments information.
 */
class CDocument : public CPicture
{
public:
    CDocument();
    virtual ~CDocument();

    void AddObserver(CDocumentObserver *observer);
    void RemoveObserver(CDocumentObserver *observer);
    void UpdateObservers();

    virtual bool LoadFile(const std::wstring &filename);
    virtual void SetPicture(const CPicture *picture);

    void SetMoments(double xbar, double ybar, double angle, double len, double wid);

    virtual void Draw(wxDC *dc);

private:
    //! Disabled
    CDocument(const CDocument &);
    //! Disabled
    CDocument &operator=(const CDocument &);

    bool   mHasMoments; //!< Do we have the following moments information?
    double mXbar;       //!< X centroid for the image
    double mYbar;       //!< Y centroid for the image
    double mAngle;      //!< The image fundamental angle
    double mLength;     //!< Shape length
    double mWidth;      //!< Shape width

    //! All of the observers of this document
    std::list<CDocumentObserver *> mObservers;
};

#endif /* CDOCUMENT_H_ */
