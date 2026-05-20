# ⚡ EpollReactor

![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg?style=for-the-badge&logo=c%2B%2B)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)

> **Note:** This is a personal project built completely from scratch to deepen my understanding of modern C++, concurrent programming, and low-level Linux networking. It was developed independently, relying strictly on official documentation and POSIX/system libraries, without the use of AI code generation tools.

## 📖 Overview

**EpollReactor** is a high-performance, event-driven networking framework tailored for Linux environments. At its core, it leverages the Linux `epoll` system call for efficient I/O multiplexing combined with a custom-built, actor-based thread pool to manage concurrent connections securely. 

This project demonstrates the practical application of low-level systems programming concepts alongside modern C++23 features, offering a robust foundation for building scalable asynchronous network servers.

## ✨ Key Features

* **Efficient I/O Multiplexing:** Utilizes Linux `epoll` (`sys/epoll.h`) to monitor multiple file descriptors simultaneously without the overhead of blocking threads or busy-waiting.
* **Actor-Based Concurrency:** Implements a custom `ActorThreadPool` where each connection/event handler acts as an isolated "actor". 
    * **Thread Safety:** Guarantees that tasks belonging to the same actor never execute concurrently.
    * **Lock Striping:** Uses an array of mutexes (lock striping) to minimize lock contention and maximize throughput during task submission and completion.
* **Modern C++23 Standards:** Strict adherence to modern C++ practices, including smart pointers, atomic operations, lambdas, and RAII principles. Compiled with `-Wall -Wextra -Wpedantic` to ensure code safety.
* **Zero Core Dependencies:** The core library (`reactor_lib`) relies solely on the C++ Standard Library and Linux system headers. (GoogleTest is used exclusively for the testing suite).

## 🏗️ Architecture

The framework is divided into several cooperating components:

1.  **`Reactor`:** The heart of the system. It runs the main event loop, waiting on `epoll_wait`. When events occur, it dispatches the appropriate I/O tasks to the thread pool. It handles waking up, shutting down, and safely updating epoll operations across threads.
2.  **`ActorThreadPool`:** A cooperative thread pool that sits on top of a standard executor. It manages a queue of pending `IO_Task` objects per `IEventHandler`, ensuring strict FIFO execution per connection.
3.  **`Executor`:** The underlying worker thread pool that actively consumes and runs tasks scheduled by the Actor Thread Pool.

## 🛠️ Getting Started

### Prerequisites
* A Linux-based operating system (required for `epoll`).
* CMake (version 3.15 or higher).
* A C++23 compatible compiler (e.g., GCC 13+, Clang 16+).

### Building the Project

This project uses CMake for building the library, examples, and tests.

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/your-username/epoll-reactor.git](https://github.com/your-username/epoll-reactor.git)
    cd epoll-reactor
    ```
2.  **Generate the build files:**
    ```bash
    mkdir build && cd build
    cmake ..
    ```
3.  **Compile the library and executables:**
    ```bash
    cmake --build .
    ```

### Running the Example
```bash 
./server-example
```

### Running the Tests
The project includes a comprehensive test suite built with GoogleTest (automatically fetched via CMake).
```bash
./reactor_tests
```