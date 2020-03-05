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

If you are experiencing a black window with nothing appearing under Arch Linux, try replacing the function fill_pixel with this one

```
int		fill_pixel(t_fdf *fdf, int color, int y, int x)
{
	int form;

	form = (((WIN_WIDTH * y) + x));
	if (x > 0 && y > 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
	{
    write(1, "", 1);
    fdf->mlx->data[form] = mlx_get_color_value(fdf->mlx->mlx_ptr, color);
	}
  return (0);
}
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
