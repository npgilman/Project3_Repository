# Project3_Repository
Food Finder: Helping people quickly identify the necessary foods that can meet their desired macronutrient needs.

There are many people in America and around the world who struggle with having healthy, balanced diets that meet their ideal macronutrient proportions. A large reason for this is because it can often be overwhelming for people to analyze and carefully pick the foods that they need to eat. Our program can solve this problem by streamlining this process of selecting nutritious foods to eat.

Users will enter their desired macronutrient amounts into the program. The program will then find the shortest, optimal combination of foods that meet these macronutrient amounts by sorting through macronutrient data from a food dataset. We know that we have solved the problem if we are able to identify a number of foods that meet the user’s specific nutritional goals. Our goal is to find the least number of foods that a person needs to eat to meet this goal.

We will be using the Food JSON dataset from the CORGIS Dataset Project, which has about 266,000 data points: https://corgis-edu.github.io/corgis/json/food/

# Workspace Setup
1. If .vscode/c_cpp_properties.json exists, delete it and hit CTRL SHIFT + P. Type "C/C++: Edit Configurations (JSON). It should generate a new c_cpp_properties.json file.
1. Run setup.py to generate a terminal command text file specific to your computer and add your SFML folder to the c_cpp_properties files.
2. Copy the terminal command from the terminalCommands.txt file when you want to build an executible
3. Run the executible to see the current state of the project