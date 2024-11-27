#include <mcs/protocol/impl/packet.hpp>

namespace mcs
{
    Packet parseCompressedPacket(AbstractBuffer* buffer)
    {
        
    }

    Packet parseUncompressedPacket(AbstractBuffer* buffer)
    {
        auto dataLength = buffer->read_varint();
        auto bytes = buffer->read_byte_array(dataLength);

        auto packetId = bytes->read_varint();
        auto data = bytes->copy_rest();

        return Packet(packetId, data);
    }

    Packet Packet::parse_buffer(AbstractClientSettingsProvider* settingsProvider, AbstractBuffer* buffer)
    {
        auto packetLength = buffer->read_varint();

        if(packetLength >= settingsProvider->get_compression_threshold())
        {
            return parseCompressedPacket(buffer);
        }
        else
        {
            return parseUncompressedPacket(buffer);
        }
    }

    mcs_varint Packet::get_data_length()
    {
        return static_cast<mcs_varint>(m_Data->size());
    }

    AbstractBuffer* Packet::get_data()
    {
        return m_Data;
    }

    Packet::Packet(mcs_varint id, AbstractBuffer* data)
    {
        m_Id = id;
        m_Data = data;
    }

    Packet::Packet(mcs_varint id, mcs::modules::Buffer* bufferModule)
    {
        m_Id = id;
        m_Data = bufferModule->create_buffer();
    }
}