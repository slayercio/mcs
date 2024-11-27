#pragma once

#include <mcs/common/linker.hpp>
#include <mcs/common/module.hpp>

CREATE_MODULE(Networking, {
    _MCS_LIB_API virtual void* create_server(short port) = 0;
    _MCS_LIB_API virtual void  delete_server(void* server) = 0;
});