import subprocess
import argparse
import glob
import os

# utility functions
c_light_gray = '\033[37m'
c_dark_gray  = '\033[90m'
c_red    = '\033[91m'
c_green  = '\033[92m'
c_yellow = '\033[93m'
c_clear  = '\033[0m'

def get_dir(dir: str) -> str:
    return f'{os.path.abspath(dir)}'

def get_file(dir: str, file: str) -> str:
    return os.path.join(get_dir(dir), file)

def log_cmd(command: str):
    print(c_light_gray + '[CMD] ' + c_dark_gray + command + c_clear)

def log_info(message: str, msg_color=c_light_gray):
    print(msg_color + "[INFO] " + message + c_clear)

def log_error(message: str):
    print(c_red + "[ERROR] " + message + c_clear)

#############################################################

APP_NAME    = 'game'
SRC_DIR     = 'src'
OBJ_DIR     = 'obj'
INC_DIR     = 'deps/include'
LIB_DIR     = 'deps/libs'

libraries = ['glew32', 'glfw3dll', 'opengl32', 'gdi32']

def compile_file(file_path: str, debug = False) -> int:
    build_mode = '-g' if debug else '-O1'
    file_name_no_dir       = file_path.split('\\')[-1]
    file_name_dot_index    = file_name_no_dir.find('.')
    file_name_no_extension = file_name_no_dir[:file_name_dot_index] if file_name_dot_index != 1 else file_name_no_dir

    compile_command = [
        'gcc',
        '-c',
        file_path,
        build_mode,
        '-I',
        get_dir(INC_DIR),
        '-I',
        get_dir(f'{INC_DIR}/GL'),
        '-I',
        get_dir(f'{INC_DIR}/GLFW'),
        '-o',
        get_dir(f'{OBJ_DIR}/{file_name_no_extension}.o'),
    ]
    
    if debug: log_info('DEBUG BUILD\n', c_yellow)
    else:     log_info('RELEASE BUILD\n', c_green)

    log_info(f'Compiling {file_path}...')
    log_cmd(' '.join(compile_command))

    compilation_result = subprocess.call(compile_command)
    if compilation_result != 0:
        log_error(f'Compilation Error on {file_path}, building stopped.')
        return False
    
    return True

def link_file(obj_file_path) -> bool:
    print(obj_file_path)

    obj_files = glob.glob(f'{OBJ_DIR}/**/*.o', recursive=True)

    link_command = [
        'gcc',
        *obj_files,
        '-o',
        APP_NAME,
        f'-L{get_dir(LIB_DIR)}',
    ]

    for lib in libraries:
        link_command.append(f'-l{lib}')

    log_info(f'Linking {obj_file_path}...')
    log_cmd(' '.join(link_command))

    link_result = subprocess.call(link_command)

    if link_result != 0:
        log_error(f'Linking Error on {obj_file_path}.')
        return False
    
    return True

def main():

    parser = argparse.ArgumentParser(description='C builder')
    parser.add_argument('--debug', action='store_true', help='Compiles program with debug symbols')
    parser.add_argument('--clean', action='store_true', help='Deletes all object files')
    parser.add_argument('--clean-all', action='store_true', help='Deletes executable and all object files')
    args = parser.parse_args()

    if args.clean or args.clean_all:
        obj_files = glob.glob(f'{OBJ_DIR}/**/*.o', recursive=True)
        
        if args.clean_all:
            if os.path.exists(APP_NAME + '.exe'):
                log_info(f'Deleting {APP_NAME}.exe.')
                os.remove(APP_NAME + '.exe')
            else: 
                log_info('Executable already cleaned.')
      
        if len(obj_files) <= 0:
           log_info('Object files already cleaned.')
           return
       
        for obj_file in obj_files:
           log_info(f'Deleting {obj_file}.')
           os.remove(obj_file)
           return
       
    src_files = glob.glob(f'{SRC_DIR}/**/*.c', recursive=True)

    # Compile
    for src_file in src_files:
        compiled_sucessfully = compile_file(src_file, args.debug)
        if not compiled_sucessfully:
            return

    log_info('Compilation succeed.\n', c_green)

    # Link
    linked_sucessfully = link_file(get_dir(OBJ_DIR))

    if not linked_sucessfully:
        return

    log_info('Linking succeed.', c_green)

    print()
    log_info('Executable built.', c_green)

if __name__ == '__main__':
    main()

