# This is the root CMakeLists.txt for the ignition-sdk monorepo.
# Its main job is to define the core C++ libraries and orchestrate
# the builds of the language-specific packages.

cmake_minimum_required(VERSION 3.15)
project(IgnitionSDK LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Add Core C++ Libraries ---
# These are our internal, private libraries. They are built first.
add_subdirectory(internal/libxinfer_runtime)
add_subdirectory(internal/libignition_link)

# --- Add Language Packages / Bindings ---
# We add each language package as a subdirectory. The CMakeLists.txt or
# other build files *inside* those directories are responsible for
# building the actual language-native package and linking it against
# our core C++ libraries.

# Add the Python package, which contains its own pybind11 logic.
add_subdirectory(packages/ignition-python)

# Add the Rust package. Its build.rs script will handle linking.
# We might add custom commands here to trigger `cargo build`.
# add_subdirectory(packages/ignition-rust)

# ... and so on for other languages.