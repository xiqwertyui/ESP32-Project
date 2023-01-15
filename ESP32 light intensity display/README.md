# Board
  Adafruit ESP32 feather

# Material
  ## BH1750 -> light sensor
    param
      - multi mode
      - wide light intensity range
    link
      - https://amzn.asia/d/aXa3jAT
  ## 128x64 1.3 inch OLED Screen -> display
    param
      - driver: SH1106
      - display Type: OLED
      - size: 128x64
      - color: blue
    link
      - https://amzn.asia/d/6Vz5Vp6
  ## LED -> setup indicator
    description
      - Used to indicate that the programe has setup successfully
    param
      - color: green
    link
      - https://amzn.asia/d/6Vz5Vp6

# Start
  - configure you wifi in **main.cpp**
    `` const char* ssid = "YOUR WIFI NAME"; ``
    `` const char* password = "YOUR WIFI PASSWORD"; ``
  - use platformio to upload code to the board
  - wait for the LED turn on

# Project preview
  - ![plot](./screenshot.png)