PrimesToRiches is a board game, reminiscent of snakes and ladders, except
there are no ladders, and all movements are determined by numeric properties
of the numbers on the cells.

The board is a rectangular array of squares, 8 wide by 16 long.
Each square contains a number, 1 through 128

Players start at square 0 (outside the board).
Players take turn rolling dice, and moving forward by the number
shown on the 2 dice. The first player to reach 128 wins.

Some squares on the board have actions associated with them
 - If a player lands on a prime number, he/she collects $1 from the bank
 - If a player lands on a number divisible by 3, they go left one square (subtract 1)
 - number divisible by 5 -> down 1 row (subtract 8)
 - number divisible by 7 -> 1 row down and 1 column to the right (subtract 7)
When a number is divisible by more than one factor, these rules are combined.
A player must follow the arrows, which may form quite a long and painful chain,
or "pay to stay". The cost to stay is: $1 for squares 1..32, $2 for squares 33..64,
$3 for square 65..96 and $4 for square 97..128

A physical board exists, this is just the supporting program for it.
This program figures out the optimal pay-to-stay strategy and checks expected
game runtime based on specified rules. The idea is that there must be a wide gap
in performance between bad and good strategies, otherwise rules are unbalanced.

The game is not too strategic, and kids quickly figure out how to play well.
Optimal strategy under this set of rules is to always pay (if you have the cash)
if the movement is 8 squares or more and you have passed square #56.
