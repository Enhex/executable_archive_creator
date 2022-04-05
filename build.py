import os
import argparse
from sys import platform

parser = argparse.ArgumentParser()
parser.add_argument("-r", "--release", help="Generate release build (debug by default).", action="store_true")
args = parser.parse_args()

build_type = 'Release' if args.release else 'Debug'

source = os.path.dirname(os.path.realpath(__file__))

def create_symlink(src, dst):
    # create all parent directories of the symlink one
    parent_dir = os.path.dirname(dst)
    os.makedirs(parent_dir, exist_ok=True)

    try:
        os.symlink(src, dst)
    except:
        pass

def build():
    build_dir = "../build/" + build_type
    os.makedirs(build_dir, exist_ok=True)
    os.chdir(build_dir)

    build_path = os.path.realpath(os.getcwd())

    create_symlink(source + '/data', './data')

    # conan
    os.system('conan install "' + source + '/" --build=outdated -s arch=x86_64 -s build_type=' + build_type)

    os.chdir(source)

    def premake_generate(generator):
        os.system('premake5 ' + generator + ' --location="' + build_dir + '/"')

    if platform == 'win32':
        premake_generate('vs2019')
    else:
        premake_generate('gmake2')
        premake_generate('vscode')

    return build_path


build()