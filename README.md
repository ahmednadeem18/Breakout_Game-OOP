## BreakOut Game
A simple version of the classic Breakout game made using C++ and object-oriented programming.

## How to Play
You move a paddle to keep the ball in the air and break all the bricks. Some bricks drop power-ups. The game gets faster with each level. You can also save and load your progress.

## Main Features
Bricks that need multiple hits to break

## Power-ups: extra balls or bigger paddle

Multiple balls at once

Levels with increasing difficulty

Paddle Up Icrease Time for specific TIme Using Chrono LIbrary

## How It Works
Each game frame does the following:

Reads paddle movement

Moves balls and checks for collisions

Updates bricks and drops power-ups

Checks for win, lose, or next level

## Code Concepts Used
Inheritance: PowerBrick inherits from Brick

Polymorphism: Different hit() methods for brick types

Templates: Custom MyVector<T> for storage

Composition: Game has balls, bricks, and paddle

📌 UML Diagram: [View UML](https://github.com/ahmednadeem18/BreakOut-Game/blob/c8a651f435b6d3914fde4b5622cfd2d3ac4c2b6c/UML%20Final.pdf)

📌 Flowchart: [View Flowchart](https://github.com/ahmednadeem18/BreakOut-Game/blob/c8a651f435b6d3914fde4b5622cfd2d3ac4c2b6c/Flow%20Chart%20FInal.pdf)
