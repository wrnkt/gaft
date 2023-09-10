#include "metadata_processor.hpp"
#include "gaft.hpp"

#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <iterator>


metadata_processor_t::metadata_processor_t() {}
metadata_processor_t::~metadata_processor_t() {}


{
}

{
}


{
    return success;
}

{
}


{
    return false;
}


path_preprocess_info_t metadata_processor_t::preprocess_info(const fs::path& dir_path)
{
    return path_preprocess_info_t {
        .path_exists = path_exists(dir_path),
        .is_dir = is_dir(dir_path)
    };
}

bool metadata_processor_t::path_exists(const fs::path& path)
{
    return fs::exists(path);
}

bool metadata_processor_t::is_dir(const fs::path& dir_path)
{
    return fs::is_directory(dir_path);
}


std::vector<file_metadata_t> metadata_processor_t::get_recursive_file_metadata(const fs::path& dir_path)
{
    std::vector<file_metadata_t> fm_vec {};
    for(fs::path f_path : fs::recursive_directory_iterator(dir_path)) {
        if(is_processable(f_path) && should_process(f_path)) {
            fm_vec.push_back(get_metadata(f_path));
        }
    }
    return fm_vec;
}

file_metadata_t metadata_processor_t::get_metadata(const fs::path& f_path)
{
    file_metadata_t fm {};
    if(f_path.has_filename()) {
        fm.file_name = f_path.filename();
    }
    return fm;
}

uintmax_t metadata_processor_t::compute_file_size(const fs::path& f_path)
{
    auto err = std::error_code {};
    auto filesize = fs::file_size(f_path, err);
    if (filesize != static_cast<uintmax_t>(-1))
        return filesize;
    return static_cast<uintmax_t>(-1);
}
