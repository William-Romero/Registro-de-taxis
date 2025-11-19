#include <iostream>
#include "TrueDrive.h"
#include <limits>

using namespace std;

bool TrueDrive::esUnico(string placa, int motor, int doc, int seguro) {
    for (auto &t : taxis) {
        if (t.getPlaca() == placa || t.getNumeroMotor() == motor ||
            t.getConductor().getDocumentoID() == doc || t.getConductor().getNumeroSeguro() == seguro)
            return false;
    }
    return true;
}

void TrueDrive::imprimirColaGenerica(queue<Taxi> temp, string titulo) {
    cout << "\n=== " << titulo << " ===\n";
    if (temp.empty()) {
        cout << "No hay taxis en esta lista.\n";
        return;
    }
    int pos = 1;
    while (!temp.empty()) {
        Taxi t = temp.front();
        cout << pos++ << ". Placa: " << t.getPlaca()
             << " | Cond: " << t.getConductor().getNombre() << " " << t.getConductor().getApellido()
             << " | Tel: " << t.getConductor().getTelefono() << endl;
        temp.pop();
    }
}

void TrueDrive::registrarTaxi() {
    string placa = leerTexto("Placa: ");
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

    if (t.getCategoria() == "Ejecutiva") colaEjecutiva.push(t);
    else colaTradicional.push(t);

    cout << " Taxi registrado con categoría: " << t.getCategoria() << endl;
}

void TrueDrive::mostrarTaxisRegistrados() {
    cout << "\n=== Inventario Total de Taxis ===\n";
    for (auto &t : taxis) {
        cout << "Placa: " << t.getPlaca() << " | Categoria: " << t.getCategoria() << endl;
    }
   cin.ignore(numeric_limits<streamsize>::max(), '\n');
   cin.get();

}

void TrueDrive::mostrarColasDisponibles() {
    imprimirColaGenerica(colaEjecutiva, "Disponibles Ejecutiva");
    imprimirColaGenerica(colaTradicional, "Disponibles Tradicional");
    
}

void TrueDrive::mostrarColasEnRuta() {
    imprimirColaGenerica(rutaEjecutiva, "En Ruta Ejecutiva");
    imprimirColaGenerica(rutaTradicional, "En Ruta Tradicional");
    
}

void TrueDrive::solicitarTaxi() {
    cout << "\n=== Solicitar Taxi ===\n";
    cout << "1. Ejecutiva\n2. Tradicional\n";
    int tipo = leerEntero("Seleccione tipo de servicio: ");

    if (tipo == 1) {
        if (colaEjecutiva.empty()) { cout << "No hay taxis Ejecutivos disponibles.\n"; return; }
        Taxi t = colaEjecutiva.front(); colaEjecutiva.pop();
        rutaEjecutiva.push(t);
        cout << "Taxi Ejecutivo asignado: " << t.getPlaca() << endl;
    } else if (tipo == 2) {
        if (colaTradicional.empty()) { cout << "No hay taxis Tradicionales disponibles.\n"; return; }
        Taxi t = colaTradicional.front(); colaTradicional.pop();
        rutaTradicional.push(t);
        cout << "Taxi Tradicional asignado: " << t.getPlaca() << endl;
    } else cout << "Opción inválida.\n";
}

void TrueDrive::finalizarViaje() {
    cout << "\n=== Finalizar Viaje ===\n";
    cout << "1. Ejecutiva\n2. Tradicional\n";
    int tipo = leerEntero("Seleccione tipo: ");

    if (tipo == 1) {
        if (rutaEjecutiva.empty()) { cout << "No hay taxis Ejecutivos en ruta.\n"; return; }
        Taxi t = rutaEjecutiva.front(); rutaEjecutiva.pop();
        colaEjecutiva.push(t);
        cout << "Taxi Ejecutivo regresó: " << t.getPlaca() << endl;
    } else if (tipo == 2) {
        if (rutaTradicional.empty()) { cout << "No hay taxis Tradicionales en ruta.\n"; return; }
        Taxi t = rutaTradicional.front(); rutaTradicional.pop();
        colaTradicional.push(t);
        cout << "Taxi Tradicional regresó: " << t.getPlaca() << endl;
    } else cout << "Opción inválida.\n";
}
