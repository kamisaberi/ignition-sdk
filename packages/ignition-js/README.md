# Ignition AI: JavaScript / TypeScript SDK (`@ignition/infer`)

<p align="center">
    <a href="https://www.npmjs.com/package/@ignition/infer">
        <img src="https://badge.fury.io/js/%40ignition%2Finfer.svg" alt="NPM version"/>
    </a>
    <a href="https://github.com/your-org/ignition-sdk/blob/main/LICENSE">
        <img src="https://img.shields.io/npm/l/@ignition/infer" alt="License"/>
    </a>
    <a href="https://docs.ignition-hub.ai/javascript">
        <img src="https://img.shields.io/badge/API_Reference-Read_the_Docs-blue" alt="Documentation"/>
    </a>
</p>

---

**`@ignition/infer`** is the official JavaScript & TypeScript SDK for the Ignition AI ecosystem. It provides a high-performance, modern, and developer-friendly interface to our underlying C++/CUDA inference engine, running in the Node.js environment.

This library is designed for backend developers building high-performance APIs and services in the JavaScript ecosystem. It's the bridge that connects the world's largest developer community with the raw, GPU-accelerated power of `Ignition Hub`-optimized TensorRT engines.

This package is a native client library developed within the main **[Ignition SDK Monorepo](https://github.com/your-org/ignition-sdk)**. It uses Node-API to interface with our core C++ runtime, providing a robust and efficient bridge between JavaScript and native code.

## Key Features

*   🚀 **Extreme Performance:** Bring true GPU acceleration to your Node.js backend. Run AI models 10x-100x faster than with CPU-based JavaScript inference libraries.
*    modern **Async API:** A clean, `async/await`-first API that integrates perfectly with modern JavaScript event loops and web frameworks like Express or Fastify.
*   🔒 **TypeScript First:** The library is written in TypeScript, providing full type safety out of the box for a more robust and predictable development experience.
*   📦 **Simple NPM Integration:** Installs like any other Node.js package, with no complex setup.
*   ☁️ **Serverless Ready:** Can be packaged into serverless functions (e.g., AWS Lambda with custom runtimes) for scalable, on-demand inference.

## 🚀 Installation

Install the package from the NPM registry using `npm` or `yarn`.

```bash
npm install @ignition/infer

# or

yarn add @ignition/infer
```

**Note:** This package requires the Ignition AI native Node-API addon (`.node` file). The package on NPM will attempt to download a pre-compiled binary for your platform (e.g., Linux x64). If a pre-built binary is not available, or your environment differs (e.g., CUDA/TensorRT versions), you must use our **[Ignition Hub](https://ignition-hub.ai)** platform to get a perfectly matched engine.

## 💡 Quick Start: A "Hello, World!" for Node.js Inference

This example demonstrates the asynchronous workflow of loading an engine and running a prediction.

### Prerequisites
*   Node.js v16+.
*   A pre-built `.plan` engine file downloaded from **[Ignition Hub](https://ignition-hub.ai)**.

```typescript
// Import the necessary functions from the Ignition AI SDK
import { load, Tensor } from '@ignition/infer';

async function main() {
  console.log('Starting Ignition AI JavaScript/TypeScript Example...');

  const enginePath = './path/to/your/resnet50_fp16.plan';

  try {
    // --- 1. Load the Optimized Engine (Asynchronously) ---
    // The load function is async. It prepares the engine in a background thread
    // without blocking the Node.js event loop.
    console.log('Loading the optimized engine...');
    const model = await load(enginePath);
    console.log('Engine loaded successfully!');

    // --- 2. Prepare Your Input Data ---
    // The input is an object mapping input layer names to Tensor objects.
    // Here, we create a tensor from a flat Float32Array.
    console.log('Preparing a sample input tensor...');
    const inputShape = [1, 3, 224, 224];
    // In a real app, you would load an image (e.g., with the 'sharp' library)
    // and convert it to a flat Float32Array with the correct layout.
    const inputData = new Float32Array(1 * 3 * 224 * 224).fill(0.5);

    const inputTensor = new Tensor(inputShape, inputData);

    const inputs = {
      'input_layer_name': inputTensor, // Replace with your model's actual input name
    };

    // --- 3. Run Prediction (Asynchronously) ---
    // The predict method is also async, offloading the GPU work from the main thread.
    console.log('Running inference...');
    const results = await model.predict(inputs);
    console.log('Inference complete!');

    // --- 4. Process the Results ---
    // The output is an object of Tensors.
    const outputTensor = results['output_layer_name']; // Replace with your model's actual output name
    if (!outputTensor) {
      throw new Error('Output tensor not found in results');
    }

    // You can get the shape and data from the tensor.
    const scores: Float32Array = outputTensor.data as Float32Array;

    // Find the index of the highest score
    let maxIndex = 0;
    scores.forEach((score, i) => {
      if (score > scores[maxIndex]) {
        maxIndex = i;
      }
    });

    console.log(`Output tensor shape: [${outputTensor.shape.join(', ')}]`);
    console.log(`Predicted class index: ${maxIndex}`);

  } catch (error) {
    console.error('An error occurred:', error);
    // This often indicates a mismatch in CUDA/TensorRT versions or a missing native addon.
  }
}

main();
```

For more detailed examples, including how to build a high-performance Express.js API, please visit our main **[Ignition Examples Repository](https://github.com/your-org/ignition-examples/tree/main/javascript)**.

## Building from Source

This package is part of the `ignition-sdk` monorepo. To build it from source, you must clone the parent repository, which will compile the required C++ core libraries and the Node-API addon.

**1. Clone the Monorepo:**
```bash
git clone https://github.com/your-org/ignition-sdk.git
cd ignition-sdk
```

**2. Install Build Dependencies:**
You will need a C++ compiler, CMake, and Node.js/Yarn.

**3. Run the Build:**
The monorepo's build system will handle the C++ compilation and then trigger the build for the JS package.
```bash
# From the root of the monorepo
yarn build --filter=@ignition/infer```
This command will produce the native `.node` addon and place it in the correct directory within the `packages/ignition-js/` folder, making the package ready for local use or publishing.

## Contributing

We welcome contributions! To contribute, please open a Pull Request in the main **[ignition-sdk](https://github.com/your-org/ignition-sdk)** repository.

Please read our main `CONTRIBUTING.md` guide for more details on the process and our code of conduct.