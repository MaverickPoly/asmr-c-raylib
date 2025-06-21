#ifndef CONFIG_H
#define CONFIG_H

#include "rocket/rocket.h"
#include "laser/laser.h"
#include "meteor/meteor.h"

// Window
#define WIDTH 1700
#define HEIGHT 1000
#define STARS_NUM 40
#define STAR_SIZE 50

// Rocket
#define ROCKET_W 112
#define ROCKET_H 75
#define ROCKET_SPEED 800
#define SHOOT_RELOAD 0.2

// Laser
#define LASER_W 9
#define LASER_H 54
#define LASER_SPEED 800

// Meteor
#define METEOR_W 101
#define METEOR_H 84
#define METEOR_SPAWN_TIME 0.5

#endif //CONFIG_H
