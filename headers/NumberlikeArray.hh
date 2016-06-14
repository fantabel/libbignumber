#ifndef NUMBERLIKEARRAY_H
#define NUMBERLIKEARRAY_H

// Make sure we have NULL.
#ifndef NULL
#define NULL 0
#endif
#include <iostream>
#include <sstream>

/*!
 * \file
 * \brief File describing NumberlikeArray
 */

/*! \brief A NumberlikeArray<Blk> object holds a heap-allocated array of Blk 
 * with a length and a capacity and provides basic memory management features.
 *
 * BigUnsigned and BigUnsignedInABase both subclass it.
 *
 * NumberlikeArray provides no information hiding.  Subclasses should use
 * nonpublic inheritance and manually expose members as desired using
 * declarations like this:
 *
 * public: <br/>
 *     NumberlikeArray< the-type-argument >::getLength;
 */
template <class Blk>
class NumberlikeArray {
public:

   //! Type for the index of a block in the array
   typedef unsigned int Index;

   //! The number of bits in a block, defined below.
   static const unsigned int N;

   //! The current allocated capacity of this NumberlikeArray (in blocks)
   Index cap;
   //! The actual length of the value stored in this NumberlikeArray (in blocks)
   Index len;
   //! Heap-allocated array of the blocks (can be NULL if len == 0)
   Blk *blk;

   //! Constructs a "zero" NumberlikeArray with the given capacity.
   NumberlikeArray(Index c) : cap(c), len(0) {
      blk = (cap > 0) ? (new Blk[cap]) : NULL;
   }

   /*! \brief Constructs a zero NumberlikeArray without allocating a backing array.
    *
    * A subclass that doesn't know the needed capacity at initialization
    * time can use this constructor and then overwrite blk without first
    * deleting it.
    */
   NumberlikeArray() : cap(0), len(0) {
      blk = NULL;
   }

   //! Destructor.  Note that 'delete NULL' is a no-op.
   ~NumberlikeArray() {
      delete[] blk;
   }

   /*! \brief Ensures that the array has at least the requested capacity;
    * may destroy the contents.
    */
   void allocate(Index c);

   /*! \brief Ensures that the array has at least the requested capacity;
    * does not destroy the contents. */
   void allocateAndCopy(Index c);

   //! Copy constructor
   NumberlikeArray(const NumberlikeArray<Blk> &x);

   //! Assignment operator
   void operator=(const NumberlikeArray<Blk> &x);

   //! Constructor that copies from a given array of blocks
   NumberlikeArray(const Blk *b, Index blen);

   //! \brief Capacity Accessor
   Index getCapacity()     const { return cap;      }
   //! \brief Length Accessor
   Index getLength()       const { return len;      }
   //! \brief Block Accessor
   Blk   getBlock(Index i) const { return blk[i];   }
   //! \brief Is the array empty Accessor
   bool  isEmpty()         const { return len == 0; }

   /*! \brief Compares if two NumberlikeArray are equals.
    *
    * Equality comparison: checks if both objects have the same length and
    * equal (==) array elements to that length.  Subclasses may wish to
    * override.
    */
   bool operator ==(const NumberlikeArray<Blk> &x) const;

   /*! \brief Compares if two NumberlikeArray are different.
    *
    * Check if both objects are differents (different length or at least one
    * array element different up to that length).
    */
   bool operator !=(const NumberlikeArray<Blk> &x) const {
      return !operator ==(x);
   }

   /*! \brief Convert current object to string
    */
   std::string toString();
};

template <class Blk>
std::string NumberlikeArray<Blk>::toString() {
   std::stringstream ss;
   ss << "WTF?" << std::endl;
   ss << "Hello World" << std::endl;
   return ss.str();
}

/*!
 * Define the real size of a block 
 */
template <class Blk>
const unsigned int NumberlikeArray<Blk>::N = 8 * sizeof(Blk);

/*!
 * If the array is already at least the specified size, will do nothing.
 *
 * Deletes the array if it needs more space.
 */
template <class Blk>
void NumberlikeArray<Blk>::allocate(Index c) {
   // If the requested capacity is more than the current capacity...
   if (c > cap) {
   // Delete the old number array
   delete [] blk;
   // Allocate the new array
   cap = c;
   blk = new Blk[cap];
   }
}

/*!
 * Copies the array before allocating the new space.
 */
template <class Blk>
void NumberlikeArray<Blk>::allocateAndCopy(Index c) {
   // If the requested capacity is more than the current capacity...
   if (c > cap) {
      Blk *oldBlk = blk;
      // Allocate the new number array
      cap = c;
      blk = new Blk[cap];
      // Copy number blocks
      Index i;
      for (i = 0; i < len; i++)
         blk[i] = oldBlk[i];
      // Delete the old array
      delete[] oldBlk;
   }
}

/*!
 * Copy constructor
 */
template <class Blk>
NumberlikeArray<Blk>::NumberlikeArray(const NumberlikeArray<Blk> &x)
      : len(x.len) {
   // Create array
   cap = len;
   blk = new Blk[cap];
   // Copy blocks
   Index i;
   for (i = 0; i < len; i++)
      blk[i] = x.blk[i];
}

/*!
 * Assignment operator.
 */
template <class Blk>
void NumberlikeArray<Blk>::operator=(const NumberlikeArray<Blk> &x) {
   /* Calls like a = a have no effect; catch them before the aliasing
    * causes a problem */
   if (this == &x)
      return;
   // Copy length
   len = x.len;
   // Expand array if necessary
   allocate(len);
   // Copy number blocks
   Index i;
   for (i = 0; i < len; i++)
      blk[i] = x.blk[i];
}

/*!
 * Constructor from a block and an index.
 */
template <class Blk>
NumberlikeArray<Blk>::NumberlikeArray(const Blk *b, Index blen)
      : cap(blen), len(blen) {
   // Create array
   blk = new Blk[cap];
   // Copy blocks
   Index i;
   for (i = 0; i < len; i++)
      blk[i] = b[i];
}

/*!
 * Equality operator.
 */
template <class Blk>
bool NumberlikeArray<Blk>::operator ==(const NumberlikeArray<Blk> &x) const {
   if (len != x.len)
      // Definitely unequal.
      return false;
   else {
      // Compare corresponding blocks one by one.
      Index i;
      for (i = 0; i < len; i++)
         if (blk[i] != x.blk[i])
            return false;
      // No blocks differed, so the objects are equal.
      return true;
   }
}

#endif
