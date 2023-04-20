#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

using namespace std;

class WindowUtils
{
    // SFML variables
    sf::Color bgColor = sf::Color(221,208,200);
    sf::Color grayPanels = sf::Color(217,217,217);
    sf::Color textColor = sf::Color(64,64,64);

    // Other variables
    string title = "Food Finder!";
    string fontFile = "./assets/fonts/ariblk.ttf";
    int width = 1920, height = 1080;
    vector<string> macros = {"Carbohydrates",
                            "Protein",
                            "Fat",
                            "Fiber",
                            "Vitamin C"};

    public:
        WindowUtils();
        WindowUtils(int width, int height, string title);
        void drawBackground(sf::RenderWindow &window);
    
    private:
        void drawText(sf::RenderWindow &window, string textToDisplay, int posX, int posY, int size, sf::Color color);
        void drawPanel(sf::RenderWindow &window, float width, float height, int posX, int posY, sf::Color color);
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
    drawText(window, title, (0.05 * window.getSize().x), 0, 75, textColor);
    drawPanel(window, (0.4 * window.getSize().x), (0.85 * window.getSize().y),  (0.05 * window.getSize().x), (0.1 * window.getSize().y), grayPanels);
    drawPanel(window,  (0.4 * window.getSize().x), (0.85 * window.getSize().y), (0.55 * window.getSize().x), (0.1 * window.getSize().y), grayPanels);
    drawText(window, "Input desired macronutrients:", (0.05 * window.getSize().x), (0.1 * window.getSize().y), 40, textColor);
    drawText(window, "Your suggested foods:", (0.55 * window.getSize().x), (0.1 * window.getSize().y), 40, textColor);

    // draw small white panels for text entry later
    for (int i = 0; i < 5; i++)
    {
        float offset = 0.26;
        float spacing = 0.08;
        drawPanel(window, (0.05 * window.getSize().x), (0.05 * window.getSize().y), (0.1 * window.getSize().x), ((offset + i*(spacing)) * window.getSize().y), sf::Color::White);
        
        offset = 0.265;
        string label = (i < 4) ? "g" : "%";
        drawText(window, label, (0.155 * window.getSize().x), ((offset + i*(spacing)) * window.getSize().y), 30, textColor);
        drawText(window, macros[i], (0.19 * window.getSize().x), ((offset + i*(spacing)) * window.getSize().y), 30, textColor);
    }

    // Generate food button
    drawPanel(window, (0.2 * window.getSize().x), (0.1 * window.getSize().y), (0.15 * window.getSize().x), (0.75 * window.getSize().y), sf::Color::Black);
    drawText(window, "Find my food", (0.175 * window.getSize().x), (0.77 * window.getSize().y), 40, sf::Color::White);
}

void WindowUtils::drawText(sf::RenderWindow &window, string textToDisplay, int posX, int posY, int size, sf::Color color)
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
    text.setFillColor(color);
    text.setPosition(posX, posY);
    window.draw(text);
}

void WindowUtils::drawPanel(sf::RenderWindow &window, float width, float height, int posX, int posY, sf::Color color)
{
    sf::RectangleShape panel(sf::Vector2f(width, height));
    panel.setFillColor(color);
    panel.setPosition(posX, posY);
    window.draw(panel);
}


