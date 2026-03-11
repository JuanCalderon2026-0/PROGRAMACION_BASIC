// ============================================================
//   SISTEMA ACADEMICO PROFESIONAL v3.0
//   main.cpp — Punto de entrada del programa
//
//   Incluye todos los modulos via sus headers (.h)
//   Cada modulo tiene su propio .cpp compilado por separado
// ============================================================

#include "definiciones.h"
#include "interfaz.h"
#include "memoria.h"
#include "estudiantes.h"
#include "reportes.h"
#include "archivos.h"
#include "historial.h"
#include "busqueda.h"
#include <iostream>
#include <limits>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

// Menu actualizado con opciones de vector
void mostrarMenuCompleto() {
    cout << "\n";
    linea('=');
    cout << "\n";
    cout << "                    MENU PRINCIPAL\n";
    linea('=');
    cout << "\n\n";
    cout << "   [1]  Registrar Nuevo Estudiante\n";
    cout << "   [2]  Ver Fichas de Estudiantes\n";
    cout << "   [3]  Ingresar / Actualizar Notas\n";
    cout << "   [4]  Ver Promedios\n";
    cout << "   [5]  Ranking Academico\n";
    cout << "   [6]  Editar Datos de Estudiante\n";
    cout << "   [7]  Eliminar Estudiante\n";
    cout << "   [8]  Estadisticas + Estado de Memoria\n";
    cout << "   [9]  Buscar Estudiantes por Nombre\n";
    cout << "   [10] Ver Historial de Operaciones\n";
    cout << "   [11] Guardar y Salir\n\n";
    linea('-');
    cout << "\n  >>> Seleccione una opcion: ";
}

// Busca con vector y muestra todos los resultados
void buscarEstudiantesConVector(SistemaAcademico* sys, Historial* h) {
    linea('=');
    cout << "\n  BUSQUEDA POR NOMBRE\n";
    linea('=');
    cout << "\n\n  Ingrese nombre (o parte del nombre): ";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string busq;
    getline(cin, busq);

    // Devuelve vector<Estudiante*> con todos los coincidentes
    vector<Estudiante*> resultados = buscarTodos(sys, busq);  // << vector >>

    cout << "\n";
    linea('-');

    if (resultados.empty()) {                                  // << .empty() >>
        cout << "\n  [!] No se encontraron estudiantes con ese nombre.\n";
        historialAgregar(h, "Busqueda sin resultados: \"" + busq + "\"");
        return;
    }

    cout << "\n  Resultados encontrados: " << resultados.size()   // << .size() >>
         << "  para: \"" << busq << "\"\n\n";

    // Iterar el vector de punteros
    for (int i = 0; i < (int)resultados.size(); i++) {            // << vector[i] >>
        Estudiante* e = resultados[i];
        cout << "  [" << (i+1) << "] "
             << setw(8) << left << e->codigo
             << " | " << setw(24) << left << e->nombre
             << " | Grado " << e->grado
             << " | " << e->curso.nombre << "\n";
    }

    historialAgregar(h, "Busqueda \"" + busq + "\": " +
                     to_string((int)resultados.size()) + " resultado(s)");
}

int main() {
    srand((unsigned int)time(0));

    // Sistema academico (lista en el HEAP)
    SistemaAcademico sistema;
    inicializarSistema(&sistema);
    cargarDatos(&sistema);

    // Historial con vector<string> interno
    Historial historial;
    historialAgregar(&historial, "Sistema iniciado");

    int opcion;

    do {
        limpiarPantalla();
        mostrarBanner();
        mostrarMenuCompleto();

        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n  [X] Entrada invalida.\n";
            pausar();
            continue;
        }

        limpiarPantalla();

        switch (opcion) {
            case 1:
                registrarEstudiante(&sistema);
                historialAgregar(&historial, "Estudiante registrado");
                pausar(); break;
            case 2:
                mostrarEstudiantes(&sistema);
                historialAgregar(&historial, "Fichas consultadas");
                pausar(); break;
            case 3:
                ingresarNotas(&sistema);
                historialAgregar(&historial, "Notas ingresadas");
                pausar(); break;
            case 4:
                mostrarPromedios(&sistema);
                historialAgregar(&historial, "Promedios consultados");
                pausar(); break;
            case 5:
                mostrarRanking(&sistema);
                historialAgregar(&historial, "Ranking consultado");
                pausar(); break;
            case 6:
                editarEstudiante(&sistema);
                historialAgregar(&historial, "Datos editados");
                pausar(); break;
            case 7:
                eliminarEstudiante(&sistema);
                historialAgregar(&historial, "Estudiante eliminado");
                pausar(); break;
            case 8:
                mostrarEstadisticas(&sistema);
                cout << "\n";
                mostrarEstadoMemoria(&sistema);
                historialAgregar(&historial, "Estadisticas consultadas");
                pausar(); break;
            case 9:
                buscarEstudiantesConVector(&sistema, &historial);
                pausar(); break;
            case 10:
                historialMostrar(&historial);
                pausar(); break;
            case 11:
                guardarDatos(&sistema);
                historialAgregar(&historial, "Datos guardados - Sistema cerrado");
                limpiarPantalla();
                mostrarBanner();
                cout << "\n\n";
                linea('=');
                cout << "\n  DATOS GUARDADOS. HASTA PRONTO!\n";
                linea('=');
                cout << "\n\n";
                break;
            default:
                cout << "\n  [X] Opcion invalida (1-11).\n";
                pausar();
        }

    } while (opcion != 11);

    liberarSistema(&sistema);
    return 0;
}
