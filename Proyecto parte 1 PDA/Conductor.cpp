#include "Conductor.h"
Conductor::Conductor(string n, string a, int id, int seg, int tel)
    : nombre(n), apellido(a), documentoID(id), numeroSeguro(seg), telefono(tel) {}

string Conductor::getNombre() const { return nombre; }
string Conductor::getApellido() const { return apellido; }
int Conductor::getDocumentoID() const { return documentoID; }
int Conductor::getNumeroSeguro() const { return numeroSeguro; }
int Conductor::getTelefono() const { return telefono; }
