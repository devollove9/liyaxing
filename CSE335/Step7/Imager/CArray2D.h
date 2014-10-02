/*! \file CArray2D.h
 * Template class that implements a simple 2D image.
 * \author Charles B. Owen
 */

#pragma once
#ifndef CARRAY2D_H_
#define CARRAY2D_H_


/** \brief Template class that implements a simple 2D array.
 * This class implements 2D arrays of arbitrary types.
 * An array is width by height and is treated as x,y values, so
 * the arrays work much like an image.
 */
template <class T> class CArray2D
{
public:
    /** \brief Constructor
     * The default constructor constructs to an empty array of size 0 by 0
     */
    CArray2D()
    {
        mArray = NULL;
        mWid = 0;
        mHit = 0;
    }

    /** \brief Constructor
     *
     * Construct an array of a specified size
     * \param wid Width of the array
     * \param hit Height of the array
     */
    CArray2D(int wid, int hit)
    {
        mArray = NULL;

        SetSize(wid, hit);
    }

    /** \brief Destructor */
    ~CArray2D()
    {
        delete [] mArray;
    }

    /** \brief Sets the array size
     *
     * Creates an array of a specified size
     * \param wid Width of the array
     * \param hit Height of the array
     */
    void SetSize(int wid, int hit)
    {
        Clear();
        mWid = wid;
        mHit = hit;
        mArray = new T[wid * hit];
    }

    /** \brief Clear the array
     *
     * Clears the array to size zero and no allocated memory.
     */
    void Clear()
    {
        delete [] mArray;
        mArray = NULL;
        mWid = 0;
        mHit = 0;
    }

    /** \brief Get the value at a given x, y location
     * \param x X location (column)
     * \param y Y location (row)
     * \returns Value at location x, y
     */
    T Get(int x, int y)
    {
        if(x < 0 || x >= mWid || y < 0 || y >= mHit)
            return (T)0;

        return mArray[y * mWid + x];
    }

    /** \brief Set the value at a given x, y location
     * \param x X location (column)
     * \param y Y location (row)
     * \param t The value to set
     */
    void Set(int x, int y, T t) {mArray[y * mWid + x] = t;}

    /** \brief Set all array locations to a given value
     * \param t The value to set
     */
    void SetAll(T t)
    {
        for(int i=0;  i<mWid * mHit; i++)
            mArray[i] = t;
    }

    /** \brief Get the array width
     * \returns Array width
     */
    int GetWid() const {return mWid;}

    /** \brief Get the array height
     * \returns Array height
     */
    int GetHit() const {return mHit;}

private:
    //! Disabled
    CArray2D(const CArray2D<T> &);
    //! Disabled
    void operator=(const CArray2D<T> &);

    int mWid;       //!< Width of array
    int mHit;       //!< Height of array
    T *mArray;      //!< Pointer to array data
};

#endif /* CARRAY2D_H_ */
