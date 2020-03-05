# Fdf
Create wireframe projection using OpenGl and isometric vue

![Screen Shot 2020-03-04 at 4 46 44 PM](https://user-images.githubusercontent.com/42534397/75975803-79a51e80-5ed9-11ea-9825-e9718d4e89a1.png)

## How to compile ?
To compile Fdf, you have to run:
```
make SIERRA=true  // if you are on MacOS
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
