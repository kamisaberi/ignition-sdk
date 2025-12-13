# Ignition AI: Python SDK (`ignition-infer`)

<p align="center">
    <a href="https://pypi.org/project/ignition-infer/">
        <img src="https://badge.fury.io/py/ignition-infer.svg" alt="PyPI version"/>
    </a>
    <a href="https://github.com/your-org/ignition-sdk/blob/main/LICENSE">
        <img src="https://img.shields.io/pypi/l/ignition-infer" alt="License"/>
    </a>
    <a href="https://docs.ignition-hub.ai/python">
        <img src="https://img.shields.io/badge/API_Reference-Read_the_Docs-blue" alt="Documentation"/>
    </a>
</p>

---

**`ignition-infer`** is the official Python SDK for the Ignition AI ecosystem. It provides a clean, high-level, and "Pythonic" interface to the hyper-performance of our underlying C++/CUDA inference engine.

This library is designed for AI researchers, data scientists, and ML engineers who want to run their trained models in production with the **maximum possible speed and efficiency**, without ever leaving the comfort of the Python ecosystem. It's the bridge from a slow `model.forward()` to a production-ready, 10x faster `model.predict()`.

This package is a native client library developed within the main **[Ignition SDK Monorepo](https://github.com/your-org/ignition-sdk)**.

## Key Features

*   🚀 **Extreme Performance:** Run your AI models 10x-100x faster than their native PyTorch or TensorFlow counterparts by leveraging our `Ignition Hub`-optimized TensorRT engines.
*   🧠 **Simple, High-Level API:** We abstract away all the painful boilerplate of the TensorRT and CUDA APIs. Load an engine and run a prediction in just two lines of code.
*   🐍 **Pure Python Experience:** Feels just like a native Python library. It integrates seamlessly with `NumPy`, the standard for numerical data in the Python world.
*   🔒 **Type Safe:** Comes with full type hints, enabling modern, robust development with tools like MyPy.
*   🤖 **Future-Ready:** Designed to integrate with our upcoming `ignition-link` library for robotics and IoT applications.

## 🚀 Installation

The recommended way to install is from PyPI.

```bash
pip install ignition-infer
```

**Note:** The pre-compiled wheels provided on PyPI are built for a specific set of common environments (Linux, CUDA 11.8, TensorRT 8.6). If your environment differs, you may need to build from source or, even better, use our **[Ignition Hub](https://ignition-hub.ai)** platform to get an engine perfectly matched to your setup.

## 💡 Quick Start: A "Hello, World!" for Inference

This example shows the complete end-to-end workflow: taking a trained model, optimizing it with **[Ignition Hub](https://ignition-hub.ai)**, and running it with this SDK.

### Prerequisites
*   An `Ignition Hub` account (sign up for free).
*   A pre-built `.plan` engine file downloaded from the Hub. For this example, we'll use a pre-built ResNet-50 from our **[engine zoo](https://github.com/your-org/pre-built-engines)**.

```python
import ignition as ig
import numpy as np
# You'll also need a library for image processing, like Pillow or OpenCV
# from PIL import Image

# --- 1. Load the Optimized Engine ---
# This single line handles all the complex setup: loading the engine from disk,
# creating a CUDA execution context, and allocating GPU memory.
try:
    print("Loading the optimized engine...")
    model = ig.load("./path/to/your/resnet50_fp16.plan")
    print("Engine loaded successfully!")
except Exception as e:
    print(f"Error loading engine: {e}")
    # This usually happens if your CUDA/TensorRT versions don't match.
    exit()

# --- 2. Prepare Your Input Data ---
# The input must be a NumPy array. Here, we create a random tensor that
# matches the expected input shape of ResNet-50 (batch, channels, height, width).
print("Preparing a sample input tensor...")
dummy_image = np.random.rand(1, 3, 224, 224).astype(np.float32)

# --- 3. Run Prediction ---
# This is it. One simple call. The SDK handles the complex data transfer
# from your CPU (NumPy) to the GPU, runs the inference, and copies
# the results back to the CPU as a new NumPy array.
print("Running inference...")
results = model.predict(dummy_image)
print("Inference complete!")

# --- 4. Process the Results ---
# The output is a dictionary of NumPy arrays, keyed by the output layer names.
# For ResNet-50, there's a single output layer with 1000 class scores.
output_tensor = results['output_layer_name'] # Replace with your model's actual output name
predicted_class_index = np.argmax(output_tensor)

print(f"Output tensor shape: {output_tensor.shape}")
print(f"Predicted class index: {predicted_class_index}")
```

For more detailed and real-world examples, please visit our main **[Ignition Examples Repository](https://github.com/your-org/ignition-examples/tree/main/python)**.

## Building from Source

This package is part of the `ignition-sdk` monorepo. To build it from source, you must clone the parent repository. This process will automatically compile the required C++ core libraries.

**1. Clone the Monorepo:**
```bash
git clone https://github.com/your-org/ignition-sdk.git
cd ignition-sdk
```

**2. Install Build Dependencies:**
You will need a C++ compiler, CMake, and `pybind11`.

**3. Run the Build:**
We recommend using the monorepo's build system.
```bash
# From the root of the monorepo
yarn build --filter=ignition-python
```
This will place a new, installable wheel file in the `packages/ignition-python/dist/` directory.

## Contributing

We welcome contributions! This package is developed as part of a larger ecosystem. To contribute, please open a Pull Request in the main **[ignition-sdk](https://github.com/your-org/ignition-sdk)** repository.

Please read our main `CONTRIBUTING.md` guide for more details on the process and our code of conduct.