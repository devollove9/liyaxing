/*! \file CBaseCanny.h
 * Implements Canny edge detection on an image creating a
 * false color edge image.
 *
 * Base Version
 *
 * \version 1.0 11-15-2012 Initial version
 * \version 1.1 11-28-2012 Modified to make more likely to have race conditions
 * \author Charles B. Owen
 */

#pragma once
#ifndef CBASECANNY_H_
#define CBASECANNY_H_

#include "CProcessor.h"
#include "CArray2D.h"

#include <list>

/** \brief Implementation of Canny edge detection.
 * This is the base (reference) implementation
 * 
 * See http://en.wikipedia.org/wiki/Canny_edge_detector for a
 * complete description of this method.
 */
class CBaseCanny : public CProcessor
{
public:
    CBaseCanny(const CPicture *picture);
    virtual ~CBaseCanny();

    /** \brief The actual processing */
    virtual void Process();

private:
    //! The gradient directions at any pixel
    enum Directions {D0=0, D45=1, D90=2, D135=3};

    double mThresholdHigh;      //!< High threshold for edge detection
    double mThresholdLow;       //!< Low threshold for edge detection


    void GaussianFilter(CArray2D<double> &gaussianArray);
    void DetermineGradient(CArray2D<double> &gaussian, CArray2D<double> &gradient,
            CArray2D<Directions> &directions);
    void NonMaximumSuppression(CArray2D<double> &gradient,
            CArray2D<CBaseCanny::Directions> &directions, CArray2D<double> &gradientNM);
    void TraceEdges(CArray2D<double> &gradient, std::list<wxPoint> &edges);
    void Trace(int x, int y, CArray2D<double> &gradient, std::list<wxPoint> &edges);

    void ComputeGaussianKernel(int size, double sigma, double *gaussian);

protected:
    virtual const wchar_t *Name() const {return L"canny";}
};

#endif /* CBASECANNY_H_ */
