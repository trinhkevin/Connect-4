## Final Project: Report

# User Perspective:

From the user perspective, you would launch up the program and you'd see a game board and a side 
panel. On the side panel, there's a circle with the color of the current "turn" or current 
player playing. To play this game, you need two players and they play against each other. There 
is also controls on the side panel. You use the arrows to go left and right, the spacebar to 
insert a disc, 'n' for a new game, and 'q' for quitting. On the board, you have a 7x6 board. 
There's a white ring around the part of the board that you can insert a disc into. Two players 
would then play this until there is a four in a row, hence "Connect 4". Once someone wins, there 
is a prompt that displays the winner and a footnote under the prompt that tells the user to 
click 'n' to begin another game.

# Programmer Perspective:

From the programmer perspective, I had several functions that I called from within a while loop 
that would run forever. I drew the board first (which is the board rectangle in the background 
that the playable area is in), then I drew the disc. It would draw black disc if it was "empty" 
to show that it was playable, red disc if a red disk was there, and yellow disk if a yellow disk 
was there. Then, based on where the slider (to show where the user), I would draw a white ring 
around the area that the disk would "land on". The board was simply an 11x10 array. I added 4 to 
the original 7x6 array because I wanted to check if there was a 4 in a row, and to do that I 
needed a "ghost" array around the edges. Then I drew the side panel. The only thing that would 
change within the side panel was the "current turn" and that simply started at red and then 
changed to yellow (and vice versa) is a placement was a success. Then I checked if there was a 
win on the board, if there was, the win prompt would appear. After that, there's a if statement 
that would wait for user input. I would increment the sliderPos if the right or left arrow was 
pressed, and then I would try to insert a disc if the spacebar was pressed. This was done with 
an insertdisc function that would return a 1 or a 0 if I was able to place a disc in the slider 
position. Then if it was a success, the "turn" would change. Onto the other possible inputs.... 
If the user press 'n', I would simply clear the array and thus, clear the board. If the user 
pressed 'q', I would return 0. At the end of my while loop, I would sleep and then clear the 
screen.

# Troubleshooting Steps:

For the graphics, I would change the coordinate values until it look right on the screen. It was 
a lot of guessing and checking or math if I was drawing within a loop. Most of my functions were 
very straight forward and the biggest problems I had were just computing the numbers to draw 
every I had correctly. One stupid problem I had was a compiling error, it kept giving me an 
error that I needed to add a ';' after the '{' or ')'. After checking my code for a couple 
minutes, I saw that I didn't do anything wrong. The error was from this: "// Diagonal \". 
Apparent after the comments "//" I cannot write a "\" or I would get a compiling error.
