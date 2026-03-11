#include "memoria.h"
#include "interfaz.h"
#include <iostream>
using namespace std;

// ============================================================
//   MODULO: Memoria Dinamica
// ============================================================

// ------------------------------------------------------------------
// Inicializa el sistema con capacidad inicial CAP_INICIAL
// Crea el arreglo de punteros en el heap
// ------------------------------------------------------------------
void inicializarSistema(SistemaAcademico* sys) {
    sys->capacidad = CAP_INICIAL;
    sys->cantidad  = 0;
    sys->lista     = new Estudiante*[sys->capacidad];   // arreglo de punteros
    for (int i = 0; i < sys->capacidad; i++)
        sys->lista[i] = nullptr;
}

// ------------------------------------------------------------------
// Libera TODA la memoria: cada Estudiante y su arreglo de notas,
// luego el arreglo de punteros principal
// ------------------------------------------------------------------
void liberarSistema(SistemaAcademico* sys) {
    for (int i = 0; i < sys->cantidad; i++) {
        if (sys->lista[i] != nullptr) {
            liberarEstudiante(sys->lista[i]);
            sys->lista[i] = nullptr;
        }
    }
    delete[] sys->lista;       // libera el arreglo de punteros
    sys->lista    = nullptr;
    sys->cantidad = 0;
    sys->capacidad = 0;
}

// ------------------------------------------------------------------
// Crea un Estudiante en el heap.
// Sus notas se crean como nullptr (sin notas aun).
// ------------------------------------------------------------------
Estudiante* crearEstudiante() {
    Estudiante* est = new Estudiante;
    est->notas          = nullptr;   // sin notas todavia
    est->cantidadNotas  = 0;
    est->capacidadNotas = 0;
    est->grado          = 0;
    est->activo         = true;
    return est;
}

// ------------------------------------------------------------------
// Libera la memoria de un Estudiante (primero sus notas, luego el)
// ------------------------------------------------------------------
void liberarEstudiante(Estudiante* est) {
    if (est == nullptr) return;
    if (est->notas != nullptr) {
        delete[] est->notas;    // libera el arreglo de notas
        est->notas = nullptr;
    }
    delete est;                 // libera el Estudiante del heap
}

// ------------------------------------------------------------------
// Agrega un estudiante a la lista.
// Si la lista esta llena, la DUPLICA (nueva capacidad = capacidad*2)
// usando new + copia manual + delete[].
// ------------------------------------------------------------------
void agregarEstudiante(SistemaAcademico* sys, Estudiante* est) {
    // Si la lista esta llena → expandir con nueva memoria
    if (sys->cantidad >= sys->capacidad) {
        int nuevaCap = sys->capacidad * 2;

        // 1. Crear nuevo arreglo de punteros mas grande
        Estudiante** nuevaLista = new Estudiante*[nuevaCap];

        // 2. Copiar los punteros existentes al nuevo arreglo
        for (int i = 0; i < sys->cantidad; i++)
            nuevaLista[i] = sys->lista[i];

        // 3. Inicializar los nuevos slots en nullptr
        for (int i = sys->cantidad; i < nuevaCap; i++)
            nuevaLista[i] = nullptr;

        // 4. Liberar el arreglo VIEJO de punteros
        delete[] sys->lista;

        // 5. Actualizar el sistema con la nueva lista
        sys->lista    = nuevaLista;
        sys->capacidad = nuevaCap;

        cout << "  [MEM] Lista expandida: " << (nuevaCap / 2)
             << " -> " << nuevaCap << " slots.\n";
    }

    sys->lista[sys->cantidad] = est;
    sys->cantidad++;
}

// ------------------------------------------------------------------
// Asigna (o re-asigna) el arreglo de notas de un estudiante.
// Si ya tenia notas, las libera y crea un nuevo arreglo.
// ------------------------------------------------------------------
void redimensionarNotas(Estudiante* est, int nuevaCantidad) {
    // Liberar notas anteriores si las habia
    if (est->notas != nullptr) {
        delete[] est->notas;
        est->notas = nullptr;
    }
    // Crear nuevo arreglo de Nota en el heap
    est->notas          = new Nota[nuevaCantidad];
    est->capacidadNotas = nuevaCantidad;
    est->cantidadNotas  = 0;   // se llenara despues

    // Inicializar a 0
    Nota* ptr = est->notas;
    for (int i = 0; i < nuevaCantidad; i++, ptr++) {
        ptr->bimestre = 0;
        ptr->valor    = 0.0f;
    }
}

// ------------------------------------------------------------------
// Muestra el estado actual de la memoria (util para entender
// como funciona la memoria dinamica)
// ------------------------------------------------------------------
void mostrarEstadoMemoria(const SistemaAcademico* sys) {
    linea('=');
    cout << "\n";
    cout << "            ESTADO DE MEMORIA DINAMICA\n";
    linea('=');
    cout << "\n";
    cout << "  SistemaAcademico* (heap):\n";
    cout << "    Capacidad lista : " << sys->capacidad << " slots\n";
    cout << "    Estudiantes     : " << sys->cantidad  << " activos\n";
    cout << "    Slots libres    : " << (sys->capacidad - sys->cantidad) << "\n\n";

    cout << "  Desglose por estudiante:\n";
    cout << "  " ;
    linea('-', 58);
    cout << "\n";

    size_t totalBytes = sizeof(Estudiante**) + sys->capacidad * sizeof(Estudiante*);

    for (int i = 0; i < sys->cantidad; i++) {
        Estudiante* e = sys->lista[i];
        if (e == nullptr) continue;

        size_t bytesEst  = sizeof(Estudiante);
        size_t bytesNotas = e->capacidadNotas * sizeof(Nota);
        totalBytes += bytesEst + bytesNotas;

        cout << "  [" << i << "] " << e->codigo
             << " | Estudiante: " << bytesEst << "B"
             << " | Notas[" << e->capacidadNotas << "]: "
             << bytesNotas << "B\n";
    }

    cout << "  ";
    linea('-', 58);
    cout << "\n";
    cout << "  Memoria total estimada : ~" << totalBytes << " bytes\n";
    linea('=');
    cout << "\n";
}
