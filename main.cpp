//Trabalho Pokedex - C04
/*Alunos:
Guilherme Bastos Florêncio - 322 - GES
Matheus Vieira Honorio de Souza - 525 - GES
Otavio Augusto Silva Lima - 279 - GES
Vinicius Vilela Paulino - 436 - GES
Vitor Dias Carlos - 445 - GES
*/
//O código cria cidades com nome, código, e se tem ou nao centro Pokemon, e mostra a cidade cadastrada.

#include <iostream>

#include <string>

#include <list>

using namespace std;

struct estrada { //estrutura estrada
  int origem;
  int destino;
  int distancia;
};

struct Cidade { //estrutura cidade
  int codigo;
  string nome;
  bool centro_pokemon;
  list < estrada > vizinhos;
};

void cria_cidade(int num_cidades, int num_estradas, Cidade cidade[]) { //função para criar cidade

  for (int i = 0; i < num_cidades; i++) {
    cidade[i].codigo = i;
    cout << "nome da cidade: ";
    cin >> cidade[i].nome;
    cout << "centro pokemon? (1 para sim, 0 para nao): ";
    cin >> cidade[i].centro_pokemon;
  }

  int origem, destino, distancia;
  for (int i = 0; i < num_estradas; i++) {
    cout << "entre com o codigo da cidade de origem, da de destino, e a distancia: ";
    cin >> origem >> destino >> distancia;

    cidade[origem].vizinhos.push_back({origem,destino,distancia
    });
    cidade[destino].vizinhos.push_back({destino,origem,distancia
    });

  }

}

void mostra_cidades(int num_cidades, Cidade cidade[]) {
  for (int i = 0; i < num_cidades; i++) {
    cout << "codigo: " << cidade[i].codigo << endl;
    cout << "nome: " << cidade[i].nome << endl;
    if (cidade[i].centro_pokemon == 1) {
      cout << "tem centro pokemon" << endl;
    } else {
      cout << "nao tem centro pokemon" << endl;
    }
    list < estrada > ::iterator it;

    cout << "cidades vizinhas: ";

    for (it = cidade[i].vizinhos.begin(); it != cidade[i].vizinhos.end(); it++) {
      cout << it -> destino << endl;
    }

  }

}

int main() { //função principal

  int
  var; //variável para escolher a opção

  cout << "quantas cidades deseja cadastrar? ";
  int num_cidades, num_estradas;
  cin >> num_cidades;
  cout << "quantas estradas deseja cadastrar? ";
  cin >> num_estradas;

  Cidade cidades[num_cidades]; //variável para a cidade

  while (true) { //loop para escolher a opção

    cout << "1 - Cadastrar cidades" << endl;
    cout << "2 - Mostrar conteudo" << endl;
    cout << "3 - Sair" << endl;

    cin >>
      var; //escolhe a opção	

    switch (var) { //switch para escolher a opção

    case 1: //cria a cidade
      cria_cidade(num_cidades, num_estradas, cidades);
      break;

    case 2: //mostra o conteúdo da cidade

      mostra_cidades(num_cidades, cidades);

      break;

    case 3: //sai do programa
      return 0;

    default: //opção invalida
      break;

    }
  }
  return 0;
}