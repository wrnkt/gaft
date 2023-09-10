#include <iostream>
#include <format>

#include "interface.hpp"

using namespace std;

void console_interface_t::display_welcome()
{

}

void console_interface_t::display_usage(const std::string& prog)
{
    cout << format("[USAGE]: {} <dir-path>", prog) << endl;
}
