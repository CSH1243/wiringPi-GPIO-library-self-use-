#include <stdio.h>
#include <wiringPi.h>

#define PUL_PIN1 1
#define DIR_PIN1 2
#define PUL_PIN2 3
#define DIR_PIN2 4
#define PUL_PIN3 5
#define DIR_PIN3 6
#define SWITCH_PIN 7
#define LED_PIN 8

 pinMode(PUL_PIN1, OUTPUT);
 pinMode(DIR_PIN1, OUTPUT);
 pinMode(PUL_PIN2, OUTPUT);
 pinMode(DIR_PIN2, OUTPUT);

int main() {
    if (wiringPiSetup() == -1) {
        fprintf(stderr, "无法初始化 WiringPi\n");
        return 1;
    }

    pinMode(LED_PIN, OUTPUT);
    pinMode(SWITCH_PIN, INPUT);

    for (int i = 0; i < NUM_MOTORS; i++) {
        pinMode(PUL_PINS[i], OUTPUT);
        pinMode(DIR_PINS[i], OUTPUT);
    }

    while (1) {
        int switchState = digitalRead(SWITCH_PIN);

        if (switchState == LOW) {
            // 停止所有电机运动
            for (int i = 0; i < NUM_MOTORS; i++) {
                digitalWrite(PUL_PINS[i], LOW);
            }

            // 点亮LED
            digitalWrite(LED_PIN, HIGH);
        } else {
            // 启动电机运动
            digitalWrite(LED_PIN, LOW);

            // 设置方向（根据需要设置高或低）
            for (int i = 0; i < NUM_MOTORS; i++) {
                digitalWrite(DIR_PINS[i], HIGH);  // 或 LOW，根据电机运动方向设置
            }

            // 发送脉冲信号，控制电机运动
            for (int i = 0; i < NUM_MOTORS; i++) {
                digitalWrite(PUL_PINS[i], HIGH);
                delay(1);  // 调整脉冲的宽度和速度
                digitalWrite(PUL_PINS[i], LOW);
                delay(1);
            }
        }
    }

    return 0;
}