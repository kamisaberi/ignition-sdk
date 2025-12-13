# Ignition AI: C# / .NET SDK

<p align="center">
    <a href="https://www.nuget.org/packages/Ignition.Infer/">
        <img src="https://badge.fury.io/nu/Ignition.Infer.svg" alt="NuGet version"/>
    </a>
    <a href="https://github.com/your-org/ignition-sdk/blob/main/LICENSE">
        <img src="https://img.shields.io/nuget/l/Ignition.Infer" alt="License"/>
    </a>
    <a href="https://docs.ignition-hub.ai/csharp">
        <img src="https://img.shields.io/badge/API_Reference-Read_the_Docs-blue" alt="Documentation"/>
    </a>
</p>

---

**`Ignition.Infer`** is the official C#/.NET SDK for the Ignition AI ecosystem. It provides a high-performance, easy-to-use, and idiomatic C# interface to our underlying C++/CUDA inference engine, allowing you to run state-of-the-art AI models in your .NET applications and Unity games with maximum performance.

This library is designed for developers who need to run AI inference in latency-critical environments where Python is not an option. It's the bridge that connects the power of `Ignition Hub`-optimized TensorRT engines to the rich and productive C# ecosystem.

This package is a native client library developed within the main **[Ignition SDK Monorepo](https://github.com/your-org/ignition-sdk)**.

## Key Features

*   🚀 **Unmatched Performance:** Execute your AI models at near-native C++ speed, 10x-100x faster than alternative C# inference solutions. Perfect for real-time applications.
*   🎮 **Unity Game Engine Ready:** Designed from the ground up to be seamlessly integrated into Unity, enabling you to build intelligent NPCs, real-time physics simulations, and other AI-powered game mechanics.
*   ✨ **Simple, Object-Oriented API:** A clean, modern C# API that abstracts away all the complexity of P/Invoke and native library management. It feels like any other C# library.
*   📦 **Easy Integration:** Distributed as a standard NuGet package, it can be added to any .NET or Unity project in seconds.
*   🔒 **Cross-Platform:** Provides native binaries for both Windows (x64) and Linux (x64), with support for more platforms planned.

## 🚀 Installation

The recommended way to install is via the NuGet Package Manager.

#### For a standard .NET Project:

```bash
dotnet add package Ignition.Infer
```

#### For a Unity Project:

Use your preferred NuGet package manager for Unity (e.g., [NuGetForUnity](https://github.com/GlitchEnzo/NuGetForUnity)) and search for `Ignition.Infer`.

**Note:** The native binaries bundled with the NuGet package are built for a specific set of common environments (e.g., CUDA 11.8, TensorRT 8.6). For different environments, you must use our **[Ignition Hub](https://ignition-hub.ai)** platform to get a perfectly matched engine.

## 💡 Quick Start: A "Hello, World!" for C# Inference

This example shows the complete workflow of loading a pre-built engine and running a simple inference.

### Prerequisites
*   A .NET 6+ or compatible Unity project.
*   A pre-built `.plan` engine file downloaded from **[Ignition Hub](https://ignition-hub.ai)**. For this example, we'll use a ResNet-50.

```csharp
// Import the necessary namespaces
using Ignition.Infer;
using System;

public class InferenceExample
{
    public static void Main(string[] args)
    {
        Console.WriteLine("Starting Ignition AI C# Example...");

        // --- 1. Load the Optimized Engine ---
        // This single line handles loading the native C++ library and
        // deserializing the TensorRT engine into GPU memory.
        Engine model;
        try
        {
            Console.WriteLine("Loading the optimized engine...");
            model = new Engine("./path/to/your/resnet50_fp16.plan");
            Console.WriteLine("Engine loaded successfully!");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error loading engine: {ex.Message}");
            // This often indicates a mismatch in CUDA/TensorRT versions or a missing dependency.
            return;
        }

        // --- 2. Prepare Your Input Data ---
        // The input is a dictionary mapping input layer names to a Tensor object.
        // Here we create a random tensor that matches the expected input shape of ResNet-50.
        Console.WriteLine("Preparing a sample input tensor...");
        var inputShape = new long[] { 1, 3, 224, 224 };
        var inputTensor = Tensor.FromRandomFloat(inputShape);

        var inputs = new Dictionary<string, Tensor>
        {
            { "input_layer_name", inputTensor } // Replace with your model's actual input name
        };

        // --- 3. Run Prediction ---
        // This call pushes the data to the GPU, executes the inference,
        // and brings the results back to the CPU.
        Console.WriteLine("Running inference...");
        Dictionary<string, Tensor> results = model.Predict(inputs);
        Console.WriteLine("Inference complete!");

        // --- 4. Process the Results ---
        // The output is a dictionary of Tensors, keyed by the output layer names.
        // For ResNet-50, we expect a single output with 1000 class scores.
        Tensor outputTensor = results["output_layer_name"]; // Replace with your model's actual output name
        float[] scores = outputTensor.ToFloatArray();

        // Find the index of the highest score
        int predictedClassIndex = Array.IndexOf(scores, scores.Max());

        Console.WriteLine($"Output tensor shape: {string.Join(", ", outputTensor.Shape)}");
        Console.WriteLine($"Predicted class index: {predictedClassIndex}");

        // It is good practice to dispose of the engine to free up GPU memory.
        model.Dispose();
    }
}
```

For more detailed examples, including Unity integration, please visit our main **[Ignition Examples Repository](https://github.com/your-org/ignition-examples/tree/main/csharp)**.

## Building from Source

This package is part of the `ignition-sdk` monorepo. To build it from source, you must clone the parent repository. This process will automatically compile the required C++ core libraries and then build the .NET solution.

**1. Clone the Monorepo:**
```bash
git clone https://github.com/your-org/ignition-sdk.git
cd ignition-sdk
```

**2. Install Build Dependencies:**
You will need a C++ compiler, CMake, and the .NET SDK.

**3. Run the Build:**
We recommend using the monorepo's build system.
```bash
# From the root of the monorepo
yarn build --filter=ignition-csharp
```
This will compile the native C++ binaries and place them in the correct directory within the C# project, and then build the .NET solution. The final NuGet package will be in the `packages/ignition-csharp/dist/` directory.

## Contributing

We welcome contributions! To contribute, please open a Pull Request in the main **[ignition-sdk](https://github.com/your-org/ignition-sdk)** repository.

Please read our main `CONTRIBUTING.md` guide for more details on the process and our code of conduct.