# C++ Data Structures and Tensor Utility (Custom Data Handler)

## 🎯 Project Overview

This project is a fundamental C++ library developed as a core assignment. It focuses on implementing high-performance, reusable data structures and essential data handling utilities required for modern computational tasks, specifically those involving multi-dimensional arrays (tensors).

The components serve as the foundational backend for processing data, including dataset creation, batching, and shuffling, before being passed to higher-level models.

## ✨ Key Features

* **Developed and implemented core C++ list data structures** (`XArrayList` and `DLinkedList`) using OOP and generic programming principles.
* **Integrated the high-performance `xtensor` library** to manage and perform tasks on multi-dimensional array data (tensors).
* **Built a robust data handling utility** (e.g., `Dataset` and `DataLoader` classes) to efficiently **create and split datasets** into process-ready batches.
* **Applied advanced OOP and generic programming principles**, utilizing custom iterators (forward and backward) and function pointers to ensure code reusability and safe memory management.

## 🛠️ Technologies & Structure

### Technologies Used

| Category | Component | Description |
| :--- | :--- | :--- |
| **Language** | C++17 | Primary language, emphasizing high performance and generic programming. |
| **Libraries** | xtensor | Used for working with N-dimensional arrays (tensors). |
| **Principles** | OOP, Generic Programming | Extensive use of template classes, inheritance (`IList`), and custom iterators. |

### Repository Structure

| Folder/File | Description |
| :--- | :--- |
| `include/` | Contains header files (`.h`) for all data structures (`DLinkedList.h`, `XArrayList.h`, `IList.h`) and data utilities (`dataloader.h`, `dataset.h`). |
| `src/` | Contains source file implementations (if any, typically `.cpp`, but often combined with `.h` in template libraries). |
| `test_*` | Contains testing logic to demonstrate the functionality of implemented structures and utilities. |
| `run.sh` | Shell script for compiling and executing the project. |

## 🚀 Setup and Run

### Prerequisites

* A C++ compiler supporting C++17 (e.g., g++).
* The `xtensor` library and its dependencies (if not locally provided).

### Build Instructions

1.  Clone the repository:
    ```bash
    git clone [https://github.com/ngodanghao2005/DSA-Project.git](https://github.com/ngodanghao2005/DSA-Project.git)
    cd DSA-Project
    ```
2.  Compile and run the project using the provided script:
    ```bash
    ./run.sh
    # Alternatively, compile manually using g++
    # g++ -std=c++17 -Iinclude src/*.cpp main.cpp -o main
    # ./main
    ```

***
*Note: This assignment specifically excludes the submission of classes related to the full MLP Neural Network.*
