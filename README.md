# Learning To Write A Compiler
-------------------------------

<p align="center">
        <a href="https://doc.lagout.org/programmation/C/CPP101.pdf"><img src="https://img.shields.io/badge/code_style-standard-brightgreen.svg">
        </a>
</p>

<b>Built With :</b>
        Custom Makefile

<p>
We are learning to write a compiler. We will create a single-pass compiler(or interpreter) initially. It will contain a Lexer, a recursive-descent Parser that creates an Abstract Syntax Tree(AST) and multiple visitor patterns that visit the AST and perform the specific task like pretty-printing, creating symbol table, semantic analysis and so on.
</p>

The compiler will initially have only data types and not any data structures. The context-free grammer(Backaus-naur form) of the language can be found in docs/syntax_specification.txt and the tokens recognized by the language along with the use case can be found in [docs/language_tokens.md](languages_tokens.md#top).
The Git Help page can be found in [docs/git_help.md](git_help.md#top).


<b><i>Future Improvements : </b></i>
<p>
        The motivation behind creating this language is to be able to create a language that is extendible by the users. So after we have learned to create a basic compiler, we will focus on making it an extensible programming language.
</p><p> 
        We also hope to create appropriate files to export to text editors for syntax highlighting and formatting according to the language.
</p>

<b>License : GNU Public License 3.0 </b>
