#include "missile.h"


void Missile::setShootingSound(sf::SoundBuffer &sound){

    shooting_sound.setBuffer(sound);

}

void Missile::setShootingVolume(float volume){

    shooting_sound.setVolume(volume);

}

void Missile::playShootingSound(){

    shooting_sound.play();

}

