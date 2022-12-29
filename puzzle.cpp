#include <string>
#include <cstdlib>
#include <vector>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

// Declare the SDL2 objects
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Rect rect;

// Save a global varible representing the empty tile
int emptyPos = 0;

// Declare consts
const int SCREEN_WIDTH = 680;
const int SCREEN_HEIGHT = 680;
// Number of rows and columns for the puzzle
int ROWS = 4;
int COLS = 4;

// Game puzzle
vector<int> puzzle;

// Initializes the puzzle by shuffling the numbers
void initPuzzle()
{
  // A vector to keep track of which numbers have been generated
  vector<bool> used(16, false);
  // Clear the puzzle
  while (puzzle.size() != 0)
    puzzle.pop_back();

  // Generate a seed
  srand(time(0));

  // Generate a random number between 0 and 15, insert it into the puzzle,
  // and mark it as used
  for (int i = 0; i < 16; i++)
  {
    int num = rand() % 16;
    while (used[num])
      num = rand() % 16;
    if (num == 0)
      emptyPos = num;
    used[num] = true;
    puzzle.push_back(num);
  }
}

// Returns true if the puzzle is solved, false otherwise
bool isSolved()
{
  // Set last to 0
  int last = 0;
  // Loop through the puzzle
  for (int i = 0; i < ROWS * COLS; i++)
  {
    // If the element is not 0
    if (puzzle[i] != 0)
    {
      // If the element is not one more than last, return false
      if (puzzle[i] != ++last)
        return false;
    }
  }
  // Return true if all elements are in order
  return true;
}

// Draw the puzzle onto the window
void displayPuzzle()
{
  // Clear the window
  SDL_RenderClear(renderer);
  // Set the draw color for the renderer
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  // Clear the window
  SDL_RenderClear(renderer);

  // Set the font and font size
  TTF_Font *font = TTF_OpenFont("font.ttf", 300);
  // Set the text color
  SDL_Color color = {255, 255, 255};

  // Loop through the puzzle and draw each element
  for (int i = 0; i < ROWS * COLS; i++)
  {
    // Create a rectangle to draw the element in
    rect.x = (i % COLS) * SCREEN_WIDTH / COLS;
    rect.y = (i / COLS) * SCREEN_HEIGHT / ROWS;
    rect.w = SCREEN_WIDTH / COLS;
    rect.h = SCREEN_HEIGHT / ROWS;

    // Draw a white border around the tile
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);

    // If the tile is not the empty tile
    if (puzzle[i] != 0)
    {
      // Convert the element to a string
      string element = to_string(puzzle[i]);

      // Render the element as a texture
      SDL_Surface *surface = TTF_RenderText_Solid(font, element.c_str(), color);
      SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

      // Draw the texture onto the window
      SDL_RenderCopy(renderer, texture, NULL, &rect);

      // Free the surface and texture
      SDL_FreeSurface(surface);
      SDL_DestroyTexture(texture);
    }
    else
    {
      // Render a white square
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      SDL_RenderFillRect(renderer, &rect);
      SDL_RenderPresent(renderer);
    }
  }
  // Update the window to show the puzzle
  SDL_RenderPresent(renderer);
  // Close the font
  TTF_CloseFont(font);
}

// Display that the game has been one
void displayWin()
{
  // Clear the window
  SDL_RenderClear(renderer);

  // Create a rectangle for the background
  rect.x = SCREEN_WIDTH;
  rect.y = SCREEN_HEIGHT;
  rect.w = 0;
  rect.h = 0;

  // Draw a black background
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer, &rect);

  // Set the font and font size
  TTF_Font *font = TTF_OpenFont("font.ttf", 100);
  // Set the text color
  SDL_Color color = {255, 255, 255};

  // Convert the message to a string
  string message = "You Win!";

  // Render the message as a texture
  SDL_Surface *surface = TTF_RenderText_Solid(font, message.c_str(), color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

  // Get the dimensions of the message
  int w, h;
  TTF_SizeText(font, message.c_str(), &w, &h);

  // Calculate the x and y positions for the message
  int x = (SCREEN_WIDTH - w) / 2;
  int y = (SCREEN_HEIGHT - h) / 2;

  // Create a rectangle to draw the message in
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;

  // Draw the message onto the window
  SDL_RenderCopy(renderer, texture, NULL, &rect);

  // Free the surface and texture
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);

  // Update the window
  SDL_RenderPresent(renderer);
  // Clean up the font
  TTF_CloseFont(font);
}

// Display a pause menu
void displayPause()
{
  // Clear the window
  SDL_RenderClear(renderer);

  // Create a rectangle for the background
  rect.x = 0;
  rect.y = 0;
  rect.w = SCREEN_WIDTH;
  rect.h = SCREEN_HEIGHT;

  // Draw a white background
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &rect);

  // Set the font and font size
  TTF_Font *font = TTF_OpenFont("font.ttf", 100);
  // Set the text color
  SDL_Color color = {0, 0, 0};

  // Convert the message to a string
  string message = "Press space to restart";

  // Render the message as a texture
  SDL_Surface *surface = TTF_RenderText_Solid(font, message.c_str(), color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

  // Get the dimensions of the message
  int w, h;
  TTF_SizeText(font, message.c_str(), &w, &h);

  // Calculate the x and y positions for the message
  int x = (SCREEN_WIDTH - w / 2) / 2;
  int y = (SCREEN_HEIGHT - h / 2) / 2;

  // Create a rectangle to draw the message in
  rect.x = x;
  rect.y = y;
  rect.w = w / 2;
  rect.h = h / 2;

  // Draw the message onto the window
  SDL_RenderCopy(renderer, texture, NULL, &rect);

  // Free the surface and texture
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);

  // Update the window
  SDL_RenderPresent(renderer);
  // Clean up the font
  TTF_CloseFont(font);
  // Render the present renderer
  SDL_RenderPresent(renderer);
}

// Makes a move in the puzzle if it is valid
// Returns true if the move was successful, false otherwise
bool makeMove(int dr, int dc)
{
  // Get the position of the empty tile
  for (int i = 0; i < ROWS * COLS; i++) {
    if (puzzle[i] == 0)
    {
      emptyPos = i;
      break;
    }
  }
  // Caculate the position
  int newRow = emptyPos / ROWS + dr;
  int newCol = emptyPos % COLS + dc;
  int newPos = newRow * ROWS + newCol;
  // Detect if the move is possible
  if (newRow < 0 || newRow >= ROWS || newCol < 0 || newCol >= COLS)
    return false;

  // Swap the positions
  swap(puzzle[emptyPos], puzzle[newPos]);
  return true;
}

// A loop to maintain a pause
int maintainPause()
{
  while (1)
  {
    // Handle events and input
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      // If the mouse was moved, pass
      if (event.type == SDL_MOUSEMOTION)
        continue;
      // Return 0 if the result is a quit
      if (event.type == SDL_QUIT)
      {
        // Clean up SDL2/TTF
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();

        return 0;
      }

      if (event.type == SDL_KEYDOWN)
      {
        // Get the key that was pressed
        int key = event.key.keysym.sym;
        // Return 1 if unpuase
        if (key == SDLK_ESCAPE)
        {
          return 1;
        }
        // Restart the game if the space key is pressed and return 2
        if (key == SDLK_SPACE)
        {
          initPuzzle();
          return 2;
        }

        displayPause();
      }
      else
        displayPause();
    }
  }
  return 0;
}

int WinMain()
{
  // Initialize SDL2/TTF
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  // Create window
  window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  // Create renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // Initialize the puzzle
  initPuzzle();
  // Draw the puzzle onto the window
  displayPuzzle();

  // Keep track of whether the game has been won
  bool isWon = false;

  // Game loop
  while (1)
  {
    // Handle events and input
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      // If the mouse was moved, pass
      if (event.type == SDL_MOUSEMOTION)
        continue;
      // Exit the program if quit is detected
      if (event.type == SDL_QUIT)
      {
        // Clean up SDL2/TTF
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();

        return 0;
      }
      // If the game is not wo
      if (!isWon)
      {
        if (event.type == SDL_KEYDOWN)
        {
          // Get the key that was pressed
          int key = event.key.keysym.sym;
          // Make a move based on the key pressed
          if (key == SDLK_UP || key == SDLK_w)
            makeMove(-1, 0);
          else if (key == SDLK_DOWN || key == SDLK_s)
            makeMove(1, 0);
          else if (key == SDLK_LEFT || key == SDLK_a)
            makeMove(0, -1);
          else if (key == SDLK_RIGHT || key == SDLK_d)
            makeMove(0, 1);
          // Pause the game for a pause
          else if (key == SDLK_ESCAPE)
          {
            if (maintainPause() == 0)
              return 0;
            else
              displayPuzzle();
          }
        }
        // If a key was not pressed
        else
        {
          // Draw the updated puzzle onto the window
          displayPuzzle();
          // Update isWon if the game has been solved
          if (isSolved())
            isWon = true;
        }
      }
      // Display win if the game has been won
      else
      {
        if (event.type == SDL_KEYDOWN)
        {
          // Get the key that was pressed
          int key = event.key.keysym.sym;
          // Check if the game is unpaused
          // Restart the game if the space key is pressed
          if (key == SDLK_SPACE)
          {
            isWon = false;
            initPuzzle();
            displayPuzzle();
          }

          // Pause the game for a pause
          else if (key == SDLK_ESCAPE)
          {
            int pauseReturn = maintainPause();
            // If maintain pause is eqaul to 0 quit
            if (pauseReturn == 0)
              return 0;
            // If maintain pause is equal to 1 display win
            else if (pauseReturn == 1)
              displayWin();
            // Else the puzzle has been reset
            else
            {
              isWon = false;
              displayPuzzle();
            }
          }
        }
        // If a key was not pressed then display win
        else
          displayWin();
      }
    }
  }

  return 0;
}
