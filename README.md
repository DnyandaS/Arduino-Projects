# Cat OLED Animation

A small Arduino project: a cat on a tiny OLED screen that changes its expression when you press a button. Idle, it sits with big eyes and a calm face. Press the button and it squeezes its eyes shut and looks startled, as if it just hit the table, and the buzzer plays a short thud. Let go and it goes back.

I built it to practise writing my own Arduino code and to learn how to turn pictures into data a microcontroller can draw.

## Parts

- Arduino Nano (CH340 clone)
- 0.96" SSD1306 OLED screen, 128x64, I2C (4 pins)
- 1 push button
- HW-508 passive buzzer module
- Breadboard and jumper wires

## Wiring

| Part | Pin | Connects to |
|---|---|---|
| OLED | GND | GND |
| OLED | VDD / VCC | 5V |
| OLED | SDA | A4 |
| OLED | SCK / SCL | A5 |
| Button | one leg | D2 |
| Button | other leg | GND |
| Buzzer | S (signal) | D8 |
| Buzzer | - (ground) | GND |
| Buzzer | middle pin | not connected |

The button uses the Nano's internal pull-up resistor (`INPUT_PULLUP`), so no extra resistor is needed. The pin reads `HIGH` normally and `LOW` while the button is pressed.

## How it works

1. Two 128x64 black-and-white pictures, `cat_idle.png` and `cat_hit.png`, were converted to byte arrays with [image2cpp](https://javl.github.io/image2cpp/) (horizontal, 1 bit per pixel). The arrays are stored in `cat_oled_bitmap.h`.
2. The arrays are marked `PROGMEM`, so they live in flash memory. The Nano only has 2 KB of RAM, and the screen buffer already uses 1 KB of it.
3. In `loop()`, the sketch reads the button. If it is pressed it draws `cat_hit`, otherwise `cat_idle`, then sends the picture to the screen with `display.display()`.
4. The buzzer is a passive one, so it needs a signal from the code. `tone(8, 300, 100)` plays a 300 Hz sound for 100 ms. A variable remembers whether the button was pressed on the previous pass through `loop()`, so the thud plays once per press and not continuously while the button is held down.

## Running it

1. Install the Arduino IDE.
2. In the Library Manager, install **Adafruit SSD1306** (also install its dependencies, including **Adafruit GFX Library**).
3. Open `cat_oled.ino`. Keep `cat_oled_bitmap.h` in the same folder.
4. Select **Tools > Board > Arduino Nano**, **Processor > ATmega328P** (use *Old Bootloader* if the upload fails), and your COM port.
5. If the screen stays blank, change the I2C address in `display.begin(...)` from `0x3C` to `0x3D`.
6. Upload.

## Files

- `cat_oled.ino`: the main sketch
- `cat_oled_bitmap.h`: the two image arrays (`cat_idle` and `cat_hit`)
- `cat_idle.png`, `cat_hit.png`: the source pictures

## Ideas for next

- A hit counter shown on the screen
- Make the cat react when the board is shaken, using the MPU-6050
