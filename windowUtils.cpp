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

    int windowWidth = 1920, windowHeight = 1080;
    vector<string> macros = {"Carbohydrates",
                            "Protein",
                            "Fat",
                            "Fiber",
                            "Vitamin C"};
    map<string, pair<pair<int, int>, pair<int, int>>> clickBounds = {};
    map<string, string> buttonValues = {};
    bool buttonSelected = false;
    bool resultsGenerated = false;
    string activeButton = "";

    public:
        WindowUtils();
        WindowUtils(sf::RenderWindow &window);
        void drawBackground(sf::RenderWindow &window);
        void drawResults(sf::RenderWindow &window);
        void handleClick(sf::RenderWindow &window, sf::Event mouseEvent);
        void handleText(sf::RenderWindow &window, sf::Event mouseEvent);
        
    
    private:
        void drawPanel(sf::RenderWindow &window, float width, float height, int posX, int posY, sf::Color color);
        void drawText(sf::RenderWindow &window, string textToDisplay, int posX, int posY, int size, sf::Color color);
        void results(sf::RenderWindow &window);


};

WindowUtils::WindowUtils() {}

WindowUtils::WindowUtils(sf::RenderWindow &window)
{
    this->windowWidth = window.getSize().x;
    this->windowHeight = window.getSize().y;

    for (int i = 0; i < macros.size(); i++)
    {
        buttonValues[macros[i]] = "0";
    }
}

void WindowUtils::drawBackground(sf::RenderWindow &window)
{
    window.clear(bgColor);
    drawText(window, title, (0.05 * windowWidth), 0, 75, textColor);
    drawPanel(window, (0.4 * windowWidth), (0.85 * windowHeight),  (0.05 * windowWidth), (0.1 * windowHeight), grayPanels);
    drawPanel(window,  (0.4 * windowWidth), (0.85 * windowHeight), (0.55 * windowWidth), (0.1 * windowHeight), grayPanels);
    drawText(window, "Input desired macronutrients:", (0.05 * windowWidth), (0.1 * windowHeight), 40, textColor);
    drawText(window, "Your suggested foods:", (0.55 * windowWidth), (0.1 * windowHeight), 40, textColor);

    // draw small white panels for text entry later
    // todo: Convert buttons into custom button class
    pair<int, int> posXY = make_pair(0,0);
    pair<int, int> dimensionsXY = make_pair(0,0);
    for (int i = 0; i < 5; i++)
    {
        float offset = 0.26;
        float spacing = 0.08;
        posXY = make_pair((0.1 * windowWidth), (offset + i*(spacing)) * windowHeight);
        dimensionsXY = make_pair((0.05 * windowWidth), (0.05 * windowHeight));
        drawPanel(window, (dimensionsXY.first), (dimensionsXY.second), (posXY.first), (posXY.second), sf::Color::White);
        
        clickBounds[macros[i]] = make_pair(posXY, make_pair(posXY.first + dimensionsXY.first, posXY.second + dimensionsXY.second));

        offset = 0.265;
        string label = (i < 4) ? "g" : "%";
        posXY = make_pair((0.1 * windowWidth), (offset + i*(spacing)) * windowHeight);
        drawText(window, label, (0.155 * windowWidth), (posXY.second), 30, textColor);
        drawText(window, macros[i], (0.19 * windowWidth), (posXY.second), 30, textColor);
    }


    // Generate food button
    drawPanel(window, (0.2 * windowWidth), (0.1 * windowHeight), (0.15 * windowWidth), (0.75 * windowHeight), sf::Color::Black);
    drawText(window, "Find my food", (0.175 * windowWidth), (0.77 * windowHeight), 40, sf::Color::White);
    
    posXY = make_pair((0.15 * windowWidth), (0.75 * windowHeight));
    dimensionsXY = make_pair((0.2 * windowWidth), (0.1 * windowHeight));
    clickBounds["Generate"] = make_pair(posXY, make_pair(posXY.first + dimensionsXY.first, posXY.second + dimensionsXY.second));

    drawResults(window);

}

void WindowUtils::drawResults(sf::RenderWindow &window)
{
    for (auto i = buttonValues.begin(); i != buttonValues.end(); i++)
    {
        drawText(window, i->second, clickBounds[i->first].first.first, clickBounds[i->first].first.second, 30, sf::Color::Black);
    }

    if (resultsGenerated)
    {
        results(window);
    }
    else
    {
        drawText(window, "Click the button to find", 0.59 * windowWidth, 0.5 * windowHeight, 50, sf::Color::Black);
        drawText(window, "your food!", 0.675 * windowWidth, 0.55 * windowHeight, 50, sf::Color::Black);
    }
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
        activeButton = buttonName;
        buttonSelected = true;
        if (buttonName.compare("Generate") == 0)
        {
            
            resultsGenerated = true;
        }
    }
    else 
    {
        activeButton = "";
        buttonSelected = false;
    }
}

void WindowUtils::handleText(sf::RenderWindow &window, sf::Event event)
{
    if (buttonSelected)
    {   
        if (buttonValues.find(activeButton) == buttonValues.end())
            return;
        
        string str = buttonValues[activeButton];
        if (event.text.unicode == '\b')
        {
            if (!str.empty())
                str.erase(str.size() - 1, 1);
        }
        else if (event.text.unicode < 58 && event.text.unicode > 47)
        {
            if (str.size() < 5)
                str += static_cast<char>(event.text.unicode);
        }
        buttonValues[activeButton] = str;
    }
}

/// TODO: Change this to pull proper sorted results
void WindowUtils::results(sf::RenderWindow &window)
{
    float offset = 0.2;
    float spacing = 0.08;
    for (int i = 0; i < 9; i++)
    {
        drawPanel(window, (0.3 * windowWidth), (0.07 * windowHeight), (0.6 * windowWidth), (offset + i*(spacing)) * windowHeight, sf::Color::White);    
    }

    int count = 0;
    for (auto i = buttonValues.begin(); i != buttonValues.end(); i++)
    {
        drawText(window, i->first, (0.6 * windowWidth), ((offset + count*(spacing)) * windowHeight), 40, sf::Color::Black);
        drawText(window, i->second, (0.8 * windowWidth), ((offset + count*(spacing)) * windowHeight), 40, sf::Color::Black);
        count++;
    }
}