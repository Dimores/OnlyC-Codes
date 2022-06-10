// Programa que vai servir como um "symbolab" de Grafos, analisando os possíveis conceitos de grafos
// nao direcionados.
//
// O programa vai ter que ler o arquivo de texto, montar uma matriz de ajdacencia, e uma matriz de
// indicendia, em que ambas seriam a representacao do grafo. Com essas matrizes vamos conseguir
// analisar os conceitos do grafo.
//
// Objetivo secundario: deixar a funcao main mais "limpa" possivel.
//
// No arquivo de teste temos o exemplo de um grafo completo de 4 vertices.r

#include <iostream>
#include <fstream>

using namespace std;

string FILE_NAME = "teste.txt"; // nome do arquivo externo
ifstream file;

//Funções de leitura do arquivo
   
    //Open_file: função que abre o arquivo para leitura, caso não seja possível abrir, ela fecha o progama.
void open_file(){
    file.open(FILE_NAME);
    if(!file.is_open()){
        cout << "Nao foi possivel abrir o arquivo!" << endl;
        file.close();
        exit(0);
    }
}

    //Close_file: função que fecha o arquivo.
void close_file(){
    file.close();
}

    //Get_vertice: função que pega o valor do vértice no arquivo.
int pegaVertice(){
    string text;
    int vertice;
    file.seekg(0); 
    getline(file, text);
    vertice = stoi(text);
    return vertice;        
}

    //Get_aresta: função que pega o valor de arestas no arquivo.
int pegaArestas(){
    string text;
    int aresta;
    file.seekg(0); 
    getline(file, text);
    getline(file, text);
    aresta = stoi(text.substr(text.find(",") + 1, text.size() - text.find(",") + 1));
    return aresta;        
}

    //Get_vertice: função que pega as ligaçoes do arquivo.
        //Essa função retorna uma matriz, de [a][2], contendo todas as ligações.
int **get_ligacoes(){
    int **ligacoes;
    int arestas = pegaArestas();
    string text;

    //garantir que vamos começar da segunda linha
    file.seekg(0); 
    //vai para a segunda linha
    getline(file, text);
	getline(file, text);
    ligacoes = new int*[arestas];
    for (int i = 0; i < arestas; i++){
        ligacoes[i] = new int[2];
    }

    for (int i = 0; i < arestas; i++){
        getline(file, text);
        ligacoes[i][0] = stoi(text.substr(0, text.find(";")));
        ligacoes[i][1] = stoi(text.substr(text.find(";") + 1, text.size() - text.find(",") + 1));
    }

//     for (int i = 0; i < arestas; i++){
//        cout << ligacoes[i][0] << "--" << ligacoes[i][1] << endl;
//    }

    return ligacoes;
}

//Funções para matriz

    //Criar_Matriz: cria uma matriz com os valores dados, e a preenche com 0.
int **criar_matriz(int linha, int coluna){
    int **matriz;
    matriz = new int*[linha];
    for (int i = 0; i < linha; i++){
        matriz[i] = new int[coluna];
    }

    for (int i = 0; i < linha; i++){
        for (int j = 0; j < coluna; j++){
            matriz[i][j] = 0;
        }
    }

    return matriz;
}

    //imprimir_matriz: Funcao que imprime qualquer matriz
void imprimir_matriz(int **matriz, int linha, int coluna){
    for (int i = 0; i < linha; i++){
        for (int j = 0; j < coluna; j++){
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

    //imprimir_matriz_adj: Fucao que imprime de forma stilizada a matriz de adjacencia.
void imprimir_matriz_adj(int **matriz_adj, int vertice){
    cout << "\n\tMatriz de Adjacendia\n" << endl;
    cout << "\t";
    for(int i = 0; i < vertice; i++){
        cout << "v" << i + 1 << "\t";
    }
    cout << endl;
    for (int i = 0; i < vertice; i++){
        cout << "v" << i + 1 << "\t";
        for (int j = 0; j < vertice; j++)
            cout << matriz_adj[i][j] << "\t";
        cout << endl;
    }
    cout << endl;
}

    //imprimir_matriz_inc: Fucao que imprime de forma stilizada a matriz de incidencia.
void imprimir_matriz_inc(int **matriz_inc, int vertice, int aresta){
    cout << "\n\tMatriz de Incidencia\n" << endl;
    cout << "\t";
    for(int i = 0; i < vertice; i++)
        cout << "v" << i + 1 << "\t";
    cout << endl;
    for (int i = 0; i < aresta; i++){
        cout << "a" << i + 1 << "\t";
        for (int j = 0; j < vertice; j++)
            cout << matriz_inc[i][j] << "\t";
        cout << endl;
    }
    cout << endl;
}

    //Preencher_matriz_adj: dada a lista, essa funcao preenche a matriz de adj de forma correta.
void preencher_matriz_adj(int **matriz_adj, int aresta, int **ligacoes){
    int l1, l2;

    for (int i = 0; i < aresta; i++){
        matriz_adj[ligacoes[i][0] - 1][ligacoes[i][1] - 1] = 1;
        matriz_adj[ligacoes[i][1] - 1][ligacoes[i][0] - 1] = 1;
    }
}

    //Preencher_matriz_inc: dada a lista, essa funcao preenche a matriz de inc de forma correta.
void preencher_matriz_inc(int **matriz_inc, int aresta, int **ligacoes){

    for (int i = 0; i < aresta; i++){
        matriz_inc[i][ligacoes[i][0] - 1] += 1;
        matriz_inc[i][ligacoes[i][1] - 1] += 1;
    }
}

int main(){
    //leitura do arquivo
    open_file();
    int v = pegaVertice();
    int a = pegaArestas();
    int **l = get_ligacoes();
    close_file();

    //saida dos dados recebidos do arquivo lido.
    cout << "vertice = " << v << endl;
    cout << "arestas = " << a << endl;
    cout << "\nligacoes:\n" << endl;
    imprimir_matriz(l, a, 2);

    //criacao e preenchimento e impressao das matrizes.
    int **m_adj = criar_matriz(v, v);
    preencher_matriz_adj(m_adj, a, l);

    int **m_inc = criar_matriz(a, v);
    preencher_matriz_inc(m_inc, a, l);

    imprimir_matriz_adj(m_adj, v);
    imprimir_matriz_inc(m_inc, v, a);

    //teste: verifica se o grafo é determinado tipo, caso Verdadeiro ele ira imprimir uma mensagem, se não vai apenas ignorar.
/*  if(is_simples(m_adj, m_inc, v, a))
        cout << "E simples!" << endl;
    
    if(is_multigrafo(m_adj, m_inc, v, a))
        cout << "E multigrafo!" << endl;
    
    if(is_pseu_do_grafo(m_adj, m_inc, v, a))
        cout << "E pseu do grafo!" << endl;
    
    if(is_reflexivo(m_adj, m_inc, v, a))
        cout << "E reflexivo!" << endl;

    if(is_vazio_v1(m_adj, m_inc, v, a))
        cout << "E vazio!" << endl;

    if(is_nulo(m_adj, m_inc, v, a))
        cout << "E nulo!" << endl;

    if(is_grafo_trivial(m_adj, m_inc, v, a))
        cout << "E trivial!" << endl;

    if(is_completo(m_adj, m_inc, v, a))
        cout << "E completo!" << endl;

    if(is_regular(m_adj, m_inc, v, a))
        cout << "E regular!" << endl;*/

    return 0;
}
