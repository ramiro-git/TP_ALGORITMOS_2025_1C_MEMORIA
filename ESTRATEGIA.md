# Estrategia del Juego de Cartas

## Estructuras de Datos Utilizadas

### 1. **Pila**
Utilizamos pilas para representar tanto el **mazo de cartas** como el **mazo de descarte**, ya que este tipo de estructura se adapta perfectamente a la lógica del juego. Las pilas funcionan bajo la política LIFO (Last In First Out), siendo ideales para:

- Mazo de cartas: Cuando se mezclan y colocan las cartas, el jugador o la IA "toman" la carta superior del mazo.
- Mazo de descarte: Al final de cada turno, las cartas jugadas se descartan, es decir, se colocan sobre la pila de descarte.

Esta lógica refleja de manera natural la dinámica física de un mazo de cartas real.

---

### 2. **Lista Simplemente Enlazada**
Para manejar el **ranking de jugadores**, utilizamos una lista simplemente enlazada, ordenada por cantidad de victorias. Esta estructura fue elegida por las siguientes razones:

- Permite inserciones ordenadas eficientes sin necesidad de recorrer y reorganizar un arreglo completo.
- Como solo necesitamos recorrerla hacia un lado, es mas eficiente que una lista doblemente enlazada u otras variantes, ya que permite una logica mucho mas simple y clara.

Los datos del ranking se obtienen de una API externa, y una vez obtenidos, se insertan en la lista de manera ordenada por cantidad de victorias obtenidas. Así, al mostrar el ranking, simplemente recorremos la lista desde el inicio.

---

## Estrategia del Juego

El juego está basado en una partida entre el jugador humano y una IA, donde cada uno juega una carta por turno. Cada carta tiene un **efecto específico** que puede alterar los puntos propios o del rival, o realizar alguna otra modificacion en el ritmo de la partida.

### Flujo General:
- Ambos jugadores comienzan con **0 puntos** y **3 cartas**.
- Cada jugador, en su respectivo turno, elige una carta de su mano para jugar.
- Al jugar una carta, esta se aplica (afecta puntos u otros efectos) y luego se apila en el mazo de descarte.
- El jugador que tiró una carta, levanta otra del mazo principal.
- En caso de que no queden cartas para levantar, se barajan todas las cartas del mazo de descarte y se apilan en el principal.
- El primero en alcanzar la **meta de puntos definida** es el ganador.

### IA:
La inteligencia artificial decide qué carta jugar, evaluando distintas condiciones segun el nivel de dificultad seleccionado:
- Facil: elige una carta aleatoria.
- Medio: evita jugadas inservibles.
- Dificil: elige la mejor jugada posible, segun un orden de prioridades predefinido.

### Estrategia:
- Se garantiza que las cartas se repartan de forma aleatoria, usando una función de mezcla al inicio de la partida.
- Cuando el mazo se vacía, se mezcla y reutiliza el mazo de descarte, lo cual imita el reciclaje de cartas en juegos reales.
- El uso de pilas facilita este intercambio dinámico entre el mazo principal y el descarte.

---

## Conclusión

Las estructuras de datos fueron seleccionadas con el objetivo de favorecer las mecánicas naturales del juego. Las pilas permiten manejar los mazos de manera ordenada y eficiente, mientras que la lista enlazada ofrece una solución flexible para mostrar el ranking actualizado y ordenado de forma muy sencilla.