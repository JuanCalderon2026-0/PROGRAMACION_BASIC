#include "Archivos.h"
#include "Utilidades.h"
#include "definiciones.h"
#include <iostream>
#include <fstream>
using namespace std;

// ============================================================
//   MODULO: Archivos — persistencia en datos.txt
// ============================================================

void Archivos::guardarDatos(const SistemaAcademico& sys) {
    ofstream archivo(ARCHIVO_DATOS.c_str());
    if (!archivo) {
        cout << "\n  [X] ERROR: No se pudo abrir el archivo para guardar.\n";
        return;
    }

    archivo << sys.getCantidad() << "\n";

    for (int i = 0; i < sys.getCantidad(); i++) {
        Estudiante* e = sys.getEstudiante(i);
        if (e == nullptr || !e->isActivo()) continue;

        archivo << e->getCodigo()              << "\n";
        archivo << e->getNombre()              << "\n";
        archivo << e->getGrado()               << "\n";
        archivo << e->getCurso().getNombre()   << "\n";
        archivo << e->getCurso().getProfesor() << "\n";
        archivo << e->getFechaRegistro()       << "\n";
        archivo << (e->isActivo() ? 1 : 0)     << "\n";
        archivo << e->getCantidadNotas()       << "\n";

        for (int j = 0; j < e->getCantidadNotas(); j++) {
            archivo << e->getNota(j).getBimestre() << " "
                    << e->getNota(j).getValor()    << "\n";
        }
    }
    archivo.close();
}

void Archivos::cargarDatos(SistemaAcademico& sys) {
    ifstream archivo(ARCHIVO_DATOS.c_str());
    if (!archivo) return;  // primera ejecucion, normal

    int total = 0;
    archivo >> total;
    archivo.ignore();

    for (int i = 0; i < total; i++) {
        string codigo, nombre, nomCurso, profCurso, fecha;
        int    grado, activo, cantNotas;

        getline(archivo, codigo);
        getline(archivo, nombre);
        archivo >> grado; archivo.ignore();
        getline(archivo, nomCurso);
        getline(archivo, profCurso);
        getline(archivo, fecha);
        archivo >> activo >> cantNotas;
        archivo.ignore();

        Curso curso(nomCurso, profCurso);
        Estudiante* est = new Estudiante(codigo, nombre, grado, curso, fecha);
        est->setActivo(activo == 1);

        for (int j = 0; j < cantNotas; j++) {
            int bim; float val;
            archivo >> bim >> val;
            archivo.ignore();
            est->agregarNota(Nota(bim, val));
        }

        sys.agregarEstudiante(est);
    }
    archivo.close();
}
