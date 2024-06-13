#include "button.h"

void Button::setButtonStyle(std::string text, sf::Font &font, const sf::Color &text_color, const sf::Color &outline_color, const sf::Vector2f &position, int size, int thickness, int id){
    setString(text);
    setFont(font);
    setFillColor(text_color);
    setOutlineColor(outline_color);
    setPosition(position);
    setCharacterSize(size);
    setOutlineThickness(thickness);
    action_id = id;
}

void Button::click(sf::RenderWindow &window, int &game_state, int &score, sf::Sound &soundtrack, int &ship_id){

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !pressed){
        sf::FloatRect button_bounds = getGlobalBounds();
        if(sf::Mouse::getPosition(window).x >= button_bounds.left &&
            sf::Mouse::getPosition(window).x <= button_bounds.left+button_bounds.width &&
            sf::Mouse::getPosition(window).y >= button_bounds.top &&
            sf::Mouse::getPosition(window).y <= button_bounds.top+button_bounds.height){

            pressed = true;

            switch(action_id){

            case 0:

                startGame(game_state, score, soundtrack);

                break;

            case 1:

                quitGame(window);

                break;

            case 2:

                changeShip(ship_id);

                break;

            case 3:

                goToMenu(game_state);

                break;

            default:

                break;
            }
        }
    }

    if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) && pressed){
        pressed = false;
    }
}

void Button::startGame(int &game_state, int &score, sf::Sound &soundtrack){
    game_state = 1;
    score = 0;
    soundtrack.play();
}

void Button::quitGame(sf::RenderWindow &window){
    window.close();
}

void Button::changeShip(int &ship_id){
    if(ship_id == 0){
        ship_id = 1;
    }
    else{
        ship_id = 0;
    }
}

void Button::goToMenu(int &game_state){
    game_state = 0;
}

