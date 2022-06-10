#include <iostream>
using namespace std;

int main(){

    //ponteiro p para inteiro
    int *p;

    //tamanho do vetor
    int n = 0;

    cout << "\n ------------------->> Programa vetor unidimensional: <<-------------------\n\n";

    cout << "Informe o numero de elementos do vetor: ";
    cin >> n;
    cout << endl;

    p = new int[n];

    // Preenchendo o vetor
    for(int i = 0; i < n; i++){
        cout << "Informe um numero: ";
        cin >> p[i];
        cout << endl;
    }

    // Imprimindo o vetor
    cout << "\nVetor: \n\n";

    cout << "[";
    cout << p[0];

    for(int i = 0; i < n; i++){

        if(i != 0 ){
            cout << ", " << p[i];
        }
    }

    cout << "]\n";

    cout << " -------------------------------------------------------------------------\n";

    return 0;

}