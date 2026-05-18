# ⚖️ OLEDPesa

Repositorio para el sistema de báscula de 4 celdas de carga utilizando **Arduino Mega 2560**, módulos **HX711** y un **LCD Keypad Shield**.

---

## 📌 Historial del Proyecto

* **27 Dic 2025:** Creación inicial del repositorio.
* **12 Abr 2026:** Adición del sistema de escala y pruebas individuales de sensores (uno a uno).
* **Último cambio:** Local, hace 2 días.

---

## 🔌 Conexión de las Celdas de Carga (HX711)

Configuración del cableado del puente de Wheatstone hacia los módulos de pesaje:

* **E+** 🔴 Rojo
* **E-** ⚫ Negro
* **A-** ⚪ Blanco
* **A+** 🟢 Verde

---

## 📊 Registro de Calibración de Sensores

Distribución física de los sensores en la tarima base, hilos asignados en el bus RJ45, pines digitales en el Arduino Mega y valores crudos de referencia con un peso patrón de 10 kg:

| Posición | Sensor | Color Cable (RJ45) | Pin Arduino Mega | Rango de Valor Crudo (10 kg) |
| :--- | :---: | :--- | :---: | :---: |
| **Arriba Izquierda** | 1 | Verde | Pin 24 | `2154` a `2162` |
| **Arriba Derecha** | 2 | Café | Pin 25 | `2090` a `2111` |
| **Abajo Derecha** | 3 | Azul | Pin 26 | `2095` a `2105` |
| **Abajo Izquierda** | 4 | Blanco Azul | Pin 27 | `2121` a `2125` |

> *Nota: El pin de reloj (SCK) está unificado y compartido en el pin **22** para optimizar el bus del cable de red.*

---

## 📝 Próximos Pasos / Ajustes Físicos
- [x] Corrección y remapeo de pines digitales del bloque central (24 al 27).
- [ ] Calibración final considerando el peso muerto de la estructura (fierro y base de madera de la tarima).
