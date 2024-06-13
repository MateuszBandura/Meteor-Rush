#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>


class AnimatedSprite : public sf::Sprite{

public:

    void setBounds(int left, int right, int top, int bottom);

    void setFps(int fps_);

    void animate(const sf::Time &elapsed);

    void addAnimationFrame(const sf::IntRect &animation_frame);

    void setFrame(int frame_);

    int getCurrentFrameId();

    int getFramesSize();

    void setSpriteSound(sf::SoundBuffer &sound_, bool looped);

    void setSpriteVolume(float volume);

    void playSound();

    void stopSound();

    int soundStatus();

private:

    std::vector<sf::IntRect> animation_frames;
    sf::Sound sound;
    unsigned long long int frame = 0;
    float timeout = 0;
    int fps = 1;
    int bound_top = 0;
    int bound_bottom = 0;
    int bound_left = 0;
    int bound_right = 0;

};

#endif // ANIMATEDSPRITE_H
