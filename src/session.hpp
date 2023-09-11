#pragma once

#include <vector>

#include "metadata_processor.hpp"
#include "interface.hpp"


class session_t
{
    public:
        session_t  ();
        ~session_t ();

        metadata_processor_t&        metadata_processor;

        std::set<GAFT_F_EXT>         default_search_exts;
        std::set<GAFT_F_KIND>        default_search_kinds;

    private:
        void init_defaults();

        std::vector<file_metadata_t> f_metadata;
};

class console_session_t : session_t
{
    public:
        console_session_t  ();
        ~console_session_t ();

        void start         (int argc, char* argv[]);
        void log_dir_info  (const std::string& f_path_str);

        console_interface_t& interface;

    private:
};

