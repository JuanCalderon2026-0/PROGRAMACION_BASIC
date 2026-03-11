    #include <iostream>
    using namespace std;
    int main () {
        int opcion;
     cout<<"Seleccione alguna de estas opciones: "<<endl;
     cout<<"1.Suma"<<endl;
    cout<<"2.Resta"<<endl;
     cout<<"3. Multiplicación"<<endl;
     cout<<"4. Division"<<endl;
    cin >> opcion;
    switch (opcion) {
        case 1:
            cout << "Suma";
            break;
        case 2:
            cout << "Resta";
            break;
        case 3:
            cout << "Multiplicación";
            break;
        case 4:
            cout << "División";
            break;
        default:
            cout << "Opción no válida";
    }
        return 0;
    }
