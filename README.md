# nictophobia
## Basic information
Small C++ game-engine (2D and minimal 3D) (GL+GLFW+AL+glm)

- **status**: in-development
- **current dependencies**: GL, GLFW, [GLM](https://github.com/g-truc/glm), libpng, libfreetype
- **standard**: C++17

Project also contain subprojects:
- miocpp - C++ implementation of [MIO](https://github.com/MihailRis/mio-files) storages interface
- necore - nictophobia engine itself
- nictoscript [in-development]

## Build (Linux):

```shell
mkdir build
ln -s res build/res
cd build
make -f ../Makefile BUILD_MODE=run

# then run
./Nictophobia
```

## Text formatting
`^` character used as prefix for formatting modifiers.

example: draw bold text with `^btext that must be bold^b`

modifiers:
- `^b` - toggle bold mode
- `^c` - reset color to initial
- `^r` - reset formatting
- `^w` - text waving effect
- `^s` - text shaking effect
- `^#hex_color_code` - set color
  
   examples: 
   - `^#FF0000this text is red^c`
   - `^#FFFFFF80this text is white with 50% opacity^c`
   - `^1#FF8000^ 024^c` - way to separate modifier from text digits (will output `1024` without spaces)
