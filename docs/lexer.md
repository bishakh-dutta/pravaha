# Lexer Documentation

## Overview

The lexer (or lexical analyzer) is responsible for breaking down source code into tokens, which are meaningful units such as keywords, identifiers, operators, literals, and more. This documentation provides an overview of the lexer implementation for the Pravaha programming language.

## Components

### `lexer.h`

This header file defines the lexer class (`Lexer`) and its associated structures and enums.

#### Enumerations

- **TokenType**: Specifies the type of each token recognized by the lexer, including keywords, identifiers, operators, literals, and special tokens like `INDENT` and `DEDENT`.

#### Structures

- **Token**: Represents a token with its type, lexeme (actual string representation), line, and column in the source code.

#### Class: `Lexer`

- **Constructor**: Initializes the lexer with the input source code.
  
- **Methods**:
  - `getTokens()`: Returns a vector of `Token` objects after tokenizing the input source code.
  - `peek()`, `isSpace()`, `isNewLine()`: Helper methods for character inspection.
  - `indentSet()`: Handles indentation levels and returns `INDENT` or `DEDENT` tokens.
  - `isString()`: Recognizes string literals.
  - `isKeyword()`, `isDecimal()`, `checkAlpha()`: Methods for identifying keywords, decimal numbers, and checking alphanumeric characters.
  - `skipComment()`: Skips over single-line comments in the source code.

### `lexer_logic.h`

This header file implements the logic for the lexer class (`Lexer`). It includes definitions for all methods declared in `lexer.h`.

### `lexer.cpp`

This file contains the main entry point (`main()`) where the lexer is instantiated with source code input, and tokens are generated and printed.

## Usage

To use the lexer:

1. Include `lexer.h` in your project.
2. Instantiate a `Lexer` object with the source code string.
3. Call `getTokens()` to retrieve the vector of `Token` objects.
4. Process or analyze the tokens as needed for parsing or further stages of compilation.

## Example

Here’s a basic example of using the lexer:

```cpp
#include<iostream>
#include<fstream>
#include "lexer_logic.h"

int main(){
    // Read source code from a file
    string filePath = "../../examples/hello.prv";
    string sourceCode = readSourceCode(filePath);

    // Create a lexer instance
    Lexer lexer(sourceCode);

    // Get tokens from the lexer
    vector<Token> tokens = lexer.getTokens();

    // Print tokens
    for(const Token& token : tokens){
        cout << "[  " + getTokenTypeName(token.type) + " : " + token.lexeme
             + "       (Line: " + to_string(token.line) + " Col: " + to_string(token.column) + ") ]" << endl;
    }

    return 0;
}
```