// Problema 2: Cambio mínimo de monedas
#include <algorithm>
#include <functional>
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

//valor que representa cantidad imposible de formar
const int UNREACHABLE = numeric_limits<int>::max();

struct CoinChangeResult { // estructura que define los dos parámetros principales:
    vector<int> minCoinsTable; // mínimo de monedas usadas para formar a
    vector<int> lastCoinUsed; // última moneda usada en la solución óptima
};

CoinChangeResult buildCoinTable(const vector<int>& coins, int targetAmount) {
    CoinChangeResult result;
    result.minCoinsTable.assign(targetAmount + 1, UNREACHABLE);
    result.lastCoinUsed.assign(targetAmount + 1, 0);
    result.minCoinsTable[0] = 0;

    for (int amount = 1; amount <= targetAmount; ++amount) {
        for (int coin : coins) {
            if (coin > amount) continue;                        // la moneda no cabe en esta cantidad
            int previous = result.minCoinsTable[amount - coin];
            if (previous == UNREACHABLE) continue;              // el resto no se puede formar

            // Solo se actualiza con una mejora estricta; como las monedas llegan
            // ordenadas de mayor a menor, ante empates se prefiere la moneda más grande.
            if (previous + 1 < result.minCoinsTable[amount]) {
                result.minCoinsTable[amount] = previous + 1;
                result.lastCoinUsed[amount] = coin;             // se guarda para reconstruir la solución
            }
        }
    }
    return result;
}

vector<int> rebuildCombination(const CoinChangeResult& result, int targetAmount) {
    vector<int> combination;
    int remaining = targetAmount;
    while (remaining > 0) {
        int coin = result.lastCoinUsed[remaining];
        combination.push_back(coin);
        remaining -= coin;
    }
    return combination;
}

int main() {
    // límite de entrada
    const int MAX_AMOUNT = 1000000;

    int coinCount = readNumber<int>("Cantidad de denominaciones: ", 1, 1000);
    vector<int> coins(coinCount);

    cout << "Monedas (enteros positivos separados por espacio): ";
    for (int& coin : coins) {
        while (!(cin >> coin) || coin < 1) {
            cout << "  Entrada invalida, reingrese ese valor (entero >= 1): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    int targetAmount = readNumber<int>("Cantidad objetivo: ", 0, MAX_AMOUNT);

    // Se ordenan de mayor a menor y se eliminan repetidas (no aportan nada nuevo).
    sort(coins.begin(), coins.end(), greater<int>());
    coins.erase(unique(coins.begin(), coins.end()), coins.end());

    CoinChangeResult result = buildCoinTable(coins, targetAmount);

    if (result.minCoinsTable[targetAmount] == UNREACHABLE) {
        cout << "\nNo es posible formar la cantidad " << targetAmount
             << " con las monedas dadas.\n";
    } else {
        cout << "\nCantidad minima de monedas: " << result.minCoinsTable[targetAmount] << "\n";

        vector<int> combination = rebuildCombination(result, targetAmount);
        cout << "Combinacion: ";
        if (combination.empty()) cout << "(ninguna moneda)";
        for (size_t i = 0; i < combination.size(); ++i) {
            cout << combination[i] << (i + 1 < combination.size() ? " + " : "");
        }
        cout << "\n";
    }

    // La tabla se muestra siempre; las cantidades imposibles se marcan con INF.
    cout << "Tabla DP:\n[";
    for (size_t i = 0; i < result.minCoinsTable.size(); ++i) {
        if (result.minCoinsTable[i] == UNREACHABLE) cout << "INF";
        else cout << result.minCoinsTable[i];
        cout << (i + 1 < result.minCoinsTable.size() ? ", " : "");
    }
    cout << "]\n";
    return 0;
}