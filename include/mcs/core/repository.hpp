#pragma once
#include <unordered_map>
#include <string>
#include <typeindex>

namespace mcs {
    class Repository {
    public:
        void set(std::string key, void* ptr) 
        {
            m_Items[key] = ptr;
        }

        void* get(std::string key) 
        {
            return m_Items.contains(key) ? m_Items[key] : nullptr;
        }

        void remove(std::string key)
        {
            m_Items.erase(key);
        }

    private:
        std::unordered_map<std::string, void*> m_Items;
    };
}