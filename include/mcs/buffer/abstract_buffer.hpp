#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <mcs/protocol/data_types.hpp>

namespace mcs
{
    class AbstractBuffer; 
    class AbstractReadBuffer; 
    class AbstractWriteBuffer;

    class AbstractReadBuffer
    {
    public: // 8 bit
        virtual mcs_byte        read_byte()                     = 0;
        virtual mcs_ubyte       read_ubyte()                    = 0;

    public: // 16 bit
        virtual mcs_short       read_short()                    = 0;
        virtual mcs_ushort      read_ushort()                   = 0;
        
    public: // 32 bit
        virtual mcs_int         read_int()                      = 0;
        virtual mcs_uint        read_uint()                     = 0;
        
    public: // 64 bit
        virtual mcs_long        read_long()                     = 0;
        virtual mcs_ulong       read_ulong()                    = 0;
        
    public: // var bit
        virtual mcs_varint      read_varint()                   = 0;
        virtual mcs_varlong     read_varlong()                  = 0;
        
    public: // float 32/64 bit
        virtual mcs_float       read_float()                    = 0;
        virtual mcs_double      read_double()                   = 0;
        
    public: // structures
        virtual JString         read_string()                   = 0;
        virtual mcs::Position   read_position()                 = 0;
        virtual AbstractBuffer* read_byte_array(mcs_ulong size) = 0;
        
        virtual AbstractBuffer* copy_rest()                     = 0;
    };

    class AbstractWriteBuffer
    {
    public: // 8 bit
        virtual void write_byte(mcs_byte v)              = 0;
        virtual void write_ubyte(mcs_ubyte v)            = 0;
    
    public: // 16 bit
        virtual void write_short(mcs_short v)            = 0;
        virtual void write_ushort(mcs_ushort v)          = 0;
    
    public: // 32 bit
        virtual void write_int(mcs_int v)                = 0;
        virtual void write_uint(mcs_uint v)              = 0;
    
    public: // 64 bit
        virtual void write_long(mcs_long v)              = 0;
        virtual void write_ulong(mcs_ulong v)            = 0;

    public: // var bit
        virtual void write_varint(mcs_varint v)          = 0;
        virtual void write_varlong(mcs_varlong v)        = 0;

    public: // float 32/64 bit
        virtual void write_float(mcs_float v)            = 0;
        virtual void write_double(mcs_double v)          = 0;

    public: // structures
        virtual void write_string(JString v)             = 0;
        virtual void write_position(mcs::Position v)     = 0;
        virtual void write_byte_array(AbstractBuffer* v) = 0;
    };

    class AbstractBuffer: public AbstractReadBuffer, public AbstractWriteBuffer
    {
    public:
        using data_type = mcs_byte;
        using size_type = mcs_ulong;

    public:
        virtual data_type*       data_raw() = 0;
        virtual std::vector<data_type> data() = 0;

    public:
        virtual const size_type size() = 0;
    };
}