#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver();

#define BAZA     0
#define UMAR     1
#define COT      2
#define WRIST    3
#define GRIPPER  4

// pozitii initiale
int posBaza = 320;
int posUmar = 420;
int posCot = 370;
int posWrist = 320;
int posGrip = 320;

void smoothMove(uint8_t servo, int &currentPos, int targetPos, int viteza)
{
  if(currentPos < targetPos)
  {
    for(int i=currentPos; i<=targetPos; i++)
    {
      pca.setPWM(servo, 0, i);
      delay(viteza);
    }
  }
  else
  {
    for(int i=currentPos; i>=targetPos; i--)
    {
      pca.setPWM(servo, 0, i);
      delay(viteza);
    }
  }

  currentPos = targetPos;
}

void setup()
{
  Serial.begin(115200);

  pca.begin();
  pca.setPWMFreq(50);

  delay(2000);

  // pozitie initiala SAFE
  pca.setPWM(BAZA, 0, posBaza);
  pca.setPWM(UMAR, 0, posUmar);
  pca.setPWM(COT, 0, posCot);
  pca.setPWM(WRIST, 0, posWrist);
  pca.setPWM(GRIPPER, 0, posGrip);

  delay(3000);
}

void loop()
{
  // =========================
  // ROTIRE BAZA
  // =========================

  smoothMove(BAZA, posBaza, 220, 2);
  delay(700);

  smoothMove(BAZA, posBaza, 430, 2);
  delay(700);

  smoothMove(BAZA, posBaza, 320, 2);
  delay(700);

  // =========================
  // UMAR
  // =========================

  // ridica
  smoothMove(UMAR, posUmar, 520, 2);
  delay(1000);

  // coboara putin
  smoothMove(UMAR, posUmar, 390, 2);
  delay(1000);

  // =========================
  // COT
  // =========================

  // miscare mica safe
  smoothMove(COT, posCot, 430, 3);
  delay(1000);

  smoothMove(COT, posCot, 360, 3);
  delay(1000);

  // =========================
  // WRIST
  // =========================

  smoothMove(WRIST, posWrist, 430, 2);
  delay(700);

  smoothMove(WRIST, posWrist, 250, 2);
  delay(700);

  smoothMove(WRIST, posWrist, 320, 2);
  delay(700);

  // =========================
  // GRIPPER
  // =========================

  // deschide
  smoothMove(GRIPPER, posGrip, 520, 2);
  delay(1500);

  // inchide
  smoothMove(GRIPPER, posGrip, 220, 2);
  delay(1500);

  // =========================
  // REVENIRE SAFE
  // =========================

  smoothMove(UMAR, posUmar, 430, 2);
  delay(500);

  smoothMove(COT, posCot, 370, 3);
  delay(500);

  smoothMove(WRIST, posWrist, 320, 2);
  delay(500);

  delay(3000);
}
