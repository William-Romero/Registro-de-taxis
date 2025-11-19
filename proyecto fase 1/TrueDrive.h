#ifndef TRUEDRIVE_H
#define TRUEDRIVE_H
#include <vector>
#include <queue>
#include "Taxi.h"
#include "Funciones.h"
using namespace std;

class TrueDrive {
private:
    vector<Taxi> taxis;
    queue<Taxi> colaEjecutiva, colaTradicional;
    queue<Taxi> rutaEjecutiva, rutaTradicional;

    bool esUnico(string placa, int motor, int doc, int seguro);
    void imprimirColaGenerica(queue<Taxi> temp, string titulo);

public:
    void registrarTaxi();
    void mostrarTaxisRegistrados();
    void mostrarColasDisponibles();
    void mostrarColasEnRuta();
    void solicitarTaxi();
    void finalizarViaje();
};
#endif
