// Problema 1: Escaleras
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

// Lee un número de tipo T y vuelve a pedirlo hasta que sea válido y esté en [minimumValue, maximumValue].
template <typename T>
T readNumber(const string& prompt, T minimumValue, T maximumValue) {
    T value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minimumValue && value <= maximumValue) {
            return value;
        }
        cout << "  Entrada invalida. Debe ser un numero entre " << minimumValue
             << " y " << maximumValue << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');   // limpia y descarta ante entradas inválidas
    }
}

vector<unsigned long long> buildWaysTable(int stepCount) {
    vector<unsigned long long> waysTable(stepCount + 1);
    waysTable[0] = 1;
    if (stepCount >= 1) waysTable[1] = 1;

    // cada celda se calcula una sola vez reutilizando resultados ya guardados.
    for (int step = 2; step <= stepCount; ++step) {
        waysTable[step] = waysTable[step - 1] + waysTable[step - 2];
    }
    return waysTable;
}

// NOTA: Con N = 92 el resultado es el mayor que cabe en un entero sin signo de 64 bits; por eso ese es el límite de entrada.
int main() {
    const int MAX_STEPS = 92;
    int stepCount = readNumber<int>("Numero de escalones N (0-92): ", 0, MAX_STEPS);

    vector<unsigned long long> waysTable = buildWaysTable(stepCount);

    cout << "\nFormas posibles: " << waysTable[stepCount] << "\n";
    cout << "Tabla DP:\n[";
    for (size_t i = 0; i < waysTable.size(); ++i) {
        cout << waysTable[i] << (i + 1 < waysTable.size() ? ", " : "");
    }
    cout << "]\n";
    return 0;
}