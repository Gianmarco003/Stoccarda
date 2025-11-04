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
int RPM = -1;
int IntakeAirTemp;
int MAF;
int BarometricPressure;
int CatalystTemp1 = 0;
int CatalystTemp2;
float Voltage;
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
    lcd.print("Speed:    |Bat:");
    lcd.setCursor(0, 1);
    lcd.print("A/in:     |MAF:");
    lcd.setCursor(0, 2);
    lcd.print("Cool:     |Baro:");
    lcd.setCursor(0, 3);
    lcd.print("Oil:      |Cat:");
}

void accelerationCalc()
{
    Speed = OBD2.pidRead(obdSpeed);
    elapsed = chrono.elapsed();
    acceleration = ((Speed * 10000) - (lastSpeed * 10000)) / elapsed;
    lastSpeed = Speed;
    chrono.restart();
}

void obdRead()
{
    switch (OBDidRead)
    {
    case 0:
        Coolant = OBD2.pidRead(obdCoolant);
        IntakeAirTemp = OBD2.pidRead(obdIntakeAirTemp);
        MAF = OBD2.pidRead(obdMAF);
        BarometricPressure = OBD2.pidRead(obdBarometricPressure);
        OilTemp = OBD2.pidRead(obdOilTemp);
        Voltage = OBD2.pidRead(obdVoltage);

    case 1:
        Coolant = OBD2.pidRead(obdCoolant);
        break;

    case 2:
        IntakeAirTemp = OBD2.pidRead(obdIntakeAirTemp);
        break;

    case 3:
        MAF = OBD2.pidRead(obdMAF);
        break;

    case 4:
        BarometricPressure = OBD2.pidRead(obdBarometricPressure);
        break;

    case 5:
        if (OBD2.pidRead(obdRPM) > 0 && RPM == -1)
        {
            RPM = 0;
        }
        if (RPM >= 0)
        {
            CatalystTemp1 = OBD2.pidRead(obdCatalystTemp1);
        }
        break;

    case 6:
        OilTemp = OBD2.pidRead(obdOilTemp);
        break;
    case 7:
        Voltage = OBD2.pidRead(obdVoltage);
        break;
    case 8:
        Speed = OBD2.pidRead(obdSpeed);
        break;

    default:
        OBDidRead = 0;
        break;
    }

    OBDidRead++;

    // CatalystTemp2 = OBD2.pidRead(obdCatalystTemp2);
    // AmbientAirTemp = OBD2.pidRead(obdAmbientAirTemp);
    // Fuel = OBD2.pidRead(obdFuel);
    // RPM = OBD2.pidRead(obdRPM);
}

String formatInt(float data)
{
    sprintf(buffer, "%4d", (int)data);
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

    lcd.setCursor(15, 0);
    lcd.print(Voltage);

    lcd.setCursor(16, 1);
    lcd.print(formatInt(MAF));

    lcd.setCursor(16, 2);
    lcd.print(formatInt(BarometricPressure));

    lcd.setCursor(16, 3);
    lcd.print(formatInt(CatalystTemp1));
}

void serialData()
{
    Serial.print(">");

    Serial.print("Speed: ");
    Serial.print(Speed);
    Serial.print(", ");

    Serial.print("Intake: ");
    Serial.print(IntakeAirTemp);
    Serial.print(", ");

    Serial.print("Coolant: ");
    Serial.print(Coolant);
    Serial.print(", ");

    Serial.print("Oil: ");
    Serial.print(OilTemp);
    Serial.print(", ");

    Serial.print("Battery: ");
    Serial.print(Voltage);
    Serial.print(", ");

    Serial.print("MAF: ");
    Serial.print(MAF);
    Serial.print(", ");

    Serial.print("Pressure: ");
    Serial.print(BarometricPressure);
    Serial.print(", ");

    Serial.print("Catalyst: ");
    Serial.print(CatalystTemp1);
    Serial.println();
}

void setup()
{
    Serial.begin(115200);
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

void loop()
{
    obdRead();
    lcdData();
    serialData();
    delay(100);
}
