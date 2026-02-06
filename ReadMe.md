# OpenGLTutorial

## Plans
The purpose of this repo is to start with the tutorials provided from 
https://learnopengl.com and implement some kind of a OpenGL game engine ( ? )
after many rewrites.

### Assets
The creators of each asset used can be found below

| Name           | Creator    | Website                 | Socials              |
| :-:            |  :-:       | :-:                     | :-:                  |
Torment Textures | Bradley D. | https://strideh.itch.io | @strideh.bsky.social |

# Steps to install

The following steps are for a Windows enviroment alongside VSCode

## Mingw

Download from https://github.com/niXman/mingw-builds-binaries/releases the release option
x86_64-15.2.0-release-win32-seh-ucrt-rt_v13-rev0.7z ( name might be different )
Extract zip and move the folder in C:/

## cmake
Download from https://cmake.org/download/

## glfw

```powershell
git clone https://github.com/glfw/glfw.git
mkdir build
cmake -G "MinGW Makefiles" -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_EXAMPLES=OFF -S . -B build
cd build
cmake --build
cmake --install C:/Lib
```

## glad

Go to https://glad.dav1d.de/ and choose
- Language: C/C++
- API gl
    - 4.6 for the recent
    - 4.1 if mac
    - 3.3 if old 
- Profile: core
- Options: Generate a loader: checked

Extract the directory to C:/Lib and insert the following CMakeLists.txt
```c
cmake_minimum_required(VERSION 3.10.0)

project(glad)

add_library(glad include/glad/glad.h src/glad.c)
target_include_directories(glad PUBLIC include/)
```

## clangd

Download the clangd binary https://github.com/clangd/clangd/releases and install the vscode clangd extensions
with the following settings
- Arguments
    - --background-index
    - --header-insertion=never
    - --query-driver=/path/to/g++
    - --compile-commands-dir=/path/to/dir
- Clangd:Path
    - Insert path to the clangd binary

## glm

Go to https://github.com/g-truc/glm and follow the instructions of the
ReadMe.md files.

In case the file does not exist then:
download repo
```powershell
cd /path/to/glm
mkdir build
cmake -G "MinGW Makefiles" -DGLM_BUILD_TESTS=OFF -DBUILD_SHARED_LIBS=OFF -B build .
cmake --build build -- all
cmake --build build -- install
# Move new folder to C:/Lib
```

# TODO

- ~~Continue to second section ( Lighting )~~
- ~~Find how to create Debug/Release build~~
- ~~Better error logs to ease the debugging process~~
- Probably rewrite again 
- Implement some type of scheduler, after finishing the OpenGLTutorial
