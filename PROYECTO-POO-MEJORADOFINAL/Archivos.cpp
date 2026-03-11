#include "Archivos.h"
#include "Utilidades.h"
#include "Excepciones.h"
#include "definiciones.h"
#include <iostream>
#include <fstream>
using namespace std;

// ============================================================
//   MODULO: Archivos — persistencia en datos.txt
//
//   Concepto nuevo:
//     - try-catch para ArchivoException en operaciones de E/S
//     - Buena practica: separar el error de archivo del flujo normal
// ============================================================

void Archivos::guardarDatos(const SistemaAcademico& sys) {
    // --------------------------------------------------------
    //   MANEJO DE EXCEPCION: ArchivoException
    //   Concepto: operaciones de archivo envueltas en try-catch.
    //   Si el archivo no puede abrirse se lanza ArchivoException.
    // --------------------------------------------------------
    try {
        ofstream archivo(ARCHIVO_DATOS.c_str());
        if (!archivo)
            throw ArchivoException(ARCHIVO_DATOS, "escritura");

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

    } catch (const ArchivoException& e) {
        cout << "\n  [X] " << e.what() << "\n";
    } catch (const ExcepcionSistema& e) {
        cout << "\n  [X] Error inesperado al guardar: " << e.what() << "\n";
    }
}

void Archivos::cargarDatos(SistemaAcademico& sys) {
    // --------------------------------------------------------
    //   MANEJO DE EXCEPCION en lectura de archivo
    //   Concepto: multiples catch — ArchivoException especifico
    //   y ExcepcionSistema como red de seguridad general.
    // --------------------------------------------------------
    try {
        ifstream archivo(ARCHIVO_DATOS.c_str());
        if (!archivo) return;  // Primera ejecucion: normal, sin excepcion

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

    } catch (const ArchivoException& e) {
        cout << "\n  [!] " << e.what() << "\n";
    } catch (const ExcepcionSistema& e) {
        cout << "\n  [!] Error al cargar datos: " << e.what() << "\n";
    }
}
