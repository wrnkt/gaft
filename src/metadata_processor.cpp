#include "metadata_processor.hpp"

#include <string>
#include <filesystem>
#include <vector>

using namespace std;

path_preprocess_info_t metadata_processor_t::preprocess_info(const filesystem::path& p) {
    return path_preprocess_info_t {
        .path_exists = path_exists(p),
        .is_dir = is_dir(p)
    };
}

bool metadata_processor_t::path_exists(const filesystem::path& p) {
    return filesystem::exists(p);
}

bool metadata_processor_t::is_dir(const filesystem::path& p) {
    return filesystem::is_directory(p);
}
