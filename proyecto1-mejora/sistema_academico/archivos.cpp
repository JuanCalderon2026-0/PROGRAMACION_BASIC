#include "archivos.h"
#include "memoria.h"
#include <iostream>
#include <fstream>
using namespace std;

// ============================================================
//   MODULO: Archivos
// ============================================================

// ------------------------------------------------------------------
// Guarda todos los estudiantes en datos.txt
// ------------------------------------------------------------------
void guardarDatos(const SistemaAcademico* sys) {
    ofstream archivo(ARCHIVO_DATOS.c_str());

    if (!archivo) {
        cout << "\n  [X] ERROR: No se pudo abrir el archivo para guardar.\n";
        return;
    }

    archivo << sys->cantidad << "\n";

    Estudiante* const* ptr = sys->lista;
    for (int i = 0; i < sys->cantidad; i++, ptr++) {
        if (*ptr == nullptr) continue;

        archivo << (*ptr)->codigo          << "\n";
        archivo << (*ptr)->nombre          << "\n";
        archivo << (*ptr)->grado           << "\n";
        archivo << (*ptr)->curso.nombre    << "\n";
        archivo << (*ptr)->curso.profesor  << "\n";
        archivo << (*ptr)->fechaRegistro   << "\n";
        archivo << (*ptr)->activo          << "\n";
        archivo << (*ptr)->cantidadNotas   << "\n";

        // Guardar notas usando puntero
        const Nota* nptr = (*ptr)->notas;
        for (int j = 0; j < (*ptr)->cantidadNotas; j++, nptr++) {
            archivo << nptr->bimestre << " " << nptr->valor << "\n";
        }
    }

    archivo.close();
}

// ------------------------------------------------------------------
// Carga estudiantes desde datos.txt
// Crea cada Estudiante en el heap con crearEstudiante()
// ------------------------------------------------------------------
void cargarDatos(SistemaAcademico* sys) {
    ifstream archivo(ARCHIVO_DATOS.c_str());
    if (!archivo) return;  // archivo no existe aun, normal en primera ejecucion

    int total = 0;
    archivo >> total;
    archivo.ignore();

    for (int i = 0; i < total; i++) {
        // Crear el Estudiante en el heap
        Estudiante* est = crearEstudiante();

        getline(archivo, est->codigo);
        getline(archivo, est->nombre);
        archivo >> est->grado;
        archivo.ignore();
        getline(archivo, est->curso.nombre);
        getline(archivo, est->curso.profesor);
        getline(archivo, est->fechaRegistro);
        archivo >> est->activo;
        archivo >> est->cantidadNotas;
        archivo.ignore();

        // Reservar memoria dinamica para las notas
        if (est->cantidadNotas > 0) {
            est->notas          = new Nota[est->cantidadNotas];
            est->capacidadNotas = est->cantidadNotas;

            Nota* nptr = est->notas;
            for (int j = 0; j < est->cantidadNotas; j++, nptr++) {
                archivo >> nptr->bimestre >> nptr->valor;
                archivo.ignore();
            }
        }

        // Agregar al sistema (expande si es necesario)
        agregarEstudiante(sys, est);
    }

    archivo.close();
}
