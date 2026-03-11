#include <iostream>
using namespace std;

int main() {

    int n;
    cout << "Cuantas temperaturas? ";
    cin >> n;
	 int t[100];
	  int max = t[0];
    int min = t[0];
    int mayores30 = 0;

    for(int i=0;i<n;i++){
        cin >> t[i];
    }


    for(int i=0;i<n;i++){

        if(t[i] > max) max = t[i];
        if(t[i] < min) min = t[i];
        if(t[i] > 30) mayores30++;
            }

    cout << "Maxima: " << max << endl;
    cout << "Minima: " << min << endl;
    cout << "Mayores a 30: " << mayores30;

    return 0;
}

