add_executable(console console.cpp)
target_compile_features(console PRIVATE cxx_std_20)
target_link_libraries(console PRIVATE gaft_library)

add_executable(gui gui.cpp)
target_compile_features(gui PRIVATE cxx_std_20)
target_link_libraries(gui PRIVATE gaft_library)
