/*
 * Name:     CDocumentObserver.h
 *
 *
 * Class:    CDocumentObserver
 * Impl:     CDocumentObserver.cpp
 * Created : Oct 7, 2011
 * Author :  Charles B. Owen
 */

#pragma once
#ifndef CDOCUMENTOBSERVER_H_
#define CDOCUMENTOBSERVER_H_

class CDocument;

/** \brief Implementation of the observer pattern document observer
 */
class CDocumentObserver
{
public:
    virtual ~CDocumentObserver();

    /** \brief This function is called to update any observers */
    virtual void UpdateObserver() = 0;

    /** \brief Get the document
     * \returns The document pointer
     */
    CDocument *GetDocument() {return mDocument;}

protected:
    CDocumentObserver(CDocument *document);

private:
    //! Disabled
    CDocumentObserver();
    //! Disabled
    CDocumentObserver(const CDocumentObserver &);
    //! Disabled
    CDocumentObserver &operator=(const CDocumentObserver &);

    CDocument *mDocument;       //!< Document we are observing
};

#endif /* CDOCUMENTOBSERVER_H_ */
