#include "str_convert.h"

#include <codecvt>

std::string utf16_to_utf8(std::basic_string_view<WCHAR_T> src) {
#ifdef _WINDOWS
    // VS bug
    // https://social.msdn.microsoft.com/Forums/en-US/8f40dcd8-c67f-4eba-9134-a19b9178e481/vs-2015-rc-linker-stdcodecvt-error?forum=vcgeneral
    static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> cvt_utf8_utf16;
    return cvt_utf8_utf16.to_bytes(reinterpret_cast<const wchar_t *>(src.data()),
                                   reinterpret_cast<const wchar_t *>(src.data() + src.size()));
#else
    static std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> cvt_utf8_utf16;
    return cvt_utf8_utf16.to_bytes(reinterpret_cast<const char16_t *>(src.data()),
                                   reinterpret_cast<const char16_t *>(src.data() + src.size()));
#endif
}

std::basic_string<WCHAR_T> utf8_to_utf16(std::string_view src) {
#ifdef _WINDOWS
    static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> cvt_utf8_utf16;
    std::wstring tmp = cvt_utf8_utf16.from_bytes(src.data(), src.data() + src.size());
    return std::basic_string(reinterpret_cast<const WCHAR_T *>(tmp.data()), tmp.size());
#else
    static std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> cvt_utf8_utf16;
    std::u16string tmp = cvt_utf8_utf16.from_bytes(src.data(), src.data() + src.size());
    return std::basic_string(reinterpret_cast<const WCHAR_T *>(tmp.data()), tmp.size());
#endif
}
