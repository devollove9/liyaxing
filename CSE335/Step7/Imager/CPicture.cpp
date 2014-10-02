/*
 * Name:     CPicture.cpp
 *
 *
 * Class:    CPicture
 * Header:   CPicture.h
 * Created : Nov 15, 2011
 * Author :  Charles B. Owen
 */

#include "wx/prec.h"
#include <cassert>
#include "CPicture.h"

/** \cond */
inline BYTE ByteRange(int b)
{
    if(b < 0)
        return 0;
    if(b > 255)
        return 255;
    return (BYTE)b;
}
/** \endcond */

//! Constructor
CPicture::CPicture()
{
    // Newly created
    mState = New;

    mImageData = NULL;
}

//! Destructor
CPicture::~CPicture()
{
    Clear();
}


/** \brief Clear the picture to new state.
 * Clear the picture to no data at all.
 */
void CPicture::Clear()
{
    mImageData = NULL;
    mState = New;
    mFilename.Clear();
}

/** \brief Validate x,y values for an image
 * This tests that x,y values are valid for an image and throws and
 * assertion if they are not.
 */
void CPicture::Validate(int x, int y) const
{
    assert(x >= 0 && x < GetWidth());
    assert(y >= 0 && y < GetHeight());
}

/** \brief Get the RGB value for a pixel
 *
 * Given an x,y location in an image, return the r, g, b value
 * at that location. Pixel values are in the range 0 to 255 (bytes)
 * \param x X location in image (column). Must be valid column value.
 * \param y Y location in image (row). Must be valid row value. Row numbers
 * are from the top down.
 * \param r Red output value
 * \param g Green output value
 * \param b Blue output value
 */
void CPicture::GetRGB(int x, int y, int &r, int &g, int &b) const
{
    Validate(x, y);
    int loc = (y * GetWidth() + x) * 3;
    r = mImageData[loc];
    g = mImageData[loc+1];
    b = mImageData[loc+2];
}

/** \brief Set the RGB value for a pixel
 *
 * Given an x,y location in an image, set the r, g, b values
 * at that location. Pixel values are in the range 0 to 255 (bytes). If
 * values exceed that range, they are clamped.
 * \param x X location in image (column). Must be valid column value.
 * \param y Y location in image (row). Must be valid row value. Row numbers
 * are from the top down.
 * \param r Red value
 * \param g Green value
 * \param b Blue value
 */
void CPicture::SetRGB(int x, int y, int r, int g, int b)
{
    Validate(x, y);
    int loc = (y * GetWidth() + x) * 3;
    mImageData[loc] = ByteRange(r);
    mImageData[loc+1] = ByteRange(g);
    mImageData[loc+2] = ByteRange(b);
}


/** \brief Create an image for writing
 *
 * Images are either readable images we load or new images we write.
 * This function creates a new image for writing with a specified size.
 * The image is initialized to green.
 * \param size The image size to create.
 */
void CPicture::Create(wxSize size)
{
    Clear();
    mState = Write;
    mSize = size;

    mImageData = (BYTE *)malloc(mSize.GetWidth() * mSize.GetHeight() * 3);
    mImage = wxImage(mSize.GetWidth(), mSize.GetHeight(), mImageData);

    for(int i=0;  i<mSize.GetWidth() * mSize.GetHeight() * 3;  i+=3)
    {
        mImageData[i] = 0;
        mImageData[i+1] = 255;
        mImageData[i+2] = 0;
    }
}


/** \brief Get the image as a wxImage
 *
 * This function gets the underlying wxImage for the picture. It is
 * used to display the image in wxWidgets.
 * \returns The wxImage.
 */
const wxImage *CPicture::GetImage() const
{
    return &mImage;
}


/** \brief Compare this picture to another picture.
 *
 * Compare this picture to another pictures. If they are identical,
 * the function returns zero. If there are differences, the number of
 * differing pixels is returned.
 * \param p The picture to compare with.
 * \returns Number of differing pixels.
 */
int CPicture::Compare(const CPicture *p) const
{
    int cnt = 0;
    for(int y=0; y<GetHeight();  y++)
    {
        for(int x=0;  x<GetWidth();  x++)
        {
            int r1, g1, b1, r2, g2, b2;
            GetRGB(x, y, r1, g1, b1);
            p->GetRGB(x, y, r2, g2, b2);
            if(r1 != r2 || g1 != g2 || b1 != b2)
                cnt++;
        }
    }

    return cnt;
}




/** \brief Load an image from a file
 *
 * Load an image from a disk file. This works for any supported
 * wxWidgets image importer.
 * \param filename Filename to load
 * \returns true if succesful
 */
bool CPicture::LoadFile(const std::wstring &filename)
{
    Clear();
    bool ret = mImage.LoadFile(filename.c_str());
    mFilename.Assign(filename);
    PrepareToRead();
    return ret;
}




/** \brief Set the picture to a copy of another picture.
 *
 * Make this picture identical to another picture and puts the component
 * in read mode.
 * \param picture The picture we are copying.
 */
void CPicture::SetPicture(const CPicture *picture)
{
    Clear();
    mImage = *picture->GetImage();
    PrepareToRead();
}


/*! Prepare an image that has been set for reading.
 */
void CPicture::PrepareToRead()
{
    mState = Read;          // This is a readable image
    mImageData = mImage.GetData();
    mSize = wxSize(mImage.GetWidth(), mImage.GetHeight());
}
