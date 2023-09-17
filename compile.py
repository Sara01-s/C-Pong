import subprocess
import os

file_name   = "game"
main_name   = "main.c"
src_dir     = "src"
include_dir = "deps/include"
libs_dir    = "deps/libs"

libraries = ["glfw3", "glew32s", "opengl32", "gdi32"]

def main():
    # Compile
    compile_command = [
        "gcc",
        "-c",
        f"{os.path.abspath(src_dir)}/{main_name}",
        "-I",
        os.path.abspath(include_dir),
        "-I",
        f"{os.path.abspath(include_dir)}/GL",
        "-I",
        f"{os.path.abspath(include_dir)}/GLFW",
        "-o",
        "main.o"
    ]

    compile_result = subprocess.call(compile_command)

    if compile_result != 0:
        print("Compilation Error, linking stopped.")
        return

    # Link
    link_command = [
        "gcc",
        "main.o",
        "-o",
        file_name,
        "-L",
        libs_dir,
    ]

    for lib in libraries:
        link_command.append(f"-l{lib}")

    link_result = subprocess.call(link_command)

    if link_result == 0:
        print("Compilation Succeed.")
        os.remove("main.o")
    else:
        print("Linking Error.")

if __name__ == "__main__":
    main()