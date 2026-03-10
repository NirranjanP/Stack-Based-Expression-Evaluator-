Infix to Postfix Expression Evaluator
A robust C implementation of Dijkstra's Shunting Yard algorithm designed to parse, convert, and evaluate complex mathematical expressions.
This project demonstrates core concepts in lexical scanning, operator precedence, and stack-based parsing.

🚀Features
1. Floating-Point Arithmetic: Full support for decimal numbers and precise floating-point division.
2. Advanced Lexical Scanning: Accurately groups multi-digit numbers and correctly identifies unary negative signs versus binary subtraction.
3. Operator Precedence & Associativity: Handles arithmetic operators such as ^, *, /, +, - with standard mathematical precedence, 
alongside nested parenthesis ().
4. Memory Safety: Includes strict bounds checking to prevent static stack overflows.
5. Syntax Validation: Terminates with informative error messages for bracket mismatches, invalid characters, or insufficient operands.

🧠Program Logic

The program operates in two distinct phases:
1. Infix to Postfix Conversion (Shunting Yard)
Converts human-readable mathematical notation (e.g., 3 + 4 * 2) into Reverse Polish Notation / Postfix (e.g., 3 4 2 * +).
This phase utilizes a character stack to hold operators and parenthesis, ensuring higher-precedence operators are pushed to the output string before lower-precedence ones.
2. Postfix Evaluation
Reads the generated Postfix expression from left to right. Numbers are pushed onto a floating-point stack.
When an operator is encountered, the top two numbers are popped, the operation is applied, and the result is pushed back onto the stack.

Compilation and Usage

Because the code uses the pow() function from the standard math library, you must compile it with the -lm flag using GCC:
gcc filename.c -o filename -lm
./filename

Example I/O

Example 1: Standard Arithmetic
Input: 10 + 2 * 6
PostFix Expression: 10 2 6 * + 
Expression Result: 22.0000

Example 2: Floating Points and Negative Numbers
Input: -5.5 + (3.14 * 2) ^ 2
PostFix Expression: -5.5 3.14 2 * 2 ^ + 
Expression Result: 33.9396

Example 3: Error Handling
Input: 5 + (3 * 2
Invalid Expression-Bracket Mismatch
