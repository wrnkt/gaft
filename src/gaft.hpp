#pragma once

#include <map>
#include <string>
#include <unordered_map>

enum class GAFT_F_EXT {
    NONE,
    UNKNOWN,

    TXT,
    MD,

    MP3,
    MP4,
    WAV
};

enum class GAFT_F_KIND : char {
    UNKNOWN,
    TEXT,
    AUDIO,
    VIDEO
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
    { ".md", { GAFT_F_EXT::MD, GAFT_F_KIND::TEXT } },

    { ".mp3", { GAFT_F_EXT::MP3, GAFT_F_KIND::AUDIO } },
    { ".mp4", { GAFT_F_EXT::MP4, GAFT_F_KIND::VIDEO } },
    { ".wav", { GAFT_F_EXT::WAV, GAFT_F_KIND::AUDIO } }
};
