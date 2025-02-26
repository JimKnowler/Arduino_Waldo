#pragma once

#include "Ensure.h"
#include "Slice.h"

namespace core
{
    /**
     * @class Vector
     * @brief Lightweight implementation of <vector> for Arduino_Waldo project
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
        /**
         * @brief Construct a new Vector object from a slice of another vector
         * 
         * @param slice 
         */
        Vector(const SliceT& slice);

        /**
         * @brief add an element to the end of the vector
         * 
         * @param element the element to add at the end of the vector
         */
        void Add(const T& element);

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
         * 
         * @param Size
         */
        void SetSize(int Size);

        /**
         * @brief Reset the vector to an empty vector
         * @note Does not change memory allocation
         */
        void Reset();

        /**
         * @brief create a slice that references to a subsequence of the vector
         * @note the slice does not have any ownership over the lifetime of the vector
         * 
         * @param Start Start index
         * @param Length Number of elements
         * @return Slice 
         */
        Slice<T> Slice(int Start, int Length);

    private:
        // actual data of data array
        int Size = 0;
        
        // number of elements stored in the data array
        int Used = 0;

        // 
        T* Data = nullptr;
    };

    template <typename T>
    Vector<T>::Vector()
    {

    }

    template <typename T>
    Vector<T>::Vector(const Vector<T>::SliceT& slice) {
        const int sliceLength = slice.end - slice.start;
        SetSize(sliceLength);

        for (int i=slice.start; i<slice.end; i++)
        {
            Add(slice[i]);
        }
    }

    template <typename T>
    void Vector<T>::Add(const T& element)
    {
        if (Data == nullptr) {
            SetSize(kDefaultSize);
        } else if (Used == Size) {
            const T* oldData = Data;
            Data = nullptr;
            
            SetSize(Size * 2);
            
            for (int i=0; i<Used; i++) {
                Data[i] = oldData[i];
            }

            free(oldData);
        }

        Data[Used] = element;
        Used += 1;
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
        if (Size == NewSize) {
            return;
        }

        if (Data) {
            free(Data);
            Data = nullptr;
        }

        Size = NewSize;
        Used = 0;

        const int numBytes = sizeof(T) * Size;
        Data = malloc(numBytes);        
        memset(Data, 0, numBytes);
    }

    template <typename T>
    void Vector<T>::Reset()
    {
        Used = 0;
    }

    template <typename T>
    Slice<T> Vector<T>::Slice(int Start, int Length)
    {
        return {
            .Data = Data,
            .Start = Start,
            .Length = Length
        };
    }

} // namespace core
