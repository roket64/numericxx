#ifndef STRINGMANIP_H
#define STRINGMANIP_H

#include <string>
#include <vector>

#include "../int_types.h"

namespace base64 {
static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string Encode(const std::string &text) {
    std::string ret;

    u32 val = 0;
    i32 valb = -6;

    for (const char &c : text) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            ret.push_back(base64_chars[(val >> valb) & 0x3f]);
            valb -= 6;
        }
    }

    if (valb > -6)
        ret.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3f]);

    while (ret.size() % 4) ret.push_back('=');

    return ret;
}

std::string Decode(const std::string &text) {
    std::string ret;

    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) T[base64_chars[i]] = i;

    u32 val = 0;
    i32 valb = -8;

    for (const char &c : text) {
        if (T[c] == -1) break;

        val = (val << 6) + T[c];
        valb += 6;

        if (valb >= 0) {
            ret.push_back(static_cast<char>((val >> valb) & 0xff));
            valb -= 8;
        }
    }

    return ret;
}
}  // namespace base64

#endif  // stringmanip.h