#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "display.h"


void show_off_graphic_skills(void)
{
    const sf::Color figure_fill(101, 128, 216);
    const sf::Color text_fill(9, 9, 86);

    sf::RenderWindow window(
                    sf::VideoMode(640, 480),
                    "HACKS",
                    sf::Style::Titlebar | sf::Style::Close);
    sf::Font font;
    font.loadFromFile("assets/LobsterTwo-BoldItalic.ttf");
    sf::Music music;
    music.openFromFile("assets/music.wav");
    music.setLoop(true);

    window.setPosition(sf::Vector2i(700, 300));
    
    sf::CircleShape pentagon(200.0f, 5);
    pentagon.setFillColor(figure_fill);
    pentagon.setOrigin(200, 200);
    pentagon.setPosition(320, 240);

    sf::Text text;
    text.setFont(font);
    text.setFillColor(text_fill);
    text.setString("You have been hacked...");

    sf::FloatRect txt_bounds = text.getGlobalBounds();
    text.setOrigin(txt_bounds.width/2, txt_bounds.height/2);
    text.setPosition(320, 240);

    sf::Clock clock;
    const float angular_speed  = 2*360/5.f; // deg/s
    const float blink_interval = 0.3f;      // s

    float seconds = 0;
    bool is_fill_red = true;

    sf::Color fill = sf::Color::Red;

    music.play();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time time_delta = clock.restart();
        pentagon.rotate(angular_speed * time_delta.asSeconds());
        seconds += time_delta.asSeconds();
        if (seconds >= blink_interval)
        {
            seconds -= blink_interval;
            if (is_fill_red) fill = sf::Color::White;
            else             fill = sf::Color::Red;
            is_fill_red = !is_fill_red;
        }

        window.clear(fill);

        window.draw(pentagon);
        window.draw(text);

        window.display();
    }
    music.stop();
    
    return;
}
