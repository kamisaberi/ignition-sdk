# Ignition AI: Go SDK

<p align="center">
    <a href="https://pkg.go.dev/github.com/ignition-ai/go-infer">
        <img src="https://img.shields.io/badge/go.dev-reference-007d9c?style=flat&logo=go" alt="Go Reference"/>
    </a>
    <a href="https://github.com/your-org/ignition-sdk/blob/main/LICENSE">
        <img src="https://img.shields.io/badge/license-Apache_2.0-green" alt="License"/>
    </a>
    <a href="https://docs.ignition-hub.ai/go">
        <img src="https://img.shields.io/badge/API_Reference-Read_the_Docs-blue" alt="Documentation"/>
    </a>
</p>

---

**`go-infer`** is the official Go SDK for the Ignition AI ecosystem. It provides a simple, performant, and idiomatic Go interface to our underlying C++/CUDA inference engine.

This library is designed for backend and infrastructure engineers who are building high-throughput, concurrent systems in Go and need to incorporate AI inference with the lowest possible latency. It is the bridge between Go's powerful concurrency model and the raw performance of `Ignition Hub`-optimized TensorRT engines.

This package is a native client library developed within the main **[Ignition SDK Monorepo](https://github.com/your-org/ignition-sdk)**. It uses Cgo to interface with our core C++ runtime.

## Key Features

*   🚀 **Extreme Performance:** Run your AI models at near-native C++ speed, bringing the power of GPU acceleration to your Go applications.
*   ⚡ **Concurrency Safe:** The SDK is designed to be safe for concurrent use in goroutines, allowing you to build massively parallel inference services.
*   ✨ **Idiomatic Go API:** A clean, simple API that follows Go conventions, including explicit error handling. It feels like a standard Go library, not a C++ wrapper.
*   📦 **Standard Go Module:** Integrates into your project with a simple `go get` command.
*   ☁️ **Cloud-Native Ready:** Perfect for building high-performance microservices that can be deployed in containers and orchestrated with Kubernetes.

## 🚀 Installation

Add the SDK to your project using the standard `go get` command:

```bash
go get github.com/ignition-ai/go-infer
```

**Note:** This SDK requires the Ignition AI native libraries (`libxinfer_runtime.so` or `.dll`) to be present on your system. The pre-compiled binaries are built for specific environments (e.g., Linux, CUDA 11.8, TensorRT 8.6). For different environments, you must use our **[Ignition Hub](https://ignition-hub.ai)** platform to get a perfectly matched engine.

## 💡 Quick Start: A "Hello, World!" for Go Inference

This example demonstrates the basic workflow of loading an engine and running a prediction.

### Prerequisites
*   Go 1.18+ installed.
*   The Ignition AI native runtime library is installed in a standard location (e.g., `/usr/local/lib`).
*   A pre-built `.plan` engine file downloaded from **[Ignition Hub](https://ignition-hub.ai)**.

```go
package main

import (
	"fmt"
	"log"

	"github.com/ignition-ai/go-infer/infer" // Import the infer package
	"gonum.org/v1/gonum/mat" // A popular library for matrix operations, similar to NumPy
)

func main() {
	fmt.Println("Starting Ignition AI Go Example...")

	// --- 1. Load the Optimized Engine ---
	// The Load function takes the path to the engine file and returns a
	// pointer to an Engine or an error, following standard Go conventions.
	fmt.Println("Loading the optimized engine...")
	engine, err := infer.Load("./path/to/your/resnet50_fp16.plan")
	if err != nil {
		log.Fatalf("Error loading engine: %v", err)
		// This often indicates a mismatch in CUDA/TensorRT versions or the native library is not found.
	}
	// We use `defer` to ensure the engine's GPU memory is freed when the function exits.
	defer engine.Close()
	fmt.Println("Engine loaded successfully!")

	// --- 2. Prepare Your Input Data ---
	// The input is a map of strings to Tensors.
	// Here, we create a tensor with random data that matches the expected input shape.
	fmt.Println("Preparing a sample input tensor...")
	inputShape := []int{1, 3, 224, 224}
	// In a real app, you would load and preprocess an image into this float32 slice.
	inputData := make([]float32, 1*3*224*224)
	for i := range inputData {
		inputData[i] = 0.5 // Simplified random data
	}

	inputTensor, err := infer.NewTensor(inputShape, inputData)
	if err != nil {
		log.Fatalf("Failed to create input tensor: %v", err)
	}

	inputs := map[string]*infer.Tensor{
		"input_layer_name": inputTensor, // Replace with your model's actual input name
	}

	// --- 3. Run Prediction ---
	// The Predict method takes the input map and returns the output map or an error.
	fmt.Println("Running inference...")
	results, err := engine.Predict(inputs)
	if err != nil {
		log.Fatalf("Inference failed: %v", err)
	}
	fmt.Println("Inference complete!")

	// --- 4. Process the Results ---
	// The output is a map of Tensors.
	outputTensor, ok := results["output_layer_name"] // Replace with your model's actual output name
	if !ok {
		log.Fatalf("Output tensor not found in results")
	}

	// You can get the shape and data from the tensor.
	shape := outputTensor.Shape()
	data, err := outputTensor.Data()
	if err != nil {
		log.Fatalf("Failed to get output data: %v", err)
	}

	// Find the index of the max value in the output slice
	maxIndex := 0
	for i := 1; i < len(data); i++ {
		if data[i] > data[maxIndex] {
			maxIndex = i
		}
	}

	fmt.Printf("Output tensor shape: %v\n", shape)
	fmt.Printf("Predicted class index: %d\n", maxIndex)
}
```

For more detailed examples, including how to build a concurrent web service, please visit our main **[Ignition Examples Repository](https://github.com/your-org/ignition-examples/tree/main/go)**.

## Building from Source

This package is part of the `ignition-sdk` monorepo. To build it from source, you must clone the parent repository, which will compile the required C++ core libraries.

**1. Clone the Monorepo:**
```bash
git clone https://github.com/your-org/ignition-sdk.git
cd ignition-sdk
```

**2. Install Build Dependencies:**
You will need a C++ compiler, CMake, and the Go toolchain.

**3. Run the Build:**
The monorepo's build system will handle the C++ compilation. You can then build the Go package normally.
```bash
# From the root of the monorepo
yarn build --filter=ignition-go
```
This command will ensure the C++ dependencies are compiled before the Go package is built, making the Cgo linking process succeed.

## Contributing

We welcome contributions! To contribute, please open a Pull Request in the main **[ignition-sdk](https://github.com/your-org/ignition-sdk)** repository.

Please read our main `CONTRIBUTING.md` guide for more details on the process and our code of conduct.