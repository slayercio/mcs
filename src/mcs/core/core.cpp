#include <mcs/core/core.hpp>
#include <mcs/core/repository.hpp>
#include <iostream>
#include <algorithm>

struct Core_Internal: public mcs::modules::Core {
    Core_Internal(void*) {}
    
    void* get_module(std::string key) 
    {
        std::transform(key.begin(), key.end(), key.begin(),
            [](unsigned char c) { return std::tolower(c); });
        return m_Repository.get(key);
    }

    void set_module(std::string key, void* ptr)
    {
        std::transform(key.begin(), key.end(), key.begin(),
            [](unsigned char c) { return std::tolower(c); });
        m_Repository.set(key, ptr);
    }

    void delete_module(std::string key)
    {
        m_Repository.remove(key);
    }

private:
    mcs::Repository m_Repository;
};

CREATE_MODULE_IMPL(Core);