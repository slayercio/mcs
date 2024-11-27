#include <mcs/buffer/impl/memory_buffer.hpp>

namespace mcs
{
    MemoryBuffer::MemoryBuffer(size_t size, mcs_byte* data)
        : m_Data(data, data + size), m_Position(0), m_Size(size)
    {
    }

    MemoryBuffer::MemoryBuffer()
        : m_Position(0), m_Size(0)
    {
    }

    mcs_byte MemoryBuffer::read_byte()
    {
        assert_can_read<mcs_byte>();

        return m_Data.at(m_Position++);
    }

    mcs_ubyte MemoryBuffer::read_ubyte()
    {
        assert_can_read<mcs_ubyte>();

        return static_cast<mcs_ubyte>(read_byte());
    }

    mcs_short MemoryBuffer::read_short()
    {
        auto bytes = read_bytes<2>();

        return *reinterpret_cast<mcs_short*>(bytes.data());
    }

    mcs_ushort MemoryBuffer::read_ushort()
    {
        auto bytes = read_bytes<2>();

        return *reinterpret_cast<mcs_ushort*>(bytes.data());
    }

    mcs_int MemoryBuffer::read_int()
    {
        auto bytes = read_bytes<4>();

        return *reinterpret_cast<mcs_int*>(bytes.data());
    }

    mcs_uint MemoryBuffer::read_uint()
    {
        auto bytes = read_bytes<4>();

        return *reinterpret_cast<mcs_uint*>(bytes.data());
    }

    mcs_long MemoryBuffer::read_long()
    {
        auto bytes = read_bytes<8>();

        return *reinterpret_cast<mcs_long*>(bytes.data());
    }

    mcs_ulong MemoryBuffer::read_ulong()
    {
        auto bytes = read_bytes<8>();

        return *reinterpret_cast<mcs_ulong*>(bytes.data());
    }

    mcs_varint MemoryBuffer::read_varint()
    {
        mcs_int value = 0;
        int position  = 0;
        mcs_byte currentByte;

        while(true)
        {
            currentByte = read_byte();
            value |= (currentByte & 0x7F) << position;

            if((currentByte & 0x80) == 0) break;

            position += 7;

            if(position >= 32) throw std::runtime_error("varint is too big!");
        }

        return value;
    }

    mcs_varlong MemoryBuffer::read_varlong()
    {
        mcs_long value = 0;
        int position = 0;
        mcs_byte currentByte;

        while(true)
        {
            currentByte = read_byte();
            value |= (currentByte & 0x7F) << position;

            if((currentByte & 0x80) == 0) break;

            position += 7;

            if(position >= 64) throw std::runtime_error("varlong is too big!");
        }

        return value;
    }

    mcs_float MemoryBuffer::read_float()
    {
        auto bytes = read_bytes<4>();

        return *reinterpret_cast<mcs_float*>(bytes.data());
    }

    mcs_double MemoryBuffer::read_double()
    {
        auto bytes = read_bytes<8>();

        return *reinterpret_cast<mcs_double*>(bytes.data());
    }

    JString MemoryBuffer::read_string()
    {
        auto size = read_varint();
        auto data = read_bytes(size);

        char* data_copy = new char[size];
        memcpy(data_copy, data.data(), size);

        return JString(size, data_copy);
    }

    mcs::Position MemoryBuffer::read_position()
    {
        auto val = read_long();

        return mcs::Position(val);
    }

    mcs::AbstractBuffer* MemoryBuffer::read_byte_array(mcs_ulong size)
    {
        auto bytes = read_bytes(size);
        auto copy = new mcs_byte[size];

        memcpy(copy, bytes.data(), size);

        return new MemoryBuffer(size, copy);
    }

    mcs::AbstractBuffer* MemoryBuffer::copy_rest()
    {
        size_t lengthRemaining = m_Size - m_Position;
        auto bytes = read_bytes(lengthRemaining);
        auto copy = new mcs_byte[lengthRemaining];
        
        memcpy(copy, bytes.data(), lengthRemaining);

        return new MemoryBuffer(lengthRemaining, copy);
    }

    void MemoryBuffer::write_byte(mcs_byte v)
    {
        m_Data.push_back(v);
        m_Size++;
    }

    void MemoryBuffer::write_ubyte(mcs_ubyte v)
    {
        m_Data.push_back(static_cast<mcs_byte>(v));
        m_Size++;
    }

    void MemoryBuffer::write_short(mcs_short v)
    {
        write_bytes(2, reinterpret_cast<mcs_byte*>(&v));
    }

    void MemoryBuffer::write_ushort(mcs_ushort v)
    {
        write_bytes(2, reinterpret_cast<mcs_byte*>(&v));
    }

    void MemoryBuffer::write_int(mcs_int v)
    {
        write_bytes(4, reinterpret_cast<mcs_byte*>(&v));
    }

    void MemoryBuffer::write_uint(mcs_uint v)
    {
        write_bytes(4, reinterpret_cast<mcs_byte*>(&v));
    }

    void MemoryBuffer::write_long(mcs_long v)
    {
        write_bytes(8, reinterpret_cast<mcs_byte*>(&v));
    }

    void MemoryBuffer::write_ulong(mcs_ulong v)
    {
        write_bytes(8, reinterpret_cast<mcs_byte*>(&v));
    }

    void MemoryBuffer::write_varint(mcs_varint v)
    {
        while(true)
        {
            if((v & ~0x7F) == 0)
            {
                write_byte(static_cast<mcs_byte>(v));
                break;
            }

            write_byte(static_cast<mcs_byte>((v & 0x7F) | 0x80));

            v >>= 7;
        }
    }

    void MemoryBuffer::write_varlong(mcs_varlong v)
    {
        while(true)
        {
            if((v & ~0x7F) == 0)
            {
                write_byte(static_cast<mcs_byte>(v));
                break;
            }

            write_byte(static_cast<mcs_byte>((v & 0x7F) | 0x80));

            v >>= 7;
        }
    }

    void MemoryBuffer::write_float(mcs_float v)
    {
        write_bytes(4, reinterpret_cast<mcs_byte*>(&v));
    }

    void MemoryBuffer::write_double(mcs_double v)
    {
        write_bytes(8, reinterpret_cast<mcs_byte*>(&v));
    }

    void MemoryBuffer::write_string(JString v)
    {
        write_varint(v.size);
        write_bytes(v.size, reinterpret_cast<mcs_byte*>(v.data));
    }

    void MemoryBuffer::write_position(mcs::Position v)
    {
        write_long(v.to_long());
    }

    void MemoryBuffer::write_byte_array(AbstractBuffer* v)
    {
        write_bytes(v->size(), v->data_raw());
    }

    AbstractBuffer::data_type* MemoryBuffer::data_raw()
    {
        return m_Data.data();
    }

    std::vector<AbstractBuffer::data_type> MemoryBuffer::data()
    {
        return m_Data;
    }

    const AbstractBuffer::size_type MemoryBuffer::size()
    {
        return m_Size;
    }
}