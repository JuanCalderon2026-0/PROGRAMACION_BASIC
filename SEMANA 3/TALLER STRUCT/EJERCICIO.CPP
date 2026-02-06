#include <iostream>
using namespace std;

struct Producto {
    int codigo;
    char nombre[20];
    float precio;
    int stock;
};

int main() {

    Producto p[5];
    int n = 0, op;

    do {
        cout << "\n1 Registrar";
        cout << "\n2 Mostrar";
        cout << "\n3 Buscar por codigo";
        cout << "\n4 Buscar por nombre";
        cout << "\n5 Mayor stock";
        cout << "\n6 Mas caro";
        cout << "\n7 Total inventario";
        cout << "\n8 Ordenar por precio";
        cout << "\n9 Ordenar por nombre";
        cout << "\n10 Salir";
        cout << "\nOpcion: ";
        cin >> op;

        if(op == 1 && n < 5) {
            cout << "Codigo: "; cin >> p[n].codigo;
            cout << "Nombre: "; cin >> p[n].nombre;
            cout << "Precio: "; cin >> p[n].precio;
            cout << "Stock: "; cin >> p[n].stock;
            n++;
        }

        else if(op == 2) {
            for(int i=0;i<n;i++) {
                cout << "\nCodigo: " << p[i].codigo;
                cout << "\nNombre: " << p[i].nombre;
                cout << "\nPrecio: " << p[i].precio;
                cout << "\nStock: " << p[i].stock << endl;
            }
        }

        else if(op == 3) {
            int c, ok=0;
            cout << "Codigo: "; cin >> c;
            for(int i=0;i<n;i++)
                if(p[i].codigo==c){
                    cout<<p[i].nombre<<" "<<p[i].precio<<" "<<p[i].stock<<endl;
                    ok=1;
                }
            if(ok==0) cout<<"No encontrado\n";
        }

      else if(op == 4) {
    char nom[20];
    int ok = 0;

    cout << "Nombre: ";
    cin >> nom;

    for(int i = 0; i < n; i++) {
        if(p[i].nombre[0] == nom[0]) {   // compara solo la primera letra
            cout << "Codigo: " << p[i].codigo << endl;
            cout << "Nombre: " << p[i].nombre << endl;
            cout << "Precio: " << p[i].precio << endl;
            cout << "Stock: " << p[i].stock << endl;
            ok = 1;
        }
    }

    if(ok == 0)
        cout << "No encontrado\n";
}


        else if(op == 5) {
            int m=0;
            for(int i=1;i<n;i++)
                if(p[i].stock>p[m].stock) m=i;
            cout<<"Mayor stock: "<<p[m].nombre<<endl;
        }

        else if(op == 6) {
            int m=0;
            for(int i=1;i<n;i++)
                if(p[i].precio>p[m].precio) m=i;
            cout<<"Mas caro: "<<p[m].nombre<<endl;
        }

        else if(op == 7) {
            float total=0;
            for(int i=0;i<n;i++)
                total+=p[i].precio*p[i].stock;
            cout<<"Total: "<<total<<endl;
        }

        else if(op == 8) { // ordenar por precio
            for(int i=0;i<n-1;i++)
                for(int j=i+1;j<n;j++)
                    if(p[i].precio < p[j].precio){
                        Producto aux=p[i];
                        p[i]=p[j];
                        p[j]=aux;
                    }
            cout<<"Ordenado por precio.\n";
        }

        else if(op == 9) { // ordenar por nombre
            for(int i=0;i<n-1;i++)
                for(int j=i+1;j<n;j++){
                    int k=0;
                    while(p[i].nombre[k]==p[j].nombre[k] && p[i].nombre[k]!='\0') k++;
                    if(p[i].nombre[k] > p[j].nombre[k]){
                        Producto aux=p[i];
                        p[i]=p[j];
                        p[j]=aux;
                    }
                }
            cout<<"Ordenado por nombre.\n";
        }

    } while(op != 10);

    return 0;
}
