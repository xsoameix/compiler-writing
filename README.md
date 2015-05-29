# Introduction

These are self-written exercise answers for *The Theory and Practice of Compiler Writing*.

For instance, run the answer for 5th question of exercises 7-1 by typing:

    $ gcc 7.1.ex.5.c -o 7.1.ex.5.bin
    $ ./7.1.ex.5.bin

The following are questions for each exercise.

# Chapter 7 Bottom-up Parsing

## Exercises 7-1

1.  Consider expressions which contain relational operators. In particular, obtain the precedence functions which will handle the relational operators

        <, ≤, =, >, ≠, and ≥

    To avoid excessive parenthesization, the relational operators should have a lower priority than the arithmetic operators.

2.  As a continuation of Exercise 1, consider extending the expressions so that they contain logical operators. In particular, obtain the precedence functions that will handle the logical operators

        ¬ (not)
        & (and)
        | (or)

    which are given in decreasing order of priority. These operators have lower priority than the relational and arithmetic operators.

3.  Describe how conditional statements (if...then...else) can be implemented in the suffix Polish framework. In particular extend the precedence functions obtained in Exercise 2 so as to incorporate conditional statements. 

4.  Thus far, we have only been concerned with the binary subtraction operator. In mathematics there are three usages of the minus sign: to indicate the binary subtraction operator, the unary minus operator (such as - x), and the sign of a constant (such as x + (- 5)). Obtain a precedence table capable of handling assignment statements containing the unary minus (denoted by θ) and the assignment operator (denoted by ←). (Hint: It is an easy matter to distinguish the different occurrences of minus. A minus symbol will denote a binary operator if it does not occur either at the beginning of an expression or immediately after a left parenthesis. A minus symbol at the beginning of an expression or immediately after a left parenthesis will be a unary operator unless it is followed by a digit or decimal point.) 

5.  As we mentioned earlier, for certain applications the scanning of the infix expression is restricted to a left-to-right one-character-at-a-time scan. In an infix to prefix conversion, two stacks instead of one (as for infix to suffix conversion) are required: an operator stack and an operand stack (to store temporarily the intermediate operands). Recall that all variables and constants retain their relative order when an infix expression is converted to prefix form. The operators, however, are reordered according to their relative precedence, and the operator stack is used in this reordering. The operand stack is used for temporary storage of intermediate operands so that, when finally the operator which connects them is found to be applicable, it can be placed in front of the concatenated operands. 

    Formulate an algorithm to perform the translation assuming infix expressions consisting of single-letter variables and the four arithmetic operators. 

6.  Investigate the possibility of obtaining precedence functions for an expression in APL. What difficulties, if any, are there in obtaining these functions? 
