#pragma once

#include <vector>

#include "metadata_processor.hpp"
#include "interface.hpp"


class session_t
{
    public:
        session_t();
        ~session_t();

    private:
        std::vector<file_metadata_t> f_metadata;
        metadata_processor_t& metadata_processor;
};

class console_session_t : session_t
{
    public:
        console_session_t();
        ~console_session_t();

        void prompt(int argc, char* argv[]);
        void log_dir_info(const std::string& f_path_str);

    private:
        console_interface_t& interface;
};

