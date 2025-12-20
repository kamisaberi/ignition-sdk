# This CMakeLists.txt defines the build for our core C++ inference runtime library.

# Define the library target.
# We create a STATIC library, meaning its code will be copied directly into
# the final language bindings, resulting in a self-contained package.
add_library(xinfer_runtime STATIC
    src/runtime.cpp
    # ... other .cpp files would be listed here
)

# Specify the include directories.
# The `PUBLIC` keyword means that any target that links against this library
# will also automatically get this include path.
target_include_directories(xinfer_runtime PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# --- Find Dependencies ---
# Here, we would find the required system libraries like CUDA and TensorRT.
# This is a simplified example. A real project would have more robust logic.

# Find the CUDA toolkit
find_package(CUDA REQUIRED)
target_link_libraries(xinfer_runtime PUBLIC CUDA::cudart)

# Find TensorRT
# In a real project, you would have a FindTensorRT.cmake module to locate these.
# find_package(TensorRT REQUIRED)
# target_include_directories(xinfer_runtime PUBLIC ${TensorRT_INCLUDE_DIRS})
# target_link_libraries(xinfer_runtime PUBLIC ${TensorRT_LIBRARIES})

message(STATUS "Configured C++ library: xinfer_runtime")