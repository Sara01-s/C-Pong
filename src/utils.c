#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

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

const char* read_file(const char* file_path) {
    FILE* file = fopen(file_path, "r");

    if (file == NULL) {
        log_error("Failed to open file.");
        exit(EXIT_FAILURE);
        return NULL;
    }

    fseek(file, 0, SEEK_END);       // Move pointer to last file byte
    long file_size = ftell(file);   // Save the file size
    fseek(file, 0, SEEK_SET);       // Move pointer to initial file sizes

    char* file_contents = (char*) malloc(file_size + 1);

    if (file_contents == NULL) {
        log_error("Failed to allocate memory for the file.");
        fclose(file);
        return NULL;
    }

    size_t read_size = fread(file_contents, 1, file_size, file);
    file_contents[read_size] = '\0';

    fclose(file);

    return (const char*) file_contents;
}