# Ignition AI: Rust SDK (`ignition`)

<p align="center">
    <a href="https://crates.io/crates/ignition">
        <img src="https://img.shields.io/crates/v/ignition.svg?style=flat&logo=rust" alt="Crates.io"/>
    </a>
    <a href="https://github.com/your-org/ignition-sdk/blob/main/LICENSE">
        <img src="https://img.shields.io/crates/l/ignition" alt="License"/>
    </a>
    <a href="https://docs.rs/ignition">
        <img src="https://img.shields.io/badge/docs.rs-ignition-66c2a5?style=flat&logo=rust" alt="docs.rs"/>
    </a>
</p>

---

**`ignition`** is the official, idiomatic Rust SDK for the Ignition AI ecosystem. It provides safe, high-performance, and ergonomic bindings to our underlying C++/CUDA inference engine.

This crate is designed for systems programmers, backend engineers, and robotics developers who demand the highest level of performance combined with the safety guarantees of the Rust language. It is the bridge that connects Rust's powerful concurrency and safety features with the raw, GPU-accelerated performance of `Ignition Hub`-optimized TensorRT engines.

This package is a native client library developed within the main **[Ignition SDK Monorepo](https://github.com/your-org/ignition-sdk)**. It uses a minimal C FFI layer to safely interface with our core C++ runtime.

## Key Features

*   🚀 **Extreme Performance:** Run your AI models at near-native C++ speed, bringing the world's fastest inference to your Rust applications.
*   🔒 **Safe by Design:** Provides a safe Rust API that handles the complexities of memory management and native resource lifetimes (RAII), preventing common FFI pitfalls.
*   ✨ **Ergonomic & Idiomatic Rust:** A clean, modern Rust API that feels natural to use. It leverages Rust's powerful type system and `Result` type for robust error handling.
*   📦 **Standard Cargo Crate:** Integrates into any Rust project with a simple `cargo add ignition` command.
*   ⚡ **Fearless Concurrency:** The core `Engine` is `Send + Sync`, making it safe to share across threads for building massively concurrent inference pipelines with tools like Tokio or Rayon.

## 🚀 Installation

Add the crate to your project's `Cargo.toml` or use `cargo add`.

```bash
cargo add ignition```

**Note:** This crate requires the Ignition AI native libraries (`libxinfer_runtime.so` or `.dll`) to be present on your system. The `build.rs` script will attempt to link against them. These native libraries are built for specific environments (e.g., Linux, CUDA 11.8, TensorRT 8.6). For different environments, you must use our **[Ignition Hub](https://ignition-hub.ai)** platform to get a perfectly matched engine.

## 💡 Quick Start: A "Hello, World!" for Rust Inference

This example demonstrates the basic workflow of loading an engine and running a prediction, with proper error handling.

### Prerequisites
*   Rust toolchain (stable).
*   The Ignition AI native runtime library is installed in a standard location.
*   A pre-built `.plan` engine file downloaded from **[Ignition Hub](https://ignition-hub.ai)**.

```rust
// Import the necessary components from the ignition crate
use ignition::infer::{Engine, Tensor};
use std::collections::HashMap;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    println!("Starting Ignition AI Rust Example...");

    // --- 1. Load the Optimized Engine ---
    // The `load` function is fallible, returning a `Result`. This allows us
    // to handle errors gracefully if the engine file is not found or invalid.
    println!("Loading the optimized engine...");
    let engine_path = "./path/to/your/resnet50_fp16.plan";
    let model = Engine::load(engine_path)?; // The `?` operator propagates errors.
    println!("Engine loaded successfully!");

    // --- 2. Prepare Your Input Data ---
    // The input is a HashMap of String to Tensor.
    // Here, we create a tensor with random data that matches the expected shape.
    println!("Preparing a sample input tensor...");
    let input_shape = vec![1, 3, 224, 224];
    // In a real app, you would load an image (e.g., with the 'image' crate)
    // and convert it to a Vec<f32>.
    let input_data: Vec<f32> = vec![0.5; 1 * 3 * 224 * 224];

    let input_tensor = Tensor::from_slice(&input_data, input_shape)?;

    let mut inputs = HashMap::new();
    inputs.insert("input_layer_name".to_string(), input_tensor); // Replace with your model's actual input name

    // --- 3. Run Prediction ---
    // The `predict` method also returns a Result.
    println!("Running inference...");
    let results = model.predict(&inputs)?;
    println!("Inference complete!");

    // --- 4. Process the Results ---
    // The output is a HashMap of Tensors.
    let output_tensor = results.get("output_layer_name")
        .ok_or("Output tensor not found in results")?; // Return an error if the key is missing

    // You can get the shape and data from the tensor.
    let shape = output_tensor.shape();
    let scores: &[f32] = output_tensor.as_slice()?;

    // Find the index of the highest score
    let (max_index, _) = scores.iter()
        .enumerate()
        .max_by(|(_, a), (_, b)| a.partial_cmp(b).unwrap())
        .ok_or("Failed to find max value in output")?;

    println!("Output tensor shape: {:?}", shape);
    println!("Predicted class index: {}", max_index);

    // No need to manually free the model; Rust's ownership model (RAII)
    // handles freeing the underlying GPU resources when `model` goes out of scope.

    Ok(())
}
```

For more detailed examples, including building a concurrent web service with Axum or Actix-web, please visit our main **[Ignition Examples Repository](https://github.com/your-org/ignition-examples/tree/main/rust)**.

## Building from Source

This crate is part of the `ignition-sdk` monorepo. To build it from source, you must clone the parent repository. The `build.rs` script will automatically find and link against the C++ core libraries compiled by the root build system.

**1. Clone the Monorepo:**
```bash
git clone https://github.com/your-org/ignition-sdk.git
cd ignition-sdk
```

**2. Install Build Dependencies:**
You will need a C++ compiler, CMake, and the Rust toolchain.

**3. Run the Build:**
The monorepo's build system will handle the C++ compilation, and then you can build the Rust crate normally with Cargo.
```bash
# From the root of the monorepo, first build the C++ dependencies
yarn build --filter=!ignition-rust # Build everything *except* the rust package itself

# Then, navigate to the rust package and build
cd packages/ignition-rust
cargo build --release
```

## Contributing

We welcome contributions! The Rust community is known for its high standards, and we aim to meet them. To contribute, please open a Pull Request in the main **[ignition-sdk](https://github.com/your-org/ignition-sdk)** repository.

Please read our main `CONTRIBUTING.md` guide for more details on the process and our code of conduct.