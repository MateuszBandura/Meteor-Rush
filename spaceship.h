#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "animatedsprite.h"

class SpaceShip : public sf::Sprite{

public:

    void setBounds(int left, int right, int top, int bottom);

    void setSpeed(int speed_x, int speed_y);

    void setRechargeTime(float rtime);

    void setAccelerationRate(float ar);

    void setMissileTexture(sf::Texture &tex);

    void setMissileInitialFrame(const sf::IntRect &animation_frame);

    void addMissileFrame(const sf::IntRect &animation_frame);

    void setMissileSound(sf::SoundBuffer &sound, float volume);

    void setMissileFps(int fps);

    void setFlamesTexture(sf::Texture &tex);

    void addFlamesFrame(const sf::IntRect &animation_frame);

    void setFlamesFps(int fps);

    void setFlamesSound(sf::SoundBuffer &sound, float volume);

    void moveInDirection(const sf::Time &elapsed, sf::RenderWindow &window);

    void shot(const sf::Time &elapsed, std::vector<AnimatedSprite> &missiles, sf::Text &missile_ui);

    void reset();

private:

    int speed_x = 0;
    int speed_y = 0;
    int max_speed_y = 0;
    int max_speed_x = 0;
    float acceleration_y = 0;
    float acceleration_x = 0;
    float acceleration_rate = 0;
    int bound_top = 0;
    int bound_bottom = 0;
    int bound_left = 0;
    int bound_right = 0;
    float cooldown = 1;
    float recharge_time = 1;
    AnimatedSprite missile;
    AnimatedSprite flames;

};

#endif // SPACESHIP_H
