#include "metadata_processor.hpp"

#include <string>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <iterator>

metadata_processor_t::metadata_processor_t()
    : file_ext_filters {}
    , ext_filter_map {
        { file_ext_filter::TEXT, has_text_extension }
    }
{
}

metadata_processor_t::~metadata_processor_t()
{
}


path_preprocess_info_t metadata_processor_t::preprocess_info(const fs::path& p) {
    return path_preprocess_info_t {
        .path_exists = path_exists(p),
        .is_dir = is_dir(p)
    };
}

// TODO: not implemented
// std::vector<file_metadata_t> get_recursive_file_metadata(const fs::path& dir_path);

// TODO: not implemented
// bool remove_file_filter(file_filter f);
bool metadata_processor_t::add_file_ext_filter(file_ext_filter f) {
    auto [it, success] = file_ext_filters.insert(f);
    return success;
}

// TODO: not implemented
// bool remove_file_ext_filter(file_filter f);

bool metadata_processor_t::path_exists(const fs::path& p) {
    return fs::exists(p);
}

bool metadata_processor_t::is_dir(const fs::path& p) {
    return fs::is_directory(p);
}

// TODO: not implemented
//bool metadata_processor_t::valid_file(const fs::path& f_path);

// TODO: not implemented
// bool metadata_processor_t::get_metadata(const fs::path& file_path, file_metadata_t* const fm);
