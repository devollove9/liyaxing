/*
 * Name:     CBlackAndWhite.h
 * Converts an image from color to monochrome.
 *
 *
 * Class:    CBlackAndWhite
 * Impl:     CBlackAndWhite.cpp
 * Created : Nov 15, 2011
 * Author :  Charles B. Owen
 */

#pragma once
#ifndef CBLACKANDWHITE_H_
#define CBLACKANDWHITE_H_

#include "CProcessor.h"

/** \brief Converts an image from color to monochrome.
 */
class CBlackAndWhite : public CProcessor
{
public:
    CBlackAndWhite(const CPicture *picture);
    virtual ~CBlackAndWhite();

    /** \brief The actual image processing */
    virtual void Process();

protected:
    virtual const wchar_t *Name() const {return L"bw";}
};

#endif /* CBLACKANDWHITE_H_ */
