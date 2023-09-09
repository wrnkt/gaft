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

bool metadata_processor_t::has_text_extension(const fs::path& p)
{
    std::string ext = p.extension();
    return is_in(p.extension(), ".txt", ".md");
}

// TODO: implement
static bool has_audio_extension(const fs::path& p);

path_preprocess_info_t metadata_processor_t::preprocess_info(const fs::path& p) {
    return path_preprocess_info_t {
        .path_exists = path_exists(p),
        .is_dir = is_dir(p)
    };
}

bool metadata_processor_t::add_file_ext_filter(file_ext_filter f) {
    auto [it, success] = file_ext_filters.insert(f);
    return success;
}

bool metadata_processor_t::remove_file_ext_filter(file_ext_filter f) {
    return file_ext_filters.erase(f);
}

bool metadata_processor_t::path_exists(const fs::path& p) {
    return fs::exists(p);
}

bool metadata_processor_t::is_dir(const fs::path& p) {
    return fs::is_directory(p);
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

uintmax_t metadata_processor_t::compute_file_size(const fs::path& path)
{
    auto err = std::error_code {};
    auto filesize = fs::file_size(path, err);
    if (filesize != static_cast<uintmax_t>(-1))
        return filesize;
    return static_cast<uintmax_t>(-1);
}
