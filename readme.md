Description of the Language:
1. The language contains two types: integer and string.
2. The language contains 4 operators: +, -, *, and []. All operators are left associative.
3. A VarStmt is a variable declaration and initialization in one statement. The type of the IDENT is determined by the type of the Expr.
4. A SetStmt sets the value of IDENT to the value of Expr.
5. A PrintStmt prints the value of the Expr followed by a newline.
6. A RepeatStmt repeats Stmt Expr times.
7. The + and - operators represent addition and subtraction.
8. The * operator represents multiplication.
9. The [ ] operator represents slicing a string.
10. It is an error if a variable is used in an Expr before it is declared in a VarStmt. STATIC
11. It is an error if the type of a variable does not match the type of Expr in a SetStmt. STATIC
12. It is an error if the Expr in a RepeatStmt is not a non-negative integer. STATIC DYNAMIC
13. Addition is defined between two integers (the result being the sum) or two strings (the result being the concatenation). STATIC
14. Subtraction is defined between two integers (the result being the difference) or two strings (the result being the removal of the first occurrence of the second string from the first string, or the first string if the second string is not present in the first string). STATIC
15. Multiplication is defined for integers (the result being the product) or for an integer and a string (the result being the string repeated integer times). STATIC
16. Slicing is defined as creating a substring of a Primary. The first Expr must be a nonnegative integer. The second Expr must be an integer greater than the first Expr. Slicing returns a new string beginning at the character position of the first Expr and ending before the character position of the second Expr. Character positions begin at 0. STATIC DYNAMIC
17. Performing an operation with incorrect types or type combinations is an error. STATIC
18. Multiplying a string by a negative integer is an error. DYNAMIC
19. Slicing an integer is an error. STATIC
20. Specifying slicing arguments that are outside the range of the string being sliced is an error. DYNAMIC

Lexical Analyzer:
1. recognizes invalid command line flags, a file that cannot be opened, and case with more than one file name
2. recognizes string with a newline in it as an error
3. recognizes string with a # in it as a string, not a comment
4. recognizes all valid token types
5. recognizes various erroneous tokens

Parser:
1. tests against badly formed programs and incorrect arguments.
2. tests against well formed programs

Interpreter:
1. retests badly formed programs and incorrect arguments, and tests the print statement and integer operations.
2. tests variables, set, and string operations (except for slicing).
3. tests slicing and the repeat statement.
