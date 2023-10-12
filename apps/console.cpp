#include <iostream>
#include <format>

#include "gaft/session.hpp"

int main(int argc, char* argv[])
{
    console_interactive_session_t session {};
    session.start(argc, argv);
    return 0;
}
