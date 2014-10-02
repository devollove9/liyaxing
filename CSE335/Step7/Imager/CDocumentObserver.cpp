/*
 * Name:     CDocumentObserver.cpp
 *
 *
 * Class:    CDocumentObserver
 * Header:   CDocumentObserver.h
 * Created : Oct 7, 2011
 * Author :  Charles B. Owen
 */

#include "wx/prec.h"
#include "CDocumentObserver.h"
#include "CDocument.h"

/** \brief Constructor for a document observer.
 * \param document The document to observer
 */
CDocumentObserver::CDocumentObserver(CDocument *document) : mDocument(document)
{
    mDocument->AddObserver(this);
}

/** \brief Destructor */
CDocumentObserver::~CDocumentObserver()
{
    mDocument->RemoveObserver(this);
}
