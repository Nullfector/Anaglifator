### Anaglifator

**Anaglifator** is a simple program designed to visualize a 3D object from inserted data and make simple modifications to it: moving, rescaling & rotating. The shapes are visualized in a style of an anaglyph. 
This program was written using wxWidgets library.

---

## How to run it:
The best option for running the program is with Visual Studio 2022 as a project, tough there is a .exe file in this repo that should open this app without problems.
Its location is: **out/build/x64-Debug**

The files this program requires must have a specyfic structure:
1. The first line of the file has to be a number of edges the object has. This number must be above 0 and no more than 500.
2. Each of the next lines must start with a '1' and have 6 values separated with a space: the first 3 are the x,y & z coordinates for the fisrt node, and latter 3 are x,y&z coordinates of the second node.
3. Any additional tekst appearing after the 6th value will be ignored.
4. The number of lines must be equal to the value in the first line.

There are some sample files that showcase how it should look: hehe.txt, wsad.txt & test_450.txt

---
## Screenshots showcasing how the program looks:

