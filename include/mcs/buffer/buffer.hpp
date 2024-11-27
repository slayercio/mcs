#pragma once

#include <mcs/common/module.hpp>
#include <mcs/buffer/abstract_buffer.hpp>

CREATE_MODULE(Buffer, {
    _MCS_LIB_API virtual mcs::AbstractBuffer* create_buffer() = 0;
    _MCS_LIB_API virtual mcs::AbstractReadBuffer* create_read_buffer(size_t length, char* data) = 0;
    _MCS_LIB_API virtual mcs::AbstractWriteBuffer* create_write_buffer() = 0;
});