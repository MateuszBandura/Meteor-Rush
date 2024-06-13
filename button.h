#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Button : public sf::Text{

public:

    void setButtonStyle(std::string text, sf::Font &font, const sf::Color &text_color, const sf::Color &outline_color, const sf::Vector2f &position, int size, int thickness, int id);

    void click(sf::RenderWindow &window, int &game_state, int &score, sf::Sound &soundtrack, int &ship_id);

private:

    int action_id;
    bool pressed = false;

    void startGame(int &game_state, int &score, sf::Sound &soundtrack);
    void quitGame(sf::RenderWindow &window);
    void changeShip(int &ship_id);
    void goToMenu(int &game_state);

};

#endif // BUTTON_H
