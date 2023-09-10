#include <iostream>
#include <format>

#include "interface.hpp"

using namespace std;


void console_interface_t::display_usage(const std::string& prog)
{
    cout << format("[USAGE]: {} <directory>", prog) << endl;
    cout << format("See a flat map of your files in the given directory, tag, and categorize them.", prog) << endl;
}

void console_interface_t::alert_invalid_dir()
{
    cout << "[ERROR]: Invalid directory." << endl;
}

const std::string console_interface_t::display_directory_prompt()
{
    string input {};
    cout << endl;
    cout << "Enter the path to a directory." << endl;
    cout << ":::   ";
    getline(cin, input);
    return input;
}
