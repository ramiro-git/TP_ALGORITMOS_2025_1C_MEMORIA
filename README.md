# DoCe - Juego de Cartas por Turnos

DoCe es un juego de estrategia y azar desarrollado en C, donde un jugador humano se enfrenta a una inteligencia artificial (IA) en una batalla por llegar a 12 puntos antes que su oponente. Cada jugador usa cartas con efectos especiales para sumar puntos, atacar al rival o ganar ventaja estratégica.

---

## Requisitos

- Se **asume que `curl` ya está instalado** en el sistema del usuario. El ejecutable no lo incluye ni lo descarga.
- El proyecto incluye el **código fuente de SDL**, pero **no viene preconfigurado ni vinculado al compilador**. El usuario debe compilarlo o configurarlo según su entorno.

---

## ¿Cómo jugar?

1. Ejecutá el programa.
2. Se mostrará un menú con tres opciones:

   - `[A] Jugar`
   - `[B] Ver ranking`
   - `[C] Salir`

3. Si elegís **Jugar**:

   - Ingresás tu nombre.
   - Seleccionás el nivel de dificultad de la IA:
     - Fácil
     - Medio
     - Difícil

4. Se reparten 3 cartas a cada jugador.
5. El que comienza se elige al azar.
6. En cada turno:

   - Jugás una carta de tu mano.
   - Robás una carta del mazo (si hay disponibles).
   - Se aplican los efectos (sumar, restar puntos, repetir turno, espejo, etc.).

7. Gana quien llega primero a 12 puntos.

---

## Tipos de cartas

- `+2 puntos`: Suma 2 puntos al jugador.
- `+1 punto`: Suma 1 punto al jugador.
- `-1 punto`: Resta 1 punto al oponente (si tiene puntos).
- `-2 puntos`: Resta 2 puntos al oponente (si tiene puntos).
- `Repetir turno`: Permite jugar otra carta en el mismo turno.
- `Espejo`: Anula el efecto negativo recibido y **devuelve el valor al oponente**.

> **Importante**: el efecto espejo, en caso de jugarse luego de una carta con efecto "sacar puntos", hace que el usuario sume(recupere) los puntos que habría perdido, y que se le descuenten al rival.

---

## Niveles de dificultad de la IA

- **Fácil**: Juega cartas al azar.
- **Medio**: Evita jugadas ineficaces y prioriza sumar puntos si está cerca de ganar.
- **Difícil**: Toma decisiones estratégicas. Si el jugador está por ganar, busca impedirlo.

---

## Visualización gráfica (SDL)

- El juego incluye una ventana generada con **SDL** para visualización.
- **No se debe interactuar con la ventana**, ya que **el juego se maneja exclusivamente por terminal**.
- La ventana está pensada solo como **complemento visual** del estado del juego.

---

## Archivos generados

- Al finalizar una partida, se guarda un informe en un archivo con nombre automático basado en la fecha y hora (ejemplo: `informe_2025-06-02_1530.txt`).
- También se actualiza un ranking general de ganadores.
- **Formato del informe**:  
  Se asume que primero se escriben todas las iteraciones turno por turno (tanto de la máquina como del humano), y que **al final del archivo**, justo **antes del salto de línea final (`\n`) por convención del `.txt`**, se escribe lo siguiente:
  1. Cuántos puntos obtuvo el humano.
  2. Cuántos puntos obtuvo la máquina.
  3. Quién ganó la partida.

---

## Configuración

Si querés modificar valores como la cantidad de cartas o puntos para ganar:

- Editá las constantes en el archivo `config.h` o dentro del archivo fuente principal (si no está separado).
- Ejemplo: `#define PUNTOS_PARA_GANAR 12`

---

## Pruebas

Ver el archivo `pruebas.md` para escenarios de prueba y resultados esperados.
