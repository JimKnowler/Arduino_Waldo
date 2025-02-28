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

        typedef Slice<T> SliceT;

        Vector();
        ~Vector();

        /**
         * @brief Construct a new Vector object from a slice of another vector
         * 
         * @param slice 
         */
        Vector(const SliceT& slice);

        /**
         * @brief Assignment operator
         * 
         * @param other the vector to copy
         */
        void operator=(const Vector<T>& other);

        /**
         * @brief Copy constructor
         * 
         * @param other the vector to copy
         */
        Vector(const Vector<T>& other);

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
         */
        void Add(const T* elements, int num);

        /**
         * @brief get the number of elements in the vector
         * 
         * @return the number of elements in the vector
         */
        int Num() const;

        /**
         * @brief remove an element from the vector
         * 
         * @param Index The index of the element to remove from the vector
         */
        void Remove(int Index);

        /**
         * @brief access an element in the vector
         * 
         * @param Index the index of the element in the vector
         * @return a reference to the element in the vector
         */
        T& operator[](int Index);

        /**
         * @brief Get pointer to the underlying data array for this vector
         * @return Point to underlying data array
         */
        const T* GetData() const;

        /**
         * @brief Forcibly set the size of the vector to a new size, and erase all previous data 
         * @note Underlying array of data is not initialized to valid or null values
         * @note No guarantee that the array will be reallocated
         * @param NewSize The new size of the underlying data
         */
        void SetSize(int NewSize);

        /**
         * @brief Reset the vector to an empty vector
         * @note Does not change memory allocation
         * @note Does not call destructor on elements
         */
        void Reset();

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
        Slice<T> Slice(int Start, int Length);

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

        SetSize(sliceLength);

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
        DataSize = other.DataSize;
        Used = other.Used;
        
        if (Data) {
            free(Data);
            Data = nullptr;
        }

        Data = malloc(sizeof(T) * DataSize);
        memcpy(Data, other.Data, sizeof(T) * Used);
    }

    template <typename T>
    void Vector<T>::Add(const T& element)
    {
        if (Data == nullptr) {
            SetSize(kDefaultSize);
        } else if (Used == DataSize) {
            const T* oldData = Data;
            Data = nullptr;

            const int OldUsed = Used;
            
            SetSize(DataSize * 2);
            
            Used = OldUsed;
            memcpy(Data, oldData, sizeof(T) * Used);
            free(oldData);
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
            int newSize = Max(DataSize, static_cast<int>(kDefaultSize));
            while (newSize < required) {
                newSize *= 2;
            }

            const T* oldData = Data;
            Data = nullptr;

            const int OldUsed = Used;
            
            SetSize(newSize);
            
            Used = OldUsed;
            memcpy(Data, oldData, sizeof(T) * Used);
            free(oldData);
        }

        memcpy(Data + Used, elements, sizeof(T) * num);        
        Used += num;
    }

    template <typename T>
    int Vector<T>::Num() const
    {
        return Used;
    }

    template <typename T>
    void Vector<T>::Remove(int Index)
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
    }

    template <typename T>
    T& Vector<T>::operator[](int Index)
    {
        if (!ensure(Index < Used)) {
            return;
        }

        if (!ensure(Index >= 0)) {
            return;
        }

        return Data[Index];
    }

    template <typename T>
    const T* Vector<T>::GetData() const
    {
        return Data;
    }

    template <typename T>
    void Vector<T>::SetSize(int NewSize) {
        if (DataSize == NewSize) {
            return;
        }

        if (Data) {
            free(Data);
            Data = nullptr;
        }

        DataSize = NewSize;
        Used = 0;

        const int numBytes = sizeof(T) * DataSize;
        Data = malloc(numBytes);
    }

    template <typename T>
    void Vector<T>::Reset()
    {
        Used = 0;
    }

    template <typename T>
    Slice<T> Vector<T>::Slice(int Start, int Length)
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
