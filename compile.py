import subprocess
import os

file_name   = "game"
main_name   = "main.c"
src_dir     = "src"
include_dir = "deps/include"
libs_dir    = "deps/libs"

def get_dir(dir: str) -> str:
    return f"{os.path.abspath(dir)}"

def get_file(dir: str, file: str) -> str:
    return os.path.join(get_dir(dir), file)

libraries = ["glew32", "glfw3dll", "opengl32", "gdi32"]

def main():

    # Compile
    compile_command = [
        "gcc",
        "-c",
        get_file(src_dir, main_name),
        "-I",
        get_dir(include_dir),
        "-I",
        get_dir(f"{include_dir}/GL"),
        "-I",
        get_dir(f"{include_dir}/GLFW"),
        "-o",
        "main.o"
    ]

    print("[INFO] Compiling...")
    print("[INFO] Executing command:")
    print(' '.join(compile_command).__add__('\n'))

    compile_result = subprocess.call(compile_command)

    if compile_result != 0:
        print("[ERROR] Compilation Error, linking stopped.")
        return

    print("[INFO] Success.\n")

    # Link
    link_command = [
        "gcc",
        "main.o",
        "-o",
        file_name,
        f"-L{get_dir(libs_dir)}",
    ]

    for lib in libraries:
        link_command.append(f"-l{lib}")

    print("[INFO] Linking...")
    print("[INFO] Executing command:")
    print(' '.join(link_command).__add__('\n'))

    link_result = subprocess.call(link_command)

    if link_result == 0:
        print("[INFO] Compilation Succeed.")
        os.remove("main.o")
    else:
        print("[ERROR] Linking Error.")

if __name__ == "__main__":
    main()
