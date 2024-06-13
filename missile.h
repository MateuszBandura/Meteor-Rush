#ifndef MISSILE_H
#define MISSILE_H

#include "animatedsprite.h"
#include <SFML/Audio.hpp>

class Missile : public AnimatedSprite{

public:

    void setShootingSound(sf::SoundBuffer &sound);

    void setShootingVolume(float volume);

    void playShootingSound();

private:

    sf::Sound shooting_sound;

};

#endif // MISSILE_H
