# RayUI

A GUI library for raylib

## How to use

The only external dependency is raylib

1. Add the library as a submodule
```bash
mkdir -p thirdparty
cd thirdparty
git submodule add https://github.com/SemkiShow/RayUI
cd ..
```
2. Add RayUI to you CMakeLists.txt
```cmake
add_subdirectory(thirdparty/RayUI)
```

## Examples

1. Install Raylib following one of these tutorials based on your system: [Linux](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux), [Windows](https://github.com/raysan5/raylib/wiki/Working-on-Windows), [macOS](https://github.com/raysan5/raylib/wiki/Working-on-macOS)
1. Run 
```bash
git clone https://github.com/SemkiShow/RayUI
cd RayUI/examples
chmod +x run.sh
./run.sh
```
