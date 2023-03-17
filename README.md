# nictophobia
Small C++ game-engine (2D and minimal 3D) (GL+GLFW+AL+glm)

- **status**: in-development
- **current dependencies**: GL, GLFW, [GLM](https://github.com/g-truc/glm)
- **standard**: C++17

Project also contain subprojects:
- miocpp - C++ implementation of [MIO](https://github.com/MihailRis/mio-files) storages interface

Build (Linux):

```shell
mkdir build
cd build
make -f ../Makefile

# create link to resources folder
ln -s ../res res
# then run
./Nictophobia
```
