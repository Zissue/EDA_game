# Moria 1.1

Moria 1.1 is a turn-based strategy game where players control units on a grid. The game features different unit types such as Dwarves, Wizards, Orcs, and Trolls. The game board also includes elements like Treasures, Rocks, and Abysses.

## Gameplay

The game is played in rounds. Players issue commands to their units to move, attack, or perform other actions. The primary goal is to strategically manage your units to outmaneuver opponents, control territory, and accumulate score. Specific objectives may vary depending on the game mode or map.

## How to Play

### Compilation
The project uses a `Makefile` for compilation. To build the game, navigate to the project's root directory and run the `make` command:
```bash
make
```
This will generate the main executable, typically named `Game`.

### Running the Game
Once compiled, you can run the game from the command line.
```bash
./Game <player1_AI> <player2_AI> ... [options]
```
Replace `<player1_AI>`, `<player2_AI>`, etc., with the names of the AI implementations you want to use (e.g., `Demo`, `Null`). The game supports a variable number of players.

Available AI implementations can be found as C++ files starting with `AI` (e.g., `AIDemo.cc`, `AINull.cc`). The name to use is the filename without the `AI` prefix and `.cc` suffix (e.g., `Demo` for `AIDemo.cc`).

Common options might include:
- `-s <seed>`: To specify a seed for the random number generator.
- `-i <input_file.cnf>`: To load a specific game configuration.
- `-o <output_file>`: To redirect game output.

Refer to the game's help or specific documentation (if available) for a full list of command-line arguments.

### Viewer
The project includes a game viewer located in the `Viewer/` directory.
To use the viewer:
1. Run a game and save the output to a file. For example:
   ```bash
   ./Game Demo Demo Demo Demo -s 1 -o game_output.txt
   ```
2. Open the `Viewer/viewer.html` file in a web browser.
3. Load the `game_output.txt` file using the viewer's interface to visualize the game.
The `Viewer/viewer.sh` script might provide an alternative way to launch the viewer or serve the output.

## For Developers

### Creating a New AI
To create a custom AI for the game:
1.  **Inherit from `Player`**: Create a new C++ class that inherits from the abstract `Player` class (defined in `Player.hh`).
2.  **Implement `play()`**: Override the virtual `play()` method. This method will contain your AI's logic for deciding moves each turn. Inside this method, you can use functions provided by the `Info` and `Action` base classes to get game state information and issue commands.
3.  **Register your AI**: Use the `Registry` mechanism to make your AI available to the game. This typically involves adding a line in a file like `Registry.cc` or a similar central registration point, associating a name (string) with your new AI class.
    ```cpp
    // Example (conceptual, check actual implementation in Registry.cc):
    // In your AI's .cc file or a dedicated registration file:
    // static RegisterPlayer<MyNewAI> register_my_new_ai("MyNewAIName");
    ```
4.  **Compile**: Add your new AI's source files to the `Makefile` and recompile the project.

Refer to `AIDemo.cc` and `AINull.cc` as examples of simple AI implementations. The `Player.hh`, `Info.hh`, and `Action.hh` files are crucial for understanding the available API for AI development.

## Project Structure

Key files and directories in the Moria 1.1 project:

-   **`Game.hh`, `Game.cc`**: Contains the main game logic and orchestrates game flow.
-   **`Board.hh`, `Board.cc`**: Defines the game board, its elements, and rules for unit interaction and board state changes.
-   **`Player.hh`, `Player.cc`**: Defines the abstract base class for players (both human and AI). AI implementations inherit from this.
-   **`Settings.hh`, `Settings.cc`**: Contains game settings and constants (e.g., unit health, damage, board dimensions).
-   **`Action.hh`, `Action.cc`**: Defines actions that units can perform.
-   **`Info.hh`, `Info.cc`**: Provides access to game state information for players.
-   **`Structs.hh`, `Structs.cc`**: Contains basic data structures used throughout the game (e.g., `Pos`, `Unit`).
-   **`AI*.cc`**: Various AI implementations (e.g., `AIDemo.cc`, `AIF1.cc`). Each file typically defines an AI player.
-   **`Registry.hh`, `Registry.cc`**: Handles the registration of AI players so they can be selected at runtime.
-   **`Main.cc`**: Contains the `main` function, parses command-line arguments, and starts the game.
-   **`Viewer/`**: Directory containing the web-based game visualizer.
    -   `Viewer/viewer.html`: The main HTML file for the viewer.
    -   `Viewer/viewer.js`: JavaScript code for the viewer's functionality.
-   **`Makefile`**: The build script for compiling the project.
-   **`api.pdf`**: (If this file contains relevant API documentation, otherwise it can be omitted or described based on its actual content). Potentially contains detailed API documentation for game development.
-   **`default.cnf`**: A default configuration file for the game.

This list is not exhaustive but highlights the most important components of the project.
