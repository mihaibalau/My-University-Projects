# Toy Language Interpreter (Java)

A Java-based interpreter for a custom-designed concurrent toy programming language, built using advanced programming concepts and architectural patterns.

## Project Overview

This interpreter was developed incrementally as part of university coursework. It supports execution of programs written in a custom-defined language, demonstrating key programming principles and complex features.

## Key Concepts & Features

- **Model-View-Controller (MVC)** architecture
- **Object-Oriented Programming (OOP)** principles: interfaces, inheritance, polymorphism
- **Concurrency**: Multi-threaded execution with `fork` statements and Java's `ExecutorService`
- **Heap Management**: Dynamic memory allocation with garbage collection
- **File Operations**: Open, read, write, and close files using Java I/O streams
- **Type Checking**: Static type checking before program execution
- **Robust Exception Handling**: Custom exceptions for various runtime errors
- **Graphical User Interface (GUI)**: Interactive GUI built with JavaFX

## Technical Complexity

The project demonstrates advanced technical skills through:

- Implementation of custom data structures (Stack, Dictionary, List) using Java generics.
- Simulation of complex language features (expressions evaluation, conditional logic).
- Management of concurrent program states with shared resources (Heap, FileTable).
- Integration of static type checking to ensure program correctness.
- Comprehensive logging for debugging and program state visualization.

---

## Short Documentation

### Language Elements:

| Statements                 | Expressions                     | Types & Values            |
|----------------------------|---------------------------------|---------------------------|
| Compound (`stmt1; stmt2`)  | Arithmetic (`+`, `-`, `*`, `/`) | Integer (`int`)           |
| Assignment (`a = exp`)     | Logical (`and`, `or`)           | Boolean (`bool`)          |
| Conditional (`if`)         | Relational (`<`, `<=`, etc.)    | String (`string`)         |
| Looping (`while`)          | Heap operations (`new`, `rH`, `wH`) | Reference (`Ref type`) |
| Concurrency (`fork`)       | Variable & Constant evaluation  |                           |

### Program State Components:

- Execution Stack (statements execution order)
- Symbol Table (variables and values)
- Heap Table (dynamic memory allocation)
- Output List (program outputs)
- File Table (file management)

### GUI Visualization:

The JavaFX interface allows users to:

- Select predefined programs.
- Visualize execution steps interactively.
- Inspect heap memory, symbol tables, execution stacks, file tables, and outputs in real-time.

## Achievements

This project received the maximum grade (**10/10**) due to its complexity, correctness, adherence to software design principles, and comprehensive feature set.
