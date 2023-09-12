#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <optional>
#include <format>

#include "gaft.hpp"
#include "metadata_processor.hpp"

class program_options_t
{
    public:
        program_options_t() {}
        ~program_options_t() {}

        void search_kinds(std::set<GAFT_F_KIND> kinds) { search_kinds_ = kinds; };
        std::set<GAFT_F_KIND> search_kinds() { return search_kinds_; };
        void add_search_kind(GAFT_F_KIND kind) { search_kinds_.insert(kind); };
        void remove_search_kind(GAFT_F_KIND kind) { search_kinds_.erase(kind); };

        void search_exts(std::set<GAFT_F_EXT> exts) { search_exts_ = exts; };
        std::set<GAFT_F_EXT> search_exts() { return search_exts_; };
        void add_search_ext(GAFT_F_EXT ext) { search_exts_.insert(ext); };
        void remove_search_ext(GAFT_F_EXT ext) { search_exts_.erase(ext); };

    private:
        std::set<GAFT_F_KIND> search_kinds_ {};
        std::set<GAFT_F_EXT> search_exts_ {};
};



const std::map<std::string, GAFT_F_KIND> KIND_FLAG_OPTIONS_MAP {
    { "text", GAFT_F_KIND::TEXT },
    { "audio", GAFT_F_KIND::AUDIO },
};

class console_program_options_t : public program_options_t {
    public:
        console_program_options_t() {}
        ~console_program_options_t() {}

        std::vector<std::string> search_kinds(std::vector<std::string> kinds)
        {
            std::vector<std::string> rejected_kinds {};
            for(std::string kind_str : kinds) {
                try {
                    GAFT_F_KIND kind = KIND_FLAG_OPTIONS_MAP.at(kind_str);
                    add_search_kind(kind);
                } catch (std::out_of_range& e) {
                    rejected_kinds.push_back(kind_str);
                }
            }
            return rejected_kinds;
        }

        std::vector<std::string> search_exts(std::vector<std::string> exts)
        {
            std::string period = ".";
            std::string* built_ext;
            std::vector<std::string> rejected_exts {};
            for(std::string ext_str : exts) {
                built_ext = &(period.append(ext_str));
                try {
                    GAFT_F_EXT ext = FILE_CLASSIFICATION_MAP.at(*built_ext).ext;
                    add_search_ext(ext);
                } catch (std::out_of_range& e) {
                    rejected_exts.push_back(ext_str);
                }
            }
            return rejected_exts;
        }

};
