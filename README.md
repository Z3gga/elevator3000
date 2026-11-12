# Elevator3000

Juego de reflejos con un **ascensor impreso en 3D**. Mueves el ascensor con un joystick, y unos LEDs te indican a qué piso(s) debes llegar antes de que se acabe el tiempo. Hecho con Arduino/ESP y modelado en Autodesk Inventor.

## Cómo funciona

1. Se enciende una combinación aleatoria de LEDs (hay 6 posibles, con 3 pisos).
2. Con el joystick subes o bajas el ascensor (motor con control de velocidad por PWM).
3. A los **3 segundos** se revisan los sensores:
   - **Acierto:** se apagan los LEDs, pausa de 1 s y empieza una nueva ronda.
   - **Error:** los LEDs parpadean 5 veces y se repite con una nueva combinación.

## Conexiones (`CODIGO_FINAL.ino`)

| Función | Pin (GPIO) | Etiqueta en placa |
|---|---|---|
| Motor subir | 13 | D7 |
| Motor bajar | 12 | D6 |
| Motor ENA (PWM) | 3 | RX |
| LED 1 / 2 / 3 | 0 / 2 / 15 | D3 / D4 / D8 |
| Sensor 1 / 2 / 3 | 4 / 14 / 5 | D1 / D2 / D5 |
| Joystick | A0 | A0 |

Los sensores usan `INPUT_PULLUP` (se activan en `LOW`).

## Estructura

```
CODIGO_FINAL/     # Código final del juego (el que hay que cargar)
CODIGO_2.0/       # Versión anterior, con salida por Serial (LED/JOY) para Unity
LEDS/             # Prueba de LEDs aleatorios
Unity/            # Pruebas de joystick/motor y esquemas (layout.png, schematic.png)
Imprimir/         # Piezas listas para imprimir (.stl) y sus archivos Inventor (.ipt)
Modelar/          # Modelos de trabajo, incluye .stl y .3mf
Alto/, TEST.stl   # Piezas sueltas
TRALRULIMERO TRUDRILLO.iam   # Ensamblaje en Inventor
```

> Los archivos `.ipt` y `.iam` son de Autodesk Inventor. Si abres el ensamblaje, mantén la estructura de carpetas para que encuentre las piezas.

## Cómo usarlo

1. Abre `CODIGO_FINAL/CODIGO_FINAL.ino` en el Arduino IDE.
2. Selecciona tu placa y puerto, y súbelo.
3. Imprime las piezas de `Imprimir/` (los `.stl`) y arma el ascensor con motor, sensores, LEDs y joystick según la tabla de conexiones.

## Notas

- Los archivos G-code y las versiones automáticas de Inventor (`OldVersions/`) no se incluyen en el repositorio.
