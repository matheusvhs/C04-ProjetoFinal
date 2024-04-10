//Trabalho Pokedex - C04
/*Alunos:
Matheus Vieira Honorio de Souza - 525 - GES
Vitor Dias Carlos - 445 - GES
Vinicius Vilela Paulino - 436 - GES
Otavio Augusto Silva Lima - 279 - GES
Guilherme Bastos Florêncio - 322 - GES

O codigo cria cidades com nome, codigo, e se tem ou nao centro pokemon, e mostra a cidade cadastrada.
*/

#include <iostream>
#include <string>

using namespace std;

struct cidade{
  int codigo;
  string nome;
  bool centro_pokemon;
};

cidade cria_cidade(){
  cidade a;
  cout<<"nome da cidade: ";
  cin>>a.nome;
  cout<<"codigo da cidade: ";
  cin>>a.codigo;
  cout<<"centro pokemon? (1 para sim, 0 para nao): ";
  cin>>a.centro_pokemon;
  return a;
}
int main() {

  int var;
  cidade a;

  while(true){

    
    cout<<"1 - Cadastrar cidade"<<endl;
    cout<<"2 - Mostrar conteudo"<<endl;
    cout<<"3 - Sair"<<endl;

    cin>>var;

  switch(var){

    case 1:
      a = cria_cidade();
      break;
    
    case 2:
      cout<<"nome: "<<a.nome<<endl;
      cout<<"codigo: "<<a.codigo<<endl;
      cout<<"centro pokemon: ";
      if(a.centro_pokemon == 1)
        cout<<"sim"<<endl;
      else
        cout<<"nao"<<endl;
        break;
      
    case 3:
      return 0;
    
    default:
      break;

  
  }
}
  return 0;
}
