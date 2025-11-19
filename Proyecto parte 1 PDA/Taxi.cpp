#include "Taxi.h"

Taxi::Taxi(string p, int m, string mod, int a, Conductor c)
    : placa(p), numeroMotor(m), modelo(mod), año(a), conductor(c)
{
    if (a >= 2015) categoria = "Ejecutiva";
    else if (a >= 2010) categoria = "Tradicional";
    else categoria = "No valida";
}

string Taxi::getPlaca() const { return placa; }
int Taxi::getNumeroMotor() const { return numeroMotor; }
string Taxi::getCategoria() const { return categoria; }
const Conductor& Taxi::getConductor() const { return conductor; }
