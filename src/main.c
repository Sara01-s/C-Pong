#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <CGLM/glm/cam.h>
#include <CGLM/glm/struct.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define log(message) printf("[INFO] %s\n", message);

/* use for debugging OpenGL errors, comment if not used */
#define DEBUG_OPENGL
//#define NDEBUG

#ifdef DEBUG_OPENGL
    #define GL_CALL(expression) while (glGetError() != GL_NO_ERROR);\
                                expression;\
                                assert(GLLogCall(#expression, __FILE__, __LINE__))
#else
    #define GL_CALL(expression) expression
#endif

bool GLLogCall(const char* function_name, const char* file, int line) {
    bool success = true;
    GLenum error;

    while ((error = glGetError()) != GL_NO_ERROR) {
        GLenum error = glGetError();
        success = false;
        if (error == 1282)
            printf("[OpenGL Error] (Invalid Operation): %s %s: %d\n\n", function_name, file, line);
        else
            printf("[OpenGL Error]: (code: %d) %s %s: %d\n\n", error, function_name, file, line);
    }

    return success;
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    log("Window resized.");
    GL_CALL(glViewport(0, 0, width, height));
}

GLuint create_shader(GLenum shader_type, const char* source) {

    GL_CALL(GLuint shader_program = glCreateShader(shader_type));
    GL_CALL(glShaderSource(shader_program, 1, &source, NULL)); // OpenGL will use strlen under the hood to determine the src size
    GL_CALL(glCompileShader(shader_program));

    GLuint shader_compile_status = 0;
    GL_CALL(glGetShaderiv(shader_program, GL_COMPILE_STATUS, &shader_compile_status));

    if (shader_compile_status == GL_FALSE) {
        GLsizei log_length = 0;
        GL_CALL(glGetShaderiv(shader_program, GL_INFO_LOG_LENGTH, &log_length));
        GLchar* log_message = (char*) malloc(log_length * sizeof(GLchar));

        GL_CALL(glGetShaderInfoLog(shader_program, log_length, &log_length, log_message));
        printf(log_message);
    }
    
    return shader_program;
}

GLuint compile_shader(GLuint vert_shader, GLuint frag_shader) {

    GL_CALL(GLuint shader_program = glCreateProgram());

    GL_CALL(glAttachShader(shader_program, vert_shader));
    GL_CALL(glAttachShader(shader_program, frag_shader));
    GL_CALL(glLinkProgram(shader_program));

    GLuint shader_link_status = 0;
    GL_CALL(glGetProgramiv(shader_program, GL_LINK_STATUS, &shader_link_status));

    if (shader_link_status == GL_FALSE) {
        GLsizei log_length = 0;
        GL_CALL(glGetShaderiv(shader_program, GL_INFO_LOG_LENGTH, &log_length));
        GLchar* log_message = (char*) malloc(log_length * sizeof(GLchar));

        GL_CALL(glGetProgramInfoLog(shader_program, log_length, &log_length, log_message));
        printf(log_message);
    }

    return shader_program;
}

int main(void) {

    log("Running game...");

    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(480, 480, "Mi primer jueguito en C", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwSwapInterval(1);    // 1 means VSync
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // Vertex data
    float vertices[] = {
         0.5f,  0.5f,
         0.5f, -0.5f,
        -0.5f, -0.5f,

        -0.5f,  0.5f
    };

    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    GLuint vertex_array_object;
    GL_CALL(glGenVertexArrays(1, &vertex_array_object));
    GL_CALL(glBindVertexArray(vertex_array_object));

    GLuint vertex_buffer_object;
    GL_CALL(glGenBuffers(1, &vertex_buffer_object));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    GLuint vertex_index_buffer;
    GL_CALL(glGenBuffers(1, &vertex_index_buffer));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_index_buffer));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    /* location 0 , and it's a vec2 so we intput 2*/
    GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0));
    GL_CALL(glEnableVertexAttribArray(0));

    const char* vertex_source =
        "#version 330 core\n"
        "layout (location = 0) in vec2 Position;\n"
        "void main() {\n"
        "   gl_Position = vec4(Position, 0.0, 1.0);\n"
        "}";

    const char* fragment_source = 
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "   FragColor = vec4(0.2f, 0.8f, 0.3f, 1.0f);\n"
        "}";
        
    GLuint vertex_shader   = create_shader(GL_VERTEX_SHADER, vertex_source);
    GLuint fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_source);

    GLuint shader = compile_shader(vertex_shader, fragment_shader);

    GL_CALL(glUseProgram(shader));

    mat4 projection_matrix;
    glm_mat4_identity(projection_matrix);
    glm_ortho(-10.0f, 10.0f, -10.0f, 10.0f, -1.0f, 1.0f, projection_matrix);

    GL_CALL(glClearColor(0.2f, 0.3f, 0.8f, 1.0f));

    /* Game loop */
    while (!glfwWindowShouldClose(window)) {

        process_input(window);

        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

        GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    log("Game closed, Bye bye.");
    return 0;
}
