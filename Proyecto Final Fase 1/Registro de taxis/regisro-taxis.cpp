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
    queue<Taxi> colaEjecutiva;
    queue<Taxi> colaTradicional;

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

   
        if (t.categoria == "Ejecutiva")
            colaEjecutiva.push(t);
        else
            colaTradicional.push(t);

        cout << " Taxi registrado con categoría: " << t.categoria << endl;
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
        cout << "\n=== Cola Ejecutiva ===\n";
        queue<Taxi> temp1 = colaEjecutiva;
        int pos = 1;
        while (!temp1.empty()) {
            Taxi t = temp1.front();
            cout << pos++ << ". Placa " << t.placa << " - Conductor: " << t.conductor.nombre << endl;
            temp1.pop();
        }

        cout << "\n=== Cola Tradicional ===\n";
        queue<Taxi> temp2 = colaTradicional;
        pos = 1;
        while (!temp2.empty()) {
            Taxi t = temp2.front();
            cout << pos++ << ". Placa " << t.placa << " - Conductor: " << t.conductor.nombre << endl;
            temp2.pop();
        }
    }

   
    void solicitarTaxi() {
        cout << "\n=== Solicitar Taxi ===\n";
        cout << "1. Ejecutiva\n";
        cout << "2. Tradicional\n";

        int tipo = leerEntero("Seleccione tipo de servicio: ");

        if (tipo == 1) {
            if (colaEjecutiva.empty()) {
                cout << "\nNo hay taxis Ejecutivos disponibles.\n";
                return;
            }
            Taxi t = colaEjecutiva.front();
            colaEjecutiva.pop();

            cout << "\n=== TAXI EJECUTIVO ASIGNADO ===\n";
            cout << "Placa: " << t.placa << endl;
            cout << "Modelo: " << t.modelo << endl;
            cout << "Conductor: " << t.conductor.nombre << " " << t.conductor.apellido << endl;
            cout << "Telefono: " << t.conductor.telefono << endl;
        }
        else if (tipo == 2) {
            if (colaTradicional.empty()) {
                cout << "\nNo hay taxis Tradicionales disponibles.\n";
                return;
            }
            Taxi t = colaTradicional.front();
            colaTradicional.pop();

            cout << "\n=== TAXI TRADICIONAL ASIGNADO ===\n";
            cout << "Placa: " << t.placa << endl;
            cout << "Modelo: " << t.modelo << endl;
            cout << "Conductor: " << t.conductor.nombre << " " << t.conductor.apellido << endl;
            cout << "Telefono: " << t.conductor.telefono << endl;
        }
        else {
            cout << "Opción inválida.\n";
        }
    }
};


void usuariomenu(TrueDrive &sistema) {
    int opcion;

    do {
        cout << "\n=== MENU DE USUARIO ===\n";
        cout << "1. Mostrar taxis disponibles\n";
        cout << "2. Llamar un taxi\n";
        cout << "3. Regresar al menú principal\n";
        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {
            case 1: sistema.mostrarCola(); break;
            case 2: sistema.solicitarTaxi(); break;
            case 3: break;
            default: cout << "Opcion no valida.\n";
        }

    } while (opcion != 3);
}


int main() {
    TrueDrive sistema;
    int opcion;

    do {
        cout << "\n=== MENU TRUE DRIVE ===\n";
        cout << "1. Usuario menu\n";
        cout << "2. Registrar Taxi\n";
        cout << "3. Mostrar Taxis\n";
        cout << "4. Mostrar Cola de Espera\n";
        cout << "5. Salir\n";
        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {
            case 1: usuariomenu(sistema); break;
            case 2: sistema.registrarTaxi(); break;
            case 3: sistema.mostrarTaxis(); break;
            case 4: sistema.mostrarCola(); break;
            case 5: cout << "Saliendo...\n"; break;
            default: cout << "Opcion no valida.\n";
        }

    } while (opcion != 5);

    return 0;
}
