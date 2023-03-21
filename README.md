# nictophobia
Small C++ game-engine (2D and minimal 3D) (GL+GLFW+AL+glm)

- **status**: in-development
- **current dependencies**: GL, GLFW, [GLM](https://github.com/g-truc/glm), libpng
- **standard**: C++17

Project also contain subprojects:
- miocpp - C++ implementation of [MIO](https://github.com/MihailRis/mio-files) storages interface
- necore - nictophobia engine itself

Build (Linux):

```shell
mkdir build
ln -s res build/res
cd build
make -f ../Makefile BUILD_MODE=run

# then run
./Nictophobia
```
