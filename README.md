# The Ignition SDK

<p align="center">
  <strong>The definitive, open-source SDK for building and deploying high-performance, real-world AI applications.</strong>
</p>

<p align="center">
    <a href="https://docs.ignition-hub.ai">
        <img src="https://img.shields.io/badge/Full_Documentation-Read_the_Docs-blue?style=for-the-badge" alt="Documentation"/>
    </a>
    <a href="https://github.com/your-org/ignition-sdk/blob/main/LICENSE">
        <img src="https://img.shields.io/badge/License-Apache_2.0-green?style=for-the-badge" alt="License"/>
    </a>
    <a href="https://discord.gg/your-invite-link">
        <img src="https://img.shields.io/discord/81384788765712384.svg?logo=discord&label=Community&color=7289DA&style=for-the-badge" alt="Discord"/>
    </a>
</p>

---

Welcome to the Ignition SDK! This is the central, open-source monorepo for all of Ignition AI's core libraries and language-native client packages. Our mission is to provide the foundational, high-performance "picks and shovels" for the next generation of applied AI.

The AI industry has a "last mile" problem. Models are invented in Python, but the world's most critical applications—in robotics, automotive, defense, and finance—demand the speed and reliability of native code. The Ignition SDK is designed to bridge this gap, providing a seamless, end-to-end path from a trained model to a hyper-performant production application.

## The Ignition Philosophy

*   🚀 **Performance by Default:** We believe real-time performance is a fundamental requirement, not a feature. Our core is written in C++ and CUDA to be as close to the hardware as possible.
*   🧑‍💻 **Native Developer Experience:** A developer should feel at home. Our language-native packages are designed to be idiomatic and intuitive, whether you're working in Python, Rust, C#, or C++.
*   🔗 **A Cohesive Ecosystem:** Our libraries are designed to work together, providing a unified and powerful toolchain for the entire AI lifecycle, from training to deployment and communication.

## What's Inside This Repository?

This is a monorepo containing our core C++ libraries and the official, first-class SDKs for multiple languages.

### Core Internal Libraries

These are the high-performance C++ engines that power the entire ecosystem.

| Library | Description |
| :--- | :--- |
| **`libxinfer_runtime`** | **The Inference Engine.** A lightweight, production-grade C++ runtime for executing AI models that have been optimized with our [Ignition Hub](https://ignition-hub.ai) platform. It's the key to our 10x-100x performance gains. |
| **`libignition_link`** | **The Robotics OS.** A real-time, C++ native messaging and communication framework for robotics and IoT. It provides a robust, high-performance alternative to ROS for building production-grade autonomous systems. |

### Official Language SDKs

These are the public-facing, native packages we provide for developers. Each is a first-class citizen in this repository.

| Language | Package Name | Version | Quick Start |
| :--- | :--- | :--- | :--- |
| **Python** | `ignition-python` | [![PyPI version](https://badge.fury.io/py/ignition-infer.svg)](https://badge.fury.io/py/ignition-infer) | `pip install ignition-infer` |
| **C++** | `libxinfer_runtime`| `1.0.0` | `#include <xinfer/runtime.h>` |
| **C# / .NET** | `Ignition.Infer` | [![NuGet version](https://badge.fury.io/nu/Ignition.Infer.svg)](https://badge.fury.io/nu/Ignition.Infer) | `dotnet add package Ignition.Infer` |
| **Rust** | `ignition` | [![Crates.io](https://img.shields.io/crates/v/ignition.svg)](https://crates.io/crates/ignition) | `cargo add ignition` |
| **Java / Kotlin**| `ai.ignition:infer`| [![Maven Central](https://img.shields.io/maven-central/v/ai.ignition/infer.svg)](https://search.maven.org/artifact/ai.ignition/infer)| `implementation 'ai.ignition:infer:1.0.0'` |
| **Go** | `go-infer` | `v1.0.0` | `go get github.com/ignition-ai/go-infer` |
| **JS / TypeScript**| `@ignition/infer`| [![npm version](https://badge.fury.io/js/%40ignition%2Finfer.svg)](https://badge.fury.io/js/%40ignition%2Finfer)| `npm install @ignition/infer` |
| **Swift** | `Ignition` | `1.0.0` | ` .package(url: "...", .upToNextMajor(from: "1.0.0"))` |

---

## 🚀 Getting Started & Examples

The fastest way to understand the power of the Ignition SDK is to see it in action. We maintain a separate, lightweight repository with dozens of ready-to-run examples.

➡️ **Explore the Code Examples: [github.com/ignition-ai/ignition-examples](https://github.com/ignition-ai/ignition-examples)**

Find the language of your choice and run a "Hello, World!" for high-performance inference in just a few minutes.

## Documentation

For a deep dive into the architecture, comprehensive API references for every language, and step-by-step tutorials, please visit our full documentation website.

➡️ **Read the Full Documentation: [docs.ignition-hub.ai](https://docs.ignition-hub.ai)**

## Building From Source

This is a monorepo managed with [Turborepo](https://turbo.build/repo) and CMake. While most users will consume the pre-built packages for their language, contributors and advanced users can build the entire SDK from source.

**1. Clone the Repository:**
```bash
git clone https://github.com/your-org/ignition-sdk.git
cd ignition-sdk
```

**2. Install Prerequisites:**
*   A modern C++ compiler (GCC, Clang, or MSVC)
*   CMake (3.15+)
*   Node.js and Yarn (for the monorepo tooling)
*   The toolchain for the specific language you want to build (e.g., Python, Rust's `cargo`, etc.)

**3. Build Everything:**
```bash
yarn install  # Install monorepo tooling
yarn build    # This will build the core C++ libs and all language packages
```

For detailed, language-specific build instructions, please see the `README.md` inside each `packages/*` directory.

---

## Join the Community

The future of applied AI is being built by a global community. We invite you to be a part of ours.

*   **💬 [Join our Discord Server](https://discord.gg/your-invite-link):** The best place to ask questions, get help from the community, share your projects, and chat directly with the core Ignition AI team.
*   **🐞 [Report a Bug or Request a Feature](https://github.com/your-org/ignition-sdk/issues):** Found a problem or have a great idea? Let us know by opening an issue.
*   **✨ [Contribute](https://github.com/your-org/ignition-sdk/blob/main/CONTRIBUTING.md):** We are a community-driven project and welcome contributions of all sizes, from documentation fixes to new features. Check out our contributing guide to get started.

## License

This repository is licensed under the **[Apache 2.0 License](https://github.com/your-org/ignition-sdk/blob/main/LICENSE)**.