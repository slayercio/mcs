#pragma once
#include <mcs/protocol/data_types.hpp>
#include <mcs/buffer/abstract_buffer.hpp>

namespace mcs
{
    struct AbstractPacket
    {
    public:
        virtual mcs_varint      get_data_length() = 0;
        virtual mcs_varint      get_packet_id()   = 0;
        virtual AbstractBuffer* get_data()        = 0;

    public:
        virtual AbstractBuffer* to_buffer()  = 0;
    };
}