#include <Arduino.h>
#include <OBD2.h>
#include <LiquidCrystal.h>
#include <Chrono.h>

const int rs = 16, en = 19, d0 = 2, d1 = 3, d2 = 4, d3 = 5, d4 = 6, d5 = 7, d6 = 8, d7 = 9;
LiquidCrystal lcd(rs, en, d0, d1, d2, d3, d4, d5, d6, d7);
char buffer[10];

int obdFuel = 3;
int obdCoolant = 5;
int obdRPM = 12;
int obdSpeed = 13;
int obdIntakeAirTemp = 15;
int obdMAF = 16;
int obdBarometricPressure = 51;
int obdCatalystTemp1 = 60;
int obdCatalystTemp2 = 62;
int obdVoltage = 66;
int obdAmbientAirTemp = 70;
int obdOilTemp = 92;

int Fuel;
int Coolant;
int RPM;
int IntakeAirTemp;
int MAF;
int BarometricPressure;
int CatalystTemp1;
int CatalystTemp2;
int Voltage;
int AmbientAirTemp;
int OilTemp;
float Speed;
float lastSpeed;

Chrono chrono;
int elapsed;
int acceleration;

int OBDidRead = 0;

void lcdStartScreen()
{
    int delayAnimation = 100;
    lcd.setCursor(0, 0);
    lcd.print("--------------------");
    lcd.setCursor(0, 1);
    lcd.print("|                  |");
    lcd.setCursor(0, 2);
    lcd.print("|                  |");
    lcd.setCursor(0, 3);
    lcd.print("--------------------");

    lcd.setCursor(8, 1);
    delay(500);
    lcd.print("T");
    delay(delayAnimation);
    lcd.print("O");
    delay(delayAnimation);
    lcd.print("Y");
    delay(delayAnimation);
    lcd.print("O");
    delay(delayAnimation);
    lcd.print("T");
    delay(delayAnimation);
    lcd.print("A");

    lcd.setCursor(8, 1);
    delay(1000);
    lcd.print(" ");
    delay(delayAnimation);
    lcd.print(" ");
    delay(delayAnimation);
    lcd.print(" ");
    delay(delayAnimation);
    lcd.print(" ");
    delay(delayAnimation);
    lcd.print(" ");
    delay(delayAnimation);
    lcd.print(" ");
}

void lcdStartScreen2()
{
    int delayAnimation = 50;
    lcd.setCursor(0, 0);
    lcd.print("--------------------");
    lcd.setCursor(0, 1);
    lcd.print("|                  |");
    lcd.setCursor(0, 2);
    lcd.print("|                  |");
    lcd.setCursor(0, 3);
    lcd.print("--------------------");

    lcd.setCursor(1, 1);
    delay(500);
    lcd.print("W");
    delay(delayAnimation);
    lcd.print("e");
    delay(delayAnimation);
    lcd.print("l");
    delay(delayAnimation);
    lcd.print("c");
    delay(delayAnimation);
    lcd.print("o");
    delay(delayAnimation);
    lcd.print("m");
    delay(delayAnimation);
    lcd.print("e");
    delay(delayAnimation);
    lcd.print(" ");
    delay(delayAnimation);
    lcd.print("G");
    delay(delayAnimation);
    lcd.print("i");
    delay(delayAnimation);
    lcd.print("a");
    delay(delayAnimation);
    lcd.print("n");
    delay(delayAnimation);
    lcd.print("m");
    delay(delayAnimation);
    lcd.print("a");
    delay(delayAnimation);
    lcd.print("r");
    delay(delayAnimation);
    lcd.print("c");
    delay(delayAnimation);
    lcd.print("o");
    delay(delayAnimation);
    lcd.print("!");

    lcd.setCursor(1, 1);
    delay(1000);
    delay(delayAnimation);
    lcd.print(" ");
    delay(delayAnimation);
    lcd.print(" ");
    delay(delayAnimation);
    lcd.print(" ");
    delay(delayAnimation);
    lcd.print(" ");
    delay(delayAnimation);
    lcd.print(" ");
    delay(delayAnimation);
    lcd.print(" ");
    delay(delayAnimation);
    lcd.print(" ");
    delay(delayAnimation);
    lcd.print(" ");
    delay(delayAnimation);
    lcd.print(" ");
    delay(delayAnimation);
    lcd.print(" ");
    delay(delayAnimation);
    lcd.print(" ");
    delay(delayAnimation);
    lcd.print(" ");
    delay(delayAnimation);
    lcd.print(" ");
    delay(delayAnimation);
    lcd.print(" ");
    delay(delayAnimation);
    lcd.print(" ");
    delay(delayAnimation);
    lcd.print(" ");
    delay(delayAnimation);
    lcd.print(" ");
    delay(delayAnimation);
    lcd.print(" ");
}

void lcdInit()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Speed:    |Acc:");
    lcd.setCursor(0, 1);
    lcd.print("A/in:     |MAF:");
    lcd.setCursor(0, 2);
    lcd.print("Cool:     |Baro:");
    lcd.setCursor(0, 3);
    lcd.print("Oil:      |Cat:");
}

void setup()
{
    Serial.begin(9600);
    lcd.begin(20, 4);
    lcd.clear();
    lcdStartScreen();
    lcdStartScreen2();

    Serial.println("Toyota Yaris - OBD2 CAN bus");

    while (true)
    {
        Serial.print("Connessione... ");
        if (!OBD2.begin())
        {
            Serial.println("fallito!");
            delay(500);
        }
        else
        {
            Serial.println("successo!");
            break;
        }
    }
    lcdInit();
}

void obdRead()
{
    switch (OBDidRead)
    {
    case 0:
        Coolant = OBD2.pidRead(obdCoolant);
        break;

    case 1:
        IntakeAirTemp = OBD2.pidRead(obdIntakeAirTemp);
        break;

    case 2:
        MAF = OBD2.pidRead(obdMAF);
        break;

    case 3:
        BarometricPressure = OBD2.pidRead(obdBarometricPressure);
        break;

    case 4:
        CatalystTemp1 = OBD2.pidRead(obdCatalystTemp1);
        break;

    case 5:
        OilTemp = OBD2.pidRead(obdOilTemp);
        break;

    default:
        OBDidRead = 0;
        break;
    }

    OBDidRead++;

    // Speed = OBD2.pidRead(obdSpeed);
    // CatalystTemp2 = OBD2.pidRead(obdCatalystTemp2);
    // AmbientAirTemp = OBD2.pidRead(obdAmbientAirTemp);
    // Fuel = OBD2.pidRead(obdFuel);
    // RPM = OBD2.pidRead(obdRPM);
    // Voltage = OBD2.pidRead(obdVoltage);
}

void accelerationCalc()
{
    delay(100);
    Speed = OBD2.pidRead(obdSpeed);
    elapsed = chrono.elapsed();
    acceleration = ((Speed * 1000) - (lastSpeed * 1000)) / elapsed;
    lastSpeed = Speed;
    chrono.restart();
}

String formatInt(float data)
{
    sprintf(buffer, "%3d", (int)data);
    return buffer;
}

void lcdData()
{
    lcd.setCursor(6, 0);
    lcd.print(formatInt(Speed));

    lcd.setCursor(6, 1);
    lcd.print(formatInt(IntakeAirTemp));

    lcd.setCursor(6, 2);
    lcd.print(formatInt(Coolant));

    lcd.setCursor(6, 3);
    lcd.print(formatInt(OilTemp));

    lcd.setCursor(17, 0);
    accelerationCalc();
    lcd.print(formatInt(acceleration));

    lcd.setCursor(17, 1);
    lcd.print(formatInt(MAF));

    lcd.setCursor(17, 2);
    lcd.print(formatInt(BarometricPressure));

    lcd.setCursor(17, 3);
    lcd.print(formatInt(CatalystTemp1));
}

void loop()
{
    obdRead();
    lcdData();
    Serial.println("loop");
}