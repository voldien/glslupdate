# glslupdate #


*glslupdate* is an old, simple library for allowing a glsl-shader retain its state after being relinked with a new shader. This is done by copy the uniform state of the shader and paste the uniform in succession of the shader has been relinked.

The library has not been *tested* since it was in development, which was about 3 years ago. The library will no longer be maintained.

## Dependencies ##

The only dependence is the OpenGL library.

In order to compile the program, the following Debian packages has to be installed.
```
apt-get install mesa-common-dev
```
