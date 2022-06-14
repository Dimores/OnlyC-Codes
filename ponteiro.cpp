#include <iostream>
using namespace std;

// Funcao que vai gerar um vetor unidimensional
int *geraVetor(int n){

    int *vet = new int[n];
	
	// Preenchendo o vetor
	for(int i = 0; i < n; i++){
		cout << "Informe o valor da posicao " << i + 1 << ": ";
		cin >> vet[i];
		cout << endl;
	}
	
	return vet;
	
}

// Funcao que vai imprimir o vetor unidimensional
void imprimeVetor(int *vet, int n){
	
	cout << "Vetor: \n\n";
	cout << "[";
	
	//Imprimir o valor primeira posicao do vetor
	cout << vet[0];
	
	for(int i = 0; i < n; i++){
		
		if(i != 0){
			cout << ", " << vet[i];
		}
	}
	
	cout << "]\n";
	
}

int main(){

    /*   -->Variaveis criadas<--

        n = Tamanho do vetor
        *p = Ponteiro para inteiro(aponta para a primeira posicao do vetor)


        -->Funcoes criadas<--

        *geraVetor(int n) = Ponteiro de uma funcao. Atribui a funcao um ponteiro(no caso *p) e gera o vetor com o tamanho n.

        imprimeVetor(int *vet, int n) = Tem como parametro um vetor, em que eu passo um vetor criado(no caso *p), por isso o primeiro parametro tera que ser um vetor,
        e como segundo parametro o tamanho do vetor(no caso n).

    */

    int n = 0;

    cout << "\n ------------------->> Programa vetor unidimensional: <<-------------------\n\n";

    cout << "Informe o numero de elementos do vetor: ";
    cin >> n;
    cout << endl;

    // Criacao do vetor
    int *p = geraVetor(n);

    // Imprimindo o vetor
    imprimeVetor(p, n);

    cout << " -------------------------------------------------------------------------\n";

    return 0;

}
