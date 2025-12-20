// This file uses pybind11 to create the Python bindings for our C++ library.
// It creates a native Python module (`_ignition_internal.so`) that the
// high-level Python code can import.

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>       // For automatic conversion of C++ STL containers
#include <pybind11/numpy.h>    // For converting between xinfer::Tensor and NumPy arrays

#include "xinfer/runtime.h"    // Include our core C++ API

namespace py = pybind11;

// The name of the module defined here MUST match the name in CMakeLists.txt
PYBIND11_MODULE(_ignition_internal, m) {
    m.doc() = "Internal C++ bindings for the Ignition AI SDK";

    // --- Tensor Binding ---
    // We create a Python class `Tensor` that mirrors our C++ struct.
    py::class_<xinfer::Tensor>(m, "Tensor")
        .def(py::init<>())
        // Expose the 'shape' and 'data' members as properties.
        .def_readwrite("shape", &xinfer::Tensor::shape)
        .def("data_numpy", [](xinfer::Tensor &t) {
            // This is a powerful feature: a function that returns the tensor data
            // as a NumPy array without copying the data.
            return py::array_t<float>(t.shape, t.data.data());
        });

    // --- Engine Binding ---
    // We create a Python class `Engine` that wraps our C++ Engine.
    py::class_<xinfer::Engine>(m, "Engine")
        // Expose the static `load` method. We need to specify the return value policy
        // to correctly manage the lifecycle of the unique_ptr.
        .def_static("load", &xinfer::Engine::load, py::arg("plan_path"),
                    "Loads an optimized engine from a .plan file.",
                    py::return_value_policy::take_ownership)

        // Expose the `predict` method.
        .def("predict", [](xinfer::Engine &self,
                           const std::unordered_map<std::string, py::array_t<float>> &inputs) {

            // This lambda function is the "translation layer".
            // It converts the Python inputs (a dict of NumPy arrays) into the
            // C++ types our engine expects, and then converts the C++ results back.

            // 1. Convert Python NumPy inputs to C++ xinfer::Tensor inputs
            std::unordered_map<std::string, xinfer::Tensor> cpp_inputs;
            for (auto const& [name, arr] : inputs) {
                py::buffer_info info = arr.request();
                cpp_inputs[name] = xinfer::Tensor {
                    .shape = std::vector<int64_t>(info.shape.begin(), info.shape.end()),
                    .data = std::vector<float>(static_cast<float*>(info.ptr), static_cast<float*>(info.ptr) + info.size)
                };
            }

            // 2. Call the actual C++ predict method
            auto cpp_outputs = self.predict(cpp_inputs);

            // 3. Convert C++ xinfer::Tensor outputs back to Python NumPy outputs
            std::unordered_map<std::string, py::array_t<float>> py_outputs;
            for (auto const& [name, tensor] : cpp_outputs) {
                py_outputs[name] = py::array_t<float>(tensor.shape, tensor.data.data());
            }

            return py_outputs;
        }, "Runs inference on a batch of inputs.");
}