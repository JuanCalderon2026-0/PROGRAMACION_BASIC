#include <iostream>
using namespace std;

// Función para determinar el mayor de dos números
void espar(int n){
	if (n%2==0){
		cout<<"es par";
	}
	else {
	cout<< "es impar";
	}
}
int main(){
	int num;
    cout << "Ingrese un numero: ";
    cin >> num;
    espar(num);


    return 0;
    
}