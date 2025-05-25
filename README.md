# BreakOut-Game
# 💡 Breakout++: Bricks, Balls & Binary

A modern reimagining of the classic *Breakout* arcade game — rebuilt from the ground up to flex your object-oriented design muscles. This is more than just bouncing a ball to smash bricks; it's about thoughtful class architecture, real OOP modeling, custom libraries, and game-saving wizardry that would make even your CS prof proud.

## 🎯 Game Design Core Philosophy

This isn’t just a ball and paddle game — it’s an engineered simulation that challenges both reflexes and design principles. Every component in the game is **modular**, **scalable**, and **purpose-built** to illustrate clean software architecture using C++.

We took the traditional Breakout gameplay and enhanced it with:

* **Multi-hit bricks** for layered challenges
* **Power-ups** that spawn new balls dynamically,Increses Paddle Size
* **Level-based difficulty scaling**
* **Persistent save/load system using binary files**
* **Robust error handling and template-driven design**


---

## 🎮 Game Overview

The player controls a paddle that bounces a ball to break bricks arranged at the top of the screen. Destroying certain bricks spawns a power-up that adds more balls. Each level increases the game speed, and players can save/load their game progress.

---

## 🔁 Core Gameplay Loop

Each frame of the game involves:

1. **Input handling** — Paddle movement
2. **Ball update** — Position, velocity, and collisions
3. **Brick collision checks** — Breakable logic, power-up triggers
4. **Game state progression** — Check for win/lose or level up

> \[!NOTE]
> Some bricks require multiple hits to destroy. This is tracked using an internal durability counter in each `Brick` object.

---

## 🔋 Power Bricks

* Breaking certain bricks triggers the drop of a **power-up**
* The power-up  has two Options
* 1.Increases the number of balls in play
* 2.Increses The size of Paddle
* Multiple active balls are managed using a `MyVector<Ball>` container

These bricks are implemented via a subclass: `PowerBrick : public Brick`, showcasing polymorphism.

---

## 📈 Difficulty Progression

* Each new level increases the speed of all balls
* Bricks are re-randomized with higher durability values

---

## 📦 Features

* Multi-hit `Brick` system
* Power-up mechanics via `PowerBrick`
* Multiple active balls
* Level progression
* Save/load system using binary I/O
* Central logging system for every game event

> Example Log:

```
[EVENT] Ball collided with Brick at (5, 7)
[EVENT] Brick durability decreased to 1
[EVENT] PowerBrick destroyed - spawning extra ball
[STATE] Ball count: 2
```

---

## 🧠 OOP Design & Requirement Coverage

| Requirement            | Implementation Example                                    |
| ---------------------- | --------------------------------------------------------- |
| **Inheritance**        | `PowerBrick` inherits from `Brick`                        |
| **Polymorphism**       | `hit()` method overridden in `PowerBrick`                 |
| **Composition**        | `Game` composed of `Ball`, `Brick`, `Paddle` objects      |
| **Aggregation**        | `Game` has a `MyVector<Brick*>` representing the level    |
| **Association**        | `Ball` and `Brick` reference each other during collision  |
| **Exception Handling** | Custom exceptions for file I/O, invalid moves             |
| **Templates**          | `MyVector<T>` used throughout for collections             |
|                        | `logEvent<T>()` function logs templated data types        |
| **Logging**            | Every hit, collision, level-up, and load/save event       |
| **Binary Save/Load**   | Save/load entire game state via `fstream` and binary mode |

📌 UML Diagram: [View UML](https://github.com/ahmednadeem18/BreakOut-Game/blob/c8a651f435b6d3914fde4b5622cfd2d3ac4c2b6c/UML%20Final.pdf)

📌 Flowchart: [View Flowchart](https://github.com/ahmednadeem18/BreakOut-Game/blob/c8a651f435b6d3914fde4b5622cfd2d3ac4c2b6c/Flow%20Chart%20FInal.pdf)
