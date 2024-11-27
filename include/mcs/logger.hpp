#pragma once
#include <mcs/common/linker.hpp>
#include <mcs/common/module.hpp>
#include <string>

CREATE_MODULE(Logger, {
    _MCS_LIB_API virtual void info(std::string msg) = 0;
    _MCS_LIB_API virtual void error(std::string msg) = 0;
    _MCS_LIB_API virtual void warn(std::string msg) = 0;
    _MCS_LIB_API virtual void critical(std::string msg) = 0;
    _MCS_LIB_API virtual void debug(std::string msg) = 0;
});