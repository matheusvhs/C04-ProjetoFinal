//Trabalho Pokedex - C04
/*Alunos:
Guilherme Bastos Florêncio - 322 - GES
Matheus Vieira Honorio de Souza - 525 - GES
Otavio Augusto Silva Lima - 279 - GES
Vinicius Vilela Paulino - 436 - GES
Vitor Dias Carlos - 445 - GES
*/
//O código cria cidades com nome, código, e se tem ou nao centro Pokemon, e mostra a cidade cadastrada.

#include <iostream>
#include <string>
#include <list>
#include <climits>

using namespace std;

struct estrada{ //estrutura estrada
  int origem;
  int destino;
  int distancia;
};

struct Cidade{ //estrutura cidade
  int codigo;
  string nome;
  bool centro_pokemon;
  list<estrada> vizinhos;
};

int  dijkstra(Cidade cidade[], int nVertices, int start, int end){
  bool intree[nVertices];
  int distance[nVertices], parent[nVertices];
  for(int u = 0; u < nVertices; u++){
    intree[u] = false;
    distance[u] = INT_MAX;
    parent[u] = -1;
  }
  distance[start] = 0;
  int v = start;
  while(intree[v] == false){
    intree[v] = true;
    list<estrada>::iterator p;
    for(p = cidade[v].vizinhos.begin(); p != cidade[v].vizinhos.end(); p++){
      int dest = p->destino;
      int weight = p->distancia;
      if(distance[dest] > distance[v]+weight){
        distance[dest] = distance[v]+weight;
        parent[dest] = v;

      }
    }

      v = 0;
      int dist = INT_MAX;
    for(int u = 0; u < nVertices; u++){
      if(intree[u] == false && dist > distance[u]){
        dist = distance[u];
        v = u;
      }
    }
  }

  return distance[end];
  
}

void  show_dijkstra(Cidade cidade[], int nVertices, int start, int end){
  bool intree[nVertices];
  int distance[nVertices], parent[nVertices];
  for(int u = 0; u < nVertices; u++){
    intree[u] = false;
    distance[u] = INT_MAX;
    parent[u] = -1;
  }
  distance[start] = 0;
  int v = start;
  while(intree[v] == false){
    intree[v] = true;
    list<estrada>::iterator p;
    for(p = cidade[v].vizinhos.begin(); p != cidade[v].vizinhos.end(); p++){
      int dest = p->destino;
      int weight = p->distancia;
      if(distance[dest] > distance[v]+weight){
        distance[dest] = distance[v]+weight;
        parent[dest] = v;

      }
    }

      v = 0;
      int dist = INT_MAX;
    for(int u = 0; u < nVertices; u++){
      if(intree[u] == false && dist > distance[u]){
        dist = distance[u];
        v = u;
      }
    }
  }

	int caminho[nVertices], x = 0;
	cout<<"Menor caminho: ";
	for(int i = end; i != -1; i = parent[i]){
			caminho[x] = i;
			x++;
	}
	
	for(int i = x-1; i >= 0; i--){
		cout<<cidade[caminho[i]].nome;
		if(i >= 1)
			cout<<"->";
	}
  cout<<endl;
}

 void cria_cidade(int num_cidades,int num_estradas, Cidade cidade[]){ //função para criar cidade

  for(int i=0; i< num_cidades; i++){
    cidade[i].codigo = i;
    cout<<"nome da cidade: ";
    cin>>cidade[i].nome;
    cout<<"centro pokemon? (1 para sim, 0 para nao): ";
    cin>>cidade[i].centro_pokemon;
  }


    int origem, destino, distancia;
    cout<<"entre com o codigo da cidade de origem, da de destino, e a distancia: " << endl;
  for(int i = 0; i < num_estradas; i++){
    cin>>origem>>destino>>distancia;
    cidade[origem].vizinhos.push_back({origem,destino,distancia});
    cidade[destino].vizinhos.push_back({destino,origem,distancia});

  }

}

void mostra_cidades(int num_cidades, Cidade cidade[]){
  for(int i=0; i<num_cidades; i++){
    cout<<"codigo: "<<cidade[i].codigo<<endl;
    cout<<"nome: "<<cidade[i].nome<<endl;
    if(cidade[i].centro_pokemon == 1){
      cout<<"tem centro pokemon"<<endl;
    }else{
      cout<<"nao tem centro pokemon"<<endl;
        }
    list<estrada>::iterator it;

    cout<<"cidades vizinhas: ";

    for(it = cidade[i].vizinhos.begin(); it != cidade[i].vizinhos.end(); it++){
      cout<<cidade[it->destino].nome<<endl;
    }

  }

}

int main() { //função principal

  int var; //variável para escolher a opção
  
  cout<<"quantas cidades deseja cadastrar? ";
  int num_cidades, num_estradas;
  cin >> num_cidades;
  cout<<"quantas estradas deseja cadastrar? ";
  cin >> num_estradas;

  Cidade cidades[num_cidades];//variável para a cidade

  while(true){ //loop para escolher a opção

    cout<<"1 - Cadastrar cidades"<<endl;
    cout<<"2 - Mostrar conteudo"<<endl;
    cout<<"3 - como chegar ao centro pokemon mais proximo"<<endl;
    cout<<"4 - Sair"<<endl;

    cin>>var; //escolhe a opção	
    
    int a, custos[num_cidades], b = -1;

  switch(var){ //switch para escolher a opção

    case 1: //cria a cidade
      cria_cidade(num_cidades, num_estradas, cidades);
      break;

    case 2: //mostra o conteúdo do Grafo Cidades

      mostra_cidades(num_cidades, cidades);

      break;

    case 3: //mostra a rota mais próxima até um centro pokemon

      cout<<"em que cidade vc esta ? ";
      
      cin>>a;
      
      for(int i = 0; i < num_cidades; i++){
		  if(i != a)
		  {
		  	custos[i] = dijkstra(cidades, num_cidades, a, i);
		  }	  
	  }
	  if(cidades[a].centro_pokemon == 1){
		  cout<<"esta cidade ja tem centro pokemon"<<endl;
	  }else
	  {	  	
		   	for(int i = 0; i < num_cidades; i++) {
    			if (i != a && cidades[i].centro_pokemon == 1) { 
        			if (b == -1 || custos[i] < custos[b]) {
       	       	   	    b = i; 
 	 	 	   	   	 }
 				}
		   }
      show_dijkstra(cidades, num_cidades, a, b);
	  }
      break;
    
    case 4: //sai do programa
      return 0;

    default: //opção invalida
      break;

  }
}
  return 0;
}
