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

bool metadata_processor_t::has_text_extension(const fs::path& f_path)
{
    std::string ext = f_path.extension();
    return is_in(f_path.extension(), ".txt", ".md");
}

// TODO: implement
static bool has_audio_extension(const fs::path& f_path);

path_preprocess_info_t metadata_processor_t::preprocess_info(const fs::path& dir_path) {
    return path_preprocess_info_t {
        .path_exists = path_exists(dir_path),
        .is_dir = is_dir(dir_path)
    };
}

bool metadata_processor_t::add_file_ext_filter(file_ext_filter filter) {
    auto [it, success] = file_ext_filters.insert(filter);
    return success;
}

bool metadata_processor_t::remove_file_ext_filter(file_ext_filter filter) {
    return file_ext_filters.erase(filter);
}

bool metadata_processor_t::path_exists(const fs::path& path) {
    return fs::exists(path);
}

bool metadata_processor_t::is_dir(const fs::path& dir_path) {
    return fs::is_directory(dir_path);
}

bool metadata_processor_t::valid_file_ext(const fs::path& f_path) {
    for(auto filter : file_ext_filters) {
        if(ext_filter_map.find(filter)->second(f_path)) return true;
    }
    return false;
}

// TODO: not implemented
// std::vector<file_metadata_t> get_recursive_file_metadata(const fs::path& dir_path);

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
