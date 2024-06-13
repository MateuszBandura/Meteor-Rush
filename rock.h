#ifndef ROCK_H
#define ROCK_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Rock : public sf::Sprite{

public:

    void setSpeed(int x, int y, int rot);

    void motion(const sf::Time &elapsed);

private:

    int rotation_speed;
    int speed_x;
    int speed_y;

};

#endif // ROCK_H
