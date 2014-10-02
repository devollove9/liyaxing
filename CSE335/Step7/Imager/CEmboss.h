/*
 * Name:     CEmboss.h
 * Convert an image into what looks like an embossed image on metal
 *
 * Class:    CEmboss
 * Impl:     CEmboss.cpp
 * Created : Nov 15, 2011
 * Author :  Charles B. Owen
 */

#pragma once
#ifndef CEMBOSS_H_
#define CEMBOSS_H_

#include "CProcessor.h"

/** \brief Convert an image into what looks like an embossed image on metal
 */
class CEmboss : public CProcessor
{
public:
    CEmboss(const CPicture *picture);
    virtual ~CEmboss();

    virtual void Process();

protected:
    virtual const wchar_t *Name() const {return L"emboss";}
};

#endif /* CEMBOSS_H_ */
