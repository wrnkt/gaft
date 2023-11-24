#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <optional>
#include <vector>
#include <format>
#include <set>

#include "gaft.hpp"


struct file_search_opts_t {
    std::set<GAFT_F_KIND> _kinds {};
    std::set<GAFT_F_EXT>  _exts {};
};

class program_options_t
{
    public:
        program_options_t() {}
        ~program_options_t() {}

        void search_kinds(std::set<GAFT_F_KIND> kinds) { this->file_search_opts()._kinds = kinds; };
        std::set<GAFT_F_KIND> search_kinds() { return this->_file_search_opts._kinds; };
        void add_search_kind(GAFT_F_KIND kind) { this->_file_search_opts._kinds.insert(kind); };
        size_t remove_search_kind(GAFT_F_KIND kind) { return this->_file_search_opts._kinds.erase(kind); };

        void search_exts(std::set<GAFT_F_EXT> exts) { this->_file_search_opts._exts = exts; };
        std::set<GAFT_F_EXT> search_exts() { return this->_file_search_opts._exts; };
        void add_search_ext(GAFT_F_EXT ext) { this->_file_search_opts._exts.insert(ext); };
        size_t remove_search_ext(GAFT_F_EXT ext) { return this->_file_search_opts._exts.erase(ext); };

        file_search_opts_t file_search_opts() { return this->_file_search_opts; };

    private:
        file_search_opts_t _file_search_opts {};
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
