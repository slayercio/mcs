#pragma once
#include <cstdint>
#include <string>

namespace mcs
{
    using mcs_boolean = bool;
    using mcs_byte    = int8_t;
    using mcs_ubyte   = uint8_t;
    using mcs_short   = int16_t;
    using mcs_ushort  = uint16_t;
    using mcs_int     = int32_t;
    using mcs_uint    = uint32_t;
    using mcs_long    = int64_t;
    using mcs_ulong   = uint64_t;
    using mcs_float   = float;
    using mcs_double  = double;

    using mcs_varint  = mcs_int;
    using mcs_varlong = mcs_long;

    struct Position
    {
    public:
        constexpr Position(mcs_long value)
        {
            x = (value >> 38);
            z = (value >> 12) & 0x3ffffff;
            y = (value & 0xfff);
        }

        constexpr Position(mcs_int x, mcs_int z, mcs_int y)
        {
            this->x = x;
            this->z = z;
            this->y = y;
        }

        constexpr mcs_long to_long()
        {
            return static_cast<mcs_long>(
                (static_cast<mcs_long>((this->x & 0x3ffffff)) << 38) |
                (static_cast<mcs_long>((this->z & 0x3ffffff)) << 12) |
                (static_cast<mcs_long>((this->y & 0x0000fff)) << 00)
            );
        }

    public:
        mcs_int x;
        mcs_int z;
        mcs_int y;
    };

    struct JString
    {
    public:
        ~JString()
        {
            delete[] this->data;
        }

    public:
        static JString from_string(std::string v)
        {
            mcs_int size = static_cast<int32_t>(v.size());
            char* data = new char[size];

            return JString(size, data);
        }

        static JString from_buffer()
        {
            throw std::exception("Not implemented");
        }
    public:
        std::string to_string()
        {
            return std::string(data, size);
        }

        std::string_view to_string_view()
        {
            return std::string_view(data, size);
        }

        JString(mcs_int size, char* data)
        {
            this->size = size;
            this->data = data;
        }

    public:
        mcs_int size;
        char* data;
    };
}