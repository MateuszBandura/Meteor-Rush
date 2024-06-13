#include "animatedsprite.h"

void AnimatedSprite::setBounds(int left, int right, int top, int bottom)
{
    bound_top = top;
    bound_bottom = bottom;
    bound_right = right;
    bound_left = left;
}

void AnimatedSprite::setFps(int fps_){
    fps = fps_;
}

void AnimatedSprite::animate(const sf::Time &elapsed){

    timeout+=elapsed.asSeconds();

    if(timeout >= 1.0/fps){

        if(frame >= animation_frames.size()-1){
            frame = 0;
        }
        else{
            frame++;
        }
        timeout = 0;

    }
    setTextureRect(animation_frames[frame]);

}

void AnimatedSprite::addAnimationFrame(const sf::IntRect &animation_frame){

    animation_frames.emplace_back(animation_frame);

}

void AnimatedSprite::setFrame(int frame_){

    frame = frame_;

}

int AnimatedSprite::getCurrentFrameId(){

    return frame;

}

int AnimatedSprite::getFramesSize(){

    return animation_frames.size();

}

void AnimatedSprite::setSpriteSound(sf::SoundBuffer &sound_, bool looped){

    sound.setBuffer(sound_);
    sound.setLoop(looped);

}

void AnimatedSprite::setSpriteVolume(float volume){

    sound.setVolume(volume);

}

void AnimatedSprite::playSound(){

    sound.play();

}

void AnimatedSprite::stopSound(){

    sound.stop();

}

int AnimatedSprite::soundStatus(){

    return sound.getStatus();

}
