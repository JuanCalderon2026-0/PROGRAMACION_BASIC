#include "SistemaAcademico.h"
#include "Interfaz.h"
#include "Utilidades.h"
#include "Excepciones.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>
using namespace std;

// ============================================================
//   IMPLEMENTACION: SistemaAcademico
// ============================================================

SistemaAcademico::SistemaAcademico() {}

// Destructor: libera todos los objetos Estudiante del heap
SistemaAcademico::~SistemaAcademico() {
    for (int i = 0; i < (int)estudiantes.size(); i++) {
        delete estudiantes[i];
        estudiantes[i] = nullptr;
    }
    estudiantes.clear();
}

// ---- Agregar estudiante ----
void SistemaAcademico::agregarEstudiante(Estudiante* est) {
    estudiantes.push_back(est);
}

// ---- Eliminar estudiante por codigo ----
bool SistemaAcademico::eliminarEstudiante(const string& codigo) {
    for (int i = 0; i < (int)estudiantes.size(); i++) {
        if (estudiantes[i] != nullptr &&
            estudiantes[i]->isActivo() &&
            estudiantes[i]->getCodigo() == codigo)
        {
            delete estudiantes[i];
            estudiantes.erase(estudiantes.begin() + i);
            return true;
        }
    }
    return false;
}

// ---- Verifica si codigo ya existe ----
bool SistemaAcademico::codigoExiste(const string& codigo) const {
    for (int i = 0; i < (int)estudiantes.size(); i++) {
        if (estudiantes[i] != nullptr &&
            estudiantes[i]->isActivo() &&
            estudiantes[i]->getCodigo() == codigo)
            return true;
    }
    return false;
}

// ---- Buscar por codigo (version clasica — retorna nullptr) ----
Estudiante* SistemaAcademico::buscarPorCodigo(const string& codigo) const {
    for (int i = 0; i < (int)estudiantes.size(); i++) {
        if (estudiantes[i] != nullptr &&
            estudiantes[i]->isActivo() &&
            estudiantes[i]->getCodigo() == codigo)
            return estudiantes[i];
    }
    return nullptr;
}

// ============================================================
//   BUSQUEDA CON EXCEPCION: buscarPorCodigoSeguro
//
//   Concepto: en lugar de retornar nullptr cuando no se encuentra
//   al estudiante, este metodo lanza (throw) una excepcion
//   personalizada. El llamador DEBE usar try-catch.
//
//   Buena practica: evita verificar si el puntero es nullptr
//   en cada llamada; la excepcion obliga al manejo del error.
// ============================================================
Estudiante* SistemaAcademico::buscarPorCodigoSeguro(const string& codigo) const {
    Estudiante* encontrado = buscarPorCodigo(codigo);
    if (encontrado == nullptr)
        throw EstudianteNoEncontradoException(codigo);
    return encontrado;
}

// ---- Buscar por nombre (primer coincidente) ----
Estudiante* SistemaAcademico::buscarPorNombre(const string& nombre) const {
    string busq = nombre;
    for (int i = 0; i < (int)busq.size(); i++)
        busq[i] = tolower((unsigned char)busq[i]);

    for (int i = 0; i < (int)estudiantes.size(); i++) {
        if (estudiantes[i] == nullptr || !estudiantes[i]->isActivo()) continue;
        string nom = estudiantes[i]->getNombre();
        for (int j = 0; j < (int)nom.size(); j++)
            nom[j] = tolower((unsigned char)nom[j]);
        if (nom.find(busq) != string::npos)
            return estudiantes[i];
    }
    return nullptr;
}

// ---- Buscar todos los que coincidan ----
vector<Estudiante*> SistemaAcademico::buscarTodos(const string& nombre) const {
    vector<Estudiante*> resultados;

    string busq = nombre;
    for (int i = 0; i < (int)busq.size(); i++)
        busq[i] = tolower((unsigned char)busq[i]);

    for (int i = 0; i < (int)estudiantes.size(); i++) {
        if (estudiantes[i] == nullptr || !estudiantes[i]->isActivo()) continue;
        string nom = estudiantes[i]->getNombre();
        for (int j = 0; j < (int)nom.size(); j++)
            nom[j] = tolower((unsigned char)nom[j]);
        if (nom.find(busq) != string::npos)
            resultados.push_back(estudiantes[i]);
    }
    return resultados;
}

// ---- Acceso ----
int SistemaAcademico::getCantidad() const {
    return (int)estudiantes.size();
}
Estudiante* SistemaAcademico::getEstudiante(int i) const {
    return estudiantes[i];
}

// ---- Mostrar fichas ----
void SistemaAcademico::mostrarFichas() const {
    if (estudiantes.empty()) {
        cout << "\n  [!] No hay estudiantes registrados.\n";
        return;
    }
    Interfaz::linea('=');
    cout << "\n  FICHAS DE ESTUDIANTES\n";
    Interfaz::linea('=');

    int numero = 1;
    for (int i = 0; i < (int)estudiantes.size(); i++) {
        if (estudiantes[i] == nullptr || !estudiantes[i]->isActivo()) continue;
        cout << "\n";
        Interfaz::linea('-');
        cout << "\n  ESTUDIANTE #" << numero++ << "\n";
        Interfaz::linea('-');
        cout << "\n";
        // Llamada polimorfica a mostrarInfo()
        // Concepto: Polimorfismo en tiempo de ejecucion
        estudiantes[i]->mostrarInfo();
    }
    cout << "\n";
    Interfaz::linea('=');
    cout << "\n  Total: " << (numero - 1) << " estudiante(s).\n";
}

// ---- Promedios (implementacion de IReporte) ----
void SistemaAcademico::mostrarPromedios() const {
    if (estudiantes.empty()) {
        cout << "\n  [!] No hay estudiantes registrados.\n";
        return;
    }
    Interfaz::linea('=');
    cout << "\n  PROMEDIOS DE ESTUDIANTES\n";
    Interfaz::linea('=');
    cout << "\n\n";

    bool hayNotas = false;
    for (int i = 0; i < (int)estudiantes.size(); i++) {
        Estudiante* e = estudiantes[i];
        if (e == nullptr || !e->isActivo() || e->getCantidadNotas() == 0) continue;
        hayNotas = true;
        float prom = e->calcularPromedio();
        cout << "  " << setw(6)  << left  << e->getCodigo()
             << " | " << setw(24) << left  << e->getNombre()
             << " | " << fixed << setprecision(2) << setw(5) << right << prom
             << "  " << Utilidades::etiquetaEstado(prom) << "\n";
    }
    if (!hayNotas)
        cout << "  [!] Ningun estudiante tiene notas registradas.\n";
}

// ---- Ranking (implementacion de IReporte) ----
void SistemaAcademico::mostrarRanking() const {
    if (contarConNotas() == 0) {
        cout << "\n  [!] Ningun estudiante tiene notas registradas.\n";
        return;
    }

    vector<string> nombresRank;
    vector<string> codigosRank;
    vector<float>  promRank;

    for (int i = 0; i < (int)estudiantes.size(); i++) {
        Estudiante* e = estudiantes[i];
        if (e == nullptr || !e->isActivo() || e->getCantidadNotas() == 0) continue;
        codigosRank.push_back(e->getCodigo());
        nombresRank.push_back(e->getNombre());
        promRank.push_back(e->calcularPromedio());
    }

    int n = (int)promRank.size();
    // Burbuja
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (promRank[j] < promRank[j + 1]) {
                swap(promRank[j],    promRank[j + 1]);
                swap(nombresRank[j], nombresRank[j + 1]);
                swap(codigosRank[j], codigosRank[j + 1]);
            }
        }
    }

    Interfaz::linea('=');
    cout << "\n  RANKING ACADEMICO\n";
    Interfaz::linea('=');
    cout << "\n";
    cout << "  +------+----------+------------------------+----------+\n";
    cout << "  | Pos. | Codigo   | Nombre                 | Promedio |\n";
    cout << "  +------+----------+------------------------+----------+\n";

    for (int i = 0; i < n; i++) {
        string nom = nombresRank[i];
        if ((int)nom.length() > 22) nom = nom.substr(0, 19) + "...";
        cout << "  | " << setw(4)  << right << (i + 1)
             << " | " << setw(8)  << left  << codigosRank[i]
             << " | " << setw(22) << left  << nom
             << " | " << setw(8)  << right << fixed
             << setprecision(2)   << promRank[i] << " |\n";
    }
    cout << "  +------+----------+------------------------+----------+\n";
    cout << "\n";
    Interfaz::linea('*');
    if (n >= 1) cout << "\n  [ORO]  1er: " << nombresRank[0] << "  (" << fixed << setprecision(2) << promRank[0] << ")";
    if (n >= 2) cout << "\n  [PLAT] 2do: " << nombresRank[1] << "  (" << fixed << setprecision(2) << promRank[1] << ")";
    if (n >= 3) cout << "\n  [BRON] 3er: " << nombresRank[2] << "  (" << fixed << setprecision(2) << promRank[2] << ")";
    cout << "\n";
    Interfaz::linea('*');
    cout << "\n";
}

// ---- Estadisticas (implementacion de IReporte) ----
void SistemaAcademico::mostrarEstadisticas() const {
    Interfaz::linea('=');
    cout << "\n  ESTADISTICAS DEL SISTEMA\n";
    Interfaz::linea('=');
    cout << "\n\n";

    int   total = 0, aprobados = 0, recup = 0, desap = 0, sinNotas = 0;
    float sumaTotal = 0.0f;
    int   conNotas  = 0;

    for (int i = 0; i < (int)estudiantes.size(); i++) {
        Estudiante* e = estudiantes[i];
        if (e == nullptr || !e->isActivo()) continue;
        total++;
        if (e->getCantidadNotas() == 0) { sinNotas++; continue; }
        float prom = e->calcularPromedio();
        sumaTotal += prom;
        conNotas++;

        // --------------------------------------------------------
        //   ENUM CLASS en control de flujo (switch con enum class)
        //   Concepto: uso de getEstadoAcademico() que retorna
        //   EstadoAcademico::APROBADO / RECUPERACION / DESAPROBADO
        //   El switch compara usando el ambito del enum class.
        // --------------------------------------------------------
        switch (e->getEstadoAcademico()) {
            case EstadoAcademico::APROBADO:      aprobados++; break;
            case EstadoAcademico::RECUPERACION:  recup++;     break;
            case EstadoAcademico::DESAPROBADO:   desap++;     break;
            case EstadoAcademico::SIN_NOTAS:                  break;
        }
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

        cout << "\n";
        Interfaz::linea('-');
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

    cout << "\n  Capacidad lista     : " << estudiantes.size() << " slots\n";
    cout << "  Slots utilizados    : " << total << " slots\n";
}

// ---- Estado de memoria ----
void SistemaAcademico::mostrarEstadoMemoria() const {
    Interfaz::linea('=');
    cout << "\n";
    cout << "            ESTADO DE MEMORIA DINAMICA\n";
    Interfaz::linea('=');
    cout << "\n";
    cout << "  SistemaAcademico (vector en heap):\n";
    cout << "    Capacidad lista : " << estudiantes.capacity() << " slots\n";
    cout << "    Estudiantes     : " << estudiantes.size()     << " activos\n";
    cout << "    Slots libres    : " << (estudiantes.capacity() - estudiantes.size()) << "\n\n";

    cout << "  Desglose por estudiante:\n";
    cout << "  ";
    Interfaz::linea('-', 58);
    cout << "\n";

    size_t totalBytes = sizeof(SistemaAcademico);
    for (int i = 0; i < (int)estudiantes.size(); i++) {
        Estudiante* e = estudiantes[i];
        if (e == nullptr) continue;
        size_t bytesEst   = sizeof(Estudiante);
        size_t bytesNotas = e->getCantidadNotas() * sizeof(Nota);
        totalBytes += bytesEst + bytesNotas;

        cout << "  [" << i << "] " << e->getCodigo()
             << " | Estudiante: " << bytesEst << "B"
             << " | Notas[" << e->getCantidadNotas() << "]: "
             << bytesNotas << "B\n";
    }
    cout << "  ";
    Interfaz::linea('-', 58);
    cout << "\n";
    cout << "  Memoria total estimada : ~" << totalBytes << " bytes\n";
    Interfaz::linea('=');
    cout << "\n";
}

// ---- Contar con notas ----
int SistemaAcademico::contarConNotas() const {
    int cont = 0;
    for (int i = 0; i < (int)estudiantes.size(); i++) {
        if (estudiantes[i] != nullptr &&
            estudiantes[i]->isActivo() &&
            estudiantes[i]->getCantidadNotas() > 0)
            cont++;
    }
    return cont;
}
