# Fdf
Create wireframe projection using OpenGl and isometric vue

## How to compile ?
To compile Fdf, you have to run:
```
make SIERRA=true  // if you are on MacOS Sierra
make MOJAVE=true  // if you are on MacOs Mojave
make UNIX=true    // if you are on unix system
make              // By default, make will compile minilibx for Macos Sierra
```

If you have compiling problem on debian based distributions, please make sure freeglut3-dev is installed.

Otherwise, you can install it via apt:
```
sudo apt install freeglut3-dev
```

## How to launch it ?
You can launch it by typing
```
./fdf maps/42.fdf
```
after compiling it.
You can launch all the files in the maps folder

## Keyboard bindings:
```
+           : zoom in
-           : zoom out
r   : set/unset color
v   : change vue
esc : quit fdf
The arrows are used logically.


On MacOs:
shift + "=" : increase relief
shift + "-" : decrease relief

On unix system:
a           : decrease relief
e           : increase relief
```
