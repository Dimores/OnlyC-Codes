//Código que faz o simplex e muito mais
#include <iostream>
#include <fstream>
#include <vector>
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

//Função que pega o número de linhas do arquivo
int pegaNumLinhas(){
    abreArquivo();
    string text;
    file.seekg(0); 
    
    int linhas = 0;

    while(file){
        getline(file, text);
        linhas++;
    }
    
    fechaArquivo();
    return linhas - 2; //Excluindo a primeira, e a linha vazia no final
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

int count(string s, char c){
    
    int res = 0;
 
    for (int i = 0; i < s.length(); i++){
        
        if (s[i] == c)
            res++;
    }
 
 
    return res;
}

//Funcao que separa substring em um vetor, e converte <= em 1,e >= em -1
string split(string texto, string separador){
    vector<string> country{};
    int position;
    string outstr, token;

    string retorno;

    while ((position = texto.find(separador)) != string::npos) {

        token = texto.substr(0, position);

        //Remove the extra space from the front of the splitted string
        country.push_back(token.erase(0, token.find_first_not_of("")));
        texto.erase(0, position + separador.length());
    }



    int i = 0;
    //Print all splitted word except the last one
    for (const auto &outstr : country) {
        cout << outstr << endl;
        retorno += country[i];
        i++;
    }

    retorno += texto;
    //Print the last splitted word
    //cout << retorno << endl;

    return retorno;
} 

//Funcao que vai ler o arquivo e contar o numero de <= que encontrar
int pegaMenorIgual(){
    //Chamando a funcao para verificar o numero de linhas, e subtrair dos 3 getline lidos
    int linhas = pegaNumLinhas() - 3;
    abreArquivo();
    string text;
    int menorIgual = 0;
    file.seekg(0); 

    getline(file, text);
    getline(file, text);  
    getline(file, text);

    //Apartir da quarta linha, verificar o numero de menores iguais
    for(int i = 0; i <= linhas; i++){
        getline(file, text);
        menorIgual += count(text, '<'); //Menor já me garante que é <=
    }

    fechaArquivo();
    return menorIgual; 
}

//Funcao que vai ler o arquivo e contar o numero de >= que encontrar
int pegaMaiorIgual(){
    //Chamando a funcao para verificar o numero de linhas, e subtrair dos 3 getline lidos
    int linhas = pegaNumLinhas() - 2;
    abreArquivo();
    string text;
    int maiorIgual = 0;
    file.seekg(0); 

    getline(file, text);
    getline(file, text);  
    getline(file, text);

    //Apartir da quarta linha, verificar o numero de menores iguais
    for(int i = 0; i <= linhas; i++){
        getline(file, text);
        maiorIgual += count(text, '>'); //Maior já me garante que é >=
    }

    fechaArquivo();
    return maiorIgual; 
}

//Função que faz o módulo de qualquer float
float modulo(float numero){
    if(numero < 0)
        numero = numero * -1;
    return numero;
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

//------------------------------------Casos Especiais------------------------------------
//Multiplas solucoes
bool verificaMultiplasSolucoes(float **matriz, int l, int c){ //Creditos Arthur
    int controle = 1;

    for(int j = 0; j < c - 1; j++){
        for(int i = 0; i < l; i++){
            if(i == 0){
                if(matriz[i][j] == 0){
                    controle = 1;
                }else{
                    controle = 0;
                    break;
                }

            }else{ 
                if(matriz[i][j] != 0){
                    controle = 1;
                }else{
                    controle = 0;
                    break;
                }
            }
        }
        if(controle == 1)
            break;
    }

    if(controle == 1)
        return true;
    else
        return false;
}

//Solução ilimitado
bool verificaSolucaoIlimitada(float **matriz, int l, int c){
    //Se escalonar mais de 20 vezes, será ilimitada.
    cout << "Nao faz nada ainda";
    return false;
}

//Sem resposta
bool verificaSemSolucao(float **matriz, int l, int c){
    //Ja esta feito no entra na base.
    cout << "Nao faz nada";
    return false;
}

//Degenerada
bool verificaDegenerada(float **matriz, int l, int c){
    cout << "Nao faz nada";
    return false;   
}
//---------------------------------------------------------------------------------------

//Função que adiciona uma coluna na matriz
float **adicionaColuna(float **matriz, int l, int c){
    float **matrizCopia = copyMatrix(matriz, l, c + 1); //Cria uma copia da matriz com UMA coluna mais
    return matrizCopia;
}

//Criar o vetor de variaveis basicas(x1,x2,...)
int *varBasica(int l){
    int *basicas = new int[l-1];
    for(int i = 0; i < l-1; i++){
        basicas[i] = i;
        // cout << basicas[i] + 1 << " ";
    }
    // cout << endl;
    return basicas;
}

//Criar o vetor de variaveis nao basicas(x3,x4,...)
int *varNaoBasica(int l, int c){
    int *naoBasica = new int[c-1];
    for(int i = c - l; i < c - 1; i++){
        naoBasica[i] = i;
        // cout << naoBasica[i] + 1 << " ";
    }
    // cout << endl;
    return naoBasica;
}

// float **geraMatrizCasamento(int l, int c){
//     float **m = createMatrix(l,c);
//     //Preenchendo estaticamente
//     m[0][0] = 
//     m[0][1] = 
//     m[0][2] = 
//     m[0][3] = 
//     m[0][4] = 
//     m[0][5] = 
//     m[0][6] = 
//     m[0][7] = 
//     m[0][8] = 
//     m[0][9] = 
//     m[0][10] = 
//     m[0][11] = 
//     m[0][12] = 
//     m[0][13] = 
//     m[0][14] = 
//     m[0][15] = 
//     m[0][16] = 
//     m[0][17] = 
//     m[0][18] = 
//     m[0][19] = 
//     m[0][20] = 
//     m[0][21] = 
//     m[0][22] = 
//     m[0][23] = 
//     m[0][24] = 
//     m[0][25] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 
//     m[0][0] = 

// }

float **geraMatrizArquivo(int l, int c){

    string text; //string que vai receber o getline

    float **matriz = createMatrix(l, c);

    abreArquivo();
    file.seekg(0);
    //Começando da funcao objetivo(terceira linha)
    getline(file, text);
    getline(file, text);
    getline(file, text);

    //Contar o número de virgúlas na linha da função objetivo e somar 1 para obter a quantidade de números.
    //A variável quantidadeFuncObjetivo vai receber esse valor
    int quantidadeFuncObjetivo = count(text, ',') + 1;
    // cout << "Quantidade = " << quantidadeFuncObjetivo << endl;

    //Para cada valor, converter a subString para float e guardar na primeira linha da matriz(Z)
    for(int j = 0; j < quantidadeFuncObjetivo; j++){
        if(j != quantidadeFuncObjetivo - 1){
        matriz[0][j] = stof(text.substr(0, text.find(",")));

        //Como já leu o conteúdo antes da vírgula, precisa ler o conteúdo depois da vírgula, para isso
        //Precisa-se transformar a String no restante dela.
        text = text.substr(text.find(",") + 2, text.size());
        }
        //Tratando o último número da função objetivo
        else
            matriz[0][j] = stof(text.substr(0, text.size()));

    }

    int contador = 0;

    //Com a função objetivo preenchida corretamente, precisa-se preencher o resto da matriz.
    //Como já foi lida a primeira linha, só é necessário ler (l - 1) linhas.
    for(int i = 1; i < l; i++){
        getline(file, text);
        for(int j = 0; j < c - 1 ; j++){
            if(j == c - 2 ){
                matriz[i][c-1] = stof(text.substr(text.size() - text.find(","), text.size()));
            }else if(text.substr(0, text.find(",")) == "<="){
                matriz[i][j + contador] = 1;
                contador++;
               
            }else{
                matriz[i][j] = stof(text.substr(0, text.find(",")));
                text = text.substr(text.find(",") + 2, text.size());
            }
        }
    }
    
    printMatrix(matriz, l, c);
    fechaArquivo();
    
    return matriz;
}

//Funcao que verifica se o problema tem solucao, depende se for de maximizacao ou minimizacao
bool verificaSolucao(float **matrix, int l, int c, string maxMinimo){
    int contador = 0; //Contador para ver o número de elementos negativos no vetor
    
    for(int i = 0; i < c; i++){
        //Percorrendo a linha da função objetivo
        if(matrix[0][i] < 0 && maxMinimo == "Max")
            return true; 

        if(matrix[0][i] > 0 && maxMinimo == "Min")
            return true; 
    }

    return false;
}

void modelagem(float **matrix, int l, int c, string maxMinimo){
    //Verificando se tem solucao
    if(verificaSolucao(matrix,l,c, maxMinimo) == true){
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

//Converter a linha que possui >= da matriz
float **converteMatriz(float **matriz, int l, int c){
    int numLinhas = pegaNumLinhas() -2;
    int *posicaoI = new int[numLinhas];

    abreArquivo();
    string text;
    file.seekg(0);
    getline(file, text);
    getline(file, text);
    getline(file, text);

    for(int i = 0; i < numLinhas; i++){
        getline(file, text);
        if(text.find(">=")){
            posicaoI[i] = 1;
        }

        if(text.find("<=")){
            posicaoI[i] = 0;
        }
    }

    fechaArquivo();

    for(int i = 1; i < l; i++){
        for(int j = 0; j < c; j++){
            if(posicaoI[i] == 1){
                matriz[i][j] = (matriz[i][j]) * -1;
            }else{
                
            }
        }
    }

    return matriz;
}

//Funcao que retorna a posicao de quem entra na base, depende se for de Max ou Min
float *entraNaBase(float **matriz, int l, int c, string maxMinimo){
    int *basicas = varBasica(l);
    int *naoBasica = varNaoBasica(l, c);
    //Posicoes de quem entra na base
    float posicaoI = 0;
    float posicaoJ = 0;
    float entraBase;

    if(maxMinimo == "Max"){
        entraBase = -0.1;
        //Uma vez que ja sei que o que entra na base Inicialmente(Max) é menor que 0, e o de Min é o contrario, eu verifico
        //dentro do for

        //Percorrendo a primeira linha da matriz
        for(int i = 0; i < l; i ++){
            for(int j = 0; j < c; j++){
                if(matriz[0][j] < entraBase){
                    entraBase = matriz[0][j];
                    posicaoJ = j;
                    //cout << "POS = " << posicaoJ << endl;
                }

            }
        }
    }else if(maxMinimo == "Min"){ //Se o problema for de minimizacao, quem entra na base é o mais positivo.
        entraBase = 0.1;

        //Percorrendo a primeira linha da matriz
        for(int i = 0; i < l; i ++){
            for(int j = 0; j < c; j++){
                if(matriz[0][j] > entraBase){
                    entraBase = matriz[0][j];
                    posicaoJ = j;
                    //cout << "POS = " << posicaoJ << endl;
                }
            }
        }
    }else{
        cout << "Erro no arquivo, o problema tem que ser de Maximizacao ou de Minimizacao." << endl;
        exit(0);
    }

    //Se entra na base for 0.1 ou -0.1, quer dizer que ninguém entrou na base, logo não tem solução
    if((entraBase == 0.1) || (entraBase == -0.1)){
        cout << "Nao tem quem entre na base, nao tem solucao.";
        exit(0);
    }

    
    float *vetPosicao = new float[2];
    vetPosicao[0] = posicaoI;
    vetPosicao[1] = posicaoJ;

    //Imprimir quem entra na base
    for(int i = 0; i < c - 2; i++){
        if(basicas[i] == posicaoJ){
            cout << "\nX" << basicas[i] + 1 << " entra na base." << endl;
            break;
        }
        if(naoBasica[i] == posicaoJ){
            cout << "\nX" << naoBasica[i] + 1 << " entra na base." << endl;
            break;
        }
    }
    //cout << "Mais negativo = " << maisNegativo << endl; //mais negativo entra na base
    //cout << "X" << vetPosicao[1] << " entra" << endl; 
    return vetPosicao;
}

float *saiDaBase(float **matriz, float *base, int l, int c){
    int *basicas = varBasica(l);
    int *naoBasica = varNaoBasica(l, c);
    float *vetDivisao = new float[l-1]; //Vetor que vai armazenar as divisoes

    //j
    int jFixo = base[1];

    int posicaoI = 0;
    int posicaoJ = 0;

    float constanteMaisNegativa = -0.1;
    
    //cout << "BASE: " << base[1];

    float *retorno = new float[2]; //vetor de retorno que retorna a posicao de quem entra, encontrando o pivo

    //Ver os valores pra comparar e decidir quem sai da base
    for(int i = 0; i < l; i++){
        if((i != base[0]) && (matriz[i][jFixo] > 0)){
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
    // cout << "X" << retorno[1] << " sai" << endl;

    cout << "X" << (c - l) + retorno[0] << " sai da base.";
    return retorno;
}

float *saiDaBaseDual(float **matriz, int l, int c){
    int posicaoJ = c-1; //Sempre vai ser a última coluna(constantes)
    int posicaoI = 0; //Precisa-se saber a posicao em linha de quem vai sair da base

    float constMaisNegativa = -0.1;

    for(int i = 0; i < l; i++){
        
        if(matriz[i][c-1] < constMaisNegativa){
            constMaisNegativa = matriz[i][c-1];
            posicaoI = i;
        }
    }

    //Retorno da funcao
    float *retorno = new float[2];
    retorno[0] = posicaoI;
    retorno[1] = posicaoJ;

    return retorno;
}

float *entraNaBaseDual(float **matriz, float *saiDaBase, int l, int c){
    //Primeiro pegar a posicao de quem sai da base
    saiDaBase = saiDaBaseDual(matriz,l,c);
    int sai = saiDaBase[0];

    int posicaoEntra = 0;

    float *vetDivisao = new float[c];

    //Preenchendo o vetor com 0 para evitar lixo de memoria
    for(int i = 0; i < c; i++){
        vetDivisao[i] = 0;
    }

    for(int j = 0; j < c; j++){
        if((matriz[0][j] != 0) && (matriz[sai][j] != 0)){
            vetDivisao[j] = modulo(matriz[0][j] / matriz[sai][j]);
        }
    }

    float menor;

    for(int j = 0; j < c; j++){
        if(j == 0){
            menor = vetDivisao[j];
        }

        if((menor < vetDivisao[j]) && (menor != 0) && (vetDivisao[j] != 0)){
            menor = vetDivisao[j];
            posicaoEntra = j; //pegar a posicao certa em coluna
        }
    }

    float *retorno = new float[2];
    retorno[0] = 0; //Posicao I sempre será 0 para quem entra
    retorno[1] = posicaoEntra;
    
    return retorno;
}

//Função que faz a tabela normal e "anterior" do simplex
float **escalonamento(float **matriz, int l, int c, string maxMinimo){
    int *basicas = new int[l-1];
    int *nBasicas = new int[c-2];

    int contagem = 0;
    for(int i = 0; i < l - 1; i++){
        basicas[i] = i;
        contagem++;
    }

    for(int i = contagem; i < c - 2; i++){
        nBasicas[i] = i;
    }

    //Primeiro verificar se vai usar dual ou não
    int numMaiorIgual = pegaMaiorIgual();

    //Se for maior que 0, vai ter que usar o dual
    if(numMaiorIgual > 0){
        float **matriz3 = copyMatrix(matriz,l,c);
        matriz3 = converteMatriz(matriz3,l,c);

        float *constMaisNegativa = saiDaBaseDual(matriz,l,c);
        float *entra = entraNaBaseDual(matriz, constMaisNegativa,l,c);

        int linhaPivo = constMaisNegativa[0];
        int colunaPivo = entra[1];


        // int xA = (c - l) + linhaPivo;
        // int xB = (colunaPivo + 1);

        float pivo = matriz[linhaPivo][colunaPivo]; //pega o valor do pivo
        //cout << "Valor do pivo: " << pivo << endl;

        //Comecando a escalonar(dividindo a matriz pela linha pivo)
        for(int i = 0; i < l; i++){
            for(int j = 0; j < c; j++){
                if((i == linhaPivo) && matriz3[i][j] != 0) //gera a nova linha pivo, ignorando divisao por 0
                    matriz3[i][j] = matriz3[i][j] / pivo; //dividi a linha pelo pivo

            }
        }
        
        //Escalona toda a matriz
        for(int i = 0; i < l; i++){
            for(int j = 0; j < c; j++){
                if(i != linhaPivo)
                    matriz3[i][j] = ((matriz[i][j]) - (matriz[i][colunaPivo] * matriz3[linhaPivo][j])); //Faz a conta correta do escalonamento
            }
        }

        printMatrix(matriz3,l,c);

        //Imprimir a solucao na última iteração
        if(!verificaSolucao(matriz3, l, c, maxMinimo)){
            cout << "\n*Solucao Otima -> Z = " << matriz3[0][c-1] << endl;
            for(int i = 0; i < l - 1; i++){

            }
        }  

        return matriz3;
    }else{
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



        float *maisNegativo = entraNaBase(matriz,l,c, maxMinimo); //contem linha e coluna de quem entra na base
        float *sai = saiDaBase(matriz, maisNegativo, l,c); //contem linha e coluna de quem sai da base

        int linhaPivo = sai[0]; //pega a linha do meu pivo
        int colunaPivo = sai[1]; //pega a coluna do meu pivo

        basicas[linhaPivo] = sai[1];
        
        //X's para imprimir as bases na tela
        int xA = (c - l) + linhaPivo;
        int xB = (colunaPivo + 1);

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
        if(!verificaSolucao(matriz2, l, c, maxMinimo)){
            cout << "\n*Solucao Otima -> Z = " << matriz2[0][c-1] << endl;
            for(int i = 1; i < l; i++){
                cout << "X" << i << " = " << matriz2[i][c-1] << endl;
            }
        }  

        return matriz2;
    }
}

int main(){
    //Primeiro passo, descobrir o numero variaveis
    int var = pegaNumVariavel();
    // cout << "Numero de variaveis: " << var << endl;

    //Segundo passeo, descobrir o numero de restricoes
    int rest = pegaNumRestricoes();
    // cout << "Numero de restricoes: " << rest << endl;
    
    //Uma vez que ja tenho o numero de variaveis e restricoes, posso criar uma matriz inicial com 0
    //OBS: Não esquecer de que também existe a linha da funcao objetivo!! -> rest + 1
    //OBS: Não esquecer da coluna das CONSTANTES!! -> var + 1
    int linha = rest + 1;
    int coluna = var + rest + 1;

    //Variavel que recebe a primeira linha do arquivo, vendo se o problema é de Max ou Min
    string maxOuMin = maxMin();

    float **m3 = geraMatrizArquivo(linha, coluna);

    modelagem(m3,linha,coluna, maxOuMin); //Imprimindo se tem ou nao solucao ou nao no inicio

    while(verificaSolucao(m3,linha,coluna, maxOuMin)){
        //Verifica se e de Max ou Min
       if((maxOuMin == "Max")){
           m3 = escalonamento(m3,linha,coluna, maxOuMin);
           if(verificaMultiplasSolucoes(m3,linha,coluna)){
                cout << "Multiplas solucoes." << endl;
                break;
           }         
       }
    }
    
    return 0;
}