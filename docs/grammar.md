# Grammar for Pravaha Language

## Non-Terminals

1. **Program**
    - Represents the entire code structure.
    - `Program -> StatementList`

2. **StatementList**
    - Represents a list of statements.
    - `StatementList -> Statement StatementList'`
    - `StatementList' -> Statement StatementList' | ε`

3. **Statement**
    - Represents various types of statements in the language.
    - `Statement -> PrintStmt | VariableDecl | ConstDecl | FunctionDecl | IfStmt | SwitchStmt | ExprStmt`

4. **VariableDecl**
    - Represents variable declarations.
    - `VariableDecl -> Type Identifier "=" Expr`

5. **ConstDecl**
    - Represents constant declarations.
    - `ConstDecl -> "const" Type Identifier "=" Expr`

6. **FunctionDecl**
    - Represents function declarations.
    - `FunctionDecl -> Type Identifier "(" ParamList ")" FunctionBody`
    - `FunctionDecl -> Type Identifier "(" ")" FunctionBody`

7. **ParamList**
    - Represents parameter lists in function declarations.
    - `ParamList -> Parameter ParamList'`
    - `ParamList' -> "," Parameter ParamList' | ε`

8. **Parameter**
    - Represents parameters in function declarations.
    - `Parameter -> Type Identifier`

9. **FunctionBody**
    - Represents the body of a function.
    - `FunctionBody -> BlockStmt`

10. **BlockStmt**
    - Represents a block of statements.
    - `BlockStmt -> Indent StatementList Dedent`

11. **IfStmt**
    - Represents if statements.
    - `IfStmt -> "if" "(" Expr ")" BlockStmt ElseIfList ElsePart`
    - `ElseIfList -> ElseIf ElseIfList | ε`
    - `ElseIf -> "elif" "(" Expr ")" BlockStmt`
    - `ElsePart -> "else" BlockStmt | ε`

12. **SwitchStmt**
    - Represents switch statements.
    - `SwitchStmt -> "switch" "(" Expr ")" "Indent" CaseList DefaultPart "Dedent"`
    - `CaseList -> Case CaseList | ε`
    - `Case -> "case" Literal StatementList`
    - `DefaultPart -> "default" StatementList | ε`

13. **ExprStmt**
    - Represents expression statements.
    - `ExprStmt -> Expr`

14. **Expr**
    - Represents expressions.
    - `Expr -> AssignmentExpr`

15. **AssignmentExpr**
    - Represents assignment expressions.
    - `AssignmentExpr -> LogicalOrExpr ( "=" AssignmentExpr | ε )`

16. **LogicalOrExpr**
    - Represents logical OR expressions.
    - `LogicalOrExpr -> LogicalAndExpr ("or" LogicalAndExpr)*`

17. **LogicalAndExpr**
    - Represents logical AND expressions.
    - `LogicalAndExpr -> EqualityExpr ("and" EqualityExpr)*`

18. **EqualityExpr**
    - Represents equality expressions.
    - `EqualityExpr -> RelationalExpr (("==" | "!=") RelationalExpr)*`

19. **RelationalExpr**
    - Represents relational expressions.
    - `RelationalExpr -> AdditiveExpr ((">" | "<" | ">=" | "<=") AdditiveExpr)*`

20. **AdditiveExpr**
    - Represents additive expressions.
    - `AdditiveExpr -> MultiplicativeExpr (("+" | "-") MultiplicativeExpr)*`

21. **MultiplicativeExpr**
    - Represents multiplicative expressions.
    - `MultiplicativeExpr -> UnaryExpr (("*" | "/") UnaryExpr)*`

22. **UnaryExpr**
    - Represents unary expressions.
    - `UnaryExpr -> ("+" | "-" | "not") PrimaryExpr`

23. **PrimaryExpr**
    - Represents primary expressions.
    - `PrimaryExpr -> Literal | Identifier | "(" Expr ")"`
  
## Terminals

- **Identifier**: Represents variable and function names.
  - `Identifier -> [a-zA-Z_][a-zA-Z0-9_]*`

- **Literal**: Represents literal values such as numbers, strings, and booleans.
  - `Literal -> IntLiteral | FloatLiteral | StringLiteral | BoolLiteral`

- **Type**: Represents data types.
  - `Type -> "int" | "float" | "string" | "bool"`

- **IntLiteral**: Represents integer literals.
  - `IntLiteral -> [0-9]+`

- **FloatLiteral**: Represents floating-point literals.
  - `FloatLiteral -> [0-9]+\.[0-9]+`

- **StringLiteral**: Represents string literals.
  - `StringLiteral -> "\"" [^\n\"]* "\""`

- **BoolLiteral**: Represents boolean literals.
  - `BoolLiteral -> "true" | "false"`

- **Indent**: Represents indentation.
  - `Indent -> "INDENT"`

- **Dedent**: Represents dedentation.
  - `Dedent -> "DEDENT"`


## Keywords

`if`, `elif`, `else`, `for`, `while`, `switch`, `case`, `default`, `break`, `const`, `print`, `return`, `true`, `false`

## Operators
`"+" , "-" , "*" , "/" , "==" , "noteq" , ">" , "<" , ">=" , "<=" , "or" , "and" , "not"`