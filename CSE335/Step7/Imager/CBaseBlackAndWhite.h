/*
 * Name:     CBaseBlackAndWhite.h
 * Converts an image from color to monochrome.
 *
 * Base version
 *
 * Class:    CBaseBlackAndWhite
 * Impl:     CBaseBlackAndWhite.cpp
 * Created : Nov 15, 2011
 * Author :  Charles B. Owen
 */

#pragma once
#ifndef CBASEBLACKANDWHITE_H_
#define CBASEBLACKANDWHITE_H_

#include "CProcessor.h"

/** \brief Converts an image from color to monochrome.
 *
 * This is the base (reference) implementation.
 */
class CBaseBlackAndWhite : public CProcessor
{
public:
    CBaseBlackAndWhite(const CPicture *picture);
    virtual ~CBaseBlackAndWhite();

    /** \brief The actual image processing */
    virtual void Process();

protected:
    virtual const wchar_t *Name() const {return L"bw";}
};

#endif /* CBASEBLACKANDWHITE_H_ */
