#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>
using namespace std;
// EXCEPCION PERSONALIZADA
class CuentaNoEncontrada : public runtime_error {
public:
    CuentaNoEncontrada(const string& mensaje)
        : runtime_error(mensaje) {}
};
// CLASE CUENTABANCARIA
class CuentaBancaria {
private:
    int numeroCuenta;
    string titular;
    double saldo;

public:
    CuentaBancaria(int num, string nom, double sal)
        : numeroCuenta(num), titular(nom), saldo(sal) {}

    void depositar(double monto) {
        if (monto <= 0) {
            throw invalid_argument("El monto a depositar debe ser positivo.");
        }
        saldo += monto;
    }
    void retirar(double monto) {
        if (monto <= 0) {
            throw invalid_argument("El monto a retirar debe ser positivo.");
        }
        if (monto > saldo) {
            throw runtime_error("Saldo insuficiente para realizar el retiro.");
        }
        saldo -= monto;
    }
    double consultarSaldo() const {
        return saldo;
    }

    int getNumeroCuenta() const {
        return numeroCuenta;
    }
    string getTitular() const {
        return titular;
    }
};
class Banco {
private:
    vector<CuentaBancaria> cuentas;

public:
    void agregarCuenta() {
        int numero;
        string nombre;
        double saldoInicial;

        cout << "Numero de cuenta: ";
        cin >> numero;

        cout << "Nombre del titular: ";
        cin.ignore();
        getline(cin, nombre);

        cout << "Saldo inicial: ";
        cin >> saldoInicial;

        if (saldoInicial < 0) {
            throw invalid_argument("El saldo inicial no puede ser negativo.");
        }

        cuentas.push_back(CuentaBancaria(numero, nombre, saldoInicial));
        cout << "Cuenta creada correctamente.\n";
    }

    CuentaBancaria& buscarCuenta(int numero) {
        for (auto& cuenta : cuentas) {
            if (cuenta.getNumeroCuenta() == numero) {
                return cuenta;
            }
        }
        throw CuentaNoEncontrada("La cuenta no existe.");
    }

    void mostrarCuentas() {
        if (cuentas.empty()) {
            cout << "No hay cuentas registradas.\n";
            return;
        }

        for (const auto& cuenta : cuentas) {
            cout << "Cuenta: " << cuenta.getNumeroCuenta()
                 << " | Titular: " << cuenta.getTitular()
                 << " | Saldo: " << cuenta.consultarSaldo() << endl;
        }
    }
};
int main() {

    Banco banco;
    int opcion;

    do {
        try {
            cout << "\n===== SISTEMA BANCARIO =====\n";
            cout << "1. Crear cuenta\n";
            cout << "2. Depositar dinero\n";
            cout << "3. Retirar dinero\n";
            cout << "4. Consultar saldo\n";
            cout << "5. Mostrar todas las cuentas\n";
            cout << "6. Salir\n";
            cout << "Seleccione una opcion: ";

            cin >> opcion;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Debe ingresar un numero valido.");
            }

            if (opcion < 1 || opcion > 6) {
                throw out_of_range("Opcion fuera de rango.");
            }
            int numero;
            double monto;
            switch (opcion) {
                case 1:
                    banco.agregarCuenta();
                    break;
                case 2:
                    cout << "Numero de cuenta: ";
                    cin >> numero;
                    cout << "Monto a depositar: ";
                    cin >> monto;
                    banco.buscarCuenta(numero).depositar(monto);
                    cout << "Deposito realizado correctamente.\n";
                    break;
                case 3:
                    cout << "Numero de cuenta: ";
                    cin >> numero;
                    cout << "Monto a retirar: ";
                    cin >> monto;
                    banco.buscarCuenta(numero).retirar(monto);
                    cout << "Retiro realizado correctamente.\n";
                    break;
                case 4:
                    cout << "Numero de cuenta: ";
                    cin >> numero;
                    cout << "Saldo actual: "
                         << banco.buscarCuenta(numero).consultarSaldo()
                         << endl;
                    break;

                case 5:
                    banco.mostrarCuentas();
                    break;

                case 6:
                    cout << "Saliendo del sistema...\n";
                    break;
            }

        }
        catch (const CuentaNoEncontrada& e) {
            cout << "ERROR: " << e.what() << endl;
        }
        catch (const invalid_argument& e) {
            cout << "ERROR: " << e.what() << endl;
        }
        catch (const out_of_range& e) {
            cout << "ERROR: " << e.what() << endl;
        }
        catch (const runtime_error& e) {
            cout << "ERROR: " << e.what() << endl;
        }
        catch (const exception& e) {
            cout << "ERROR GENERAL: " << e.what() << endl;
        }
    } while (opcion != 6);

    return 0;
}