### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

SPI Pin: SCLK/MOSI/MISO/CS GPIO11/GPIO10/GPIO9/GPIO8.

GPIO Pin: RESET/CMD_DATA GPIO27/GPIO17.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
# open another terminal
./st7789_server 

# use the CMake terminal
make test
```

Find the compiled library in CMake. 

```cmake
find_package(st7789 REQUIRED)
```
### 3. ST7789

#### 3.1 Command Instruction

1. Show st7789 chip and driver information.

   ```shell
   st7789 (-i | --information)
   ```

2. Show st7789  help.

   ```shell
   st7789 (-h | --help)
   ```

3. Show st7789  pin connections of the current board.

   ```shell
   st7789 (-p | --port)
   ```

4. Run st7789 display test.

   ```shell
   st7789 (-t display | --test=display)
   ```

5. Run st7789 basic init function.

   ```shell
   st7789 (-e basic-init | --example=basic-init)
   ```

6. Run st7789 basic deinit function.

   ```shell
   st7789 (-e basic-deinit | --example=basic-deinit)
   ```

7. Run st7789 show string function, string means the shown string. 

   ```shell
   st7789 (-e basic-str | --example=basic-str) [--str=<string>]
   ```

8. Run st7789 display on function.

   ```shell
   st7789 (-e basic-display-on | --example=basic-display-on)
   ```

9. Run st7789 display off function.

   ```shell
   st7789 (-e basic-display-off | --example=basic-display-off)
   ```

10. Run st7789 clear screen function.

    ```shell
    st7789 (-e basic-clear | --example=basic-clear)
    ```

11. Run st7789 write pont function, x0 is the x of the point and y0 is the y of the point, rgb565 means the filled color.

    ```shell
    st7789 (-e basic-point | --example=basic-point) --x0=<x0> --y0=<y0> [--color=<rgb565>]
    ```

12. Run st7789 draw rectangle function, x1 is the top left x of the rect, y1 is the top left y of the rect, x2 is the bottom right x of the rect and y2 is the bottom right y of the rect, rgb565 means the filled color.

    ```shell
    st7789 (-e basic-rect | --example=basic-rect) --x1=<x1> --y1=<y1> --x2=<x2> --y2=<y2> [--color=<rgb565>]
    ```

#### 3.2 How to run

```shell
# open one terminal and run the server
./st7789_server 
```
```shell
# open another terminal and sent the command
./st7789 xxx xxx xxx ...
```

#### 3.3 Command Example

```shell
./st7789 -i

st7789: chip is Sitronix ST7789.
st7789: manufacturer is Sitronix.
st7789: interface is SPI.
st7789: driver version is 1.0.
st7789: min supply voltage is 2.4V.
st7789: max supply voltage is 3.3V.
st7789: max current is 7.50mA.
st7789: max temperature is 85.0C.
st7789: min temperature is -30.0C.
```

```shell
./st7789 -p

st7789: SCK connected to GPIO11(BCM).
st7789: MISO connected to GPIO9(BCM).
st7789: MOSI connected to GPIO10(BCM).
st7789: CS connected to GPIO8(BCM).
st7789: cmd data gpio GPIO connected to GPIO17(BCM).
st7789: reset GPIO connected to GPIO27(BCM).
```

```shell
./st7789 -t display

st7789: chip is Sitronix ST7789.
st7789: manufacturer is Sitronix.
st7789: interface is SPI.
st7789: driver version is 1.0.
st7789: min supply voltage is 2.4V.
st7789: max supply voltage is 3.3V.
st7789: max current is 7.50mA.
st7789: max temperature is 85.0C.
st7789: min temperature is -30.0C.
st7789: start display test.
st7789: font 12 test.
st7789: font 16 test.
st7789: font 24 test.
st7789: rectangle test.
st7789: rand point test.
st7789: picture test.
st7789: finish display test.
```

```shell
./st7789 -e basic-str --str=12345abcdEFGH

st7789: 12345abcdEFGH.
```

```shell
./st7789 -e basic-init

st7789: init success.
```

```shell
./st7789 -e basic-display-off

st7789: display off.
```

```shell
./st7789 -e basic-display-on

st7789: display on.
```

```shell
./st7789 -e basic-clear

st7789: clear screen.
```

```shell
./st7789 -e basic-deinit

st7789: deinit st7789.
```

```shell
./st7789 -e basic-point --x0=16 --y0=16 --color=65535

st7789: write point 16 16 65535.
```

```shell
./st7789 -e basic-rect --x1=0 --y1=0 --x2=72 --y2=72 --color=65535

st7789: draw rect 0 0 72 72.
```

```shell
./st7789 -h

Usage:
  st7789 (-i | --information)
  st7789 (-h | --help)
  st7789 (-p | --port)
  st7789 (-t display | --test=display)
  st7789 (-e basic-init | --example=basic-init)
  st7789 (-e basic-deinit | --example=basic-deinit)
  st7789 (-e basic-str | --example=basic-str) [--str=<string>]
  st7789 (-e basic-display-on | --example=basic-display-on)
  st7789 (-e basic-display-off | --example=basic-display-off)
  st7789 (-e basic-clear | --example=basic-clear)
  st7789 (-e basic-point | --example=basic-point) --x0=<x0> --y0=<y0> [--color=<rgb565>]
  st7789 (-e basic-rect | --example=basic-rect) --x1=<x1> --y1=<y1> --x2=<x2> --y2=<y2> [--color=<rgb565>]

Options:
      --color=<rgb565>     Set the chip color.([default: 65535])
  -e <basic-init | basic-deinit | basic-str | basic-display-on | basic-display-off | basic-clear
     | basic-point | basic-rect>, --example=<basic-init | basic-deinit | basic-str | basic-display-on
     | basic-display-off | basic-clear | basic-point | basic-rect>
                          Run the driver example.
  -h, --help              Show the help.
  -i, --information       Show the chip information.
  -p, --port              Display the pin connections of the current board.
      --str=<string>      Set the display string.([default: libdriver])
  -t <display>, --test=<display>
                          Run the driver test.
      --x0=<x0>           Set the x0 and it is the x of the point.
      --x1=<x1>           Set the x1 and it is the top left x of the rect.
      --x2=<x2>           Set the x2 and it is the bottom right x of the rect.
      --y0=<y0>           Set the y0 and it is the y of the point.
      --y1=<y1>           Set the y1 and it is the top left y of the rect.
      --y2=<y2>           Set the y2 and it is the bottom right y of the rect.
```

