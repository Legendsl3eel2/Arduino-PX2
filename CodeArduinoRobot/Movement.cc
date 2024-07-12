#include "ModelNanoPlus.h"
#include "Servo.h"

#define PS2_DAT  14 // ต่อขา DATA กับขาพอร์ต 14
#define PS2_CMD  15 // ต่อขา COMMAND กับขาพอร์ต 16
#define PS2_SEL  16  // ต่อขา SELECT กับขาพอร์ต 2
#define PS2_CLK 17   // ต่อขา CLOCK กับขาพอร์ต 3

PS2X ps2x;  // ประกาศตัวแปรสำหรับจอยสติ๊ก PS2

void setup() {
  servo(1, 0);
  servo(2, 0);
  servo(3, 0);
  XIO();
  delay(1000);     // หน่วงเวลา 1 วินาทีเพื่อรอให้บอร์ดพร้อมทำงาน
  oledClear();     // เคลียร์ภาพทั้งหมดบนหน้าจอแสดงผล
  oledMode(0);     // กำหนดให้หน้าจอแสดงผลเป็นแนวนอน
  setTextSize(1);  // กำหนดขนาดตัวหนังสือ

  while (true)  // วนการทำงานเพื่อรอการเชื่อมต่อกับจอยสติ๊ก
  {
    // กำหนดขาเชื่อมต่อกับจอยสติ๊ก โดยมีการเก็บค่าที่ส่งกลับมาเป็น Integer เพื่อรู้ได้ว่า เชื่อมต่อได้หรือไม่
    int error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, false, false);
    if (error == 0)  // กรณีที่เชื่อมต่อได้ Error = 0
    {
      oled(0, 0, "Connected");  // แสดงข้อความว่าเชื่อมต่อกับจอยสติ๊กเรียบร้อยแล้ว
      break;                    // ออกจาก while(true)
    } else {
      oled(0, 0, "Connecting");  // แสดงข้อความเพื่อแจ้งว่า กำลังเชื่อมต่อกับจอยสติ๊ก
    }
    delay(500);  // หน่วงเวลา 500 มิลลิวินาทีเพื่อรอการเชื่อมต่อครั้งต่อไปในกรณีที่เชื่อมต่อไม่สำเร็จ
  }
}



void loop() {
  ps2x.read_gamepad(false, false);  // อ่านข้อมูลจากจอยสติ๊ก
  control();
  servo_control();
}

void control() {
  if (ps2x.Button(PSB_PAD_UP)) {
    oled(30, 30, "Forward");
    motor(1, 100);
    motor(2, 100);
  } else if (ps2x.Button(PSB_PAD_RIGHT)) {
    oled(30, 30, "Right");
    motor(1, -100);
    motor(2, 100);
  } else if (ps2x.Button(PSB_PAD_LEFT)) {
    oled(30, 30, "Left");
    motor(1, 100);
    motor(2, -100);
  } else if (ps2x.Button(PSB_PAD_DOWN)) {
    oled(30, 30, "Backward");
    motor(1, -100);
    motor(2, -100);
  } else {
    oled(30, 30, "Not moving");
    motor(1, 0);
    motor(2, 0);
  }
}

void servo_control() {
  if (ps2x.Button(PSB_R1)) {
    Serial.println("R1 pressed");
    servo(2, 180);
  } else {
    servo(2, 0);
  }
  if (ps2x.Button(PSB_L1)) {
    Serial.println("L1 pressed");
    servo(1, 90);
  } else {
    servo(1, 0);
  }
  if (ps2x.Button(PSB_L2)) {
    Serial.println("L2 pressed");
    servo(3, 45);
  } else {
    servo(3, 0);
  }
}
