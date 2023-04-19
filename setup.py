import os
smflFolder = os.getcwd() + "Libraries\\SFML-2.5.1"

commands = """Generate .o and .exe file (Powershell or Git Bash):
g++ -c main.cpp -I"{}\\include" -DSFML_STATIC; g++ main.o -o main -L"{}\\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main

Clear .o and .exe file (Powershell or Git Bash):
rm main.o; rm main.exe""".format(smflFolder, smflFolder)

with open("terminalCommands.txt",'w') as file:
    file.write(commands)

# c_cpp_prop_JSON = """{
#     "configurations": [
#         {
#             "name": "Win32",
#             "includePath": [
#                 "${workspaceFolder}/**",
#                 "${workspaceFolder}/Libraries/SFML-2.5.1/include",
#                 "{}\\include"
#             ],
#             "defines": [
#                 "_DEBUG",
#                 "UNICODE",
#                 "_UNICODE"
#             ],
#             "compilerPath": "C:\\msys64\\mingw64\\bin\\gcc.exe",
#             "cStandard": "c17",
#             "cppStandard": "gnu++17",
#             "intelliSenseMode": "windows-gcc-x64"
#         }
#     ],
#     "version": 4
# }""".format(smflFolder,smflFolder,smflFolder)

# with open("c_cpp_properties.json",'w') as file:
#     file.write(c_cpp_prop_JSON)