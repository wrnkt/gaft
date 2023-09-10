#include <iostream>

#include "interface.hpp"
#include "metadata_processor.hpp"
#include "session.hpp"

session_t::session_t() 
    : metadata_processor { *new metadata_processor_t() }
{}

session_t::~session_t() {}


console_session_t::console_session_t()
    : interface { *new console_interface_t() }
{
}

console_session_t::~console_session_t() {}


void console_session_t::prompt(int argc, char* argv[])
{
    if( argc != 2 ) {
        interface.display_usage(argv[0]);
    }
}


