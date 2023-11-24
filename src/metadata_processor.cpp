#include "gaft/metadata_processor.hpp"
#include "gaft/gaft.hpp"
#include "gaft/program_options.hpp"

#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <optional>
#include <algorithm>
#include <iterator>


metadata_processor_t::metadata_processor_t() {}
metadata_processor_t::~metadata_processor_t() {}


bool metadata_processor_t::should_process(const fs::path& f_path, file_search_opts_t opts)
{
    try {
        const auto& [ext, kind] = FILE_CLASSIFICATION_MAP.at(f_path.extension());
        if(opts._exts.contains(ext) || opts._kinds.contains(kind)) return true;
    } catch (const std::out_of_range &e) {
        return false;
    };
    return false;
}

bool metadata_processor_t::is_processable(const fs::path& f_path)
{
    return fs::is_regular_file(f_path) && fs::exists(f_path);
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


std::optional<std::vector<file_metadata_t>> metadata_processor_t::get_recursive_file_metadata(const fs::path& dir_path, file_search_opts_t search_opts)
{
    if( !(path_exists(dir_path) && is_dir(dir_path)) ) {
        return std::nullopt;
    }
    std::vector<file_metadata_t> fm_vec {};
    for(fs::path f_path : fs::recursive_directory_iterator(dir_path)) {
        if(is_processable(f_path) && should_process(f_path, search_opts)) {
            fm_vec.push_back(get_metadata(f_path));
        }
    }
    return std::make_optional(fm_vec);
}

file_metadata_t metadata_processor_t::get_metadata(const fs::path& f_path)
{
    file_metadata_t fm {};
    fm.file_path(f_path);
    uintmax_t f_size = compute_file_size(fm.file_path());
    fm.file_size(f_size);
    return fm;
}

uintmax_t metadata_processor_t::compute_file_size(const fs::path& f_path)
{
    auto err = std::error_code {};
    auto filesize = fs::file_size(f_path, err);
    if (filesize != static_cast<uintmax_t>(-1)) {
        return filesize;
    }
    return static_cast<uintmax_t>(-1);
}
