#include <iostream>
#include <optional>
#include <compare>

#include "interface.hpp"
#include "metadata_processor.hpp"
#include "session.hpp"

using namespace std;

const std::set<GAFT_F_EXT>   DEFAULT_SEARCH_EXTS {
    GAFT_F_EXT::TXT
};

const std::set<GAFT_F_KIND>  DEFAULT_SEARCH_KINDS {
    GAFT_F_KIND::TEXT
};


session_t::session_t() 
    : metadata_processor    { *new metadata_processor_t() }
    , default_search_exts   { DEFAULT_SEARCH_EXTS  }
    , default_search_kinds  { DEFAULT_SEARCH_KINDS }
{
    init_defaults();
}

session_t::~session_t() {}

void session_t::init_defaults()
{
    for(auto ext : default_search_exts)
        metadata_processor.add_file_search_ext(ext);

    for(auto kind : default_search_kinds)
        metadata_processor.add_file_search_kind(kind);
}


console_session_t::console_session_t()
    : interface { *new console_interface_t() }
{
}

console_session_t::~console_session_t() {}


void console_session_t::start(int argc, char* argv[])
{
    optional<string> dir_opt = interface.init(argc, argv);

    if(!dir_opt) {
        return;
    }

    auto fm_vec = metadata_processor.get_recursive_file_metadata(dir_opt.value());
    interface.display_metadata_list(fm_vec);

    /*
    std::string path_str;
    bool valid_dir = false;
    bool first_pass = true;
    do {
        if (!first_pass && !valid_dir) interface.alert_invalid_dir();
        path_str = interface.display_directory_prompt();
        auto pp_info = metadata_processor.preprocess_info(path_str);
        valid_dir  = pp_info.is_processable();
        first_pass = false;
    } while (!valid_dir);

    auto fm_vec = metadata_processor.get_recursive_file_metadata(path_str);
    interface.display_metadata_list(fm_vec);
    */
}


