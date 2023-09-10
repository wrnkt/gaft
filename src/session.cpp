#include <iostream>
#include <compare>

#include "interface.hpp"
#include "metadata_processor.hpp"
#include "session.hpp"

using namespace std;

session_t::session_t() 
    : metadata_processor { *new metadata_processor_t() }
{}

session_t::~session_t(){}



console_session_t::console_session_t()
    : interface { *new console_interface_t() }
{
}

console_session_t::~console_session_t()
{
}


void console_session_t::prompt(int argc, char* argv[])
{
    if (argc <= 1) {
        interface.display_usage(argv[0]);
    } else {
        string s(argv[1]);
        if(s.compare("-h") == 0 || argc > 2) {
            interface.display_usage(argv[0]);
        }
    }
    bool valid_dir = false;
    bool first_pass = true;
    do {
        if (!first_pass) interface.alert_invalid_dir();
        std::string path_str = interface.display_directory_prompt();
        auto pp_info = metadata_processor.preprocess_info(path_str);
        valid_dir  = pp_info.is_processable();
        first_pass = false;
    } while (!valid_dir);

}


