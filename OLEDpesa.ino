#include <LiquidCrystal.h>
#include "HX711.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Tus pines corregidos
const int PIN_SCK = 22; 
const int DT1 = 24;     
const int DT2 = 25;     
const int DT3 = 26;     
const int DT4 = 27;     

HX711 s1, s2, s3, s4;
int sensorActual = 1; // Variable para saber qué sensor ver

// ... (Tus definiciones iniciales igual)

void setup() {
  lcd.begin(16, 2);
  s1.begin(DT1, PIN_SCK); s2.begin(DT2, PIN_SCK);
  s3.begin(DT3, PIN_SCK); s4.begin(DT4, PIN_SCK);

  // Configuramos las escalas una sola vez aquí
  s1.set_scale(215.8); s2.set_scale(210.0);
  s3.set_scale(210.0); s4.set_scale(212.3);

  lcd.print("Bascula Lista");
  delay(1500);
}

void loop() {
  int boton = analogRead(A0);
  
  // Navegación (DERECHA / IZQUIERDA)
  if (boton < 100) { 
    sensorActual++;
    if (sensorActual > 5) sensorActual = 1;
    lcd.clear(); // Limpiamos al cambiar de modo
    delay(300); 
  } 
  else if (boton < 600 && boton > 400) { 
    sensorActual--;
    if (sensorActual < 1) sensorActual = 5;
    lcd.clear();
    delay(300);
  }

  // Lógica de visualización
  if (sensorActual <= 4) {
    // MODO DIAGNÓSTICO (Sensores individuales)
    lcd.setCursor(0, 0);
    lcd.print("Sensor Indiv: "); lcd.print(sensorActual);
    lcd.setCursor(0, 1);
    
    long valorCrudo = 0;
    // Usamos una lectura rápida para diagnóstico
    if (sensorActual == 1 && s1.is_ready()) valorCrudo = s1.get_value(1);
    else if (sensorActual == 2 && s2.is_ready()) valorCrudo = s2.get_value(1);
    else if (sensorActual == 3 && s3.is_ready()) valorCrudo = s3.get_value(1);
    else if (sensorActual == 4 && s4.is_ready()) valorCrudo = s4.get_value(1);
    
    lcd.print("Raw/100: "); lcd.print(valorCrudo / 100);
    lcd.print("      "); // Limpia caracteres sobrantes
  } 
  else {
    // MODO BÁSCULA TOTAL (Case 5)
    if (s1.is_ready() && s2.is_ready() && s3.is_ready() && s4.is_ready()) {
      float total = s1.get_units(2) + s2.get_units(2) + s3.get_units(2) + s4.get_units(2);
      
      lcd.setCursor(0, 0);
      lcd.print("PESO TOTAL:     ");
      lcd.setCursor(0, 1);
      lcd.print(total, 2); lcd.print(" kg      ");

      // Botón SELECT para TARA (Solo en modo total)
      if (boton < 800 && boton > 600) {
        lcd.setCursor(0, 1);
        lcd.print("Ajustando Cero..");
        s1.tare(); s2.tare(); s3.tare(); s4.tare();
      }
    } else {
      lcd.setCursor(0,0);
      lcd.print("ERROR CONEXION");
    }
  }
  delay(100); 
}
