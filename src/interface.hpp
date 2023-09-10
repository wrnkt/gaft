#pragma once

#include <iostream>
#include <string>
#include <format>

class interface_t
{
};

class console_interface_t: interface_t
{
    public:
        void display_welcome();
        void display_usage();
        const std::string& display_directory_prompt();
};

class gui_interface_t: interface_t
{
};
