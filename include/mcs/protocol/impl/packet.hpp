#pragma once
#include <mcs/protocol/abstract_packet.hpp>
#include <mcs/networking/abstract_client_settings_provider.hpp>
#include <mcs/buffer/buffer.hpp>

namespace mcs
{
    struct Packet: public AbstractPacket
    {
    public:
        static Packet parse_buffer(AbstractClientSettingsProvider* settingsProvider, AbstractBuffer* buffer);

    public:
        mcs_varint get_data_length();
        mcs_varint get_packet_id();
        AbstractBuffer* get_data();

    public:
        AbstractBuffer* to_buffer();

    public:
        Packet(mcs_varint id, AbstractBuffer* data);
        Packet(mcs_varint id, mcs::modules::Buffer* bufferModule);

    private:
        mcs_varint m_Id;
        AbstractBuffer* m_Data;
    };
    
} // namespace mcs
