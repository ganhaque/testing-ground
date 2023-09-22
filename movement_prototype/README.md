# Movement Prototype 1

Here's some details to help you navigate the code:
- You can add terrain/obstacle by doing `grid[some_x][some_y] = 1`. `0` mean walk-able (default)
- I smoothed out the player movement and created switch statement to detect user input (the IsKeyDown is used to detect if a key is pushed AND hold down)
- I added save and load JSON using the library "nlohmann/json" (don't worry, it's included so you don't have to do wacky stuffs to get it to work)
- The save location is `movement_prototype/save`
- The Sprite2D, StringParser, and Tile are not used in anything (commented out or removed).
- loadRoom and the out of bound check is not used. You can try to make it work by un-comment out the code inside the out of bound check.

