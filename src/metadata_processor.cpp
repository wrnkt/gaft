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

bool metadata_processor_t::path_exists(const fs::path& p) {
    return fs::exists(p);
}

bool metadata_processor_t::is_dir(const fs::path& p) {
    return fs::is_directory(p);
}

}
