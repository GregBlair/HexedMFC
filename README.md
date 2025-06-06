When I was a kid, my mom gave me this puzzle because I loved puzzles.
https://www.nobleknight.com/P/2147797442/Hexed?srsltid=AfmBOopvzovwjiKASsxSvs2Dxh5Ry-1TzpyPIFi6W9FScWU51d9QuPIw

Basically, it was all 12 possible combinations of pieces composed of 5 contiguous blocks and figuring out how they fit into a 10 X 6 rectangle.
The version I received stated there were 2339 ways to fit these pieces into a rectangle.
Decades ago, I verified the 12 pieces by pencil and paper and verified the 2339 (10 X 6) solutions with a brute force C++ solution.
Incidentally, I also found 4 solutions for a 20 X 3 rectangle.

This suggests a more generic approach.  I am currently unemployed and intend to use this project to demonstrate my C++ skills.  This version also uses BCG since a prospective client uses BCG.

The goal of this project is to generate all the possible pieces for a particular block count, determine the possible rectangles for these pieces, and determine the solutions for all these rectangles.

Note: Block counts 1 and 2 are trivial with only one possible piece.  8 blocks can enclose an empty space.  I plan to explore higher block counts if the 7 block solutions are interesting.

Note: Over the decades, I have only generated 1 solution using the actual puzzle.  My brain always gets distracted with the ideas brough forth in this code solution.
A good friend had his first solution in about 3 minutes, also providing some motivation. 
