#include <iostream>
#include <format>
#include "metadata_processor.hpp"

int main(int argc, char* argv[])
{
    std::string path = argv[1];

    metadata_processor_t proc;
    proc.add_file_filter(file_ext_filter::TEXT);
    path_preprocess_info_t info = proc.preprocess_info(path);
    std::cout << std::format("path_exists: {}\nis_dir: {}\nis_valid: {}", info.path_exists, info.is_dir, info.is_processable()) << std::endl;
    std::cout << std::format("valid file: {}\n", proc.valid_file_ext(path)) << std::endl;
    return 0;
}
