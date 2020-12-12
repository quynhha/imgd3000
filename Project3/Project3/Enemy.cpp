/*
Enemy.cpp
*/
#include "Enemy.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventOut.h"
#include "EventView.h"
#include "Explosion.h"
#include "Points.h"
#include "Bullet.h"
#include "EnemyBlood.h"
#include "EventNuke.h"
#include "Sound.h"
#include "Saucer.h"
#include "Door.h"
#include "EventStep.h"
#include "EnemyBullet.h"
#include "EnemyMagicEvent.h"

Enemy::Enemy () {
    // Setup "enemy" sprite.
    setSprite("testenemy");

    // Set object type.
    setType("Enemy");

    // Set speed in horizontal direction.
    //setVelocity(df::Vector(0, 0)); // faster than normal saucer

    // Set starting Health.
    enemyhp = 20;
    enemymagichp = 30;
    //Set Location for enemy
    df::Vector temp_pos;
    df::Vector p((float)(rand() % (int)WM.getBoundary().getHorizontal()),
        (float)(rand() % (int)WM.getBoundary().getVertical()));
    setPosition(p);
    //WM.moveObject(this, temp_pos);
   
    //Register Nuke Events
    registerInterest(NUKE_EVENT);
    registerInterest(df::STEP_EVENT);
}

Enemy::Enemy(int blood, int sp)
{
    // Setup "enemy" sprite.
    setSprite("testenemy");

    // Set object type.
    setType("Enemy");


    // Set speed in horizontal direction.
    //setVelocity(df::Vector(0, 0)); // faster than normal saucer

    // Set starting Health.
    enemyhp = blood;
    enemymagichp = sp;


    if (enemyhp == 1)
    {
        enlv = 1;
    }
    if (enemyhp == 5)
    {
        enlv = 2;
    }
    if (enemyhp == 10)
    {
        enlv = 3;
    }
    if (enemyhp == 15)
    {
        enlv = 4;
    }
    if (enemyhp == 20)
    {
        enlv = 5;
    }

    //Set Location for enemy
    df::Vector p((float)(rand() % (int)WM.getBoundary().getHorizontal()),
        (float)(rand() % (int)WM.getBoundary().getVertical()));
    setPosition(p);

    //Register Nuke Events
    registerInterest(NUKE_EVENT);
    registerInterest(df::STEP_EVENT);
}

Enemy::~Enemy() {
    // Send "view" event with 500 points to interested ViewObjects.
    df::EventView ev(POINTS_STRING, 500, true);
    WM.onEvent(&ev);
    new Door(this->getPosition(), enlv);
}
void Enemy::fire(df::Vector target) {
    // Fire Bullet towards target.
    // Compute normalized vector to position, then scale by speed (1).
    df::Vector v = target - getPosition();
    v.normalize();
    v.scale(1);
    EnemyBullet* p = new EnemyBullet(getPosition());
    p->setVelocity(v);
    // Play "fire" sound.
    //df::Sound* p_sound = RM.getSound("fire");
    //p_sound->play();
}
// Handles events.
int Enemy::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::OUT_EVENT) {
        out();
        return 1;
    }if (p_e->getType() == df::STEP_EVENT) {
        if (dynamic_cast <const df::EventStep*> (p_e)
            ->getStepCount() % 100 == 0) {
        

        }
        return 1;
    }
    else if (p_e->getType() == df::COLLISION_EVENT) {
        // handle collisions with various other objects
        const df::EventCollision* p_collision_event =
            dynamic_cast <df::EventCollision const*> (p_e);
        hit(p_collision_event);
        return 1;
    }
    if (p_e->getType() == NUKE_EVENT) {
        // Create an explosion.
        Explosion* p_explosion = new Explosion;
        p_explosion->setPosition(this->getPosition());
        df::addParticles(df::SPARKS, getPosition(), 3, df::BLUE);
        df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);
        df::addParticles(df::SPARKS, getPosition(), 4, df::RED);
        df::addParticles(df::SPARKS, getPosition(), 1, df::RED);
        //Minus the enemy hp in ViewObject and the enemy
        enemyhp -= 10;
        df::EventView ev(ENEMY_BLOOD, -10, true);
        WM.onEvent(&ev);
    }
    return 0;
}
// Almost same with out in Sauce but do not create new Enemy
void Enemy::out() {
    if (getPosition().getX() >= 0)
        return;

    moveToStart();
    
}
void Enemy::moveToStart() {
    df::Vector temp_pos;

    float world_horiz = WM.getBoundary().getHorizontal();
    float world_vert = WM.getBoundary().getVertical();

    // x is off right side of window
    temp_pos.setX(world_horiz + rand() % (int)world_horiz + 3.0f);
    // y is in vertical range.
    temp_pos.setY(WM.getBoundary().getVertical() / 2);

    // If collision, move right slightly until empty space.
    df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
    while (!collision_list.isEmpty()) {
        temp_pos.setX(temp_pos.getX() + 1);
        collision_list = WM.getCollisions(this, temp_pos);
    }

    WM.moveObject(this, temp_pos);
}

// Removes the boss in a big explosion
void Enemy::die() {
    // Make a big explosion with particles
    df::addParticles(df::SPARKS, getPosition(), 2, df::BLUE);
    df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);
    df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
    df::addParticles(df::SPARKS, getPosition(), 3, df::RED);

    // Play explosion sound
    df::Sound* p_sound = RM.getSound("explode");
    p_sound->play();

    // Remove the Boss
    WM.markForDelete(this);
}


// Handles collisions between the Enemy and various other Objects.
void Enemy::hit(const df::EventCollision* p_c) {
    // The Boss just runs over smaller saucers, causing them to explode
    if (p_c->getObject1()->getType() == "Saucer") {
        // Explode
        Explosion* p_explosion = new Explosion;
        p_explosion->setPosition(p_c->getObject1()->getPosition());

        // Play explode sound
        df::Sound* p_sound = RM.getSound("explode");
        p_sound->play();

        WM.markForDelete(p_c->getObject1());
        

        // spawn a new saucer to replace the dead one
        new Saucer;
    }
    if (p_c->getObject2()->getType() == "Saucer") {
        // Explode
        Explosion* p_explosion = new Explosion;
        p_explosion->setPosition(p_c->getObject2()->getPosition());

        // Play explode sound
        df::Sound* p_sound = RM.getSound("explode");
        p_sound->play();

        // Delete the dead saucer
        WM.markForDelete(p_c->getObject2());
        

        // spawn a new saucer to replace the dead one
        new Saucer;
    }
    if (p_c->getObject1()->getType() == "Bullet") {
        // Make an explosion
        Explosion* p_explosion = new Explosion;
        p_explosion->setPosition(p_c->getObject1()->getPosition());

        // Play explosion sound
        df::Sound* p_sound = RM.getSound("explode");
        p_sound->play();

        enemyhp -= 1;
        df::EventView ev(ENEMY_BLOOD, -1, true);
        WM.onEvent(&ev);

        // Remove the bullet
        WM.markForDelete(p_c->getObject1());

        if (enemyhp <= 0 && enemymagichp <= 0)
            die();
    }
    if (p_c->getObject2()->getType() == "Bullet") {
        // Make an explosion
        Explosion* p_explosion = new Explosion;
        p_explosion->setPosition(p_c->getObject2()->getPosition());

        // Play explosion sound
        df::Sound* p_sound = RM.getSound("explode");
        p_sound->play();

        enemyhp -= 1;
        df::EventView ev(ENEMY_BLOOD, -1, true);
        WM.onEvent(&ev);

        // Remove the bullet
        WM.markForDelete(p_c->getObject2());

        // Kill the Boss if health is below 0
        if (enemyhp <= 0 && enemymagichp <= 0)
            die();
    }if (p_c->getObject1()->getType() == "Magic") {
        // Make an explosion
        Explosion* p_explosion = new Explosion;
        p_explosion->setPosition(p_c->getObject1()->getPosition());

        // Play explosion sound
        df::Sound* p_sound = RM.getSound("explode");
        p_sound->play();

        enemymagichp -= 3;
        df::EventView ev(ENEMY_MAGIC_BLOOD, -3, true);
        WM.onEvent(&ev);

        // Remove the bullet
        WM.markForDelete(p_c->getObject1());

        if (enemyhp <= 0 && enemymagichp <= 0)
            die();
    }
    if (p_c->getObject2()->getType() == "Magic") {
        // Make an explosion
        Explosion* p_explosion = new Explosion;
        p_explosion->setPosition(p_c->getObject2()->getPosition());

        // Play explosion sound
        df::Sound* p_sound = RM.getSound("explode");
        p_sound->play();

        enemymagichp -= 3;
        df::EventView ev(ENEMY_MAGIC_BLOOD, -3, true);
        WM.onEvent(&ev);

        // Remove the bullet
        WM.markForDelete(p_c->getObject2());

        // Kill the Boss if health is below 0
        if (enemyhp <= 0 && enemymagichp <= 0)
            die();
    }
}