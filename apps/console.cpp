#include <iostream>
#include <format>

#include "gaft/session.hpp"

int main(int argc, char* argv[])
{
    console_session_t session {};
    int exit_code = session.start(argc, argv);
    return exit_code;
}
