//Código que faz o simplex e muito mais
#include <iostream>
#include <fstream>
using namespace std;

string FILE_NAME = "info.txt"; // Nome do arquivo externo
ifstream file;

//AbreArquivo: função que abre o arquivo para leitura, caso não seja possível abrir, ela fecha o progama.
void abreArquivo(){
    file.open(FILE_NAME);
    if(!file.is_open()){
        cout << "Nao foi possivel abrir o arquivo!" << endl;
        file.close();
        exit(0);
    }
}

//Função que fecha o arquivo
void fechaArquivo(){
    file.close();
}

//Função que pega o número de linhas do arquivo, lendo cada linha separadamente
int pegaNumVariavel(){
    abreArquivo();
    string text;
    int variavel = 0;
    file.seekg(0); 
    
    getline(file, text);
    getline(file, text);  //Pegando a segunda linha do arquivo
    
    //Pegando o numero de linhas corretamente
    variavel = stoi(text.substr(text.find(",") - 1, text.find(",")));

    fechaArquivo();
    return variavel; 
}

int pegaNumRestricoes(){
    abreArquivo();
    string text;
    int restricao = 0;
    file.seekg(0); 
    
    getline(file, text);
    getline(file, text);  //Pegando a segunda linha do arquivo
    
    //Pegando o numero de linhas corretamente
    restricao = stoi(text.substr(text.find(",") + 1, text.find(" ")));

    fechaArquivo();
    return restricao; 
}

// Function that return count of the given
// character in the string
int count(string s, char c){
    // Count variable
    int res = 0;
 
    for (int i = 0; i < s.length(); i++){
        // checking character in string
        if (s[i] == c)
            res++;
    }
 
 
    return res;
}

//Função que olha o arquivo e verifica se é de Max ou main
string maxMin(){
    abreArquivo();
    file.seekg(0); //Garante que vai começar da primeira linha
    string palavra; 
    getline(file, palavra); //Palavra que vai receber a primeira linha
    string resposta = palavra.substr(0, 3); //Pegando as 3 letras da minha palavra
    
    //Imprime corretamente a resposta
    if((resposta == "Max") || (resposta == "max")) //Se a resposta for max
        cout << "\nO problema e de Maximizacao." << endl;

    if((resposta == "Min") || (resposta == "min")) //Se a resposta for min
        cout << "\nO problema e de Minimizacao." << endl;

    fechaArquivo();
    return resposta; //Retorna a resposta
}

//Função que cria uma matriz com 0's
float **createMatrix(int l, int c){
    float **matrix = new float*[l];
    
    for(int i  = 0; i < l; i++){
        matrix[i] = new float[c];
    }
    
    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

//Função que imprime uma matriz
void printMatrix(float **matrix, int l, int c){
    cout << "\n\n-------Matriz-------\n\n";
    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

//Função que faz uma cópia de matriz
float **copyMatrix(float **matrix, int l, int c){
    float **copy = createMatrix(l,c);
    
    //Copiando
    for(int i  = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            copy[i][j] = matrix[i][j];
        }
    }
    return copy;
}

//Função que adiciona uma coluna na matriz
float **adicionaColuna(float **matriz, int l, int c){
    float **matrizCopia = copyMatrix(matriz, l, c + 1); //Cria uma copia da matriz com UMA coluna mais
    return matrizCopia;
}

float **geraMatrizArquivo(int l, int c){

    string text; //string que vai receber o getline

    float **matriz = createMatrix(l, c);


    abreArquivo();
    file.seekg(0);
    //Começando da terceira linha p frente
    getline(file, text);
    getline(file, text);
    getline(file, text);
    
    //Função objetivo
    matriz[0][0] = stof(text.substr(0, text.find(",")));
    matriz[0][1] = stof(text.substr(text.find(",") + 1, text.find(" ")));
                
         
    //cout << "TEXTO: " << text << endl;
    //Verifica se o arquivo esta vazio ou nao
    //if(text.length() == 0)
        //cout << "FIM DO ARQUIVO!" << endl;
    //Preenchendo a matriz inicial
    
    //Restrições
    getline(file, text);
    matriz[1][0] = stof(text.substr(0, text.find(",")));
    matriz[1][1] = stof(text.substr(text.find(",") + 1, text.size()));
    matriz[1][c - 1] = stof(text.substr(text.find(";") + 5, text.size()));
    
    getline(file, text);
    matriz[2][0] = stof(text.substr(0, text.find(",")));
    matriz[2][1] = stof(text.substr(text.find(",") + 1, text.size()));
    matriz[2][c - 1] = stof(text.substr(text.find(";") + 5, text.size()));


        //}
    //}
    
    printMatrix(matriz, l, c);
    fechaArquivo();
    
    return matriz;
}

bool verificaSolucao(float **matrix, int l, int c){
    int contador = 0; //Contador para ver o número de elementos negativos no vetor
    
    for(int i = 0; i < c; i++){
        //Percorrendo a linha da função objetivo
        if(matrix[0][i] < 0)
            return true; 
    }

    return false;
}

void modelagem(float **matrix, int l, int c){
    //Verificando se tem solucao
    if(verificaSolucao(matrix,l,c) == true){
        cout << "\nO problema tem solucao.\n";
    }else{
        cout << "\nO problema nao tem solucao.\n";
    }
}

void imprimeAnalise(float **matriz, int l, int c){
    cout << "\n\n-------Matriz-------\n\n";
    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            cout << matriz[i][j] << "x" << j << "\t";
        }
        cout << endl;
    }
}

//Funcao que acha o numero mais negativo na primeira linha da matriz
float *entraNaBase(float **matriz, int l, int c){
    float maisNegativo = -0.1;
    //Posicoes do mais negativo
    float posicaoI = 0;
    float posicaoJ = 0;

    //Percorrendo a primeira linha da matriz
    for(int i = 0; i < l; i ++){
        for(int j = 0; j < c; j++){
            if(matriz[0][j] < maisNegativo){
                maisNegativo = matriz[0][j];
                posicaoJ = j;
                //cout << "POS = " << posicaoJ << endl;
            }
        }
    }
    float *vetPosicao = new float[2];
    vetPosicao[0] = posicaoI;
    vetPosicao[1] = posicaoJ;
    //cout << "Mais negativo = " << maisNegativo << endl; //mais negativo entra na base
    //cout << "X" << vetPosicao[1] << " entra" << endl; 
    return vetPosicao;
}

float *saiDaBase(float **matriz, float *base, int l, int c){
    float *vetDivisao = new float[l-1]; //Vetor que vai armazenar as divisoes

    //j
    int jFixo = base[1];

    int posicaoI = 0;
    int posicaoJ = 0;
    
    //cout << "BASE: " << base[1];

    float *retorno = new float[2]; //vetor de retorno que retorna a posicao de quem entra, encontrando o pivo

    //Ver os valores pra comparar e decidir quem sai da base
    for(int i = 0; i < l; i++){

        if((i != base[0])){
            vetDivisao[i - 1] = matriz[i][c - 1] / matriz[i][jFixo];
            //cout << "\nVetor: " << vetDivisao[i-1];
        }

    }

    float menor;

    for(int i = 0; i < l - 1; i++){
        if(i == 0){
            menor = vetDivisao[i];
        }

        if(menor > vetDivisao[i]){
            menor = vetDivisao[i];
            posicaoI = i; //pegar a posicao certa em linha
        }

    }
    //cout << "\nMenor: " << menor;


    //Vetor que vai armazenar as posicoes i e j do meu retorno
    retorno[0] = posicaoI + 1; //linha do pivo(posicao correta)
    retorno[1] = jFixo;
    
    

    //Temos que a variavel "posicaoI" indica a linha que sera a pivo da nova tabela
    //cout << "\nLinha pivo: " << retorno[0] << endl; //eu so preciso da posicao em linha, já que já possui a em coluna
    //cout << "X" << retorno[1] << " sai" << endl;

    return retorno;
}

//Função que faz a tabela normal e "anterior" do simplex
float **escalonamento(float **matriz, int l, int c){

    float **matriz2 = copyMatrix(matriz,l,c);  //Criando uma copia da primeira matriz para escalonar

    /*
        Oque eu preciso para escalonar{
            1->Ver quem entra e quem sai da base, a funcao sai da base ja chama a que entra.
            2->Dividir a linha do pivo pelo pivo.
            3->Fazer a operacao de escalonamento para tirar o negativo encontrado,e escalonar o resto da matriz.
        }

        Como escalonar{
            1->Li = LiAnterior - (numeroColunaAnteior * pivoAtual)
        }
    */


    float *maisNegativo = entraNaBase(matriz,l,c); //contem linha e coluna de quem entra na base
    float *sai = saiDaBase(matriz, maisNegativo, l,c); //contem linha e coluna de quem sai da base

    int linhaPivo = sai[0]; //pega a linha do meu pivo
    int colunaPivo = sai[1]; //pega a coluna do meu pivo
    
    //X's para imprimir as bases na tela
    int xA = (c - l) + linhaPivo;
    int xB = (colunaPivo + 1);

    cout << "\nX" << xA << " sai.";
    cout << "\nX" << xB << " entra." << endl;
    //cout << "SAI[" << linhaPivo << "][" << colunaPivo << "]" << endl;

    float pivo = matriz[linhaPivo][colunaPivo]; //pega o valor do pivo
    //cout << "Valor do pivo: " << pivo << endl;

    //Comecando a escalonar(dividindo a matriz pela linha pivo)
    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            if((i == linhaPivo) && matriz2[i][j] != 0.0) //gera a nova linha pivo, ignorando divisao por 0
                matriz2[i][j] = matriz2[i][j] / pivo; //dividi a linha pelo pivo

        }
    }
    
    //Escalona toda a matriz
    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            if(i != linhaPivo)
                matriz2[i][j] = ((matriz[i][j]) - (matriz[i][colunaPivo] * matriz2[linhaPivo][j])); //Faz a conta correta do escalonamento
        }
    }

    printMatrix(matriz2,l,c);

    //Imprimir a solucao na última iteração
    if(!verificaSolucao(matriz2, l, c)){
        cout << "\n*Solucao Otima -> Z = " << matriz2[0][c-1] << endl;
        cout << " X" << xB << " = " << matriz2[1][c-1] << endl;
        cout << " X" << (xB - 1) << " = " << matriz2[2][c-1] << endl;
}  

    return matriz2;
}


int main(){
    //Primeiro passo, descobrir o numero variaveis
    int var = pegaNumVariavel();
    cout << "Numero de variaveis: " << var << endl;

    //Segundo passeo, descobrir o numero de restricoes
    int rest = pegaNumRestricoes();
    cout << "Numero de restricoes: " << rest << endl;
    
    //Uma vez que ja tenho o numero de variaveis e restricoes, posso criar uma matriz inicial com 0
    //OBS: Não esquecer de que também existe a linha da funcao objetivo!! -> rest + 1
    //OBS: Não esquecer da coluna das CONSTANTES!! -> var + 1
    int linha = rest + 1;
    int coluna = var + rest + 1;

    //Vendo o numero de linhas do meu arquivo
    string maxOuMin = maxMin();

    float **m3 = geraMatrizArquivo(linha, coluna);

    modelagem(m3,linha,coluna); //Imprimindo se tem ou nao solucao ou nao no inicio


    while(verificaSolucao(m3,linha,coluna)){
        //Verifica se e de Max ou Min
        if(maxOuMin == "Max"){
            m3 = escalonamento(m3,linha,coluna);         
        }
        
        if(maxOuMin == "Min"){
            cout << "Nada ainda" << endl;
            break;
        }
    }

    
    return 0;
}