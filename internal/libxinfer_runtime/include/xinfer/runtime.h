// This is the public API for the xInfer Runtime.
// It is designed to be clean, simple, and hide all the complex implementation details
// of TensorRT and CUDA behind a straightforward interface.

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace xinfer {

// A simple structure to represent a multi-dimensional tensor (the data container).
struct Tensor {
    std::vector<int64_t> shape;
    std::vector<float> data;
};

// The main Engine class. This is the primary object users will interact with.
// Note: We use the PIMPL (Pointer to Implementation) idiom here. The `Engine` class
// only holds a pointer to the real implementation (`EngineImpl`), hiding all the
// complex private members (like TensorRT contexts, streams, etc.) from the header file.
class Engine {
public:
    // Factory function to load and create an engine instance from a .plan file.
    // This is the only way to create an Engine. It returns a nullptr on failure.
    static std::unique_ptr<Engine> load(const std::string& plan_path);

    // The core inference function.
    // It takes a map of input tensors and returns a map of output tensors.
    std::unordered_map<std::string, Tensor> predict(
        const std::unordered_map<std::string, Tensor>& inputs);

    // Destructor must be declared in the header when using PIMPL with unique_ptr.
    ~Engine();

private:
    // Private constructor to force use of the `load` factory.
    Engine();

    // The "Pointer to Implementation". All the real logic and complex
    // private members live in the `EngineImpl` class in the .cpp file.
    class EngineImpl;
    std::unique_ptr<EngineImpl> pimpl;
};

} // namespace xinfer