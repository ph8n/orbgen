// External Libs
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

// Std libs
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

// header files
#include "camera.h"
#include "objects.h"
#include "physics.h"
#include "vec.h"

SDL_Window *window = NULL;
SDL_GLContext context = NULL;

void drawCircle(float x, float y, float radius, int numSegments) {
  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(x, y);
  for (int i = 0; i <= numSegments; i++) {
    float theta = 2.0f * (float)M_PI * (float)i / (float)numSegments;
    float dx = radius * cosf(theta);
    float dy = radius * sinf(theta);
    glVertex2f(x + dx, y + dy);
  }
  glEnd();
}

Camera2D cam = {{0.0f, 0.0f}, 0.5f};

void applyCamera(const Camera2D *camera, int windowWidth, int windowHeight) {
  float aspectRatio = (float)windowWidth / (float)windowHeight;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  float orthoHalfWidth = aspectRatio / 2.0f * camera->scale;
  float orthoHalfHeight = 1.0f / 2.0f * camera->scale;

  glOrtho(-orthoHalfWidth, orthoHalfWidth, -orthoHalfHeight, orthoHalfHeight,
          -1.0f, 1.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glTranslatef(-camera->pos.x, -camera->pos.y, 0.0f);
}

Object2D object1 = {.pos = {-2, 0},
                    .vel = {0, 0},
                    .acc = {0, 0},
                    .mass = 10e10f,
                    .radius = 0.5f,
                    .color = {1, 0, 0}};
Object2D object2 = {.pos = {2, 0},
                    .vel = {0, 0},
                    .acc = {0, 0},
                    .mass = 10e10f,
                    .radius = 0.5f,
                    .color = {0, 0, 1}};

int main() {
  int w = 1280;
  int h = 800;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
    return 1;
  }

  window = SDL_CreateWindow("Ariel<3", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, w, h,
                            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |
                                SDL_WINDOW_RESIZABLE); // Add resizable
  if (window == NULL) {
    fprintf(stderr, "Failed to create SDL window: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  context = SDL_GL_CreateContext(window);
  if (context == NULL) {
    fprintf(stderr, "Failed to create OpenGL context: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  glewExperimental = GL_TRUE;
  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW: %s\n",
            glewGetErrorString(glewError));
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  bool quit = false;
  SDL_Event event;
  Uint32 lastTime = SDL_GetTicks();
  float deltaTime = 0.0f;
  while (!quit) {
    Uint32 currentTime = SDL_GetTicks();
    deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    // --- Event Handling ---
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }
      // Handle window resize events
      if (event.type == SDL_WINDOWEVENT &&
          event.window.event == SDL_WINDOWEVENT_RESIZED) {
        w = event.window.data1;
        h = event.window.data2;
        glViewport(0, 0, w, h);
      }
      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_UP:
          cam.pos.y += 0.05f * cam.scale; // Move camera up
          break;
        case SDLK_DOWN:
          cam.pos.y -= 0.05f * cam.scale; // Move camera down
          break;
        case SDLK_LEFT:
          cam.pos.x -= 0.05f * cam.scale; // Move camera left
          break;
        case SDLK_RIGHT:
          cam.pos.x += 0.05f * cam.scale; // Move camera right
          break;
        case SDLK_EQUALS: // Zoom in (increase scale)
          cam.scale *= 0.95f;
          break;
        case SDLK_MINUS: // Zoom out (decrease scale)
          cam.scale *= 1.05f;
          break;
        }
      }
    } // End of event polling loop

    updateTwoBodyEuler(&object1, &object2, deltaTime);

    // --- Rendering Logic ---
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    applyCamera(&cam, w, h);

    // draw object1
    glColor3f(object1.color[0], object1.color[1],
              object1.color[2]); // Set color to white
    drawCircle(object1.pos.x, object1.pos.y, object1.radius, 36);

    // draw object2
    glColor3f(object2.color[0], object2.color[1],
              object2.color[2]); // Set color to blue
    drawCircle(object2.pos.x, object2.pos.y, object2.radius, 36);

    SDL_GL_SwapWindow(window);
  } // End of main game loop

  // --- Cleanup ---
  if (context != NULL) {
    SDL_GL_DeleteContext(context);
    context = NULL;
  }
  if (window != NULL) {
    SDL_DestroyWindow(window);
    window = NULL;
  }
  SDL_Quit();

  return 0;
}
