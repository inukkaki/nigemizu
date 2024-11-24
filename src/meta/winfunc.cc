#include "meta/winfunc.h"

#include <iostream>

#if (defined(__WIN32) || defined(__WIN64))
#include <windows.h>
#endif

namespace nigemizu::meta::winfunc {

namespace impl {

#if (defined(__WIN32) || defined(__WIN64))
using FuncType1 = BOOL (WINAPI *)();
using FuncType2 = HRESULT (WINAPI *)(int);

enum class ProcessDpiAwareness : int {
    kProcessDpiUnaware = 0,
    kProcessSystemDpiAware = 1,
    kProcessPerMonitorDpiAware = 2
};
#endif

}  // namespace impl

namespace {

#if (defined(__WIN32) || defined(__WIN64))
impl::FuncType1 GetSetProcessDPIAware() {
    impl::FuncType1 set_process_dpi_aware = nullptr;
    HMODULE user_dll = LoadLibraryA("User32.dll");
    if (user_dll != nullptr) {
        set_process_dpi_aware =
            (impl::FuncType1)GetProcAddress(user_dll, "SetProcessDPIAware");
    }
    return set_process_dpi_aware;
}

impl::FuncType2 GetSetProcessDpiAwareness() {
    impl::FuncType2 set_process_dpi_awareness = nullptr;
    HMODULE shcore_dll = LoadLibraryA("Shcore.dll");
    if (shcore_dll != nullptr) {
        set_process_dpi_awareness =
            (impl::FuncType2)GetProcAddress(
                shcore_dll, "SetProcessDpiAwareness");
    }
    return set_process_dpi_awareness;
}
#endif

}  // namespace

/*  References:
 *      Eric Wasylishen.
 *      https://discourse.libsdl.org/t/sdl-getdesktopdisplaymode-resolution-
 *      reported-in-windows-10-when-using-app-scaling/22389/4,
 *      (accessed 2024-11-02).
 */
void ResolveBlurriness() {
    #if (defined(__WIN32) || defined(__WIN64))
    bool succeeds = true;
    std::cout
        << "[ResolveBlurriness] Start to resolve the blurriness of the screen."
        << std::endl;

    // Get needed processes from DLLs
    impl::FuncType1 set_process_dpi_aware = GetSetProcessDPIAware();
    impl::FuncType2 set_process_dpi_awareness = GetSetProcessDpiAwareness();

    // Try to resolve the blurriness
    std::cout
        << "[ResolveBlurriness] ";
    if (set_process_dpi_awareness != nullptr) {
        std::cout
            << "Access SetProcessDpiAwareness."
            << std::endl;
        HRESULT result = set_process_dpi_awareness(
            static_cast<int>(
                impl::ProcessDpiAwareness::kProcessPerMonitorDpiAware));
        if (result != S_OK) {
            succeeds = false;
        }
    } else if (set_process_dpi_aware != nullptr) {
        std::cout
            << "Access SetProcessDPIAware."
            << std::endl;
        BOOL result = set_process_dpi_aware();
        if (result == 0) {
            succeeds = false;
        }
    } else {
        std::cout
            << "Failed in accessing any process."
            << std::endl;
    }

    // Report the result
    std::cout
        << "[ResolveBlurriness] "
        << (succeeds ? "Succeeded" : "Failed") << " "
        << "in resolving the blurriness of the screen."
        << std::endl;
    #endif
}

}  // namespace nigemizu::meta::winfunc
