#include <mcs/buffer/buffer.hpp>
#include <mcs/buffer/impl/memory_buffer.hpp>
#include <mcs/core/core.hpp>

struct Buffer_Internal: public mcs::modules::Buffer
{
    Buffer_Internal(void* core)
    {
    }

    mcs::AbstractBuffer* create_buffer()
    {
        return new mcs::MemoryBuffer();
    }

    mcs::AbstractReadBuffer* create_read_buffer(size_t length, char* data)
    {
        return new mcs::MemoryBuffer(length, reinterpret_cast<mcs::mcs_byte*>(data));
    }
    
    mcs::AbstractWriteBuffer* create_write_buffer()
    {
        return create_buffer();
    }
};

CREATE_MODULE_IMPL(Buffer);