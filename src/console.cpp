#include <iostream>
#include <format>

#include "gaft.hpp"
#include "session.hpp"
#include "metadata_processor.hpp"



int main(int argc, char* argv[])
{
    console_session_t session {};
    session.start(argc, argv);
    return 0;
}
