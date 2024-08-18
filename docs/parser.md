# Pravaha Language - Operator Precedence


| Precedence Level | Operators              | Associativity |
|------------------|------------------------|---------------|
| 1 (Highest)      | `not`                  | Left to right         |
| 2                | `*`, `/`, `+`, `-`| Left to right          |
| 3                | `<`, `<=`, `>`, `>=`   | Left to right          |
| 4                | `==`, `noteq`          | Left to right          |
| 5                | `and`                  | Left to right          |
| 6 (Lowest)       | `or`                   | Left to right          |


## Precedence Tree for Conditional Expression
```not a > b and c == d or e <= f```


              or
           /     \
         and      <=
        /   \     / \
       >     ==  e   f
      / \   /  \
    not  b c    d
     |
     a