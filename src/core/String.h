#pragma once

#include "Vector.h"

#include <string.h>

namespace core
{

    /**
     * @class String
     * @brief Lightweight implementation of <string> for Arduino_Waldo project
     * 
     */
    class String
    {
    public:
        String();
        String(const char* str);
        String& operator=(const char* str);
        String& operator=(core::Slice<uint8_t> slice);
        String& operator+=(const char* str);
        const char operator[](int Index) const;
        bool operator==(const String& other) const;

        const char* c_str() const;

        int Length() const;

    private:
        core::Vector<char> Data;
    };

    inline String::String()
    {
        Data.SetSize(1);
        Data.Add(0);
    }

    inline String::String(const char* str)
    {
        (*this) = str;
    }

    inline String& String::operator=(const char* str)
    {
        // resize the underlying buffer (with space for null terminator)
        const int Length = strlen(str);
        Data.SetSize(Length + 1);

        // copy across the string
        for (const char* p = str; *p != 0; p++) 
        {
            Data.Add(*p);
        }

        Data.Add(0);

        return *this;
    }

    inline String& String::operator=(core::Slice<uint8_t> slice)
    {
        Data.SetSize(slice.Length);
        Data.Add(slice.Data + slice.Start, slice.Length);
        Data.Add(0);

        return *this;
    }

    inline String& String::operator+=(const char* str) 
    {
        const int CurrentLength = Length();

        // remove the null pointer
        Data.Remove(CurrentLength);

        // add new string
        for (const char* p = str; *p != 0; p++) 
        {
            Data.Add(*p);
        }

        Data.Add(0);

        return *this;
    }

    inline const char String::operator[](int Index) const
    {
        return Data[Index];
    }

    inline bool String::operator==(const String& other) const
    {
        return strcmp(c_str(), other.c_str()) == 0;
    }

    inline const char* String::c_str() const
    {
        return Data.GetData();
    }

    inline int String::Length() const
    {
        // note: offset length by 1, to remove null terminator
        const int length = Data.Num() - 1;

        return length;
    }
}
