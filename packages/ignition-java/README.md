# Ignition AI: Java / JVM SDK

<p align="center">
    <a href="https://search.maven.org/artifact/ai.ignition/infer">
        <img src="https://img.shields.io/maven-central/v/ai.ignition/infer.svg?label=Maven%20Central" alt="Maven Central"/>
    </a>
    <a href="https://github.com/your-org/ignition-sdk/blob/main/LICENSE">
        <img src="https://img.shields.io/badge/license-Apache_2.0-green" alt="License"/>
    </a>
    <a href="https://docs.ignition-hub.ai/java">
        <img src="https://img.shields.io/badge/API_Reference-Read_the_Docs-blue" alt="Documentation"/>
    </a>
</p>

---

**`ai.ignition:infer`** is the official Java SDK for the Ignition AI ecosystem. It provides a high-performance, object-oriented, and robust Java interface to our underlying C++/CUDA inference engine.

This library is designed for enterprise and Android developers who need to integrate AI inference into their applications with the lowest possible latency and highest throughput. It is the bridge that connects the reliability and scalability of the Java Virtual Machine (JVM) with the raw performance of `Ignition Hub`-optimized TensorRT engines.

This package is a native client library developed within the main **[Ignition SDK Monorepo](https://github.com/your-org/ignition-sdk)**. It uses the Java Native Interface (JNI) to communicate with our core C++ runtime.

## Key Features

*   🚀 **Extreme Performance:** Run your AI models at near-native C++ speed, bringing the power of GPU acceleration to your Java and Kotlin applications.
*   🔒 **Resource Safe:** The API is designed with a `try-with-resources` pattern, ensuring that native GPU memory is always managed safely and correctly, preventing memory leaks.
*   ✨ **Idiomatic Java API:** A clean, object-oriented API that follows standard Java conventions. It feels like a standard Java library, not a thin C++ wrapper.
*   📦 **Standard Maven/Gradle Dependency:** Integrates seamlessly into any standard Java or Android project via Maven Central.
*   🏢 **Enterprise Ready:** Perfect for building high-throughput, concurrent microservices or for enabling on-device AI in Android applications.

## 🚀 Installation

Add the SDK as a dependency to your project using Maven or Gradle.

#### For Gradle (Recommended for modern Java / Android):
```groovy
// In your build.gradle file
dependencies {
    implementation 'ai.ignition:infer:1.0.0'
}
```

#### For Maven:
```xml
<!-- In your pom.xml file -->
<dependency>
    <groupId>ai.ignition</groupId>
    <artifactId>infer</artifactId>
    <version>1.0.0</version>
</dependency>
```

**Note:** This library requires the Ignition AI native JNI libraries (`libignition_jni.so` or `.dll`) to be present on the system. The JAR on Maven Central can be configured to automatically bundle these for common platforms. For different environments, you must use our **[Ignition Hub](https://ignition-hub.ai)** platform to get a perfectly matched engine.

## 💡 Quick Start: A "Hello, World!" for Java Inference

This example demonstrates the standard workflow of loading an engine and running a prediction.

### Prerequisites
*   A Java Development Kit (JDK) 11+ or a compatible Android environment.
*   A pre-built `.plan` engine file downloaded from **[Ignition Hub](https://ignition-hub.ai)**.

```java
// Import the necessary classes from the Ignition AI SDK
import ai.ignition.infer.Engine;
import ai.ignition.infer.Tensor;
import java.util.Map;
import java.util.HashMap;

public class InferenceExample {

    public static void main(String[] args) {
        System.out.println("Starting Ignition AI Java Example...");

        String enginePath = "./path/to/your/resnet50_fp16.plan";

        // --- 1. Load the Optimized Engine ---
        // We use a try-with-resources block to ensure the Engine is automatically closed,
        // which safely releases all underlying GPU memory and resources.
        try (Engine model = new Engine(enginePath)) {
            System.out.println("Engine loaded successfully!");

            // --- 2. Prepare Your Input Data ---
            // The input is a Map of String to Tensor objects.
            // Here, we create a tensor with random data that matches the expected input shape.
            System.out.println("Preparing a sample input tensor...");
            long[] inputShape = {1, 3, 224, 224};
            float[] inputData = new float[1 * 3 * 224 * 224];
            // In a real app, you would load and preprocess an image into this float array.
            for (int i = 0; i < inputData.length; i++) {
                inputData[i] = 0.5f; // Simplified random data
            }

            Tensor inputTensor = new Tensor(inputShape, inputData);

            Map<String, Tensor> inputs = new HashMap<>();
            inputs.put("input_layer_name", inputTensor); // Replace with your model's actual input name

            // --- 3. Run Prediction ---
            // The predict method takes the input map and returns the output map.
            System.out.println("Running inference...");
            Map<String, Tensor> results = model.predict(inputs);
            System.out.println("Inference complete!");

            // --- 4. Process the Results ---
            // The output is a map of Tensors.
            Tensor outputTensor = results.get("output_layer_name"); // Replace with your model's actual output name
            if (outputTensor == null) {
                System.err.println("Output tensor not found in results");
                return;
            }

            // You can get the shape and data from the tensor.
            float[] scores = outputTensor.getFloatData();

            // Find the index of the highest score
            int maxIndex = 0;
            for (int i = 1; i < scores.length; i++) {
                if (scores[i] > scores[maxIndex]) {
                    maxIndex = i;
                }
            }

            System.out.println("Output tensor shape: " + java.util.Arrays.toString(outputTensor.getShape()));
            System.out.println("Predicted class index: " + maxIndex);

        } catch (Exception ex) {
            System.err.println("An error occurred: " + ex.getMessage());
            // This often indicates a mismatch in CUDA/TensorRT versions or a missing JNI library.
            ex.printStackTrace();
        }
    }
}
```

For more detailed examples, including Android integration and building concurrent web services with frameworks like Spring Boot, please visit our main **[Ignition Examples Repository](https://github.com/your-org/ignition-examples/tree/main/java)**.

## Building from Source

This package is part of the `ignition-sdk` monorepo. To build it from source, you must clone the parent repository, which will compile the required C++ core libraries and the JNI bindings.

**1. Clone the Monorepo:**
```bash
git clone https://github.com/your-org/ignition-sdk.git
cd ignition-sdk
```

**2. Install Build Dependencies:**
You will need a C++ compiler, CMake, and a JDK.

**3. Run the Build:**
The monorepo's build system will handle the C++ compilation and then trigger the Gradle build for the Java package.
```bash
# From the root of the monorepo
yarn build --filter=ignition-java
```
This command will produce a JAR file in the `packages/ignition-java/build/libs/` directory, ready to be used locally or published to Maven Central.

## Contributing

We welcome contributions! To contribute, please open a Pull Request in the main **[ignition-sdk](https://github.com/your-org/ignition-sdk)** repository.

Please read our main `CONTRIBUTING.md` guide for more details on the process and our code of conduct.