#include <boost/program_options/parsers.hpp>
#include <boost/program_options/positional_options.hpp>
#include <iostream>
#include <format>
#include <boost/program_options.hpp>

#include "interface.hpp"

using namespace std;
namespace po = boost::program_options;

optional<string> console_interface_t::init(int argc, char* argv[])
{
    po::options_description general;
    general.add_options()
        ("help,h", "view program help")
        ("interactive,i", "start in interactive mode")
        /*
           ("kinds",
           po::value<vector<string>>(&opt)->default_value(),
           "kinds of files to include/exclude")
           ("exts",
           po::value<vector<string>>(&opt)->default_value(),
           "file extensions to include/exclude")
           */
        ;

    po::options_description hidden;
    hidden.add_options()
        ("search_dir", po::value<string>(), "search directory")
        ;

    // NOTE: accepted on command line
    po::options_description cmdline_options;
    cmdline_options.add(general).add(hidden);

    // NOTE: show with --help
    po::options_description visible("OPTIONS");
    visible.add(general);

    po::positional_options_description p;
    p.add("search_dir", -1);

    po::variables_map v_map;

    try {
        po::store(
            po::command_line_parser(argc, argv)
                .options(cmdline_options).positional(p).run(),
            v_map
        );
        po::notify(v_map);

    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    if(
        (v_map.count("help") || !v_map.count("search_dir"))
        && !v_map.count("interactive")
      ) {
        display_usage(argv[0]);
        cout << visible << endl;
        return nullopt;
    }

    if(v_map.count("search_dir")) {
        return optional<string>(v_map["search_dir"].as<string>());
    }

    return nullopt;
}



void console_interface_t::display_usage(const std::string& prog)
{
    cout << format("USAGE: {} [FLAGS] <directory>", prog) << endl;
    cout << format("See a flat map of files in a given directory, tag, and categorize them.", prog) << endl;
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

void console_interface_t::display_metadata_list(vector<file_metadata_t> fm_vec)
{
    cout << endl;
    cout << "FILES:" << endl;
    cout << "----------------" << endl;
    for(auto metadata : fm_vec) {
        cout << metadata.file_name() << endl;
    }
}
