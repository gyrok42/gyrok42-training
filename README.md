# **Training Embedded Systems Concepts**
#### Building with Bazel | Unit-test with Google Test
## **Overview**
This repository offers C and C++ training exercises built with **Bazel**, providing a structured environment for learning key concepts.<br>
Exercises are in `src/` and `include/`, with unit tests using **Google Test** in `tests/`. More exercises will be added over time.<br>
See below for setup and usage instructions.

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
It is just building the experiments as a library and running unit-tests.

### **6. Generate Documentation with Doxygen**
To generate the project documentation using **Doxygen**, follow these steps:

#### **6.1 Install Doxygen**
Ensure you have **Doxygen** installed. If not, install it using:

- **Ubuntu/Debian:**
  ```sh
  sudo apt-get install doxygen
  ```
- **MacOS (Homebrew):**
  ```sh
  brew install doxygen
  ```
- **Windows:**
  Download and install from [Doxygen's official site](https://www.doxygen.nl/download.html).

#### **6.2 Run Doxygen**
To generate the documentation, execute:

```sh
doxygen Doxyfile
```

#### **6.3 View the Documentation**
Once generated, the documentation will be available in:
- **HTML format:** `docs/html/index.html`
- **LaTeX format:** `docs/latex/`

To view the HTML documentation, open:

```sh
xdg-open docs/html/index.html  # Linux
open docs/html/index.html      # MacOS
start docs/html/index.html     # Windows
```

## **Project Structure**

```
.
├── docs
│   ├── html
│   ├── latex
│   └── CODEOWNERS
├── include
│   └── bitwise-operations
├── src
│   └── bitwise-operations
├── tests
│   └── bitwise-operations
├── third-party
├── tools
├── Doxyfile
├── LICENSE
├── MODULE.bazel
└── README.md
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

