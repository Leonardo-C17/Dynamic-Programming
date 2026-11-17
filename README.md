# Dynamic-Programming

Actividad 08: Programación Dinámica (PD). El repositorio contiene dos programas en C++ independientes, uno por problema:

| Archivo | Problema |
|---|---|
| `stairs.cpp` | Escaleras |
| `coins.cpp` | Cambio mínimo de monedas |

## Requisitos

- Un compilador de C++ con soporte para C++17 (por ejemplo, `g++` o `clang++`).
- Una terminal abierta en la carpeta del repositorio.

## Compilación y ejecución

**Escaleras**

```bash
g++ -std=c++17 -o stairs stairs.cpp
./stairs
```

**Cambio mínimo de monedas**

```bash
g++ -std=c++17 -o coins coins.cpp
./coins
```

En Windows, el ejecutable se llama con `stairs.exe` y `coins.exe`.

## Uso

Cada programa pide sus datos por consola y valida la entrada: si se ingresa un valor no numérico o fuera de rango, lo vuelve a solicitar.

### Escaleras

Dato solicitado: el número de escalones N (entero entre 0 y 92; con valores mayores el resultado no cabe en un entero de 64 bits).

Entrada de ejemplo:

```
Numero de escalones N (0-92): 5
```

Salida:

```
Formas posibles: 8
Tabla DP:
[1, 1, 2, 3, 5, 8]
```

### Cambio mínimo de monedas

Datos solicitados: la cantidad de denominaciones (tipos de moneda), las denominaciones (enteros positivos separados por espacio, en cualquier orden y pueden repetirse) y la cantidad objetivo (entre 0 y 1 000 000).

Entrada de ejemplo:

```
Cantidad de denominaciones: 3
Monedas (enteros positivos separados por espacio): 1 3 4
Cantidad objetivo: 6
```

Salida:

```
Cantidad minima de monedas: 2
Combinacion: 3 + 3
Tabla DP:
[0, 1, 2, 1, 1, 2, 2]
```

Si la cantidad no se puede formar con las monedas dadas, el programa lo indica y marca esas posiciones con `INF` en la tabla.

## Estrategia de Programación Dinámica utilizada (también incluida en el documento de presentación)

### Escaleras

Para llegar al escalón `i` solo hay dos posibilidades: venir del escalón `i-1` con un paso de 1, o del escalón `i-2` con un paso de 2. Por eso `ways[i] = ways[i-1] + ways[i-2]`, con los casos base `ways[0] = 1` y `ways[1] = 1`. La tabla se llena de menor a mayor (tabulación), de modo que cada valor se calcula una sola vez y se reutiliza, en lugar de recalcularlo como haría una recursión directa. La tabla resultante coincide con la sucesión de Fibonacci.

Complejidad: O(N) en tiempo y O(N) en espacio.

### Cambio mínimo de monedas

Se define `minCoins[a]` como el mínimo de monedas necesarias para formar exactamente la cantidad `a`. Para cada cantidad se prueba cada moneda `c` que quepa y se toma la mejor opción: `minCoins[a] = 1 + min(minCoins[a - c])`, con el caso base `minCoins[0] = 0`. La tabla se llena de menor a mayor y, en paralelo, se guarda la última moneda usada en cada cantidad para reconstruir una combinación válida retrocediendo desde la cantidad objetivo. Una estrategia voraz no sirve aquí: con monedas [1, 3, 4] y cantidad 6 daría 4 + 1 + 1 (3 monedas), pero el óptimo es 3 + 3 (2 monedas).

Complejidad: O(k log k + A · k) en tiempo y O(A) en espacio, donde `k` es el número de denominaciones y `A` la cantidad objetivo.