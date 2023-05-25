# Set the include directories
set(mylib_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/build")

# Set the library directories and link libraries
set(mylib_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/libmylib.so")
set(mylib_LINK_LIBRARIES mylib)

# Create an imported target
add_library(mylib SHARED IMPORTED GLOBAL)
set_target_properties(mylib PROPERTIES
        IMPORTED_LOCATION "${mylib_LIBRARIES}"
        INTERFACE_INCLUDE_DIRECTORIES "${mylib_INCLUDE_DIRS}"
        INTERFACE_LINK_LIBRARIES "${mylib_LINK_LIBRARIES}"
        )
