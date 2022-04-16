# Mykhailo Glushchenko, 9403890, glushchenko@ucsb.edu
# UCSB CS160 Spring 2022
# On Piazza, and probably gauchospace too:
# Michael Glushchenko

Some problems encountered along the way:

1) Scanner problems (with -s flag):
    - actually finding the input stream and reading the getline() documentation for which delimeters are automatically skipped over.
    - making the nextToken() differentiate between when we find a ";\n" and should call getline() again, versus when T_EOF is found.
    - checking for the modulo token was tedious since I had to check it char by char.
    - overall, the scanner was the much easier part for me, this part took only a part of a single day.

2) Parser problems (with no flag):
    - The original CFG I designed did not accept the same language, as I put the paranthesis on the final level as such:
    factor -> (factor) | num, when I should have had factor -> (expression) | num
        - after reading chapter 3 of the textbook, I figured out what my problem was; after I fixed this, all parenthesized expressions
        started getting parsed correctly.
        - this problem took me about a day to figure out, wasn't too difficult, but quite time-consuming to debug.

3) Parser problems (with -e flag):
    - the hardest part of the project for me.
    - figuring out how to construct a polish post-order notation string for expression evaluation was incredibly tedious.
        - I did not want to build an unnecessary parse tree, so I tried to add the symbols into a string as I expanded the CFG.
        - this was done in a post-order type of way (first things were expanded, then we added the current symbol to the string.)
        - at the end, I used the polish post-order notation processing algorithm (using the stack) to compute the expressions.
        - left-associativty is giving me trouble now that I am half-way done through implementing the above description.

4) Cleaning up the evaluation solution
    - Instead of having a function evaluate the expression at the end, we can implemnent a stack into our Parser, and evaluate the
    expressions on the go, printing the result to cout every time we encounter a stack with 1 element left or a semicolon.
    - the final challenge I encountered through this project was not printing any output until we know there are no errors present in the entire arithmetic expression that was piped into the program.

5) INCREDIBLE DIFFICULTY IN FIGURING OUT WHY THIS WORKED ON MAC BUT NOT LINUX
    - solution ended up being that the -n flag is not allowed on MacOS, and thus is simply passed in as a part of cin (which I then succesfully filtered out every time).
        - the problem was that on linux this flag is actually read by the shell and does not go into the cin.
        - the result of the shell actually reading the -n flag on Linux is that my getline() code and the code that returns the T_EOF token needed to be tweaked
        from checking whether getline() produces an empty string to checking whether getline() produces the same string twice in a row.