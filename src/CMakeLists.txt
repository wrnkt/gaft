# headers must be listed in add_library to show up in IDEs
set(HEADER_LIST "${GAFT_SOURCE_DIR}/include/gaft/*.hpp")

add_library(gaft_library
            session.cpp interface.cpp metadata_processor.cpp
            ${HEADER_LIST)

target_include_directories(gaft_library PUBLIC ../include)

target_link_libraries(gaft_library PRIVATE Boost::boost)
target_link_libraries(gaft_library PRIVATE raylib::raylib)
target_link_libraries(gaft_library PRIVATE raygui::raygui)

target_compile_features(gaft_library PUBLIC cxx_std_20)
