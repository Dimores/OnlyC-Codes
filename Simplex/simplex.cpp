//Código que faz o simplex e muito mais
#include <iostream>
using namespace std;

//Função que cria uma matriz com 0's
int **createMatrix(int l, int c){
    int **matrix = new int*[l];
    
    for(int i  = 0; i < l; i++){
        matrix[i] = new int[c];
    }
    
    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

//Função que imprime uma matriz
void printMatrix(int **matrix, int l, int c){
    cout << "\n\n-------Matriz-------\n\n";
    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

//Função que faz uma cópia de matriz
int **copyMatrix(int **matrix, int l, int c){
    int **copy = new int*[l];
    
    for(int i  = 0; i < l; i++){
        copy[i] = new int[c];
    }
    
    //Copiando
    for(int i  = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            copy[i][j] = matrix[i][j];
        }
    }
    return copy;
}

bool verificaSolucao(int **matrix, int l, int c){
    int *aux  = new int[c];
    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            //Percorrendo a linha da função objetivo
            if(i == 0){
                aux[i] = matrix[i][j];
            }
        }
    }
    
    for(int i = 0; i < l; i++){
        if(aux[i] < 0){
            return true;
        }
    }
    return false;
}

void modelagem(int **matrix, int l, int c){
    //Verificando se tem solucao
    if(verificaSolucao(matrix,l,c) == true){
        cout << "\n\nO problema tem solucao.\n\n";
    }else{
        cout << "\nO problema nao tem solucao.\n\n";
    }
}

//Função que faz a tabela normal e "anterior" do simplex
void escalonamento(int l, int c){
    int **m1 = createMatrix(l,c);
    int **m2 = copyMatrix(m1,l,c);
    
    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            m2[i][j] += 1;
        }
    }
    printMatrix(m1,l,c);
    printMatrix(m2,l,c);
    modelagem(m2,l,c);
}


int main(){
    escalonamento(4,3);
    
    
    return 0;
}

