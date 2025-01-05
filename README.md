# WaWMapSPExporter

**ONLY** for the CoD WaW patch *1.7.1263* (Singleplayer)\

## Features
- Map exporting
  - Might have small geometry artifacts as this is almost copy paste from cod4 (and its .map format)
- Collision rendering

## How to use
1. Download the dll
2. Launch the game
3. Inject the dll
4. Launch any map

### Exporting
1. Write /cm_mapexport into the console
2. If everything was successful, there should be a /map_source/kej/ subdirectory in your game directory

### Collision rendering
1. set cm_showCollision to something other than 0
2. use cm_showCollisionFilter (insert material name here)
   - Example: cm_showCollision 1; cm_showCollisionFilter "clip ladder"
3. Make sure you also utilize the rest of the commands with the "cm_" prefix :)

![image](https://github.com/user-attachments/assets/bee7ad74-f84f-4fcb-aa56-c1002605227d)
![image](https://github.com/user-attachments/assets/e2ad53b5-05bd-4d9f-b58a-356f9bc404dc)
