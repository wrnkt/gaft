#pragma once

#include <iostream>
#include <string>
#include <optional>
#include <format>

#include "gaft.hpp"
#include "metadata_processor.hpp"


class interface_t {};

class gui_interface_t: interface_t {};

class console_interface_t: interface_t
{
    public:
        std::optional<std::string>   init                     (int argc, char* argv[]);
        const std::string            display_directory_prompt ();
        void                         alert_invalid_dir        ();
        void                         display_usage            (const std::string& prog);
        void                         display_metadata_list    (std::vector<file_metadata_t> fm_vec);
};
