#pragma once

#include <iostream>
#include <string>
#include <optional>
#include <format>

#include "gaft.hpp"
#include "program_options.hpp"
#include "metadata_processor.hpp"

class interface_t
{
    public:
        interface_t();
        ~interface_t();

        virtual program_options_t program_options() = 0;
    private:
};

class gui_interface_t: public interface_t {};

class console_interface_t: public interface_t
{
    public:
        console_interface_t();
        ~console_interface_t();

        program_options_t program_options() { return program_options_; };
        void program_options(console_program_options_t options) { program_options_ = options; };

        std::optional<std::string>   init                     (int argc, char* argv[]);
        const std::string            display_directory_prompt ();
        void                         alert_invalid_dir        ();
        void                         display_usage            (const std::string& prog);
        void                         display_metadata_list    (std::vector<file_metadata_t> fm_vec);
    private:
        std::vector<std::string>            extract_kinds     (std::string kind_flag_str);

        std::map<std::string, GAFT_F_KIND>  kind_flag_opt_map;
        console_program_options_t           program_options_;
};
