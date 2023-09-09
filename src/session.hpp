#pragma once

#include <vector>
#include "metadata_processor.hpp"

class session_t {
    std::vector<file_metadata_t> f_metadata;
    metadata_processor_t metadata_processor;
};

