#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <limits>
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
    cin >> texto;
    return texto;
}

class Conductor {
public:
    string nombre;
    string apellido;
    int documentoID;
    int numeroSeguro;
    int telefono;

    Conductor(string n, string a, int id, int seg, int tel) {
        nombre = n;
        apellido = a;
        documentoID = id;
        numeroSeguro = seg;
        telefono = tel;
    }
};

class Taxi {
public:
    int placa;
    int numeroMotor;
    string modelo;
    int año;
    string categoria;
    Conductor conductor;

    Taxi(int p, int m, string mod, int a, Conductor c)
        : placa(p), numeroMotor(m), modelo(mod), año(a), conductor(c) 
    {
        if (a >= 2015) categoria = "Ejecutiva";
        else if (a >= 2010) categoria = "Tradicional";
        else categoria = "No valida";
    }
};

class TrueDrive {
private:
    vector<Taxi> taxis;
    queue<Taxi> cola;

    bool esUnico(int placa, int motor, int doc, int seguro) {
        for (auto &t : taxis) {
            if (t.placa == placa || t.numeroMotor == motor ||
                t.conductor.documentoID == doc || t.conductor.numeroSeguro == seguro)
                return false;
        }
        return true;
    }

public:
    void registrarTaxi() {
        int placa = leerEntero("Placa: ");
        int motor = leerEntero("Número de motor: ");
        string modelo = leerTexto("Modelo: ");
        int año = leerEntero("Año: ");

        if (año < 2010) {
            cout << " No se puede registrar un taxi con año menor a 2010.\n";
            return;
        }

        cout << "\n=== Datos del Conductor ===" << endl;
        string nombre = leerTexto("Nombre: ");
        string apellido = leerTexto("Apellido: ");
        int doc = leerEntero("Documento ID (numero): ");
        int seguro = leerEntero("Numero de Seguro Social: ");
        int tel = leerEntero("Telefono: ");

        if (!esUnico(placa, motor, doc, seguro)) {
            cout << " Datos duplicados. Registro cancelado.\n";
            return;
        }

        Conductor c(nombre, apellido, doc, seguro, tel);
        Taxi t(placa, motor, modelo, año, c);

        taxis.push_back(t);
        cola.push(t);

        cout << " Taxi registrado con categoria: " << t.categoria << endl;
    }

    void mostrarTaxis() {
        cout << "\n=== Lista de Taxis Registrados ===\n";
        for (auto &t : taxis) {
            cout << "Placa: " << t.placa
                 << " | Modelo: " << t.modelo
                 << " | Año: " << t.año
                 << " | Categoría: " << t.categoria
                 << " | Conductor: " << t.conductor.nombre << " " << t.conductor.apellido
                 << endl;
        }
    }

    void mostrarCola() {
        cout << "\n=== Cola de Espera ===\n";
        queue<Taxi> temp = cola;
        int pos = 1;
        while (!temp.empty()) {
            Taxi t = temp.front();
            cout << pos++ << ". " << t.placa << " (" << t.categoria << ") - Conductor: " 
                 << t.conductor.nombre << endl;
            temp.pop();
        }
    }
};

int main() {
    TrueDrive sistema;
    int opcion;

    do {
        cout << "\n=== MENU TRUE DRIVE ===\n";
        cout << "1. Registrar Taxi\n";
        cout << "2. Mostrar Taxis\n";
        cout << "3. Mostrar Cola de Espera\n";
        cout << "4. Salir\n";
        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {
            case 1: sistema.registrarTaxi(); break;
            case 2: sistema.mostrarTaxis(); break;
            case 3: sistema.mostrarCola(); break;
            case 4: cout << "Saliendo...\n"; break;
            default: cout << "Opcion no valida.\n";
        }

    } while (opcion != 4);

    return 0;
}