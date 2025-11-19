#include <iostream>
#include "TrueDrive.h"


using namespace std;

void usuariomenu(TrueDrive &sistema) {
    system("cls");
    int opcion;
    do {
        cout << "\n=== MENU DE OPERACIONES ===\n";
        cout << "1. Ver Taxis Disponibles \n";
        cout << "2. Asignar Viaje \n";
        cout << "3. Finalizar Viaje \n";
        cout << "4. Ver Taxis En Ruta\n";
        cout << "5. Regresar al menú principal\n";
        opcion = leerEntero("Seleccione una opcion: ");

        system("cls"); 

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
        system("cls");
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
            case 4:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
        }



    } while (opcion != 4);

    return 0;
}

