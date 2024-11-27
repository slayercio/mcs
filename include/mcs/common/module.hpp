#pragma once
#include <mcs/common/linker.hpp>

namespace mcs
{
    template<typename Interface>
    struct ModuleBase {
    public:
        ModuleBase(void* ptr) {
            m_Ptr = reinterpret_cast<Interface*>(ptr);
        }

        Interface* operator->() {
            return m_Ptr;
        }

    protected:
        Interface* m_Ptr;
    };
}



#define CREATE_MODULE(name, content) \
namespace mcs::modules { \
    struct name content; \
    _MCS_LIB_API void* _Create_ ##name(void* core); \
    _MCS_LIB_API void _Destroy_ ##name(void* ptr); \
    struct name##Module : mcs::ModuleBase<name> { \
        name##Module(void* core) : ModuleBase(_Create_ ##name(core)) {} \
        ~name##Module() { _Destroy_##name(m_Ptr); } \
        void* get () { \
            return (void*) m_Ptr; \
        } \
    }; \
}

#define CREATE_MODULE_IMPL(name) \
namespace mcs::modules { \
    void* _Create_##name(void* core) { \
        auto mod = new name##_Internal{core}; \
        if(core) { \
            reinterpret_cast<mcs::modules::Core*>(core)->set_module(#name, mod);        \
        }\
        return mod;\
    } \
    void _Destroy_##name(void* ptr) { \
        auto name##_ptr = reinterpret_cast<name##_Internal*>(ptr); \
        delete name##_ptr; \
    } \
}