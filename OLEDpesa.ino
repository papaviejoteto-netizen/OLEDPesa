#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "HX711.h"

#define SCREEN_WIDTH 128 // Ancho de la pantalla OLED
#define SCREEN_HEIGHT 64 // Alto de la pantalla OLED
#define OLED_RESET -1 // Pin de reset (usa -1 si está conectado a VCC)

#define DT 2
#define SCK 3

#define DT1 4
#define SCK1 5

#define DT2 6
#define SCK2 7

#define DT3 8
#define SCK3 9

HX711 balanza1;
HX711 balanza2;
/*
HX711 balanza3;
HX711 balanza4;
*/
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  balanza1.begin(DT, SCK);
  balanza2.begin(DT1, SCK1);

  float escala = 211.78;

  balanza1.set_scale(escala); // Opcional, pero util para limpiar cualquier escala previa
  balanza1.tare(20);    // Tarea la balanza (pone el peso en cero) con 20 lecturas para mayor precision

  balanza2.set_scale(escala); // Opcional, pero util para limpiar cualquier escala previa
  balanza2.tare(20);    // Tarea la balanza (pone el peso en cero) con 20 lecturas para mayor precision
/*
  balanza1.set_scale(); // Opcional, pero util para limpiar cualquier escala previa
  balanza1.tare(20);    // Tarea la balanza (pone el peso en cero) con 20 lecturas para mayor precision

  balanza3.begin(DT2, SCK2);
  balanza4.begin(DT3, SCK3);
  */
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Dirección I2C del OLED
    Serial.println(F("Error al iniciar la pantalla OLED"));
    for(;;); // No continuar
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Balanza toritos");
  display.display();
}

void loop() {
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Toro Read valor . ..");

    float rpeso = balanza1.get_units(5)/100;
    float rpeso2 = balanza2.get_units(5)/100; 
    display.setCursor(0,8);
    display.println("read = ");
    display.setCursor(0,16);
    display.println(rpeso);
    display.setCursor(0,24);
    display.println(rpeso2);
    display.display();
    delay(500);
/*
    display.setCursor(0,16);
    display.println(balanza2.get_units(), 2); // Muestra el peso con dos decimales

    balanza3.set_scale(2280.f); // Ajusta este valor según tu calibración
    balanza3.tare(); // Pone la balanza a cero

    display.setCursor(0, 24);
    display.println(balanza3.get_units(), 2);

    balanza4.set_scale(2280.f); // Ajusta este valor según tu calibración
    balanza4.tare(); // Pone la balanza a cero

    display.setCursor(0, 30);
    display.println(balanza4.get_units(), 2);
*/
  

}