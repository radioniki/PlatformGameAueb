# PENGUIN_GAMEC++
<div align = "center"> 
  <h1> 🐧 C++ Platform Game Project </h1>
</div>
This project is a C++ platform game developed as part of the 2023-2024 Programming with C++ course. The game is built using the Simple Graphics Library (SGG) provided by the course and implements core game mechanics such as dynamic memory management, inheritance, polymorphism, and collision detection.


**🎮 Game Overview**
The objective of the game is to control a character (the player) to navigate through levels, avoiding obstacles, collecting items, and reaching the end goal. Inspired by classic platform games like Super Mario, this game includes both static and dynamic elements, such as enemies, power-ups, and environmental objects.


<div aling = "center" > 
<h1>📂 Project Structure</h1>
</div>

**Fish.cpp**: Defines the behavior and characteristics of the fish objects in the game.

**GameObject.cpp**: The base class for all objects in the game, such as players, enemies, and static elements.

**GameState.cpp**: Manages the overall game state, including levels, score, and transitions.

**Igloo.cpp**: Represents igloo objects in the game.

**Level.cpp** / Level2.cpp: Define the different levels in the game, including object placement and interactions.

**Player.cpp**: Contains the player’s attributes, controls, and interactions.

**Timer.cpp**: A utility class to manage timing in the game.

**Main.cpp**: The entry point of the game, initializing the game state and starting the game loop.

**box.h**: Custom library provided by the instructor for handling collisions and bounding boxes.


<div aling = "center" > 
<h1>🛠 Features</h1>
</div>

**Dynamic Memory Management**: Objects such as enemies and power-ups are dynamically created and destroyed using memory management practices (new, delete).

**Inheritance and Polymorphism**: The game uses a hierarchy of game objects, with GameObject as the base class. Polymorphic method calls (update(), draw(), init()) are implemented to handle different game elements.

**Collision Detection**: The game checks for collisions between objects (e.g., player and enemies, player and platforms) using bounding boxes (box.h).

**Level Transitions**: The game can load different levels and manage the transition between them.

🚧 **Current Status**
The game is still under development, with the following features in progress:

Additional levels and game objectives.

Enhanced enemy AI and behaviors.

📦**Dependencies** 
Simple Graphics Library (SGG): This project exclusively uses SGG for window management, keyboard input, graphics rendering, and audio playback.
SGG Repository
