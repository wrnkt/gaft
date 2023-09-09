#include "metadata_processor.hpp"

#include <string>
#include <filesystem>
#include <vector>

using namespace std;


dir_process_result_t metadata_processor_t::confirm_for_processing(const filesystem::path& p) {
    dir_process_result_t result {
        .path_exists = path_exists(p),
        .is_dir = is_dir(p)
    };
    return result;
}

bool metadata_processor_t::path_exists(const filesystem::path& p) {
    return filesystem::exists(p);
}

bool metadata_processor_t::is_dir(const filesystem::path& p) {
    return filesystem::is_directory(p);
}
