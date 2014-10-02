/**
 * \file CApp.h
 * 
 * Application main class
 *
 * Class:    CApp
 * Impl:     CApp.cpp
 * Created : Feb 20, 2010
 * Author :  Charles B. Owen - Initial distributed version
 */

#pragma once
#ifndef CAPP_H_
#define CAPP_H_

#include "CSpeech.h"

/**
 *  \mainpage Imager Application
 *
 * This is the documentation for the CSE 335 Imager Application
 * This describes the function calls that may be needed by a
 * solution for the accompanying step assignment.
 *
 * This documentation is generated from sources using Doxygen.
 */


/** \brief Main program application class.
 *
 * Entry point for the program.
 */
class CApp : public wxApp
{
public:
    CApp();
    virtual ~CApp();

    /** \brief Program main entry point
     */
    virtual bool OnInit();
 
private:
#ifdef CSPEECH
    //! Speech component object
    CSpeech mSpeech;
#endif
};

#endif /* CAPP_H_ */
