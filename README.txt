Mykhailo Glushchenko, 9403890, glushchenko@umail.ucsb.edu.
Probably Michael Glushchenko on Piazza.
UCSB CS160 Spring 2022.

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
    - 