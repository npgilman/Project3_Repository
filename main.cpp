#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include "windowUtils.cpp"

using namespace std;

int main(void)
{   
    int height = 1080, width = 1920;
    string title = "Food Finder";
    sf::RenderWindow window(sf::VideoMode(width, height), title);
    WindowUtils wutils = WindowUtils(height, width, title);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        wutils.drawBackground(window);
        window.display();
    }
    
    return 0;
}



// void drawText(sf::RenderWindow &window, string textToDisplay, int posX, int posY, int size)
// {
//     sf::Font font;
//     if (!font.loadFromFile("./assets/fonts/ariblk.ttf"))
//     {
//         // Font load error
//         std::cout << "Font load error." << std::endl;
//         return;
//     }

//     sf::Text text;
//     text.setFont(font);
//     text.setString(textToDisplay);
//     text.setCharacterSize(size);
//     text.setFillColor(sf::Color(64,64,64));
//     text.setPosition(posX, posY);
//     window.draw(text);
// }

// void drawPanel(sf::RenderWindow &window, float width, float height, int posX, int posY)
// {
//     sf::RectangleShape panel(sf::Vector2f(width, height));
//     panel.setFillColor(sf::Color(217,217,217));
//     panel.setPosition(posX, posY);
//     window.draw(panel);
// }

// void drawBackground(sf::RenderWindow &window, string title, int width, int height)
// {
//     sf::Color bgColor = sf::Color(221,208,200);
//     window.clear(bgColor);
//     drawText(window, title, (0.05 * width), 0, 40);
//     drawPanel(window, (0.4 * width), (0.4 * height), (0.05 * width), (0.15 * height));
//     drawPanel(window, (0.4 * width), (0.4 * height), (0.55 * width), (0.15 * height));
// }


// int main()
// {
//     int width = 960, height = 540;
//     string title = "Food Finder!";
//     sf::RenderWindow window(sf::VideoMode(width, height), title);
//     window.clear(sf::Color(221,208,200));

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }
//         drawBackground(window, title, width, height);
//         window.display();
//     }

//     return 0;
// }
