#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include "spaceship.h"
#include "rock.h"
#include "button.h"
#include "animatedsprite.h"


int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(800, 800), "Meteor Rush");
    sf::Image icon;
    sf::Clock clock;
    std::fstream hs;
    sf::Font font;
    sf::Text title;
    sf::Text score_board;
    sf::Text missile_ui;
    sf::Text gameover_text;
    sf::Text final_score;
    sf::Text highscore;
    Button start_button;
    Button quit_button;
    Button menu_button;
    Button ship_button;
    sf::Texture g_texture;
    sf::Texture b1_texture;
    sf::Texture b2_texture;
    sf::Texture b3_texture;
    sf::Texture s_texture;
    sf::Texture ss_texture;
    sf::Texture s2_texture;
    sf::Texture s3_texture;
    sf::Texture ss3_texture;
    sf::Texture s4_texture;
    sf::Texture s_e_texture;
    sf::Texture ss_e_texture;
    sf::Texture r1_texture;
    sf::Texture r2_texture;
    sf::Texture r3_texture;
    sf::Texture r4_texture;
    sf::SoundBuffer m_sound;
    sf::SoundBuffer e_sound;
    sf::SoundBuffer e2_sound;
    sf::SoundBuffer f_sound;
    sf::SoundBuffer s_sound;
    sf::SoundBuffer go_sound;
    sf::Sound soundtrack;
    sf::Sound gameover_sound;
    sf::Sprite background1;
    sf::Sprite background2;
    AnimatedSprite galaxy;
    AnimatedSprite explosion;
    AnimatedSprite shipexplosion;
    AnimatedSprite shipexplosion2;
    Rock rock1;
    Rock rock2;
    Rock rock4;
    Rock rock3;
    SpaceShip ship1;
    SpaceShip ship2;
    std::vector<sf::Sprite> background;
    std::vector<AnimatedSprite> missiles;
    std::vector<AnimatedSprite> explosions;
    std::vector<AnimatedSprite> shipexplosions;
    std::vector<Rock> rock_sample;
    std::vector<Rock> rocks;
    std::vector<SpaceShip> ships;
    std::string h_score;
    int background_id = 0;
    int score = 0;
    int game_state = 0;
    int ship_id = 0;
    float spawn_cd = 0;
    bool gameover = false;
    bool button_pressed = false;


    if (!icon.loadFromFile("rock1.png")) {
        std::cerr << "Could not load icon" << std::endl;
        return 4;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    if (!font.loadFromFile("font.ttf"))
    {
        std::cerr << "Could not load font" << std::endl;
        return 2;
    }

    title.setFont(font);
    title.setString("Meteor Rush");
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Magenta);
    title.setOutlineThickness(4);
    title.setCharacterSize(40);
    title.setPosition(sf::Vector2f(window.getSize().x/2-title.getGlobalBounds().width/2, window.getSize().y/4-title.getGlobalBounds().height/2));

    score_board.setFont(font);
    score_board.setFillColor(sf::Color::White);
    score_board.setCharacterSize(20);
    score_board.setPosition(sf::Vector2f(20, 20));

    missile_ui.setFont(font);
    missile_ui.setCharacterSize(20);
    missile_ui.setPosition(sf::Vector2f(580, 20));

    gameover_text.setFont(font);
    gameover_text.setString("Gameover!");
    gameover_text.setFillColor(sf::Color::White);
    gameover_text.setOutlineColor(sf::Color::Magenta);
    gameover_text.setOutlineThickness(4);
    gameover_text.setCharacterSize(40);
    gameover_text.setPosition(sf::Vector2f(window.getSize().x/2-gameover_text.getGlobalBounds().width/2, window.getSize().y/4-gameover_text.getGlobalBounds().height/2));

    final_score.setFont(font);
    final_score.setFillColor(sf::Color::White);
    final_score.setCharacterSize(20);
    final_score.setPosition(sf::Vector2f(window.getSize().x/2-final_score.getGlobalBounds().width/2, gameover_text.getGlobalBounds().top+gameover_text.getGlobalBounds().height-final_score.getGlobalBounds().height/2+100));

    highscore.setFont(font);
    highscore.setFillColor(sf::Color::White);
    highscore.setCharacterSize(20);
    highscore.setPosition(sf::Vector2f(window.getSize().x/2-highscore.getGlobalBounds().width/2, gameover_text.getGlobalBounds().top+gameover_text.getGlobalBounds().height-highscore.getGlobalBounds().height/2+200));

    start_button.setButtonStyle("Start Game", font, sf::Color::White, sf::Color::Black, sf::Vector2f(240, 400), 25, 2, 0);

    quit_button.setButtonStyle("Quit", font, sf::Color::White, sf::Color::Black, sf::Vector2f(240, 500), 25, 2, 1);

    menu_button.setButtonStyle("Go to Menu", font, sf::Color::White, sf::Color::Black, sf::Vector2f(240, 300), 25, 2, 3);

    ship_button.setButtonStyle("Change Ship", font, sf::Color::White, sf::Color::Black, sf::Vector2f(240, 300), 25, 2, 2);

    if (!g_texture.loadFromFile("galaxy.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    if (!b1_texture.loadFromFile("background1.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    if (!b2_texture.loadFromFile("background2.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    if (!b3_texture.loadFromFile("background4.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    if (!s_texture.loadFromFile("ship1.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    if (!ss_texture.loadFromFile("ship2.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    if (!s2_texture.loadFromFile("missile.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    if (!s3_texture.loadFromFile("flame1.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    if (!ss3_texture.loadFromFile("flame2.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    if (!s4_texture.loadFromFile("explosion.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    if (!s_e_texture.loadFromFile("shipexplosion.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    if (!ss_e_texture.loadFromFile("shipexplosion2.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    if (!r1_texture.loadFromFile("rock1.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    if (!r2_texture.loadFromFile("rock2.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    if (!r3_texture.loadFromFile("rock3.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    if (!r4_texture.loadFromFile("rock4.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    if (!m_sound.loadFromFile("shootingsound.wav")){
        std::cerr << "Could not load sound" << std::endl;
        return 3;
    }
    if (!e_sound.loadFromFile("explosionsound.wav")){
        std::cerr << "Could not load sound" << std::endl;
        return 3;
    }
    if (!e2_sound.loadFromFile("shipexplosionsound.wav")){
        std::cerr << "Could not load sound" << std::endl;
        return 3;
    }
    if (!f_sound.loadFromFile("jetsound.wav")){
        std::cerr << "Could not load sound" << std::endl;
        return 3;
    }
    if (!s_sound.loadFromFile("soundtrack.wav")){
        std::cerr << "Could not load sound" << std::endl;
        return 3;
    }
    if (!go_sound.loadFromFile("gameoversound.wav")){
        std::cerr << "Could not load sound" << std::endl;
        return 3;
    }

    soundtrack.setBuffer(s_sound);
    soundtrack.setVolume(20.f);
    soundtrack.setLoop(true);

    gameover_sound.setBuffer(go_sound);
    gameover_sound.setVolume(80.f);

    background1.setTexture(b1_texture);
    background.emplace_back(background1);
    background1.setTexture(b2_texture);
    background.emplace_back(background1);
    background2.setTexture(b3_texture);

    galaxy.setTexture(g_texture);
    for(int i = 0; i < 7500; i+=150){
        for(int j = 0; j < 7500; j+=150){
            galaxy.addAnimationFrame(sf::IntRect(i, j, 150, 150));
        }
    }
    galaxy.setTextureRect(sf::IntRect(0, 0, 150, 150));
    galaxy.setScale(3, 3);
    galaxy.setPosition(sf::Vector2f(window.getSize().x/2-galaxy.getGlobalBounds().width/2, window.getSize().y/4-galaxy.getGlobalBounds().height/2));
    galaxy.setFps(30);

    explosion.setTexture(s4_texture);
    for(int i = 0; i < 2560; i+=256){
        explosion.addAnimationFrame(sf::IntRect(i, 0, 256, 256));
    }
    explosion.setTextureRect(sf::IntRect(0, 0, 256, 256));
    explosion.setFps(15);
    explosion.setSpriteSound(e_sound, false);

    shipexplosion.setTexture(s_e_texture);
    for(int i = 0; i < 1536; i+=128){
        shipexplosion.addAnimationFrame(sf::IntRect(i, 0, 128, 128));
    }
    shipexplosion.setTextureRect(sf::IntRect(0, 0, 128, 128));
    shipexplosion.setFps(15);
    shipexplosion.setSpriteSound(e2_sound, false);
    shipexplosion.setSpriteVolume(60.0f);
    shipexplosions.emplace_back(shipexplosion);

    shipexplosion2.setTexture(ss_e_texture);
    for(int i = 0; i < 1280; i+=128){
        shipexplosion2.addAnimationFrame(sf::IntRect(i, 0, 128, 128));
    }
    shipexplosion2.setTextureRect(sf::IntRect(0, 0, 128, 128));
    shipexplosion2.setFps(15);
    shipexplosion2.setSpriteSound(e2_sound, false);
    shipexplosion2.setSpriteVolume(60.0f);
    shipexplosions.emplace_back(shipexplosion2);

    rock1.setTexture(r1_texture);
    rock_sample.emplace_back(rock1);
    rock2.setTexture(r2_texture);
    rock_sample.emplace_back(rock2);
    rock3.setTexture(r3_texture);
    rock_sample.emplace_back(rock3);
    rock4.setTexture(r4_texture);
    rock_sample.emplace_back(rock4);

    ship1.setTexture(s_texture);
    ship1.setMissileTexture(s2_texture);
    ship1.setMissileInitialFrame(sf::IntRect(0, 0, 60, 22));
    ship1.setAccelerationRate(0.03);
    for(int i = 0; i < 240; i+=60){
        ship1.addMissileFrame(sf::IntRect(i, 0, 60, 22));
    }
    ship1.setMissileFps(10);
    ship1.setMissileSound(m_sound, 40.0f);
    ship1.setFlamesTexture(s3_texture);
    for(int i = 0; i < 60; i+=20){
        ship1.addFlamesFrame(sf::IntRect(i, 0, 20, 20));
    }
    ship1.setFlamesFps(10);
    ship1.setFlamesSound(f_sound, 40.0f);
    ship1.setSpeed(200, 200);
    ship1.setRechargeTime(2);
    ship1.setPosition(sf::Vector2f(window.getSize().x*0.15, window.getSize().y/2-ship1.getGlobalBounds().height/2));
    ships.emplace_back(ship1);

    ship2.setTexture(ss_texture);
    ship2.setMissileTexture(s2_texture);
    ship2.setMissileInitialFrame(sf::IntRect(0, 0, 60, 22));
    ship2.setAccelerationRate(0.015);
    for(int i = 0; i < 240; i+=60){
        ship2.addMissileFrame(sf::IntRect(i, 0, 60, 22));
    }
    ship2.setMissileFps(10);
    ship2.setMissileSound(m_sound, 40.0f);
    ship2.setFlamesTexture(ss3_texture);
    for(int i = 0; i < 112; i+=28){
        ship2.addFlamesFrame(sf::IntRect(i, 0, 28, 12));
    }
    ship2.setFlamesFps(10);
    ship2.setFlamesSound(f_sound, 40.0f);
    ship2.setSpeed(300, 300);
    ship2.setRechargeTime(4);
    ship2.setPosition(sf::Vector2f(window.getSize().x*0.15, window.getSize().y/2-ship2.getGlobalBounds().height/2));
    ships.emplace_back(ship2);

    while (window.isOpen()) {

        sf::Event event;
        sf::Time elapsed = clock.restart();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        hs.open("score.txt", std::ios::in);
        if (!hs.is_open()) {
            std::cerr << "Could not open file" << std::endl;
            return 3;
        }
        hs >> h_score;
        hs.close();

        switch(game_state){

        case 0:

            window.draw(background2);

            start_button.click(window, game_state, score, soundtrack, ship_id, button_pressed);
            start_button.setPosition(sf::Vector2f(window.getSize().x/2-start_button.getGlobalBounds().width/2, title.getGlobalBounds().top+title.getGlobalBounds().height-start_button.getGlobalBounds().height/2+100));
            start_button.setString("Start Game");
            window.draw(start_button);

            ship_button.click(window, game_state, score, soundtrack, ship_id, button_pressed);
            ship_button.setPosition(sf::Vector2f(window.getSize().x/2-ship_button.getGlobalBounds().width/2, title.getGlobalBounds().top+title.getGlobalBounds().height-ship_button.getGlobalBounds().height/2+200));
            if(ship_id == 0){
                ship_button.setString("Change Heavy Ship");
            }
            else{
                ship_button.setString("Change Light Ship");
            }

            window.draw(ship_button);

            quit_button.click(window, game_state, score, soundtrack, ship_id, button_pressed);
            quit_button.setPosition(sf::Vector2f(window.getSize().x/2-quit_button.getGlobalBounds().width/2, title.getGlobalBounds().top+title.getGlobalBounds().height-quit_button.getGlobalBounds().height/2+300));
            window.draw(quit_button);

            background_id = rand() % background.size();

            window.draw(galaxy);
            galaxy.animate(elapsed);

            window.draw(title);

            break;

        case 1:

            window.draw(background[background_id]);


            if(!gameover){

                ships[ship_id].setBounds(0, window.getSize().x, 0, window.getSize().y);
                ships[ship_id].moveInDirection(elapsed, window);
                ships[ship_id].shot(elapsed, missiles, missile_ui);

                for(long long unsigned int it = 0; it < missiles.size(); it++){

                    missiles[it].animate(elapsed);
                    missiles[it].move(350*elapsed.asSeconds(), 0);
                    window.draw(missiles[it]);

                    if(missiles[it].getGlobalBounds().left > window.getSize().x){

                        missiles.erase(missiles.begin()+it);

                    }
                    else{

                        for(long long unsigned int it2 = 0; it2 < rocks.size(); it2++){

                            if(missiles[it].getGlobalBounds().intersects(rocks[it2].getGlobalBounds())){

                                explosion.setPosition(sf::Vector2f(rocks[it2].getGlobalBounds().left+rocks[it2].getGlobalBounds().width/2-explosion.getGlobalBounds().width/2, rocks[it2].getGlobalBounds().top+rocks[it2].getGlobalBounds().height/2-explosion.getGlobalBounds().height/2));
                                explosions.emplace_back(explosion);
                                explosions[explosions.size()-1].playSound();
                                rocks.erase(rocks.begin()+it2);
                                missiles.erase(missiles.begin()+it);
                                score+=1;

                            }

                        }

                    }

                }

                for(long long unsigned int it = 0; it < explosions.size(); it++){

                    window.draw(explosions[it]);

                    if(explosions[it].getCurrentFrameId() < explosions[it].getFramesSize()-1){
                        explosions[it].animate(elapsed);
                    }
                    else{
                        explosions.erase(explosions.begin()+it);
                    }

                }

                spawn_cd+=elapsed.asSeconds();

                if(spawn_cd >= 0.15){
                    int id = rand() % 4;
                    rock_sample[id].setPosition(sf::Vector2f(window.getSize().x, rand()%(window.getSize().y-11)));
                    rock_sample[id].setSpeed(-1*(rand()%50+100), 0, rand()%200-100);
                    rocks.emplace(rocks.begin(), rock_sample[id]);
                    spawn_cd = 0;
                }

                for(long long unsigned int it = 0; it < rocks.size(); it++){

                    rocks[it].motion(elapsed);

                    sf::FloatRect rock_bounds = rocks[it].getGlobalBounds();
                    if(ships[ship_id].getGlobalBounds().intersects(rock_bounds)){
                        soundtrack.stop();
                        gameover = true;
                        shipexplosions[ship_id].setPosition(sf::Vector2f(ships[ship_id].getGlobalBounds().left+ships[ship_id].getGlobalBounds().width/2-shipexplosions[ship_id].getGlobalBounds().width/2, ships[ship_id].getGlobalBounds().top+ships[ship_id].getGlobalBounds().height/2-shipexplosions[ship_id].getGlobalBounds().height/2));
                        shipexplosions[ship_id].playSound();
                        rocks.erase(rocks.begin(), rocks.end());
                        explosions.erase(explosions.begin(), explosions.end());
                        missiles.erase(missiles.begin(), missiles.end());
                        ships[ship_id].reset();
                        ships[ship_id].setPosition(sf::Vector2f(window.getSize().x*0.15, window.getSize().y/2-ships[ship_id].getGlobalBounds().height/2));
                        break;
                    }
                    if(rock_bounds.left+rock_bounds.width <= 0){
                        rocks.erase(rocks.begin()+it);
                        score++;
                    }

                }

                window.draw(ships[ship_id]);
                for(auto &it : rocks){
                    window.draw(it);
                }
                window.draw(missile_ui);
                score_board.setString("Score: "+std::to_string(score));
                window.draw(score_board);

            }
            else{

                window.draw(shipexplosions[ship_id]);

                if(shipexplosions[ship_id].getCurrentFrameId() < shipexplosions[ship_id].getFramesSize()-1){
                    shipexplosions[ship_id].animate(elapsed);
                }
                else{
                    shipexplosions[ship_id].setFrame(0);
                    gameover_sound.play();
                    game_state = 2;
                    gameover = false;
                }

            }

            break;

        case 2:

            window.draw(background[background_id]);
            window.draw(gameover_text);

            final_score.setPosition(sf::Vector2f(window.getSize().x/2-final_score.getGlobalBounds().width/2, gameover_text.getGlobalBounds().top+gameover_text.getGlobalBounds().height-final_score.getGlobalBounds().height/2+100));
            final_score.setString("Your score: "+std::to_string(score));
            window.draw(final_score);

            highscore.setPosition(sf::Vector2f(window.getSize().x/2-highscore.getGlobalBounds().width/2, gameover_text.getGlobalBounds().top+gameover_text.getGlobalBounds().height-highscore.getGlobalBounds().height/2+200));
            if(std::stoi(h_score) < score){
                std::cout<<"p"<<std::endl;
                hs.open("score.txt", std::ios::out);
                if (!hs.is_open()) {
                    std::cerr << "Could not open file" << std::endl;
                    return 3;
                }
                else{
                    hs << std::to_string(score);
                }
                hs.close();
            }
            highscore.setString("Highscore: "+h_score);
            window.draw(highscore);

            menu_button.click(window, game_state, score, soundtrack, ship_id, button_pressed);
            menu_button.setPosition(sf::Vector2f(window.getSize().x/2-menu_button.getGlobalBounds().width/2, gameover_text.getGlobalBounds().top+gameover_text.getGlobalBounds().height-menu_button.getGlobalBounds().height/2+300));
            window.draw(menu_button);

            start_button.click(window, game_state, score, soundtrack, ship_id, button_pressed);
            start_button.setPosition(sf::Vector2f(menu_button.getGlobalBounds().left-start_button.getGlobalBounds().width-100, gameover_text.getGlobalBounds().top+gameover_text.getGlobalBounds().height-start_button.getGlobalBounds().height/2+300));
            start_button.setString("Replay");
            window.draw(start_button);

            quit_button.click(window, game_state, score, soundtrack, ship_id, button_pressed);
            quit_button.setPosition(sf::Vector2f(menu_button.getGlobalBounds().left+menu_button.getGlobalBounds().width+100, gameover_text.getGlobalBounds().top+gameover_text.getGlobalBounds().height-quit_button.getGlobalBounds().height/2+300));
            window.draw(quit_button);

            break;
        }

        window.display();
    }

    return 0;
}
