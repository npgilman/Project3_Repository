import os
import json

smflFolder = os.getcwd() + "\\Libraries\\SFML-2.5.1"

# Generate terminal compilation commands
commands = """Generate .o and .exe file (Powershell or Git Bash):
g++ -c main.cpp -I"{}\\include" -DSFML_STATIC; g++ main.o -o main -L"{}\\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main

Clear .o and .exe file (Powershell or Git Bash):
rm main.o; rm main.exe

Run executible:
./main.exe""".format(smflFolder, smflFolder)

with open("terminalCommands.txt",'w') as file:
    file.write(commands)

# Update json properties file
with open("./.vscode/c_cpp_properties.json", "r+") as f:
    data = json.load(f)
    if (not (smflFolder + "\\include") in data["configurations"][0]['includePath']):
        data["configurations"][0]['includePath'].append(smflFolder + "\\include")
        print("Added " + smflFolder + "\\include to configurations includePath in c_cpp_properties JSON")
    
    json_object = json.dumps(data, indent=4)
    with open("./.vscode/c_cpp_properties.json", "w") as out:
        out.write(json_object)
    