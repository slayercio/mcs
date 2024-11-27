#pragma once
#include <mcs/buffer/abstract_buffer.hpp>
#include <stdexcept>
#include <format>
#include <array>

namespace mcs
{
    class MemoryBuffer : public AbstractBuffer
    {
    public:
        MemoryBuffer(size_t length, mcs_byte* data);
        MemoryBuffer();

    public: // READ
        mcs_byte read_byte();
        mcs_ubyte read_ubyte();

        mcs_short read_short();
        mcs_ushort read_ushort();

        mcs_int read_int();
        mcs_uint read_uint();

        mcs_long read_long();
        mcs_ulong read_ulong();

        mcs_varint read_varint();
        mcs_varlong read_varlong();

        mcs_float read_float();
        mcs_double read_double();

        JString read_string();
        mcs::Position read_position();

        mcs::AbstractBuffer* read_byte_array(mcs_ulong size); // copies
        mcs::AbstractBuffer* copy_rest();

    public: // WRITE
        void write_byte(mcs_byte v);
        void write_ubyte(mcs_ubyte v);

        void write_short(mcs_short v);
        void write_ushort(mcs_ushort v);

        void write_int(mcs_int v);
        void write_uint(mcs_uint v);

        void write_long(mcs_long v);
        void write_ulong(mcs_ulong v);

        void write_varint(mcs_varint v);
        void write_varlong(mcs_varlong v);

        void write_float(mcs_float v);
        void write_double(mcs_double v);

        void write_string(JString v);
        void write_position(mcs::Position v);

        void write_byte_array(AbstractBuffer* v);

        AbstractBuffer::data_type* data_raw();
        std::vector<AbstractBuffer::data_type> data();

        const AbstractBuffer::size_type size();

    private:
        template<typename T>
        inline void assert_can_read()
        {
            if(m_Position + sizeof(T) > m_Size + 1)
            {
                throw std::out_of_range(std::format(
                    "cannot read data of size: {} because only {} bytes are available",
                    sizeof(T), m_Size + 1 - m_Position
                ));
            }
        }

        template<size_t K>
        inline std::array<mcs_byte, K> read_bytes()
        {
            std::array<mcs_byte, K> bytes;

            for(size_t i = 0; i < K; i++)
            {
                bytes[i] = read_byte();
            }

            return bytes;
        }

        inline std::vector<mcs_byte> read_bytes(size_t length)
        {
            std::vector<mcs_byte> bytes;

            for(size_t i = 0; i < length; i++)
            {
                bytes.push_back(read_byte());
            }

            return bytes;
        }

        inline void write_bytes(size_t length, mcs_byte* data)
        {
            for(size_t i = 0; i < length; i++)
            {
                m_Data.push_back(data[i]);
            }

            m_Size += length;
        }
    
    private:
        AbstractBuffer::size_type m_Size;
        AbstractBuffer::size_type m_Position;

        std::vector<AbstractBuffer::data_type> m_Data;
    };
} // namespace mcs
