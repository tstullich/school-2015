#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include "DrawUtils.h"

int main(void) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return 1;
    }

    // Create the window, OpenGL context
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_Window* window = SDL_CreateWindow(
        "Press the Arrow Keys to make things happen",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 480,
        SDL_WINDOW_OPENGL);

    if (!window) {
        fprintf(stderr, "Could not create window. Error Code = %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_GL_CreateContext(window);

    // Make sure we have a recent version of OpenGL
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        fprintf(stderr, "Could not initialize glew. Error Code = %s\n", glewGetErrorString(glewError));
        SDL_Quit();
    }
    if (!GLEW_VERSION_3_0) {
        fprintf(stderr, "OpenGL max supported version is too low now.\n");
        SDL_Quit();
        return 1;
    }

    // Setup OpenGL state
    glViewport(0, 0, 640, 480);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, 640, 480, 0, 0, 100);
    glEnable(GL_TEXTURE_2D);

    // Initialize sprite before displaying it
    int spriteWidth = 0;
    int spriteHeight = 0;
    int spritePosX = 140;
    int spritePosY = 60;
    GLuint sprite = glTexImageTGAFile("lambda.tga", &spriteWidth, &spriteHeight);

    // Logic to keep track of keyboard pushes
    unsigned char kbPrevState[SDL_NUM_SCANCODES] = {0};
    const unsigned char* kbState = NULL;
    kbState = SDL_GetKeyboardState(NULL);

    // Going to experiment changing the color of the background a bit
    float red = 0;
    float green = 0;
    float blue = 0;

    // The game loop
    char shouldExit = 0;
    while (!shouldExit) {
        // kbState is updated by the message pump. Copy over the old state before the pump!
        memcpy(kbPrevState, kbState, sizeof(kbPrevState));

        // Handle OS message pump
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    shouldExit = 1;
            }
        }

        // Going to handle keyboard events here
        kbState = SDL_GetKeyboardState(NULL);
        if (kbState[SDL_SCANCODE_RIGHT]) {
            red += 0.1;
            green -= 0.1;
            blue -= 0.1;
            spritePosX++;
        }
        if (kbState[SDL_SCANCODE_LEFT]) {
            red -= 0.1;
            green += 0.1;
            blue -= 0.1;
            spritePosX--;
        }
        if (kbState[SDL_SCANCODE_UP]) {
            red -= 0.1;
            green -= 0.1;
            blue += 0.1;
            spritePosY--;
        }
        if (kbState[SDL_SCANCODE_DOWN]) {
            red -= 0.1;
            green -= 0.1;
            blue -= 0.1;
            spritePosY++;
        }

        // If color values are outside of the range [0,1] we set them back to 0
        red = ((red >= 1.0) || (red <= 0)) ? 0 : red;
        green = ((green >= 1.0) || (green <= 0)) ? 0 : green;
        blue = ((blue >= 1.0) || (blue <= 0)) ? 0 : blue;

        glClearColor(red, green, blue, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        // Game logic goes here
        glDrawSprite(sprite, spritePosX, spritePosY, spriteWidth, spriteHeight);

        SDL_GL_SwapWindow(window);
    }

    SDL_Quit();
    return 0;
}
