#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

using namespace std;

class WindowUtils
{
    // SFML variables
    sf::Color bgColor = sf::Color(221,208,200);

    // Other variables
    string title = "Food Finder!";
    string fontFile = "./assets/fonts/ariblk.ttf";
    int width = 1920, height = 1080;
    
    public:
        WindowUtils();
        WindowUtils(int width, int height, string title);
        void drawBackground(sf::RenderWindow &window);
    
    private:
        void drawText(sf::RenderWindow &window, string textToDisplay, int posX, int posY, int size);
        void drawPanel(sf::RenderWindow &window, float width, float height, int posX, int posY);
};

WindowUtils::WindowUtils() {}

WindowUtils::WindowUtils(int width, int height, string title)
{
    this->width = width;
    this->height = height;
    this->title = title;
}

void WindowUtils::drawBackground(sf::RenderWindow &window)
{
    window.clear(bgColor);
    drawText(window, title, (0.05 * width), 0, 40);
    drawPanel(window, (0.4 * width), (0.4 * height),  (0.05 * width), (0.15 * height));
    drawPanel(window,  (0.4 * width), (0.4 * height), (0.55 * width), (0.15 * height));
}

void WindowUtils::drawText(sf::RenderWindow &window, string textToDisplay, int posX, int posY, int size)
{
    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/ariblk.ttf"))
    {
        // Font load error
        std::cout << "Font load error." << std::endl;
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setString(textToDisplay);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color(64,64,64));
    text.setPosition(posX, posY);
    window.draw(text);
}

void WindowUtils::drawPanel(sf::RenderWindow &window, float width, float height, int posX, int posY)
{
    sf::RectangleShape panel(sf::Vector2f(width, height));
    panel.setFillColor(sf::Color(217,217,217));
    panel.setPosition(posX, posY);
    window.draw(panel);
}


