#ifndef TAXI_H
#define TAXI_H
#include <string>
#include "Conductor.h"
using namespace std;

class Taxi {
private:
    int numeroMotor, año;
    string placa;
    string modelo, categoria;
    Conductor conductor;

public:
    Taxi(string p, int m, string mod, int a, Conductor c);
    string getPlaca() const;
    int getNumeroMotor() const;
    string getCategoria() const;
    const Conductor& getConductor() const;
};
#endif
