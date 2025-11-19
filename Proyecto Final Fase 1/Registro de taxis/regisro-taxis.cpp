#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <limits>
#include <iomanip>
using namespace std;

// ==========================================
//   FUNCIONES AUXILIARES (Del código original)
// ==========================================
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

double leerDouble(string mensaje) {
    double valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << " Entrada invalida. Ingrese un numero (decimal permitido).\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
    }
}

string leerTexto(string mensaje) {
    string texto;
    cout << mensaje;
    getline(cin, texto); // Usar getline para leer la línea completa, incluyendo espacios.
    return texto;
}

// ==========================================
//   CLASES BASE (MODIFICADAS CON ENCAPSULACIÓN)
// ==========================================
class Conductor {
private:
    string nombre, apellido;
    int documentoID, numeroSeguro, telefono;

public:
    // Constructor con lista de inicialización
    Conductor(string n, string a, int id, int seg, int tel)
        : nombre(n), apellido(a), documentoID(id), numeroSeguro(seg), telefono(tel) {}

    // Getters para acceder a los datos privados
    string getNombre() const { return nombre; }
    string getApellido() const { return apellido; }
    int getDocumentoID() const { return documentoID; }
    int getNumeroSeguro() const { return numeroSeguro; }
    int getTelefono() const { return telefono; }
};

class Taxi {
private:
    int numeroMotor, año;
    string placa;
    string modelo, categoria; 
    Conductor conductor;

public:
    // Constructor con lista de inicialización
    Taxi(string p, int m, string mod, int a, Conductor c)
        : placa(p), numeroMotor(m), modelo(mod), año(a), conductor(c) 
    {
        if (a >= 2015) categoria = "Ejecutiva";
        else if (a >= 2010) categoria = "Tradicional";
        else categoria = "No valida";
    }

    // Getters
    string getPlaca() const { return placa; }
    int getNumeroMotor() const { return numeroMotor; }
    string getCategoria() const { return categoria; }
    const Conductor& getConductor() const { return conductor; }
};

// ==========================================
//   CLASE CONTROLADORA (MODIFICADA)
// ==========================================
class TrueDrive {
private:
    vector<Taxi> taxis;
    
    // Colas de DISPONIBLES
    queue<Taxi> colaEjecutiva;
    queue<Taxi> colaTradicional;

    // Estructura de viaje para almacenar datos de ruta
    struct Viaje {
        Taxi taxi;
        string origen;
        string destino;
        double costo;
    };

    // Colas de EN RUTA (con detalles del viaje)
    queue<Viaje> rutaEjecutiva;
    queue<Viaje> rutaTradicional;

    bool esUnico(string placa, int motor, int doc, int seguro) {
        for (auto &t : taxis) {
            if (t.getPlaca() == placa || t.getNumeroMotor() == motor ||
                t.getConductor().getDocumentoID() == doc || t.getConductor().getNumeroSeguro() == seguro)
                return false;
        }
        return true;
    }

    // [TU CAMBIO MASTER] Función helper para imprimir cualquier cola
    void imprimirColaGenerica(queue<Taxi> temp, string titulo) {
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

    void imprimirColaRuta(queue<Viaje> temp, string titulo) {
        cout << "\n=== " << titulo << " ===\n";
        if (temp.empty()) {
            cout << "No hay taxis en esta lista.\n";
            return;
        }
        int pos = 1;
        cout << fixed << setprecision(2);
        while (!temp.empty()) {
            Viaje v = temp.front();
            cout << pos++ << ". Placa: " << v.taxi.getPlaca()
                 << " | Origen: " << v.origen
                 << " | Destino: " << v.destino
                 << " | Costo: $" << v.costo
                 << " | Cond: " << v.taxi.getConductor().getNombre() << " " << v.taxi.getConductor().getApellido()
                 << endl;
            temp.pop();
        }
    }

public:
    void registrarTaxi() {
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

    void mostrarTaxisRegistrados() {
        cout << "\n=== Inventario Total de Taxis ===\n";
        for (auto &t : taxis) {
            cout << "Placa: " << t.getPlaca() << " | Cat: " << t.getCategoria() << endl;
        }
    }

    void mostrarColasDisponibles() {
        imprimirColaGenerica(colaEjecutiva, "Disponibles Ejecutiva");
        imprimirColaGenerica(colaTradicional, "Disponibles Tradicional");
    }

    // [TU CAMBIO MASTER] Nueva función para ver quién está trabajando
    void mostrarColasEnRuta() {
        imprimirColaRuta(rutaEjecutiva, "En Ruta Ejecutiva");
        imprimirColaRuta(rutaTradicional, "En Ruta Tradicional");
    }
    
    // [TU CAMBIO MASTER] Modificado para mover a ruta en vez de borrar
    void solicitarTaxi() {
        cout << "\n=== Solicitar Taxi (Asignar Viaje) ===\n";
        cout << "1. Ejecutiva\n2. Tradicional\n";
        int tipo = leerEntero("Seleccione tipo de servicio: ");

        string origen = leerTexto("Origen del viaje: ");
        string destino = leerTexto("Destino del viaje: ");
        double costo = leerDouble("Costo del viaje: $");

        if (tipo == 1) {
            if (colaEjecutiva.empty()) {
                cout << "\nNo hay taxis Ejecutivos disponibles.\n";
                return;
            }
            Taxi t = colaEjecutiva.front();
            colaEjecutiva.pop();
            Viaje v{t, origen, destino, costo};
            rutaEjecutiva.push(v);
            cout << "\n>>> VIAJE ASIGNADO: Taxi Ejecutivo Placa " << t.getPlaca() << " | Origen: " << origen << " | Destino: " << destino << " | Costo: $" << costo << "\n";
        }
        else if (tipo == 2) {
            if (colaTradicional.empty()) {
                cout << "\nNo hay taxis Tradicionales disponibles.\n";
                return;
            }
            Taxi t = colaTradicional.front();
            colaTradicional.pop();
            Viaje v{t, origen, destino, costo};
            rutaTradicional.push(v);
            cout << "\n>>> VIAJE ASIGNADO: Taxi Tradicional Placa " << t.getPlaca() << " | Origen: " << origen << " | Destino: " << destino << " | Costo: $" << costo << "\n";
        }
        else cout << "Opción inválida.\n";
    }

    // [TU CAMBIO MASTER] Nueva función para finalizar viaje
    void finalizarViaje() {
        cout << "\n=== Finalizar Viaje (Regresar a Base) ===\n";
        cout << "1. Ejecutiva\n2. Tradicional\n";
        int tipo = leerEntero("Seleccione tipo de taxi que regresa: ");

        if (tipo == 1) {
            if (rutaEjecutiva.empty()) {
                cout << "No hay taxis Ejecutivos en ruta actualmente.\n";
                return;
            }
            Viaje v = rutaEjecutiva.front();
            rutaEjecutiva.pop();
            colaEjecutiva.push(v.taxi);
            cout << "\n<<< RETORNO: Taxi Ejecutivo Placa " << v.taxi.getPlaca() << " regresó de Origen: " << v.origen << " a Destino: " << v.destino << ". Disponible nuevamente.\n";
        }
        else if (tipo == 2) {
            if (rutaTradicional.empty()) {
                cout << "No hay taxis Tradicionales en ruta actualmente.\n";
                return;
            }
            Viaje v = rutaTradicional.front();
            rutaTradicional.pop();
            colaTradicional.push(v.taxi);
            cout << "\n<<< RETORNO: Taxi Tradicional Placa " << v.taxi.getPlaca() << " regresó de Origen: " << v.origen << " a Destino: " << v.destino << ". Disponible nuevamente.\n";
        }
        else cout << "Opción inválida.\n";
    }
};

// ==========================================
//   MENÚS (ACTUALIZADOS)
// ==========================================

void usuariomenu(TrueDrive &sistema) {
    int opcion;
    do {
        cout << "\n=== MENU DE OPERACIONES ===\n";
        cout << "1. Ver Taxis Disponibles \n";
        cout << "2. Asignar Viaje \n";
        cout << "3. Finalizar Viaje \n"; // [TU CAMBIO]
        cout << "4. Ver Taxis En Ruta\n";         // [TU CAMBIO]
        cout << "5. Regresar al menú principal\n";
        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {
            case 1: sistema.mostrarColasDisponibles(); break;
            case 2: sistema.solicitarTaxi(); break;
            case 3: sistema.finalizarViaje(); break;
            case 4: sistema.mostrarColasEnRuta(); break;
            case 5: break;
            default: cout << "Opcion no valida.\n";
        }
    } while (opcion != 5);
}

int main() {
    TrueDrive sistema;
    int opcion;

    do {
        cout << "\n=== SISTEMA TRUE DRIVE ===\n";
        cout << "1. Menu de Operaciones \n";
        cout << "2. Registrar Taxi Nuevo \n";
        cout << "3. Inventario Total \n";
        cout << "4. Salir\n";
        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {
            case 1: usuariomenu(sistema); break;
            case 2: sistema.registrarTaxi(); break;
            case 3: sistema.mostrarTaxisRegistrados(); break;
            case 4: cout << "Saliendo...\n"; break;
            default: cout << "Opcion no valida.\n";
        }
    } while (opcion != 4);

    return 0;
}
