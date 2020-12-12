Thi Quynh Ha Nguyen (Luna Nguyen)
tnguyen5 - 2020

For the 10% extension, I added HP for the Hero and a new enemy called Enemy. 

For the HP, I added the HitPoints class to record the hitpoints for the hero.
The hero have 3 HPs for each game. If the Hero hit the Saucer, it will not kill
the hero immediately, unless the hero has died 3 times. To do this, I modify
the Saucer class and Hero class. Instead of only the Saucer class handle the collision between 
Hero and Saucer, I modify the Hero to handle collision with Saucer<Add die, function, 
and eventHandler function> and the new Enemy class. If Hero collide with Saucer, 
destroy the collided Saucer, minus the hero HP until the HP is 0 then destroy the hero. 
If Hero collides with Enemy, kill both Hero and Enemy. 

The Enemy appears after the game start for a while. It is almost the same sprite
with saucer but instead of o it has +. It is faster than normal Saucer
and has 50 HP to itself. To move, it destroys everythings in its way include Saucers and
Hero. If Enemy and Hero collided, the player loses and the game is over. If the player use nuke, 
the HP for enemy will be minus by 10 HPs. Once the Enemy is destroyed, it will explodes and adds 500
points to the total points. The Enemy blood is displayed on the Bottom Right of the screen. 

To add this gameplay element I created the custom class Enemy, EnemyBlood< which is similar to Points>, 
HitPoints <similiar to Points> and new enemy sprite.