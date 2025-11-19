#include <iostream>
#include <limits>
#include "Funciones.h"
using namespace std;

int leerEntero(string mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << " Entrada invalida. Ingrese un numero.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
    }
}

string leerTexto(string mensaje) {
    string texto;
    cout << mensaje;
    getline(cin, texto);
    return texto;
}
