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

4. **PrintStmt**
    - Represents the print statement.
    - `PrintStmt -> "print" "(" Expr ")" ";"`

5. **VariableDecl**
    - Represents variable declarations.
    - `VariableDecl -> Type Identifier "=" Expr ";"`

6. **ConstDecl**
    - Represents constant declarations.
    - `ConstDecl -> "const" Type Identifier "=" Expr ";"`

7. **FunctionDecl**
    - Represents function declarations.
    - `FunctionDecl -> Type Identifier "(" ParamList ")" FunctionBody`
    - `FunctionDecl -> Type Identifier "(" ")" FunctionBody`

8. **ParamList**
    - Represents parameter lists in function declarations.
    - `ParamList -> Parameter ParamList'`
    - `ParamList' -> "," Parameter ParamList' | ε`

9. **Parameter**
    - Represents parameters in function declarations.
    - `Parameter -> Type Identifier`

10. **FunctionBody**
    - Represents the body of a function.
    - `FunctionBody -> BlockStmt`

11. **BlockStmt**
    - Represents a block of statements.
    - `BlockStmt -> Indent StatementList Dedent`

12. **IfStmt**
    - Represents if statements.
    - `IfStmt -> "if" "(" Expr ")" BlockStmt ElseIfList ElsePart`
    - `ElseIfList -> ElseIf ElseIfList | ε`
    - `ElseIf -> "elif" "(" Expr ")" BlockStmt`
    - `ElsePart -> "else" BlockStmt | ε`

13. **SwitchStmt**
    - Represents switch statements.
    - `SwitchStmt -> "switch" "(" Expr ")" "{" CaseList DefaultPart "}"`
    - `CaseList -> Case CaseList | ε`
    - `Case -> "case" Literal ":" StatementList`
    - `DefaultPart -> "default" ":" StatementList | ε`

14. **ExprStmt**
    - Represents expression statements.
    - `ExprStmt -> Expr ";"`

15. **Expr**
    - Represents expressions.
    - `Expr -> AssignmentExpr`

16. **AssignmentExpr**
    - Represents assignment expressions.
    - `AssignmentExpr -> LogicalOrExpr ( "=" AssignmentExpr | ε )`

17. **LogicalOrExpr**
    - Represents logical OR expressions.
    - `LogicalOrExpr -> LogicalAndExpr ("or" LogicalAndExpr)*`

18. **LogicalAndExpr**
    - Represents logical AND expressions.
    - `LogicalAndExpr -> EqualityExpr ("and" EqualityExpr)*`

19. **EqualityExpr**
    - Represents equality expressions.
    - `EqualityExpr -> RelationalExpr (("==" | "!=") RelationalExpr)*`

20. **RelationalExpr**
    - Represents relational expressions.
    - `RelationalExpr -> AdditiveExpr ((">" | "<" | ">=" | "<=") AdditiveExpr)*`

21. **AdditiveExpr**
    - Represents additive expressions.
    - `AdditiveExpr -> MultiplicativeExpr (("+" | "-") MultiplicativeExpr)*`

22. **MultiplicativeExpr**
    - Represents multiplicative expressions.
    - `MultiplicativeExpr -> UnaryExpr (("*" | "/") UnaryExpr)*`

23. **UnaryExpr**
    - Represents unary expressions.
    - `UnaryExpr -> ("+" | "-" | "not") PrimaryExpr`

24. **PrimaryExpr**
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
`"+" , "-" , "*" , "/" , "==" , "!=" , ">" , "<" , ">=" , "<=" , "or" , "and" , "not"`