#include <boost/program_options/parsers.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/tokenizer.hpp>
#include <boost/token_functions.hpp>
#include <iostream>
#include <format>
#include <boost/program_options.hpp>

#include "gaft.hpp"
#include "interface.hpp"
#include "program_options.hpp"

using namespace std;
namespace po = boost::program_options;


interface_t::interface_t() {}

interface_t::~interface_t() {}


console_interface_t::console_interface_t()
    : kind_flag_opt_map { KIND_FLAG_OPTIONS_MAP }
    , program_options_ { *new console_program_options_t() }
{
}

console_interface_t::~console_interface_t() {}


optional<string> console_interface_t::init(int argc, char* argv[])
{
    po::options_description general;
    general.add_options()
        ("help,h", "view program help")
        ("interactive,i", "start in interactive mode")
           ("kind",
           po::value<string>()->composing(),
           "list kinds of files to include (text, audio, image...)")
           ("ext",
           po::value<string>()->composing(),
           "file extensions to include (txt, md, mp4, ...)")
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

    // TODO: factor out warning printing
    
    if(v_map.count("kind")) {
        string kind_flag_str = v_map["kind"].as<string>();
        vector<string> kinds_str_vec = comma_sep_flag_args(kind_flag_str);

        vector<string> rejected_kinds = program_options_.search_kinds(kinds_str_vec);

        if(rejected_kinds.size() > 0) {
            cout << "[WARNING]: Unrecognized options for --kind:";
            for(auto kind : rejected_kinds) {
                cout << format(" {}", kind);
            }
            cout << endl;
        }
    }

    if(v_map.count("ext")) {
        string ext_flag_str = v_map["ext"].as<string>();
        vector<string> exts_str_vec = comma_sep_flag_args(ext_flag_str);

        vector<string> rejected = program_options_.search_exts(exts_str_vec);

        if(rejected.size() > 0) {
            cout << "[WARNING]: Unrecognized options for --ext:";
            for(auto ext : rejected) {
                cout << format(" {}", ext);
            }
            cout << endl;
        }
    }

    if(v_map.count("search_dir")) {
        return optional<string>(v_map["search_dir"].as<string>());
    }

    return nullopt;
}


vector<string> console_interface_t::comma_sep_flag_args(string flag_str)
{
    vector<string> args;
    boost::char_separator<char> sep(",");
    boost::tokenizer<boost::char_separator<char>> tokens(flag_str, sep);
    for(const auto& t : tokens) {
        args.push_back(t);
    }
    return args;
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
    cout << format("FILES ({} found):", fm_vec.size()) << endl;
    cout << "----------------" << endl;
    for(auto metadata : fm_vec) {
        cout << metadata.file_name() << endl;
    }
}
