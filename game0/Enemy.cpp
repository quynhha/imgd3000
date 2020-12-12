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
#include "EnemyBlood.h"
#include "EventNuke.h"
#include "Sound.h"
#include "Saucer.h"

Enemy::Enemy () {
    // Setup "enemy" sprite.
    setSprite("enemy");

    // Set object type.
    setType("Enemy");

    // Set speed in horizontal direction.
    setVelocity(df::Vector(-0.5, 0)); // faster than normal saucer

    // Set starting Health.
    enemyhp = 50;
    
    //Set Location for enemy
    df::Vector temp_pos;
    temp_pos.setX(WM.getBoundary().getVertical() * 20.0f);
    temp_pos.setY(rand() % (int)(WM.getBoundary().getVertical() - 4) + 3.0f);
    WM.moveObject(this, temp_pos);
   
    //Register Nuke Events
    registerInterest(NUKE_EVENT);
}

Enemy::~Enemy() {
    // Send "view" event with 500 points to interested ViewObjects.
    df::EventView ev(POINTS_STRING, 500, true);
    WM.onEvent(&ev);
}

// Handles events.
int Enemy::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::OUT_EVENT) {
        out();
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
    temp_pos.setY(rand() % (int)(world_vert - 4) + 4.0f);

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

        if (enemyhp <= 0)
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
        if (enemyhp <= 0)
            die();
    }
}