# The Seed Engine
The Seed Engine is unfinished, we are working on this during the assigment of *Game Engine Development* for the CITM degree in Video Game Design and Development.

The Seed Engine is a game engine developed in C++ using the external libraries: 

&emsp; -&emsp;*[SDL2](https://www.libsdl.org/)*

&emsp; -&emsp;*[OpenGL](https://www.opengl.org/)* 

&emsp; -&emsp;*[ImGui](https://github.com/ocornut/imgui)*

&emsp; -&emsp;*[GLEW](https://glew.sourceforge.net/)*

&emsp; -&emsp;*[DevIL](https://openil.sourceforge.net/)*

&emsp; -&emsp;*[MathGeoLib](https://github.com/juj/MathGeoLib)*

&emsp; -&emsp;*[PhysFS](https://icculus.org/physfs/)*

***

## Guide to execute
 * Download the Engine
 * Unpack .zip
 * Execute .exe

***
## Camera Controls
- Default Mode:
  * Mouse wheel scroll = Zoom in and out.
  * Mouse wheel click = move around.
  * 'F' = focus camera to selected object.
  
- Fly Mode (mouse right click pressed):
  * Mouse movement = look around
  * 'W' = move forward
  * 'S' = move back
  * 'A' = move left
  * 'D' = move right
  * 'Q' = move up
  * 'E' = move down
  * 'LShift' = increase movement speed
  
- Focused Mode ('Alt' + mouse left click pressed):
  * Mouse movement = orbit selected object

***
## Windows
* Windows can be docked around the screen, or keep them floating.

### * Main Menu
In this part you can find multiple dropdowns: 
* *File*: you find a button to open a popUp about de engine, a button with the link to GitHub, and a button to close the engine.
* *Basic Shapes*: a list of basic game object shapes to create.
* *Windows*: you can open/close the other windows, and change the therme of the window to **"light"**, **"dark"**, **"soft dark"** and you can **"personalise"**
* *Render*: a button to render the meshes in wireframe, a button to render bounding boxes (AABB boxes, OBB boxes, Raycast ray & frustum planes) & scene camera options.

### * Header menu
* Play/Stop button: start/stop gameplay delta time.
* Pause/Unpause button: pause delta time.
* Speed button: toggle between increased game velocity (x1, x2, x4).

### * Inspector
It shows the components of the selected object, where you can change the name or disable it. 
* Transform
* Mesh
* Texture
* Camera

### * Hierarchy
* Show the list of the objects in the scene and their parents/children.
* Right click on any object to show menu.
* 'Delete' / 'Supr' to delete selected game object.
* Drag objects into another objects to reparent them.

### * Console
Don't be afraid to resize the console, the buttons risize with it.
* Print 3 types of LOG (Warning, System, Message) that can be filtered.
* Collapse button: stacks identic logs.
* Clear button: clear all stored LOGS of the console.
* File button: toggle button to see the line where the LOG is executed at.

### * Configuration
Headers with options over basic engine functionalities.
* *FPS*: Show and limitate FPS, information about frame calculation time.
* *Window*: Toggle Fullscreen, resize (or not) the windows, borderless mode, Window information.
* *Visual*: Let you activate some additional widgets of the windows: VSync, brightness, lights, dephts test, face culling, color material, textures.
* Hardware: Shows information about the hardware your PC is using.

### * Scene
* Scene objects rendering.
* Move with the scene camera (Frustum culling activated).
* Mouse pick.
* Debug lines: raycast, bounding boxes (AABB, OBB), main game camera frustum planes.

### * Game
* Only rendering necessary game objects.
* Draws from scene main camera (Frustum culling activated).

### * Assets
* Tracks project Assets folder files.
* Surf through folders (double left click to enter folders, top buttons to backup).
* Create folders.
* Drag & Drop files: they will be copied to currently open assets folder.
* Right click to open options menu: drag to scene, move to, rename, delete.
* Drag to scene: imports asset to scene.
* Move to: move file/folder through folders.
* Rename: rename files & folders (file extensions will be preserved).
* Delete: delete file/folder.
* Icons: set for folders, .png .fbx


***
## Additional features
* Mouse picking: clicking on a scene object will select it on hierarchy. If debug bounding boxes is active, the raycast line will be drawn on scene.
* Delta Time: time tracking to correctly update time-depending stats (and game delta time).

***
## How the game engine works
  * Game Objects:
    - Everything in the scene is stored in game objects, they have variable components to add to them, in order to be fully personalisable.
    - Game objects can be selected from the hierarchy window, this also makes the inspector appear.
    - Game objects have parents and childs, which makes them interactuate in different ways.
    - In the inspector, all of the selected game object components can be modified.
    - Disabling game objects in inspector prevents rendering itself plus all of its childs.
    
  * Components:
    - Transform: stores the information of the local position, rotation and scale. Global position is calculed by their parent transform.
    - Mesh: stores the meshes that are rendering every frame.
    - Texture: stores the texture rendering on the component mesh meshes, can be changed to print no texture, or to print default checkers texture.
    - Camera: stores the information of a camera Frustum, can be set to main camera in inspector to render in the Game window.
    
 * Drag to scene:
   - Any FBX or DAE can be dropped on the scene. A game object will be created with child objects that store their meshes, if the FBX has a texture, and is loaded in Assets folder, it will be loaded automatically.
   - Any PNG, DDS or TGA image can be dropped on the scene. This will be loaded as the selected game object texture (creating a Texture Component if there isn't one yet).

 * Demo scene:
   - A demo scene is loaded from the start.
   - A camera is created and set to main camera (it has a predefined script to test Play/Stop/Pause/Speed buttons).

***

## UI

- The panel UI Creator allows user to create planes with no inputs, checkboxes and buttons.
- When an UI object is selected can be dragged to the desired position or just block the option of dragging them so its position is not altered by error.
- All UI Gameobjects can have textures. Predetermined ones are: 
    - Normal UI Plane: Brown
    - CheckBox: Red when is not active and Green when it is active
    - Button: White when no inputs are recieved, Yellow when it is being pressed.
- When pressed the start button, all the created UI GameObjects created which are inside of the orthogonal frustum, will be displayed on the screen + the DEMO.

### THE DEMO:

- At the beggining it shows a UI Plane and a Button to start the game.
- Later, when the initial screen is not visible anymore, a UI plane is shown (crosshair).
- Pressing F1 after this event, enables/disables the menu of activating the VSync, which is composed of a UI Plane and a CheckBox.
- If the checkbox of the F1 menu is green, Vsync will be activated, if it is red, no.

***

### VIDEO

* Link to video: [Video]https://youtu.be/LN9ZjiUtDiw

Github adress: https://github.com/PauOlmos/REGULAR_ENGINE_fork
## Creators


- Pau Olmos

    * Github Account: [PauOlmos](https://github.com/PauOlmos)
    
    
### Template used to create the UI Editor

- Biel Rabasa
    * Github Account: [bielrabasa](https://github.com/bielrabasa)


- Roger Salas
    * Github Account: [Draquian](https://github.com/Draquian)
    
    
