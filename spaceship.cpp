#include "spaceship.h"

void SpaceShip::setBounds(int left, int right, int top, int bottom)
{
    bound_top = top;
    bound_bottom = bottom;
    bound_right = right;
    bound_left = left;
}

void SpaceShip::setSpeed(int speed_x, int speed_y)
{
    max_speed_x = speed_x;
    max_speed_y = speed_y;
}

void SpaceShip::setRechargeTime(float rtime){
    recharge_time = rtime;
    cooldown = rtime;
}

void SpaceShip::setAccelerationRate(float ar){
    acceleration_rate = ar;
}

void SpaceShip::setMissileTexture(sf::Texture &tex)
{
    missile.setTexture(tex);
}

void SpaceShip::setMissileInitialFrame(const sf::IntRect &animation_frame){

    missile.setTextureRect(animation_frame);
}

void SpaceShip::addMissileFrame(const sf::IntRect &animation_frame)
{
    missile.addAnimationFrame(animation_frame);
}

void SpaceShip::setMissileSound(sf::SoundBuffer &sound, float volume){
    missile.setSpriteSound(sound, false);
    missile.setSpriteVolume(volume);
}

void SpaceShip::setMissileFps(int fps){
    missile.setFps(fps);
}

void SpaceShip::setFlamesTexture(sf::Texture &tex)
{
    flames.setTexture(tex);
}

void SpaceShip::addFlamesFrame(const sf::IntRect &animation_frame)
{
    flames.addAnimationFrame(animation_frame);
}

void SpaceShip::setFlamesFps(int fps){
    flames.setFps(fps);
}

void SpaceShip::setFlamesSound(sf::SoundBuffer &sound, float volume){
    flames.setSpriteSound(sound, true);
    flames.setSpriteVolume(volume);
}

void SpaceShip::moveInDirection(const sf::Time &elapsed, sf::RenderWindow &window){

    sf::FloatRect ship_bounds = getGlobalBounds();


    flames.setPosition(sf::Vector2f(ship_bounds.left-flames.getGlobalBounds().width, ship_bounds.top+ship_bounds.height/2-flames.getGlobalBounds().height/2));
    flames.animate(elapsed);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && ship_bounds.top >= bound_top)
    {
        acceleration_y += elapsed.asSeconds();
        if(acceleration_y >= acceleration_rate){
            if(speed_y > -1*max_speed_y){
                speed_y-=10;
            }
            acceleration_y = 0;
        }
        if(!(speed_y > 0 && ship_bounds.top+ship_bounds.height >= bound_bottom)){
            move(0, speed_y*elapsed.asSeconds());
        }

    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && ship_bounds.top+ship_bounds.height <= bound_bottom)
    {
        acceleration_y += elapsed.asSeconds();
        if(acceleration_y >= acceleration_rate){
            if(speed_y < max_speed_y){
                speed_y+=10;
            }
            acceleration_y = 0;
        }
        if(!(speed_y < 0 && ship_bounds.top <= bound_top)){
            move(0, speed_y*elapsed.asSeconds());
        }

    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && ship_bounds.left > bound_left)
    {
        acceleration_x += elapsed.asSeconds();
        if(acceleration_x >= acceleration_rate){
            if(speed_x > -1*max_speed_x){
                speed_x-=10;
            }
            acceleration_x = 0;
        }
        if(!(speed_x > 0 && ship_bounds.left+ship_bounds.width >= bound_right)){
            move(speed_x*elapsed.asSeconds(), 0);
        }

    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && ship_bounds.left+ship_bounds.width < bound_right)
    {
        acceleration_x += elapsed.asSeconds();
        if(acceleration_x >= acceleration_rate){
            if(speed_x < max_speed_x){
                speed_x+=10;
            }
            acceleration_x = 0;
        }
        if(!(speed_x < 0 && ship_bounds.left <= bound_left)){
            move(speed_x*elapsed.asSeconds(), 0);
        }

    }

    if((!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && (speed_y > 0 || speed_y < 0) ){
        acceleration_y += elapsed.asSeconds();
        if(acceleration_y >= acceleration_rate){
            if(speed_y > 0){
                speed_y-=10;
            }
            else if(speed_y < 0){
                speed_y+=10;
            }

            acceleration_y = 0;
        }
        if((!(ship_bounds.top+ship_bounds.height < bound_bottom) && speed_y > 0) || (!(ship_bounds.top > bound_top) && speed_y < 0)){
            speed_y=0;
        }
        move(0, speed_y*elapsed.asSeconds());
    }
    if((!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (speed_x > 0 || speed_x < 0)){
        acceleration_x += elapsed.asSeconds();
        if(acceleration_x >= acceleration_rate){
            if(speed_x > 0){
                speed_x-=10;
            }
            else if(speed_x < 0){
                speed_x+=10;
            }
            acceleration_x = 0;
        }
        if((!(ship_bounds.left+ship_bounds.width < bound_right) && speed_x > 0) || (!(ship_bounds.left > bound_left) && speed_x < 0)){
            speed_x=0;
        }
        move(speed_x*elapsed.asSeconds(), 0);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){

        window.draw(flames);

        if(!(flames.soundStatus() == 2)){
            flames.playSound();
        }

    }
    else if(!(flames.soundStatus() == 0)){

        flames.stopSound();

    }

}

void SpaceShip::shot(const sf::Time &elapsed, std::vector<AnimatedSprite> &missiles, sf::Text &missile_ui){

    sf::FloatRect ship_bounds = getGlobalBounds();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && cooldown >= recharge_time){

        missile.setPosition(sf::Vector2f(ship_bounds.left+ship_bounds.width*0.7, ship_bounds.top+ship_bounds.height/2-missile.getGlobalBounds().height/2));
        missiles.emplace_back(missile);
        missiles[missiles.size()-1].playSound();
        cooldown = 0;

    }

    if(cooldown < recharge_time){

        cooldown+=elapsed.asSeconds();
        missile_ui.setString("Recharging...");
        missile_ui.setFillColor(sf::Color::Red);

    }
    else{

        missile_ui.setString("Missile Ready!");
        missile_ui.setFillColor(sf::Color::Green);

    }

}


void SpaceShip::reset(){

    speed_x = 0;
    speed_y = 0;
    acceleration_y = 0;
    acceleration_x = 0;
    cooldown = recharge_time;
    flames.stopSound();

}
