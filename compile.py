import subprocess
import argparse
import glob
import os

####################################################################

# Config
APP_NAME    = 'game'
SRC_DIR     = 'src'
OBJ_DIR     = 'obj'
INC_DIR     = 'deps/include'
LIB_DIR     = 'deps/libs'
CFLAGS      = '-Wall'
LIBRARIES   = ['GLEW', 'glfw', 'GL', 'm']


####################################################################


# Utility functions for colored logging
LIGHT_GRAY = '\033[37m'
DARK_GRAY  = '\033[90m'
RED    = '\033[91m'
GREEN  = '\033[92m'
YELLOW = '\033[93m'
CLEAR  = '\033[0m'

def get_abs_path(directory: str) -> str:
    """Returns the absolute path of a given directory."""
    return os.path.abspath(directory)

def log_cmd(command: str):
    """Logs a command in light gray."""
    print(f"{LIGHT_GRAY}[CMD] {DARK_GRAY}{command}{CLEAR}")

def log_info(message: str, msg_color=LIGHT_GRAY):
    """Logs an informational message with optional color."""
    print(f"{msg_color}[INFO] {message}{CLEAR}")

def log_error(message: str):
    """Logs an error message in red."""
    print(f"{RED}[ERROR] {message}{CLEAR}")

####################################################################

def compile_file(file_path: str, debug: bool) -> bool:
    """Compiles a single C source file into an object file."""
    build_mode = '-g' if debug else '-O1'
    file_name_no_ext = os.path.splitext(os.path.basename(file_path))[0]
    
    compile_command = [
        'gcc', '-c', file_path, build_mode, '-I', get_abs_path(INC_DIR),
        '-I', get_abs_path(f'{INC_DIR}/GL'), '-I', get_abs_path(f'{INC_DIR}/GLFW'),
        '-o', get_abs_path(f'{OBJ_DIR}/{file_name_no_ext}.o')
    ]

    log_info(f'Compiling {file_path}...')
    log_cmd(' '.join(compile_command))
    
    if subprocess.call(compile_command) != 0:
        log_error(f'Compilation Error on {file_path}, building stopped.')
        return False

    return True

def link_files() -> bool:
    """Links all object files into the final executable."""
    obj_files = glob.glob(f'{OBJ_DIR}/**/*.o', recursive=True)
    
    link_command = ['gcc', *obj_files, '-o', APP_NAME, f'-L{get_abs_path(LIB_DIR)}']
    link_command.extend([f'-l{lib}' for lib in LIBRARIES])

    log_info(f'Linking object files...')
    log_cmd(' '.join(link_command))
    
    if subprocess.call(link_command) != 0:
        log_error('Linking Error.')
        return False
    
    return True

def clean_files(clean_all: bool):
    """Deletes all object files, and optionally the executable."""
    obj_files = glob.glob(f'{OBJ_DIR}/**/*.o', recursive=True)
    
    if clean_all and os.path.exists(APP_NAME):
        log_info(f'Deleting {APP_NAME}.')
        os.remove(APP_NAME)
    
    if not obj_files:
        log_info('Object files already cleaned.')
        return
    
    for obj_file in obj_files:
        log_info(f'Deleting {obj_file}.')
        os.remove(obj_file)

def main():
    parser = argparse.ArgumentParser(description='C builder')
    parser.add_argument('--debug', action='store_true', help='Compiles program with debug symbols')
    parser.add_argument('--clean', action='store_true', help='Deletes all object files')
    parser.add_argument('--clean-all', action='store_true', help='Deletes executable and all object files')
    args = parser.parse_args()

    if args.clean or args.clean_all:
        clean_files(args.clean_all)
        return

    src_files = glob.glob(f'{SRC_DIR}/**/*.c', recursive=True)
    build_type = 'DEBUG' if args.debug else 'RELEASE'
    log_info(f'{build_type} BUILD\n', YELLOW if args.debug else GREEN)

    for src_file in src_files:
        if not compile_file(src_file, args.debug):
            return

    log_info('Compilation succeeded.\n', GREEN)

    if not link_files():
        return

    log_info('Linking succeeded.', GREEN)
    log_info('Executable built.', GREEN)

if __name__ == '__main__':
    main()
