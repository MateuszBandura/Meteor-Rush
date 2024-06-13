#include "rock.h"

void Rock::setSpeed(int x, int y, int rot){

    speed_x = x;
    speed_y = y;
    rotation_speed = rot;

}

void Rock::motion(const sf::Time &elapsed){

    move(speed_x*elapsed.asSeconds(), speed_y*elapsed.asSeconds());
    rotate(rotation_speed*elapsed.asSeconds());

}

