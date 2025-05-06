#pragma once

#include "Ensure.h"
#include "Slice.h"
#include "Math.h"

namespace core
{
    /**
     * @class Vector
     * @brief Lightweight implementation of <vector> for Arduino_Waldo project
     * @note Suitable for POD (Plain Old Data) elements 
     *       (i.e. does not call constructor/destuctor on elements)
     */

    template <typename T>
    class Vector
    {
    public:
        enum {
            kDefaultSize = 4
        };

        typedef struct Slice<T> SliceT;

        Vector();
        ~Vector();

        /**
         * @brief Construct a new Vector object from a slice of another vector
         * 
         * @param slice 
         */
        Vector(const SliceT& slice);

        /**
         * @brief Copy constructor
         * 
         * @param other the vector to copy
         */
        Vector(const Vector<T>& other);

        /**
         * @brief Assignment operator
         * 
         * @param other the vector to copy
         */
        void operator=(const Vector<T>& other);

        /**
         * @brief Assignment operator (slice)
         * 
         * @param slice the slice to copy
         */
        void operator=(const SliceT& slice);

        /**
         * @brief add an element to the end of the vector
         * 
         * @param element the element to add at the end of the vector
         */
        void Add(const T& element);

        /**
         * @brief add multiple elements to the end of the vector
         * 
         * @param elements the array of elements to add
         * @param num the number of elements to add
         * 
         * @todo rename as 'append()'
         */
        void Add(const T* elements, int num);

        /**
         * @brief get the number of elements in the vector
         * 
         * @return the number of elements in the vector
         */
        int Num() const;

        /**
         * @brief retport whether the vector is empty
         * 
         * @return true, if the vector is empty
         */
        bool IsEmpty() const;

        /**
         * @brief remove an element from the vector
         * 
         * @param Index The index of the element to remove from the vector
         */
        void RemoveAt(int Index);

        /**
         * @brief access an element in the vector
         * 
         * @param Index the index of the element in the vector
         * @return a reference to the element in the vector
         */
        T& operator[](int Index);

        /**
         * @brief access an element in the vector
         * 
         * @param Index the index of the element in the vector
         * @return a reference to the element in the vector
         */
        const T& operator[](int Index) const;

        /**
         * @brief Get pointer to the underlying data array for this vector
         * @return Point to underlying data array
         */
        const T* GetData() const;

        /**
         * @brief Call destructor on all elements, and set the underlying size of the vector to a new size
         * @note Underlying array of data is set to zero-d memory
         * @note No guarantee that the array will be reallocated
         * @note After calling this function, Num() will return 0
         * @param NewSize The new size of the underlying data
         */
        void Reset(int NewSize = 0);


        /**
         * @brief Resize the underlying data
         * @note Call constructor on newly allocated elements, and destructor on old elements
         * @param NewSize The new size of the underlying data
         */
        void Resize(int NewSize);

        /**
         * @brief create a slice that references to a subsequence of the vector
         * @note the slice does not have any ownership over the lifetime of the vector,
         *       or its' underlying data.  The slice will become stale if you destroy 
         *       or resize the vector.
         * 
         * @param Start Start index
         * @param Length Number of elements
         * @return Slice that references part of this vector
         */
        SliceT Slice(int Start, int Length) const;

    private:
        // actual size of data array
        int DataSize = 0;
        
        // number of elements stored in the data array
        int Used = 0;

        // data array
        T* Data = nullptr;
    };

    template <typename T>
    Vector<T>::Vector()
    {

    }

    template <typename T>
    Vector<T>::~Vector()
    {
        if (Data)
        {
            free(Data);
            Data = nullptr;
        }
    }

    template <typename T>
    Vector<T>::Vector(const Vector<T>::SliceT& slice) {
        const int sliceLength = slice.Length;
        const int sliceStart = slice.Start;
        const int sliceEnd = sliceStart + sliceLength;

        Reset(sliceLength);

        for (int i=sliceStart; i<sliceEnd; i++)
        {
            Add(slice[i]);
        }
    }

    template <typename T>
    Vector<T>::Vector(const Vector<T>& other) {
        *this = other;
    }

    template <typename T>
    void Vector<T>::operator=(const Vector<T>& other) {
        *this = other.Slice(0, other.Num());
    }

    template <typename T>
    void Vector<T>::operator=(const Vector<T>::SliceT& slice) {
        Reset(slice.Length);
        
        Used = slice.Length;

        const T* source = slice.Data + slice.Start;
        for (int i=0; i<Used; i++)
        {
            Data[i] = source[i];
        }
    }

    template <typename T>
    void Vector<T>::Add(const T& element)
    {
        if (Data == nullptr) {
            Reset(kDefaultSize);
        } else if (Used == DataSize) {
            Resize(DataSize * 2);
        }

        Data[Used] = element;
        Used += 1;
    }

    template <typename T>
    void Vector<T>::Add(const T* elements, int num)
    {
        const int required = Used + num;
        
        if (required > DataSize)
        {
            Resize(required);
        }

        for (int i=0; i<num; i++)
        {
            Data[Used + i] = elements[i];
        }
        
        Used += num;
    }

    template <typename T>
    int Vector<T>::Num() const
    {
        return Used;
    }

    template <typename T>
    bool Vector<T>::IsEmpty() const
    {
        const bool bIsEmpty = (Num() == 0);
        
        return bIsEmpty;
    }

    template <typename T>
    void Vector<T>::RemoveAt(int Index)
    {
        if (!ensure(Index < Used)) {
            return;
        }

        if (!ensure(Index >= 0)) {
            return;
        }

        for (int i=Index+1; i<Used; i++) {
            Data[i-1] = Data[i];
        }

        Used -= 1;

        Data[Used].~T();
        memset(Data + Used, 0, sizeof(T));
    }

    template <typename T>
    T& Vector<T>::operator[](int Index)
    {
        ensure(Index < Used);
        ensure(Index >= 0);

        return Data[Index];
    }

    template <typename T>
    const T& Vector<T>::operator[](int Index) const
    {
        ensure(Index < Used);
        ensure(Index >= 0);

        return Data[Index];
    }

    template <typename T>
    const T* Vector<T>::GetData() const
    {
        return Data;
    }

    template <typename T>
    void Vector<T>::Reset(int NewSize) {
        for (int i=0; i<Used; i++) {
            Data[i].~T();
        }

        // prevent future use of element assignment operator from trying to 
        // cleanup any garbage left in Data
        memset(Data, 0, Used * sizeof(T));
        
        Used = 0;
        
        if (DataSize >= NewSize) {
            return;
        }

        if (Data) {
            free(Data);
            Data = nullptr;
        }

        DataSize = Max(DataSize, static_cast<int>(kDefaultSize));
        while (DataSize < NewSize) {
            DataSize *= 2;
        }
        
        const int numBytes = sizeof(T) * DataSize;
        Data = reinterpret_cast<T*>(malloc(numBytes));
        memset(Data, 0, numBytes);
    }

    template <typename T>
    void Vector<T>::Resize(int NewSize)
    {
        // TODO: this doesn't allow vector to shrink when resized

        int newDataSize = Max(DataSize, static_cast<int>(kDefaultSize));
        while (newDataSize < NewSize) {
            newDataSize *= 2;
        }

        if (newDataSize == DataSize) {
            return;
        }

        T* oldData = Data;
        Data = nullptr;

        const int OldUsed = Used;
        
        DataSize = newDataSize;
        Data = reinterpret_cast<T*>(malloc(sizeof(T) * DataSize));
        
        Used = OldUsed;
        memset(Data, 0, sizeof(T) * DataSize);

        for (int i=0; i<Used; i++)
        {
            Data[i] = oldData[i];
        }


        for (int i=0; i<Used; i++)
        {
            Data[i].~T();
        }

        free(oldData);
    }

    template <typename T>
    auto Vector<T>::Slice(int Start, int Length) const -> Vector<T>::SliceT 
    {
        ensure(Start >= 0);
        ensure((Start + Length) <= Used);

        return {
            .Data = Data,
            .Start = Start,
            .Length = Length
        };
    }

} // namespace core
