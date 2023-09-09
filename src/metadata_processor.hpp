#pragma once

#include <map>
#include <string>
#include <filesystem>
#include <vector>
#include <set>
#include <functional>

#include "util.h"


namespace fs = std::filesystem;


struct file_metadata_t {
    fs::path file_path;
    std::string file_name;
    uintmax_t file_size;
};

struct path_preprocess_info_t {
    bool path_exists { false };
    bool is_dir { false };
    bool is_processable() {
        return path_exists && is_dir;
    }
};

enum class file_ext_filter {
    TEXT,
    AUDIO,
};


using file_filter_func = std::function<bool(const fs::path&)>;
using file_ext_filter_func = file_filter_func;


class metadata_processor_t {
    public:

        metadata_processor_t();
        ~metadata_processor_t();

        path_preprocess_info_t preprocess_info(const fs::path& p);

        bool remove_file_ext_filter(file_ext_filter f);
        bool add_file_ext_filter(file_ext_filter f);

        bool valid_file_ext(const fs::path& f_path);

        std::vector<file_metadata_t> get_recursive_file_metadata(const fs::path& dir_path);


    private:
        
        // File extension filtering utilities
        std::set<file_ext_filter> file_ext_filters;
        const std::map<file_ext_filter, file_ext_filter_func> ext_filter_map;
        static bool has_text_extension(const fs::path& p);
        static bool has_audio_extension(const fs::path& p);

        // Validation
        bool path_exists(const fs::path& p);
        bool is_dir(const fs::path& p);

        // Metadata collection
        file_metadata_t get_metadata(const fs::path& file_path);
        uintmax_t compute_file_size(const fs::path& p);
};

