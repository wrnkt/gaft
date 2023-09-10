#include <iostream>
#include <format>
#include "metadata_processor.hpp"

int main(int argc, char* argv[])
{
    std::string path = argv[1];

    metadata_processor_t proc;

    proc.add_file_ext_filter(file_ext_filter::TEXT);
    //proc.add_file_ext_filter(file_ext_filter::AUDIO);

    path_preprocess_info_t info = proc.preprocess_info(path);

    std::cout << std::format("path_exists: {}\nis_dir: {}\nis_processable: {}", info.path_exists, info.is_dir, info.is_processable()) << std::endl;

    if(!info.is_processable()) {
        return 1;
    }

    auto fm_vec = proc.get_recursive_file_metadata(path);

    for(file_metadata_t fm : fm_vec) {
        std::cout << "filename: " << fm.file_name << std::endl;
        std::cout << "file size: " << fm.file_size << std::endl;
        std::cout << "\n";
    }

    return 0;
}
