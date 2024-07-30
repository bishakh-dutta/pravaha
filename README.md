 
# Pravaha Programming Language(.prv)

### Compile & Run Linux
```bash
g++ src/main.cpp src/lexer/lexer.cpp -o build/pravaha
./build/pravaha ./examples/test.prv
```

### Compile & Run Windows
```bash
clang++ -std=c++17 -target x86_64-pc-windows-gnu src/main.cpp -o src/main.exe
./src/main.exe ./examples/test.prv

clang++ -std=c++17 -target x86_64-pc-windows-gnu  src/main.cpp src/lexer/lexer.cpp -I. -o build/pravaha
./build/pravaha.exe ./examples/test.prv
```

## Features

- **Simple Syntax**: Inspired by C-style languages with a focus on readability and clarity.
- **Object-Oriented Programming**: Includes classes, inheritance, and polymorphism for structured software design.
- **Functional Programming**: Provides support for functional programming paradigms.
- **Standard Library**: A comprehensive standard library for common tasks and utilities.
- **Extensibility**: Easily extendable with modules and libraries written in Pravaha or other languages.

## Getting Started

### Installation

To use Pravaha, you need to install the Pravaha compiler and interpreter. Detailed installation instructions will be provided here.

### Hello, World!

```prv
// Hello, World! example in Pravaha
print("Hello, World!")
```
### Variables and Constants

```prv
// Variable declaration
int x = 10
float y = 3.14

// Constant declaration
const int MAX_VALUE = 100
```
### Functions

```prv
// Function declaration
bool check()
    return true
```
### Control Structures

```prv
if (x > 5)
    print("x is greater than 5")
else
    print("x is not greater than 5")

// Else-if statement
if (x > 10)
    print("x is greater than 10")
else if (x > 5)
    print("x is greater than 5 but not greater than 10")
else
    print("x is 5 or less")

// Switch-Case Statement
int choice = 2
switch (choice)
    case 1
        print("Choice is 1")
        break
    case 2
        print("Choice is 2")
        break
    default
        print("Unknown choice")
```

### Loops

```prv
while (x > 0)
    x--

for (int i = 0; i < 10; i++)
    print(i)
```
### Object-Oriented Programming

```prv
// Class declaration
class MyClass
    private
        int data
    
    public
        void setData(int value)
            data = value
        
        int getData()
            return data

// Object creation
MyClass obj
obj.setData(42)
int value = obj.getData()
```