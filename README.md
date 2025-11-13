# C++ Data Structures and Tensor Utility (Custom Data Handler)

## 🎯 Project Overview

This project is a fundamental C++ library developed as a core assignment. It focuses on implementing high-performance, reusable data structures and essential data handling utilities required for modern computational tasks, specifically those involving multi-dimensional arrays (tensors).

The components serve as the foundational backend for processing data, including dataset creation, batching, and shuffling, before being passed to higher-level models.

### 📝 Features

#### 1. Custom Data Structures (DSA)

* `IList<T>`: Abstract interface defining common list operations and list access methods.
* `XArrayList<T>`: Array-based list implementation, supporting dynamic resizing, iterator traversal, and exception-safe access.
* `DLinkedList<T>`: Doubly linked list implementation for efficient insertion and removal, including custom forward and backward iterators.

#### 2. Data Utility & Tensor Classes

* `Dataset<T>` / `TensorDataset`: Base and concrete classes for handling and accessing multi-dimensional data.
* `DataLoader<T>`: Core utility for managing data flow, batching, and iteration over datasets.
* **Tensor Integration**: Integrates the `xtensor` library to manage and perform operations on multi-dimensional arrays (tensors).

## 🧩 Class Structure

```text
/include/
├── ann/
│   ├── dataloader.h          # DataLoader utility for batch creation, shuffling, and iteration
│   ├── dataset.h             # Base Dataset, DataLabel, and TensorDataset classes
├── list/
│   ├── DLinkedList.h         # Doubly linked list implementation
│   ├── IList.h               # Abstract list interface
│   ├── XArrayList.h          # Array-based list implementation
│   ├── listheader.h          # Header providing type aliases (xvector, xlist)
├── util/
│   ├── Point.h               # Utility class for 3D coordinate point representation
