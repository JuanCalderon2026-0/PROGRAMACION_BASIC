#include <iostream>
using namespace std;
int main () {
    int Hora;
    cout<<"Ingrese una hora del dia del 0 al 23: ";
    cin>> Hora;
    if(Hora<=11)
    cout<<"Buenos dias";
    else if (Hora<=18)
    cout<<"Buenas tardes";  
    else if (Hora<=23)
    cout<<"Buenas noches";
    else
    cout<<"error";
    return 0;
}
