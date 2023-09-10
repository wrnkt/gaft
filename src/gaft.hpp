#pragma once

#include <map>
#include <string>
#include <unordered_map>

enum class GAFT_F_EXT {
    NONE,
    UNKNOWN,
    TXT,
    MD
};

enum class GAFT_F_KIND : char {
    UNKNOWN,
    TEXT,
    AUDIO
};

typedef struct {
    GAFT_F_EXT ext;
    GAFT_F_KIND kind;
} gaft_f_info;


using extension_info_map = const std::unordered_map<std::string, gaft_f_info>;

const extension_info_map FILE_CLASSIFICATION_MAP {
    { "", { GAFT_F_EXT::NONE, GAFT_F_KIND::UNKNOWN } },
    { ".", { GAFT_F_EXT::NONE, GAFT_F_KIND::UNKNOWN } },
    { ".txt", { GAFT_F_EXT::TXT, GAFT_F_KIND::TEXT } },
    { ".md", { GAFT_F_EXT::MD, GAFT_F_KIND::TEXT } }
};
