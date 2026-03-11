#include "reportes.h"
#include "interfaz.h"
#include "utilidades.h"
#include "busqueda.h"
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

// ============================================================
//   MODULO: Reportes
// ============================================================

// ------------------------------------------------------------------
// Muestra promedio de cada estudiante con notas
// ------------------------------------------------------------------
void mostrarPromedios(const SistemaAcademico* sys) {
    if (sys->cantidad == 0) {
        cout << "\n  [!] No hay estudiantes registrados.\n";
        return;
    }

    linea('=');
    cout << "\n  PROMEDIOS DE ESTUDIANTES\n";
    linea('=');
    cout << "\n\n";

    bool hayNotas = false;
    Estudiante* const* ptr = sys->lista;

    for (int i = 0; i < sys->cantidad; i++, ptr++) {
        if (*ptr == nullptr || !(*ptr)->activo || (*ptr)->cantidadNotas == 0)
            continue;
        hayNotas = true;

        float prom = calcularPromedio((*ptr)->notas, (*ptr)->cantidadNotas);
        cout << "  " << setw(6)  << left  << (*ptr)->codigo
             << " | " << setw(24) << left  << (*ptr)->nombre
             << " | " << fixed << setprecision(2) << setw(5) << right << prom
             << "  " << etiquetaEstado(prom) << "\n";
    }

    if (!hayNotas)
        cout << "  [!] Ningun estudiante tiene notas registradas.\n";
}

// ------------------------------------------------------------------
// Ranking ordenado por promedio descendente
// Usa vector<> en lugar de arreglos dinamicos con new/delete
// ------------------------------------------------------------------
void mostrarRanking(const SistemaAcademico* sys) {
    if (contarConNotas(sys) == 0) {
        cout << "\n  [!] Ningun estudiante tiene notas registradas.\n";
        return;
    }

    // Vectores temporales para el ranking (sin new/delete)
    vector<string> nombresRank;        // << vector<string> >>
    vector<string> codigosRank;        // << vector<string> >>
    vector<float>  promRank;           // << vector<float>  >>

    // Llenar vectores con push_back
    Estudiante* const* ptr = sys->lista;
    for (int i = 0; i < sys->cantidad; i++, ptr++) {
        if (*ptr == nullptr || !(*ptr)->activo || (*ptr)->cantidadNotas == 0)
            continue;
        codigosRank.push_back((*ptr)->codigo);                               // << push_back >>
        nombresRank.push_back((*ptr)->nombre);                               // << push_back >>
        promRank.push_back(calcularPromedio((*ptr)->notas, (*ptr)->cantidadNotas)); // << push_back >>
    }

    int n = (int)promRank.size();      // << .size() >>

    // Ordenamiento burbuja sobre los vectores (acceso por indice [])
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (promRank[j] < promRank[j + 1]) {    // << acceso vector[] >>
                swap(promRank[j],    promRank[j + 1]);
                swap(nombresRank[j], nombresRank[j + 1]);
                swap(codigosRank[j], codigosRank[j + 1]);
            }
        }
    }

    linea('=');
    cout << "\n  RANKING ACADEMICO\n";
    linea('=');
    cout << "\n";
    cout << "  +------+----------+------------------------+----------+\n";
    cout << "  | Pos. | Codigo   | Nombre                 | Promedio |\n";
    cout << "  +------+----------+------------------------+----------+\n";

    for (int i = 0; i < n; i++) {
        string nom = nombresRank[i];   // << acceso vector[i] >>
        if ((int)nom.length() > 22) nom = nom.substr(0, 19) + "...";

        cout << "  | " << setw(4)  << right << (i + 1)
             << " | " << setw(8)  << left  << codigosRank[i]   // << vector[i] >>
             << " | " << setw(22) << left  << nom
             << " | " << setw(8)  << right << fixed
             << setprecision(2)   << promRank[i] << " |\n";    // << vector[i] >>
    }
    cout << "  +------+----------+------------------------+----------+\n";

    // Podio
    cout << "\n";
    linea('*');
    if (n >= 1) cout << "\n  [ORO]  1er: " << nombresRank[0] << "  (" << fixed << setprecision(2) << promRank[0] << ")";
    if (n >= 2) cout << "\n  [PLAT] 2do: " << nombresRank[1] << "  (" << fixed << setprecision(2) << promRank[1] << ")";
    if (n >= 3) cout << "\n  [BRON] 3er: " << nombresRank[2] << "  (" << fixed << setprecision(2) << promRank[2] << ")";
    cout << "\n";
    linea('*');
    cout << "\n";
    // No necesita delete[] porque los vectores se liberan solos al salir de scope
}

// ------------------------------------------------------------------
// Estadisticas generales del sistema con barra de distribucion
// ------------------------------------------------------------------
void mostrarEstadisticas(const SistemaAcademico* sys) {
    linea('=');
    cout << "\n  ESTADISTICAS DEL SISTEMA\n";
    linea('=');
    cout << "\n\n";

    int   total    = 0, aprobados = 0, recup = 0, desap = 0, sinNotas = 0;
    float sumaTotal = 0.0f;
    int   conNotas  = 0;

    Estudiante* const* ptr = sys->lista;
    for (int i = 0; i < sys->cantidad; i++, ptr++) {
        if (*ptr == nullptr || !(*ptr)->activo) continue;
        total++;
        if ((*ptr)->cantidadNotas == 0) { sinNotas++; continue; }

        float prom = calcularPromedio((*ptr)->notas, (*ptr)->cantidadNotas);
        sumaTotal += prom;
        conNotas++;
        if      (prom >= 14.0f) aprobados++;
        else if (prom >= 11.0f) recup++;
        else                    desap++;
    }

    cout << "  Total estudiantes   : " << total    << "\n";
    cout << "  Con notas           : " << conNotas << "\n";
    cout << "  Sin notas           : " << sinNotas << "\n\n";

    if (conNotas > 0) {
        cout << "  Aprobados  (>=14)   : " << aprobados << "\n";
        cout << "  Recuperacion(11-13) : " << recup     << "\n";
        cout << "  Desaprobados(<11)   : " << desap     << "\n";
        cout << "\n  Promedio general    : "
             << fixed << setprecision(2) << (sumaTotal / conNotas) << "\n";

        // Barra de distribucion
        cout << "\n";
        linea('-');
        cout << "\n  DISTRIBUCION:\n\n";
        int barMax = 30;
        auto barra = [&](const char* label, int val) {
            int cant = (conNotas > 0) ? (val * barMax / conNotas) : 0;
            cout << "  " << setw(14) << left << label << " [";
            for (int k = 0; k < barMax; k++) cout << (k < cant ? '#' : '.');
            cout << "] " << val << "\n";
        };
        barra("Aprobados",    aprobados);
        barra("Recuperacion", recup);
        barra("Desaprobados", desap);
    }

    cout << "\n  Capacidad lista     : " << sys->capacidad << " slots\n";
    cout << "  Slots utilizados    : " << sys->cantidad  << " slots\n";
}
