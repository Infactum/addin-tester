#ifndef STR_CONVERT_H
#define STR_CONVERT_H

#include <string>

#include "types.h"

std::string utf16_to_utf8(std::basic_string_view<WCHAR_T> src);

std::basic_string<WCHAR_T> utf8_to_utf16(std::string_view src);

#endif //STR_CONVERT_H
