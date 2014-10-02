/*
 * Name:     CPicture.h
 *
 *
 * Class:    CPicture
 * Impl:     CPicture.cpp
 * Created : Nov 15, 2011
 * Author :  Charles B. Owen
 */

#pragma once
#ifndef CPICTURE_H_
#define CPICTURE_H_

#include <wx/filename.h>


/** \brief Type for BYTE values
 * This is the type used internally for image pixel components.
 */
typedef unsigned char BYTE;

/** \brief Image representation
 * This class represents an image in the program.
 */
class CPicture
{
public:
    CPicture();
    virtual ~CPicture();

    virtual bool LoadFile(const std::wstring &filename);


    virtual void SetPicture(const CPicture *picture);
    void Clear();

    /** \brief Get the image size
     * \returns Image Size */
    wxSize GetSize() const {return mSize;}

    /** \brief Get the image width
     * \returns Image Width */
    int GetWidth() const {return mSize.GetWidth();}

    /** \brief Get the image height
     * \returns Image Height */
    int GetHeight() const {return mSize.GetHeight();}

    void GetRGB(int x, int y, int &r, int &g, int &b) const;
    void SetRGB(int x, int y, int r, int g, int b);


    const wxImage *GetImage() const;

    void Create(wxSize size);

    int Compare(const CPicture *p) const;

    /** \brief Get the filename
     * \returns Filename as a wxFileName object
     */
    const wxFileName &GetFilename() const {return mFilename;}
    
    /** \brief Is the image empty?
     *  \returns true if the image is empty
     */
    bool IsEmpty() {return mSize.GetHeight() == 0 || mSize.GetWidth() == 0;}

private:
    //! Disabled
    void operator=(const CPicture &picture);

    void Validate(int x, int y) const;

    //! The possible picture states
    enum States {New, Read, Write};

    void PrepareToRead();

    //! This is sort of an adapter class for an image
    wxImage mImage;

    //! The underlying image data
    BYTE *mImageData;

    //! The state of this image
    States mState;

    //! The size of the image
    wxSize mSize;

    //! The filename for the picture if loaded from a file
    wxFileName mFilename;
};

#endif /* CPICTURE_H_ */
