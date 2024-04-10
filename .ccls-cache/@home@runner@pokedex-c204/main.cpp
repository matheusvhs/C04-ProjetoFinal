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

using namespace std;

struct cidade{ //estrutura cidade
  int codigo;
  string nome;
  bool centro_pokemon;
};

cidade cria_cidade(){ //função para criar cidade
  cidade a;
  cout<<"nome da cidade: ";
  cin>>a.nome;
  cout<<"codigo da cidade: ";
  cin>>a.codigo;
  cout<<"centro pokemon? (1 para sim, 0 para nao): ";
  cin>>a.centro_pokemon;
  return a;
}
int main() { //função principal

  int var; //variável para escolher a opção
  cidade a; //variável para a cidade

  while(true){ //loop para escolher a opção

    cout<<"1 - Cadastrar cidade"<<endl;
    cout<<"2 - Mostrar conteudo"<<endl;
    cout<<"3 - Sair"<<endl;

    cin>>var; //escolhe a opção	

  switch(var){ //switch para escolher a opção

    case 1: //cria a cidade
      a = cria_cidade();
      break;
    
    case 2: //mostra o conteúdo da cidade
      cout<<"nome: "<<a.nome<<endl;
      cout<<"codigo: "<<a.codigo<<endl;
      cout<<"centro pokemon: ";
      if(a.centro_pokemon == 1)
        cout<<"sim"<<endl;
      else
        cout<<"nao"<<endl;
        break;
      
    case 3: //sai do programa
      return 0;
    
    default: //opção invalida
      break;

  }
}
  return 0;
}
