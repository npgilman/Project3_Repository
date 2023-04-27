#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include "Sorting.h"
#include "../Libraries/JSON/json.hpp"


using namespace std;
typedef chrono::high_resolution_clock Clock; 

/// @brief Utility class to edit a provided sf::RenderWindow.
/// Maintiains button functionality and values, as well as calls the appropriate functions to display suggested foods.
class WindowUtils
{
    // SFML variables
    sf::Color bgColor = sf::Color(221,208,200);
    sf::Color grayPanels = sf::Color(217,217,217);
    sf::Color textColor = sf::Color(64,64,64);

    // Other variables
    int windowWidth = 1920;
    int windowHeight = 1080;
    bool resultsGenerated = false;
    string title = "Food Finder!";
    string fontFile = "./assets/fonts/ariblk.ttf";
    vector<string> macros = {"Carbohydrates", "Protein", "Fat"};

    // Button variables
    map<string, pair<pair<int, int>, pair<int, int>>> clickBounds = {};
    map<string, string> buttonValues = {};
    bool buttonSelected = false;
    string activeButton = "";

    // Sorting variables
    Sorting sortClass;
    json suggestedFoods;
    std::chrono::_V2::system_clock::time_point t1 = Clock::now();
    double sortTime = 0;

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

/// Default constructor. Does nothing.
WindowUtils::WindowUtils() {}

/// @brief 
/// @param window The window to render to the screen
WindowUtils::WindowUtils(sf::RenderWindow &window)
{
    // Update the variables from their default values
    this->windowWidth = window.getSize().x;
    this->windowHeight = window.getSize().y;

    for (int i = 0; i < macros.size(); i++)
    {
        buttonValues[macros[i]] = "0";
    }
}

/// @brief Function to render the screen and its components
/// @param window The window to render to the screen
void WindowUtils::drawBackground(sf::RenderWindow &window)
{
    // Clear the screen and draw the basic geometry of the window
    window.clear(bgColor);
    drawText(window, title, (0.05 * windowWidth), 0, 75, textColor);
    drawPanel(window, (0.4 * windowWidth), (0.85 * windowHeight),  (0.05 * windowWidth), (0.1 * windowHeight), grayPanels);
    drawPanel(window,  (0.4 * windowWidth), (0.85 * windowHeight), (0.55 * windowWidth), (0.1 * windowHeight), grayPanels);
    drawText(window, "Input desired macronutrients:", (0.05 * windowWidth), (0.1 * windowHeight), 40, textColor);
    drawText(window, "Your suggested foods:", (0.55 * windowWidth), (0.1 * windowHeight), 40, textColor);

    // Draw 3 text boxes
    pair<int, int> posXY = make_pair(0,0);
    pair<int, int> dimensionsXY = make_pair(0,0);
    for (int i = 0; i < 3; i++)
    {
        // Variables for proper spacing of the text boxes
        float offset = 0.26;
        float spacing = 0.08;
        
        // Draw a text box and add it to the clickable areas
        posXY = make_pair((0.1 * windowWidth), (offset + i*(spacing)) * windowHeight);
        dimensionsXY = make_pair((0.05 * windowWidth), (0.05 * windowHeight));
        drawPanel(window, (dimensionsXY.first), (dimensionsXY.second), (posXY.first), (posXY.second), sf::Color::White);
        clickBounds[macros[i]] = make_pair(posXY, make_pair(posXY.first + dimensionsXY.first, posXY.second + dimensionsXY.second));


        // Generate text next to the text boxes so users know which box is which
        offset = 0.265;
        posXY = make_pair((0.1 * windowWidth), (offset + i*(spacing)) * windowHeight);
        drawText(window, "g", (0.155 * windowWidth), (posXY.second), 30, textColor);
        drawText(window, macros[i], (0.19 * windowWidth), (posXY.second), 30, textColor);
    }

    // Generate food button to use merge sort
    posXY = make_pair((0.1 * windowWidth), (0.75 * windowHeight));
    dimensionsXY = make_pair((0.125 * windowWidth), (0.1 * windowHeight));
    drawPanel(window, dimensionsXY.first, dimensionsXY.second, posXY.first, posXY.second, sf::Color::Black);
    drawText(window, "Find my food", (0.125 * windowWidth), (0.77 * windowHeight), 20, sf::Color::White);
    drawText(window, "with mergesort", (0.115 * windowWidth), (0.8 * windowHeight), 20, sf::Color::White);
    clickBounds["GenerateMerge"] = make_pair(posXY, make_pair(posXY.first + dimensionsXY.first, posXY.second + dimensionsXY.second));

    // Generate food button to use pancake sort
    posXY = make_pair((0.25 * windowWidth), (0.75 * windowHeight));
    drawPanel(window, dimensionsXY.first, dimensionsXY.second, posXY.first, posXY.second, sf::Color::Black);
    drawText(window, "Find my food", (0.275 * windowWidth), (0.77 * windowHeight), 20, sf::Color::White);
    drawText(window, "with pancakesort", (0.265 * windowWidth), (0.8 * windowHeight), 20, sf::Color::White);
    clickBounds["GeneratePancake"] = make_pair(posXY, make_pair(posXY.first + dimensionsXY.first, posXY.second + dimensionsXY.second));

    drawResults(window);
}

/// @brief Function to render the results on the right panel of the application
/// @param window The window to render to the screen
void WindowUtils::drawResults(sf::RenderWindow &window)
{
    // Update the text boxes to have their proper values
    for (auto i = buttonValues.begin(); i != buttonValues.end(); i++)
    {
        drawText(window, i->second, clickBounds[i->first].first.first, clickBounds[i->first].first.second, 30, sf::Color::Black);
    }

    // If the results haven't been generated yet, draw a default screen 
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

/// @brief Helper function for drawing a panel to the screen
/// @param window The window to render to the screen
/// @param textToDisplay String to render to the screen
/// @param posX Position along the X axis to have the top left of the text start at
/// @param posY Position along the Y axis to have the top left of the text start at
/// @param size Size of the characters
/// @param color Color of the text
void WindowUtils::drawText(sf::RenderWindow &window, string textToDisplay, int posX, int posY, int size, sf::Color color)
{
    sf::Font font;
    if (!font.loadFromFile("../assets/fonts/ariblk.ttf"))
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

/// @brief Helper function for drawing a panel to the screen
/// @param window The window to render to the screen
/// @param width Width of the panel
/// @param height Height of the panel
/// @param posX Position along the X axis to have the top left corner start at
/// @param posY Position along the Y axis to have the top left corner start at
/// @param color The color of the panel
void WindowUtils::drawPanel(sf::RenderWindow &window, float width, float height, int posX, int posY, sf::Color color)
{
    sf::RectangleShape panel(sf::Vector2f(width, height));
    panel.setFillColor(color);
    panel.setPosition(posX, posY);
    window.draw(panel);
}

/// @brief Handles click functionality depending on which button is clicked
/// @param window The window to render to the screen
/// @param event The event information
void WindowUtils::handleClick(sf::RenderWindow &window, sf::Event event)
{
    int mouseX = event.mouseButton.x;
    int mouseY = event.mouseButton.y;

    // Determine which button was clicked
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
            break;
        }
    }
    
    // If a button was clicked, change the variables appropriately.
    if (clicked)
    {
        activeButton = buttonName;
        buttonSelected = true;

        // Update the suggested foods using the user inputs and the pancacke
        if (buttonName.compare("GenerateMerge") == 0)
        {
            auto t1 = Clock::now();
            suggestedFoods = sortClass.calculateFoods(true, stof(buttonValues["Protein"]), stof(buttonValues["Carbohydrates"]), stof(buttonValues["Fat"]));
            resultsGenerated = true;
            auto t2 = Clock::now(); 
            sortTime = std::chrono::duration<double, std::milli>(t2-t1).count();
        }
        // Update the suggested foods using the user inputs and the pancake sort method
        if (buttonName.compare("GeneratePancake") == 0)
        {
            auto t1 = Clock::now();
            suggestedFoods = sortClass.calculateFoods(false, stof(buttonValues["Protein"]), stof(buttonValues["Carbohydrates"]), stof(buttonValues["Fat"]));
            resultsGenerated = true;
            auto t2 = Clock::now(); 
            sortTime = std::chrono::duration<double, std::milli>(t2-t1).count();
        }
    }
    else 
    {
        activeButton = "";
        buttonSelected = false;
    }
}

/// @brief Handles input text and updates text boxes if selected
/// @param window The window to render to the screen
/// @param event 
void WindowUtils::handleText(sf::RenderWindow &window, sf::Event event)
{
    // Only handle input text if a valid text box is entered
    if (buttonSelected)
    {   
        if (buttonValues.find(activeButton) == buttonValues.end())
            return;
        
        string str = buttonValues[activeButton];
        // Handle backspaces.
        if (event.text.unicode == '\b')
        {
            // If the string is empty, do nothing
            if (!str.empty())
                str.erase(str.size() - 1, 1);
        }
        // Handle input digits. Prevents leading zeroes and keeps it to a max of 5 digits
        else if (event.text.unicode < 58 && event.text.unicode > 47)
        {
            // Don't allow leading zeroes in the text boxes
            if (str[0] == '0')
                str = static_cast<char>(event.text.unicode);
            else if (str.size() < 5)
                str += static_cast<char>(event.text.unicode);
        }
        buttonValues[activeButton] = str;
    }
}

/// @brief Helper function to display the current suggested foods based on user input
/// @param window The window to render to the screen
void WindowUtils::results(sf::RenderWindow &window)
{
    // variables required for proper positioning of the text labels
    float offset = 0.2;
    float spacing = 0.08;

    // Display each suggested food
    for (int i = 0; i < suggestedFoods.size(); i++)
    {
        drawPanel(window, (0.4 * windowWidth), (0.1 * windowHeight), (0.55 * windowWidth), (offset + spacing*i) * windowHeight, sf::Color::White);
        drawText(window, suggestedFoods[i]["Category"], (0.6 * windowWidth), ((offset + spacing*i) * windowHeight), 40, sf::Color::Black);
    }

    // Display the time taken to sort in seconds
    string str = "Sort time: ";
    str.append(to_string(((int)(sortTime * 100)) / (1000.0 * 100)));
    drawText(window, str, (0.075 * windowWidth), (0.9 * windowHeight), 40, sf::Color::White);
}