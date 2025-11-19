#ifndef CONDUCTOR_H
#define CONDUCTOR_H
#include <string>
using namespace std;

class Conductor {
private:
    string nombre, apellido;
    int documentoID, numeroSeguro, telefono;

public:
    Conductor(string n, string a, int id, int seg, int tel);
    string getNombre() const;
    string getApellido() const;
    int getDocumentoID() const;
    int getNumeroSeguro() const;
    int getTelefono() const;
};
#endif
