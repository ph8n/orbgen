#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <stdbool.h>
#include <stdio.h>

// Vertex data for a simple triangle
// Each vertex has position (x, y, z) and color (r, g, b)
GLfloat vertices[] = {
    // Positions         // Colors
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom-left, Red
    0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom-right, Green
    0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // Top, Blue
};

// Basic Vertex Shader Source
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec3 aColor;\n"
                                 "\n"
                                 "out vec3 ourColor;\n"
                                 "\n"
                                 "void main()\n"
                                 "{\n"
                                 "    gl_Position = vec4(aPos, 1.0);\n"
                                 "    ourColor = aColor;\n"
                                 "}\n";

// Basic Fragment Shader Source
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "in vec3 ourColor;\n"
                                   "\n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = vec4(ourColor, 1.0);\n"
                                   "}\n";

// Function to compile a shader
GLuint compileShader(GLenum type, const char *source) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    fprintf(stderr, "ERROR::SHADER::COMPILATION_FAILED\n%s\n", infoLog);
    glDeleteShader(shader);
    return 0;
  }
  return shader;
}

// Function to link shaders into a program
GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader) {
  GLuint program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  GLint success;
  GLchar infoLog[512];
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    glDeleteProgram(program);
    return 0;
  }
  return program;
}

int main() {
  SDL_Init(SDL_INIT_VIDEO);

  // Request an OpenGL 3.3 core profile
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_Window *window = SDL_CreateWindow(
      "Ariel<3 - Triangle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if (!window) {
    fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
    SDL_Quit();
    return -1;
  }

  SDL_GLContext context = SDL_GL_CreateContext(window);
  if (!context) {
    fprintf(stderr, "Could not create OpenGL context: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    fprintf(stderr, "Error initializing GLEW: %s\n",
            glewGetErrorString(glewError));
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  // You might also want to check the OpenGL version provided by GLEW
  if (!GLEW_VERSION_3_3) {
    fprintf(stderr, "OpenGL 3.3 core profile not available!\n");
    // Handle this case - maybe exit or try a lower version
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }
  // Compile and link shaders
  GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
  if (!vertexShader) {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }
  GLuint fragmentShader =
      compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
  if (!fragmentShader) {
    glDeleteShader(vertexShader);
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }
  GLuint shaderProgram = createShaderProgram(vertexShader, fragmentShader);
  glDeleteShader(
      vertexShader); // Shaders are linked into the program, no longer needed
  glDeleteShader(fragmentShader);
  if (!shaderProgram) {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  // Create Vertex Buffer Object (VBO) and Vertex Array Object (VAO)
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  // Bind the VAO first, then bind and set vertex buffers, and then configure
  // vertex attributes.
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Configure vertex attributes
  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                        (void *)0);
  glEnableVertexAttribArray(
      0); // Enable the vertex attribute at layout location 0
  // Color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                        (void *)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(
      1); // Enable the vertex attribute at layout location 1

  // Unbind the VBO and VAO (optional, but good practice)
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // Set the clear color
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // A bluish-green background

  bool quit = false;
  SDL_Event event;
  while (!quit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }
    }

    // --- OpenGL Rendering Code ---
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);

    // Bind the VAO
    glBindVertexArray(VAO);

    // Draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3); // Draw 3 vertices as a triangle

    // Unbind the VAO (optional)
    glBindVertexArray(0);

    // --- End OpenGL Rendering Code ---

    // Swap the back buffer to the front (display the rendered frame)
    SDL_GL_SwapWindow(window);
  }

  // Clean up OpenGL resources
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
