# Graphics Test 1

> OpenGL and GLFW Test

## Requirements

* [OpenGL](https://www.opengl.org/) v4.0+
* [CMake](https://cmake.org/download/) v3.2+
* [GLFW](https://www.glfw.org/) v3.3+
* [STB Image Header](https://github.com/nothings/stb/blob/master/stb_image.h) v2.20+
* [GLAD](https://glad.dav1d.de/#language=c&specification=gl&api=gl%3D4.0&api=gles1%3Dnone&api=gles2%3Dnone&api=glsc2%3Dnone&profile=core&localfiles=on)
  v1.0.4+

## Before compiling

* Set the environment variable `GLAD_PATH` to the path to the location of the `glad.c` or `glad.o` file.

```shell
export GLAD_PATH=/path/to/glad.c
```

## Compiling

```shell
$ cmake --build bin --target clean -j4
$ cmake --build bin --target graphicsTest1 -j4
```

## Running

```shell
$ ./bin/graphicsTest1
```

## License

> [MIT](https://opensource.org/licenses/MIT)
