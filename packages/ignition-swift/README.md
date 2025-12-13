# Ignition AI: Swift SDK

<p align="center">
    <a href="https://swift.org">
        <img src="https://img.shields.io/badge/Swift-5.7+-F05138?style=flat&logo=swift" alt="Swift Version"/>
    </a>
    <a href="https://github.com/your-org/ignition-sdk/blob/main/LICENSE">
        <img src="https://img.shields.io/badge/license-Apache_2.0-green" alt="License"/>
    </a>
    <a href="https://docs.ignition-hub.ai/swift">
        <img src="https://img.shields.io/badge/API_Reference-Read_the_Docs-blue" alt="Documentation"/>
    </a>
</p>

---

**`Ignition`** is the official Swift SDK for the Ignition AI ecosystem. It provides a safe, modern, and high-performance interface to our underlying C++/CUDA inference engine, enabling you to run complex AI models directly on-device on macOS.

This library is designed for Apple platform developers who need to integrate powerful, low-latency AI capabilities into their macOS applications. It is the bridge that connects the robust and elegant Swift language with the raw, GPU-accelerated performance of `Ignition Hub`-optimized TensorRT engines.

This package is a native client library developed within the main **[Ignition SDK Monorepo](https://github.com/your-org/ignition-sdk)**. It uses a minimal C bridging header to safely interface with our core C++ runtime.

## Key Features

*   🚀 **Extreme Performance:** Run your AI models at near-native C++ speed on NVIDIA GPUs, bringing desktop-class AI performance to your Mac applications.
*   🔒 **Safe & Swifty API:** A clean, modern Swift API that leverages Swift's powerful features like value types, optionals, and `throws` for robust error handling. It manages the lifecycle of native resources automatically.
*   📦 **Swift Package Manager:** Integrates seamlessly into any Xcode project or Swift package with a simple package dependency declaration.
*   ⚡ **Asynchronous by Design:** Core inference methods are `async`, allowing them to be run in the background without blocking the main UI thread, ensuring a responsive user experience.
*   🖥️ **macOS First:** Optimized for building powerful, professional desktop applications.

## 🚀 Installation

Add the SDK to your project using the Swift Package Manager.

In Xcode:
1.  Go to `File` > `Add Packages...`
2.  In the search bar, paste the repository URL: `https://github.com/your-org/ignition-sdk.git`
3.  Choose the appropriate dependency rule (e.g., "Up to Next Major Version").
4.  Add the `Ignition` library to your application's target.

Or, in your `Package.swift` file:
```swift
dependencies: [
    .package(url: "https://github.com/your-org/ignition-sdk.git", .upToNextMajor(from: "1.0.0"))
]
```

**Note:** This SDK requires the Ignition AI native libraries (`libxinfer_runtime.dylib`) to be present on the system. These native libraries are built for specific environments (e.g., macOS, CUDA 11.8, TensorRT 8.6). For different environments, you must use our **[Ignition Hub](https://ignition-hub.ai)** platform to get a perfectly matched engine.

## 💡 Quick Start: A "Hello, World!" for Swift Inference

This example demonstrates the basic workflow of loading an engine and running a prediction in an `async` context.

### Prerequisites
*   macOS with a compatible NVIDIA GPU and drivers.
*   Xcode 14+.
*   A pre-built `.plan` engine file downloaded from **[Ignition Hub](https://ignition-hub.ai)**.

```swift
// Import the Ignition module
import Ignition

// It's best practice to run inference within an async context.
@main
struct InferenceApp {
    static func main() async {
        print("Starting Ignition AI Swift Example...")

        let enginePath = "/path/to/your/resnet50_fp16.plan"

        do {
            // --- 1. Load the Optimized Engine ---
            // The initializer is failable (`throws`), allowing for proper error handling.
            print("Loading the optimized engine...")
            let model = try Engine(planPath: enginePath)
            print("Engine loaded successfully!")

            // --- 2. Prepare Your Input Data ---
            // The input is a dictionary of String to Tensor.
            // Here we create a tensor with random data that matches the expected shape.
            print("Preparing a sample input tensor...")
            let inputShape: [Int] = [1, 3, 224, 224]
            // In a real app, you would load an image (e.g., with CoreGraphics)
            // and convert it to a [Float] array.
            let inputData: [Float] = Array(repeating: 0.5, count: 1 * 3 * 224 * 224)

            let inputTensor = try Tensor(shape: inputShape, data: inputData)

            let inputs = [
                "input_layer_name": inputTensor // Replace with your model's actual input name
            ]

            // --- 3. Run Prediction (Asynchronously) ---
            // The predict method is async and throws, integrating perfectly with Swift's concurrency model.
            print("Running inference...")
            let results = try await model.predict(inputs: inputs)
            print("Inference complete!")

            // --- 4. Process the Results ---
            // The output is a dictionary of Tensors.
            guard let outputTensor = results["output_layer_name"] else { // Replace with your model's actual output name
                throw MyError.runtimeError("Output tensor not found in results")
            }

            // You can get the shape and data from the tensor.
            let scores: [Float] = try outputTensor.data()

            // Find the index of the highest score
            if let (maxIndex, _) = scores.enumerated().max(by: { $0.element < $1.element }) {
                print("Output tensor shape: \(outputTensor.shape)")
                print("Predicted class index: \(maxIndex)")
            }

        } catch {
            // Catch and handle any errors from loading or prediction.
            print("An error occurred: \(error)")
        }
    }
}
```

For more detailed examples, including integration with SwiftUI for building responsive UI, please visit our main **[Ignition Examples Repository](https://github.com/your-org/ignition-examples/tree/main/swift)**.

## Building from Source

This package is part of the `ignition-sdk` monorepo. To build it from source, you must clone the parent repository. The Swift Package Manager will be configured to find and link against the C++ core libraries compiled by the root build system.

**1. Clone the Monorepo:**
```bash
git clone https://github.com/your-org/ignition-sdk.git
cd ignition-sdk
```

**2. Install Build Dependencies:**
You will need a C++ compiler, CMake, and the Xcode Command Line Tools.

**3. Run the Build:**
The monorepo's build system will handle the C++ compilation. You can then build the Swift package.
```bash
# From the root of the monorepo
yarn build --filter=ignition-swift
```
This command ensures the C++ dependencies are compiled before the Swift package is built, allowing the C-bridging and linking process to succeed.

## Contributing

We welcome contributions! To contribute, please open a Pull Request in the main **[ignition-sdk](https://github.com/your-org/ignition-sdk)** repository.

Please read our main `CONTRIBUTING.md` guide for more details on the process and our code of conduct.