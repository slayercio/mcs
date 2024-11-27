#pragma once
#include <mcs/protocol/data_types.hpp>

namespace mcs
{
    struct AbstractClientSettingsProvider
    {
        virtual mcs_varint get_compression_threshold() = 0;
    };
}