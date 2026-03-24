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

Loaded object:
<img width="776" height="707" alt="screen_1" src="https://github.com/user-attachments/assets/e7475c84-4bde-4705-b918-aa10e3f757e1" />
The 'Rot' & 'Th' bars in X,Y & Z sections manipulate the rotation and placement on those axises.
'Eyes' - makes distance between 2 instances change, 'Fov' - changes the field of view & 'Th' - makes lines making the shapes thicker.

The same object but with changed rotation and placement:
<img width="777" height="708" alt="screen_2" src="https://github.com/user-attachments/assets/543981e0-646b-40de-ab3a-c2d3b9351386" />

Another object but with different colors and 'distance':
<img width="778" height="708" alt="screen_3" src="https://github.com/user-attachments/assets/3529ee4c-61b7-4a6b-b45a-07b95aa87b08" />

