Game Design Document

1.	Course
Institution			Worcester Polytechnic Institute (WPI)
Program			Interactive Media and Game Development (IMGD)
Title				IMGD 3000, Technical Game Development I
Year				Fall B-Term 2020, 10/21/2020 - 12/11/2020
Instructor			Professor Mark L. Claypool (claypool@cs.wpi.edu)


2.	Project

2.1	Team
Name				Virtuality Echo
Members			Forrest Welty 			(fswelty@wpi.edu)
				Thi Quynh Ha Nguyen (Luna)	(tnguyen5@wpi.edu)

2.2	Summary
For this project, team Virtuality Echo is designing and developing an original game using the Dragonfly game engine and C++ programming language.  Information about the game and its design can be found in sections 3.1 - 3.5.

2.3	References
IMGD Department	https://www.wpi.edu/academics/departments/interactive-media-game-development
Course Website			https://web.cs.wpi.edu/~imgd3000/b20/
Dragonfly Website		https://dragonfly.wpi.edu/


3.	Game

3.1	Title
Working			CPG (Creature-Playing Game)
Finished			-TBD- (to be determined)

3.2	Genre
Single Player, Fantasy, Action RPG, 2D Side Scroller, Platformer

3.3	Description
The player awakens as a small, sentient quadruped creature of unknown origin, in an unrecognizable world.  Faced with growing hunger and dangers lurking everywhere, the small creature is forced to travel, hunt, and fight to survive.  They soon learn that if they cannot find a way to escape this dark and unforgiving world before their hunger overwhelms them, they will lose their sense of self and be forced to wander it forever.  During their journey, the player creature may acquire various essences of Life, Strength, and Magic, enabling them to enhance or acquire physical and magical stats or abilities.

Within the scope and timeline of this project, CPG is designed to be a small, single session, short playthrough game.  Beyond the scope and timeline of this project, there is room for additional development and expansion in multiple areas and facets of CPG, such as progress saving, additional world zones, NPCs, avatar abilities, avatar progression lines, etc.

3.4	Technical Features
Menu System
Main Menu			Opening menu with game title, links to other menus
Controls Menu			Displays list of controls and descriptions for each
Settings Menu			Modify player-controllable game settings
Character Menu		Displays character info, accessible during gameplay
Pause Menu			Pause during gameplay, links to other menu

Player-Controlled Character
Left Click			Physical attack
Right Click			Magical skill
[A] Key				Walk left
[D] Key				Walk right
[Space] Key			Jump
[Q] Key				Open/close Character Menu
[E] Key				Inspect nearby hovered object
[P] Key				Open/close Pause Menu
[Escape] Key			Quit Game

Non-Player Characters, AI
Recurring, hostile non-player characters are encountered throughout gameplay.
Split into three types of creatures: Land, Air, and Water
Movement pattern based on enemy type
Will attempt to physically attack the player when in range

Procedurally Generated Game World
World environment background and foreground objects, characters, and items are generated procedurally as the player moves through the game world.

Graphical User Interface, RPG System
Player character stats and skills visible during gameplay
Health			Depletes when taking damage, regenerates over time
Hunger			Increases over time, decreases with enemy deaths
Active skill(s)		Will unlock when acquiring certain Essence items
Detailed information accessible via the Character Menu
Essence items can be found throughout gameplay which:
Provide buffs to various player character traits
Unlock magical skills that enhance mobility or combat
Interacting with specific environmental objects will display insightful flavor text

3.5	Artistic Assets
Sprite Art
Playable Character		10 Sprites total across 5 different animations facing left and right
Idle 
Movement
Physical Attack 
Cast Spell
Jump 
Non-playable Character		For non-playable characters, they often have 3 sprites but some
might have only one for their appearance at the end.
Movement
Attack
Receive Attack
Menu sprite: Two frame sprite for option selection in character and pause menu.  
Acquire objects: One frame sprite for health (Heart) & Magical spell 
Game Start and Game Over<Win and Lose> sprite.

Audio		Might be downloaded from freesound.org or made with at home foley studio. 
Sound FX:
Death 
Jump 
Acquire
Cast speed 
Physical Attack 
Select an option in the character or pause menu
Music:
Game Start 
Game Over
Game Pause <This audio also use in character and pause menu>

3.6	Implementation Plan
[Part 1] Engine Changes
Resizing world view, change character default 
Change to support multiple command actions. 
Add button to support menu
[Part 2] Menu system
Code and sprite to display all the control menu options
[Part 3] Player character, movement controls
Code: 
Fly for air creature
Swim for water creature
Move, Death, Jump for main player
Attack for all
[Part 4] World GUI
Code: 
Display users stats include health, magical ability 
[Part 5] NPC Spawning, AI
Code to generate a certain number of enemy for each levels
[Part 6] Game Clear, Game Over
Change the Game Over code of the project 2 to fit the requirement. If win then play “win” sprite if “lose” play the “lose” sprite. 
[Part 7] Item Spawning, RPG System
Code to make the object disappear after colliding with the main character and update the main character stats. 

3.7	Distribution of Work

The work will be equally distributed between both members of the team. 

Title of work
Responsible
Engine change
Luna & Forrest
Game Program
Luna & Forrest 
Sprite
Luna & Forrest 
Audio
Luna & Forrest 
Final Presentation
Luna & Forrest 


3.8	Schedule

Plan: Monday, November 30th (11:59pm)
Tasks to complete before checkpoint:
Team members discuss the plan for project 3. November 30th (11:59pm)
Alpha: Saturday, December 5th (11:59pm) 
Tasks to complete before checkpoint:
Check with prof. Mark if it is possible to implement custom color. 
Complete the game engine with button functions.
Add the main character and create a platform for the character to move freely. 

Final playable: Wednesday, December 9th (11:59pm)
Promotional material: Friday, December 11th (before class)
Presentation: Friday, December 11th (in class)
