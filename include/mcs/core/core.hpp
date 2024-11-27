#include <mcs/common/module.hpp>
#include <string>

CREATE_MODULE(Core, {
    _MCS_LIB_API virtual void* get_module(std::string name) = 0;
    _MCS_LIB_API virtual void set_module(std::string name, void* ptr) = 0;
    _MCS_LIB_API virtual void delete_module(std::string name) = 0;
});