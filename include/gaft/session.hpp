#pragma once

#include <memory>
#include <vector>

#include "metadata_processor.hpp"
#include "interface.hpp"

class session_t
{
    public:
        session_t  ();
        ~session_t ();

        void init_defaults             ();
        bool some_settings             ();
        bool some_search_settings      ();
        bool some_kind_settings        ();

        std::set<GAFT_F_EXT>         default_search_exts;
        std::set<GAFT_F_KIND>        default_search_kinds;

        std::unique_ptr<metadata_processor_t> metadata_processor;

        std::shared_ptr<interface_t> interface;

    private:

        std::vector<file_metadata_t> f_metadata;
};

class console_interactive_session_t : session_t
{
    public:
        console_interactive_session_t  ();
        ~console_interactive_session_t ();

        void start         (int argc, char* argv[]);
        void log_dir_info  (const std::string& f_path_str);

    private:
        std::shared_ptr<console_interactive_interface_t> get_interface();
};

class console_session_t : session_t
{
    public:
        console_session_t    ();
        ~console_session_t   ();

        int start            (int argc, char* argv[]);
};

