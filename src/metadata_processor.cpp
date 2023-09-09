#include "metadata_processor.hpp"

#include <string>
#include <filesystem>
#include <vector>

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

// TODO: not implemented
// bool add_file_filter(file_filter f);

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
