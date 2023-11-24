#include <iostream>
#include <optional>
#include <compare>

#include "gaft/gaft.hpp"
#include "gaft/interface.hpp"
#include "gaft/metadata_processor.hpp"
#include "gaft/session.hpp"

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
    // WARN: calling virtual get_interface when initializing session defaults.
    // Needs to be a reference to an interface before calling init_defaults.
    
    // for(auto ext : default_search_exts)
    //     //get_interface().program_options().add_search_ext(ext);
    //
    // for(auto kind : default_search_kinds)
    //     get_interface().program_options().add_search_kind(kind);
}

bool session_t::some_search_settings()
{
    return !get_interface().program_options().search_kinds().empty();
}

bool session_t::some_kind_settings()
{
    return !get_interface().program_options().search_exts().empty();
}

bool session_t::some_settings()
{
    return some_search_settings() || some_kind_settings();
}


console_interactive_session_t::console_interactive_session_t()
    : interface { *new console_interactive_interface_t() }
{
}

console_interactive_session_t::~console_interactive_session_t() {}


interface_t& console_interactive_session_t::get_interface()
{
    return this->interface;
}

void console_interactive_session_t::start(int argc, char* argv[])
{
    optional<string> dir_opt = this->interface.init(argc, argv);

    if(!dir_opt) return;

    auto fm_vec_opt = metadata_processor.get_recursive_file_metadata(
                            dir_opt.value(),
                            get_interface().program_options().file_search_opts()
                      );

    if( !fm_vec_opt ) {
        interface.alert_invalid_dir();
        return;
    }

    interface.display_metadata_list(fm_vec_opt.value());
}

int console_session_t::start(int argc, char* argv[])
{
    return 0;
}
