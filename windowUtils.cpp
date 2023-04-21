#include <SFML/Graphics.hpp>

#include <fstream>
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

    /// @brief TODO: Change to be equal to window.getSize().x/window.getSize().y 
    ///              and replace instances of window.getSize()
    int width = 1920, height = 1080;
    vector<string> macros = {"Carbohydrates",
                            "Protein",
                            "Fat",
                            "Fiber",
                            "Vitamin C"};
    map<string, pair<pair<int, int>, pair<int, int>>> clickBounds = {};

    public:
        WindowUtils();
        WindowUtils(int width, int height, string title);
        void drawBackground(sf::RenderWindow &window);
        void handleClick(sf::RenderWindow &window, sf::Event mouseEvent);
    
    private:
        void drawPanel(sf::RenderWindow &window, float width, float height, int posX, int posY, sf::Color color);
        void drawText(sf::RenderWindow &window, string textToDisplay, int posX, int posY, int size, sf::Color color);
        void generateButton(sf::RenderWindow &window);


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
    // todo: Convert buttons into custom button class
    pair<int, int> posXY = make_pair(0,0);
    pair<int, int> dimensionsXY = make_pair(0,0);
    for (int i = 0; i < 5; i++)
    {
        float offset = 0.26;
        float spacing = 0.08;
        posXY = make_pair((0.1 * window.getSize().x), (offset + i*(spacing)) * window.getSize().y);
        dimensionsXY = make_pair((0.05 * window.getSize().x), (0.05 * window.getSize().y));
        drawPanel(window, (dimensionsXY.first), (dimensionsXY.second), (posXY.first), (posXY.second), sf::Color::White);
        
        clickBounds[macros[i]] = make_pair(posXY, make_pair(posXY.first + dimensionsXY.first, posXY.second + dimensionsXY.second));

        offset = 0.265;
        string label = (i < 4) ? "g" : "%";
        posXY = make_pair((0.1 * window.getSize().x), (offset + i*(spacing)) * window.getSize().y);
        drawText(window, label, (0.155 * window.getSize().x), (posXY.second), 30, textColor);
        drawText(window, macros[i], (0.19 * window.getSize().x), (posXY.second), 30, textColor);
    }


    // Generate food button
    drawPanel(window, (0.2 * window.getSize().x), (0.1 * window.getSize().y), (0.15 * window.getSize().x), (0.75 * window.getSize().y), sf::Color::Black);
    drawText(window, "Find my food", (0.175 * window.getSize().x), (0.77 * window.getSize().y), 40, sf::Color::White);
    
    posXY = make_pair((0.15 * window.getSize().x), (0.75 * window.getSize().y));
    dimensionsXY = make_pair((0.2 * window.getSize().x), (0.1 * window.getSize().y));
    clickBounds["Generate"] = make_pair(posXY, make_pair(posXY.first + dimensionsXY.first, posXY.second + dimensionsXY.second));
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

void WindowUtils::handleClick(sf::RenderWindow &window, sf::Event event)
{
    int mouseX = event.mouseButton.x;
    int mouseY = event.mouseButton.y;

    // determine what button is clicked
    bool clicked = false;
    string buttonName;
    for (auto i = clickBounds.begin(); i != clickBounds.end(); i++)
    {
        pair<int, int> topLeft = i->second.first;
        pair<int, int> bottomRight = i->second.second;
        if (mouseX > topLeft.first && mouseX < bottomRight.first && mouseY > topLeft.second && mouseY < bottomRight.second)
        {
            clicked = true;
            buttonName = i->first;
        }
    }
    
    if (clicked)
    {
        if (buttonName.compare("Carbohydrates") == 0)
        {}
        else if (buttonName.compare("Protein") == 0)
        {}
        else if (buttonName.compare("Fat") == 0)
        {}
        else if (buttonName.compare("Fiber") == 0)
        {}
        else if (buttonName.compare("Vitamin C") == 0)
        {}
        else if (buttonName.compare("Generate") == 0)
        {generateButton(window);}
        else
        {
            // No valid button clicked
        }
    }
}

/// TODO: Change this to pull from Lester's sorted files
void WindowUtils::generateButton(sf::RenderWindow &window)
{
    for (int i = 0; i < 9; i++)
    {
        float offset = 0.2;
        drawPanel(window, (0.3 * window.getSize().x), (0.07 * window.getSize().y), (0.6 * window.getSize().x), (offset + i*(0.08)) * window.getSize().y, sf::Color::Black);    
    }
}