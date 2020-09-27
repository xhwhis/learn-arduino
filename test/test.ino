#include <Wire.h>
#include <LiquidCrystal.h>
#include <paj7620.h>
#include <Keyboard.h>

#define GES_REACTION_TIME 500
#define GES_ENTRY_TIME 800
#define GES_QUIT_TIME 1000

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
    lcd.begin(16, 2);
    uint8_t error = 0;
    error = paj7620Init();
    if (error) {
        lcd.print("INIT ERROR");
    } else {
        lcd.print("INIT OK");
    }
    pinMode(2, INPUT_PULLUP);
    Keyboard.begin();
}

void loop() {
    lcd.setCursor(0, 1);
    uint8_t data = 0, data1 = 0, error;
    error = paj7620ReadReg(0x43, 1, &data);
    if (!error) {
        switch (data) {
            case GES_RIGHT_FLAG: {
                delay(GES_ENTRY_TIME);
                paj7620ReadReg(0x43, 1, &data);
                if (data == GES_FORWARD_FLAG) {
                    lcd.print("Forward");
                    delay(GES_QUIT_TIME);
                } else if (data == GES_BACKWARD_FLAG) {
                    lcd.print("Backward");
                    delay(GES_QUIT_TIME);
                } else {
                    lcd.print("-->");
                    Keyboard.press(KEY_LEFT_CTRL);
                    Keyboard.press(KEY_LEFT_ALT);
                    Keyboard.press(KEY_RIGHT_ARROW);
                    Keyboard.releaseAll();
            } break;
            case GES_LEFT_FLAG: {
                delay(GES_ENTRY_TIME);
                }
                paj7620ReadReg(0x43, 1, &data);
                if (data == GES_FORWARD_FLAG) {
                    lcd.print("Forward");
                    delay(GES_QUIT_TIME);
                } else if (data == GES_BACKWARD_FLAG) {
                    lcd.print("Backward");
                    delay(GES_QUIT_TIME);
                } else {
                    lcd.print("<--");
                    Keyboard.press(KEY_LEFT_CTRL);
                    Keyboard.press(KEY_LEFT_ALT);
                    Keyboard.press(KEY_LEFT_ARROW);
                    Keyboard.releaseAll();
                }
            } break;
            case GES_UP_FLAG: {
                delay(GES_ENTRY_TIME);
                paj7620ReadReg(0x43, 1, &data);
                if (data == GES_FORWARD_FLAG) {
                    lcd.print("Forward");
                    delay(GES_QUIT_TIME);
                } else if (data == GES_BACKWARD_FLAG) {
                    lcd.print("Backward");
                    delay(GES_QUIT_TIME);
                } else {
                    lcd.print("Up");
                    Keyboard.press(KEY_UP_ARROW);
                    Keyboard.press(KEY_UP_ARROW);
                    Keyboard.press(KEY_UP_ARROW);
                    Keyboard.releaseAll();
                }
            } break;
            case GES_DOWN_FLAG: {
                delay(GES_ENTRY_TIME);
                paj7620ReadReg(0x43, 1, &data);
                if (data == GES_FORWARD_FLAG) {
                    lcd.print("Forward");
                    delay(GES_QUIT_TIME);
                } else if (data == GES_BACKWARD_FLAG) {
                    lcd.print("Backward");
                    delay(GES_QUIT_TIME);
                } else {
                    lcd.print("Down");
                    Keyboard.press(KEY_DOWN_ARROW);
                    Keyboard.press(KEY_DOWN_ARROW);
                    Keyboard.press(KEY_DOWN_ARROW);
                    Keyboard.releaseAll();
                }
            } break;
            case GES_FORWARD_FLAG: {
                lcd.print("Forward");
                Keyboard.press(KEY_LEFT_CTRL);
                Keyboard.press(KEY_LEFT_ALT);
                Keyboard.press('p');
                Keyboard.releaseAll();
                delay(GES_QUIT_TIME);
            } break;
            case GES_BACKWARD_FLAG: {
                lcd.print("Backward");
                delay(GES_QUIT_TIME);
            } break;
            case GES_CLOCKWISE_FLAG: {
                lcd.print("Clockwise");
                //Keyboard.press(KEY_F5);
                //Keyboard.releaseAll();
            } break;
            case GES_COUNT_CLOCKWISE_FLAG: {
                lcd.print("anti-clockwise");
            } break;
            default: {
                paj7620ReadReg(0x44, 1, &data1);
                if (data1 == GES_WAVE_FLAG) {
                    lcd.print("wave");
                }
            } break;
        }
    }
    delay(100);
}
