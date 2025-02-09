# **Bitwise Operations Training with Bazel**

## **Overview**
This repository provides training exercises, implemented in C and C++ and built using **Bazel**. The goal is to offer a structured environment to practice and understand several concepts.

## **Getting Started**

### **1. Clone the Repository**
To get a local copy of this repository, run:

```sh
git clone https://github.com/gyrok42/gyrok42-training.git
cd gyrok42-training
```

### **2. Install Dependencies**
Ensure you have **Bazel** installed. If you haven't installed it yet, follow the [Bazel installation guide](https://bazel.build/install).

To check if Bazel is installed, run:

```sh
bazel --version
```

### **3. Build the Project**
Use Bazel to build the project:

```sh
bazel build //...
```

or for a specific module:

```sh
bazel build //src/bitwise-operations:flip_bitmap
```

### **4. Run Tests**
To verify that everything works correctly, execute:

```sh
bazel test //tests/...
```

or for a specific test:

```sh
bazel test //tests/bitwise-operations:flip_bitmap_test
```

### **5. Run the Executable**
If your project produces a binary, you can run it with:

```sh
bazel run //src/bitwise-operations:flip_bitmap
```

## **Project Structure**

```
.
├── include/                # Header files
│   ├── bitwise-operations/
│   │   ├── flip_bitmap.h
│   │   ├── BUILD
├── src/                    # Source code
│   ├── bitwise-operations/
│   │   ├── flip_bitmap.cc
│   │   ├── BUILD
├── tests/                  # Unit tests
│   ├── bitwise-operations/
│   │   ├── flip_bitmap_test.cc
│   │   ├── BUILD
├── third-party/            # External dependencies (if any)
├── tools/                  # Utility scripts/tools
├── MODULE.bazel            # Bazel module definition
├── LICENSE                 # License file
├── README.md               # Project documentation
```

## **Contributing**
If you'd like to contribute:

1. Fork the repository
2. Create a new branch (`git checkout -b feature-branch`)
3. Commit your changes (`git commit -m "Add new feature"`)
4. Push to your branch (`git push origin feature-branch`)
5. Open a Pull Request

## **License**
This project is licensed under the **MIT License** – see the [LICENSE](LICENSE) file for details.

