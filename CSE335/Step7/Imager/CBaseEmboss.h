/*
 * Name:     CBaseEmboss.h
 * Convert an image into what looks like an embossed image on metal
 *
 * Base Version
 *
 * Class:    CBaseEmboss
 * Impl:     CBaseEmboss.cpp
 * Created : Nov 15, 2011
 * Author :  Charles B. Owen
 */

#pragma once
#ifndef CBASEEMBOSS_H_
#define CBASEEMBOSS_H_

#include "CProcessor.h"

/** \brief Convert an image into what looks like an embossed image on metal
 *
 * This is the base (reference) version of this class.
 */
class CBaseEmboss : public CProcessor
{
public:
    CBaseEmboss(const CPicture *picture);
    virtual ~CBaseEmboss();

    virtual void Process();

protected:
    virtual const wchar_t *Name() const {return L"emboss";}
};

#endif /* CEMBOSS_H_ */
