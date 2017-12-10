# Language Tokens
------------------------


### SEMICOLON ->              ;
It is a statement terminator.Each individual statement must end with a semicolon.

------------------------

### COLON ->                     :
No special identity till now

------------------------

### COMMA ->                     , 
------------------------

### LEFT PARANTHESES -> (
------------------------

### RIGHT PARANTHESES -> )
------------------------

### LEFT CURLY -> {
Identifies the beginning of target statement in while loop.

-----------------------

### RIGHT CURLY -> }
Identifies the end of target statement in while loop

-----------------------

### DOT -> . 

-----------------------

### LEFT SQUARE -> [ 
Identifies the beginning of the condition in while loop

-----------------------

### RIGHT SQUARE -> ] 
Identifies the beginning of the condition in while loop

-----------------------

### QUESTION -> ?

-----------------------

### BANG -> !

-----------------------

### CARET -> ^ 

-----------------------

### LEFT ARROW ->    <- 

-----------------------

### RIGHT ARROW  ->    -> 

-----------------------

### LITERAL 
Literals are the constant value. They are of two types : an integer literal and a floating literal. An integer literal can be a decimal constant.Similarly, a floating point literal has an integer part, a decimal point and a fractional part.

-----------------------

### IDENTIFIER 
It is a name used to identify a variable ( function and other user defined item after future improvements). An identifier starts with letter A to Z or a to z,followed by letters and digits. The identifier name cannot start with a digit.

-----------------------

### KEYWORD 
These are the reserved words and the user is not desired to use them as identifiers or literals. Eg, int, float cannot be used as identifier.

-----------------------

### DATA_TYPE 

-----------------------

### EOS 
End Of Source 

-----------------------

### OPERATORS
 An operator is a symbol that tells the compiler to perform specific mathematical or logical functions. There are various types of operators.They are described as follows:

**1. ARITHMETIC OPERATORS**
- **PLUS (+):** 
Adds two operands
- **MINUS(-):** 
Subtracts second operand from the first
- **MULTIPLY(*):** 
Multiplies both operands
- **DIVIDE(/):** 
Divides numerator by de-numerator
- **MODULO(%):**
Returns the remainder after division

**2. RELATIONAL OPERATORS**
- **LESSER(<):**
Checks if the value of left operand is less than the value of right operand. If yes, then the condition becomes true.
- **GREATER(>)::** 
Checks if the value of left operand is greater than the value of right operand. If yes, then the condition becomes true.
- **LESSER_EQUALS(<=):**
Checks if the value of left operand is less than or equal to the value of right operand. If yes, then the condition becomes true.
- **GREATER_EQUALS(>=):** 
Checks if the value of left operator is greater than or equal to the value of right operand. If yes, then the condition becomes true.
- **NOT_EQUALS(!=):**
This operator shall be listed in our compiler after few improvements. It will be made to check if the values of two operands are equal or not. If the values are not equal, then the condition becomes true. 
- **EQUALS_EQUALS(==):**
Checks if the vlaues of two operands are equal or not. If yes, then the condition becomes true.

--------------------


### LOOPS 
Loops are used when a block of code needs to be executed several number of times.
while loop: This loop repeatedly executes a target statement as long as a given condition is true. The condition may be any expression, and true is any non-zero value. The loop iterates while the condition is true. When the condition becomes false, the program control passes to the line immediately following the loop.

- **Syntax:**
```
[condition] 
{
     statement(s);
}
```