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
#include <climits>
#include <cmath>

using namespace std;

struct ponto {
  int x;
  int y;
};

struct segmento {
  ponto a;
  ponto b;
};

struct pokemon{
  int codigo;
  ponto coordenada;
  string nome;
  string tipo;
};

struct treenode{
  pokemon info;
  struct treenode* left;
  struct treenode* right;
  int altura;
};

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

typedef treenode *treenodeptr;

int altura(treenodeptr p){
	if(p == NULL)
		return -1;
	else
		return p->altura;
}

int balanceamento(treenodeptr p){
	if(p == NULL)
		return 0;
	return altura(p->left) - altura(p->right);
}

int maior(int a, int b){
	if(a > b)
		return a;
	else
		return b;
}

treenodeptr rotate_right(treenodeptr y){
	treenodeptr x = y->left;
	treenodeptr T2 = x->right;
	
	x->right = y;
	y->left = T2;
	
	
	y->altura = maior(altura(y->left), altura(y->right)) + 1;
	x->altura = maior(altura(x->left), altura(x->right)) + 1;
	
	return x;	
}

treenodeptr rotate_left(treenodeptr x){
	treenodeptr y = x->right;
	treenodeptr T2 = y->left;
	
	y->left = x;
	x->right = T2;
	
	
	x->altura = maior(altura(x->left), altura(x->right)) + 1;
	y->altura = maior(altura(y->left), altura(y->right)) + 1;
	
	return y;	
}

void tinsert(treenode*& p, pokemon poke) {
    if (p == NULL) {
        p = new treenode;
        p->info = poke;
        p->left = NULL;
        p->right = NULL;
        p->altura = 0;
    } else if (poke.nome < p->info.nome) {
        tinsert(p->left, poke);
    } else if (poke.nome > p->info.nome) {
        tinsert(p->right, poke);
    } else {
        // O Pokémon já existe na árvore, atualize o tipo
        p->info.tipo = poke.tipo;
    }

    p->altura = 1 + maior(altura(p->left), altura(p->right));

    int balance = balanceamento(p);

    if (balance > 1 && poke.nome < p->left->info.nome) {
        p = rotate_right(p);
    }
    if (balance < -1 && poke.nome > p->right->info.nome) {
        p = rotate_left(p);
    }
    if (balance > 1 && poke.nome > p->left->info.nome) {
        p->left = rotate_left(p->left);
        p = rotate_right(p);
    }
    if (balance < -1 && poke.nome < p->right->info.nome) {
        p->right = rotate_right(p->right);
        p = rotate_left(p);
    }
}

treenodeptr tsearch(treenodeptr p, string nome){
  if(p == NULL){
    return NULL;
  }else if(nome == p->info.nome){
      return p;
  }else if(nome < p->info.nome){
      return tsearch(p->left,nome);
  }else
    return tsearch(p->right,nome);	
}

treenodeptr tpointsmaller(treenodeptr &p){
	treenodeptr t = p;
	if(p->left == NULL){
		p = p->right;
		return t;
	}
	else
		return tpointsmaller(p->left);
}


bool tremove(treenodeptr &p, string nome) {
	if (p == NULL)
		return false;

	bool result;
	if (nome == p->info.nome) {
		if (p->left == NULL || p->right == NULL) {
			treenodeptr temp = p->left ? p->left : p->right;
			if (temp == NULL) {
				temp = p;
				p = NULL;
			} else {
				*p = *temp;
			}
			delete temp;
		} else {
			treenodeptr temp = tpointsmaller(p->right);
			p->info = temp->info;
			result = tremove(p->right, temp->info.nome);
		}
		result = true;
	} else if (nome < p->info.nome) {
		result = tremove(p->left, nome);
	} else {
		result = tremove(p->right, nome);
	}

	if (p == NULL)
		return result;

	p->altura = maior(altura(p->left), altura(p->right)) + 1;
	int balance = balanceamento(p);

	if (balance > 1 && balanceamento(p->left) >= 0)
		p = rotate_right(p);

	if (balance > 1 && balanceamento(p->left) < 0) {
		p->left = rotate_left(p->left);
		p = rotate_right(p);
	}

	if (balance < -1 && balanceamento(p->right) <= 0)
		p = rotate_left(p);

	if (balance < -1 && balanceamento(p->right) > 0) {
		p->right = rotate_right(p->right);
		p = rotate_left(p);
	}

	return result;
}

void emOrdem(treenodeptr raiz) {
	if (raiz != NULL) {
		emOrdem(raiz->left);
		cout << raiz->info.nome << " ";
		treenodeptr temp = raiz->right;
		while (temp != NULL && temp->info.nome == raiz->info.nome) {
			temp = temp->right;
		}
		raiz->right = temp;
		emOrdem(raiz->right);
	}
}

void emOrdem_info (treenodeptr raiz){
  if(raiz != NULL){
    emOrdem_info(raiz->left);
    
    cout<<"codigo: "<<raiz->info.codigo<<endl;
    cout<<"nome: "<<raiz->info.nome<<endl;
    cout<<"tipo: "<<raiz->info.tipo<<endl;
    cout<<"coordenada: "<<"("<<raiz->info.coordenada.x<<", "<<raiz->info.coordenada.y<<")"<<endl<<endl;
    
    emOrdem_info(raiz->right);
  }
}

int poketipos(treenodeptr raiz, string tipo) {
    if (raiz == NULL) {
        return 0;
    }
    int cont = 0;
    if (raiz->info.tipo == tipo) {
        cont++;
    }
    cont += poketipos(raiz->left, tipo);
    cont += poketipos(raiz->right, tipo);
    
    return cont;
}

void dijkstra(Cidade cidade[], int nVertices, int start){
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

  int distancia_centro = INT_MAX, end;
  for(int i = 0; i < nVertices; i++){
    if(cidade[i].centro_pokemon == 1 && distancia_centro > distance[i]){
      distancia_centro = distance[i];
      end = i;
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
    cin.ignore();
    getline(cin,cidade[i].nome);
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

double distancia(ponto p1, ponto p2){
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) +
          (p1.y - p2.y)*(p1.y - p2.y));
}

int poke100m(treenodeptr p, ponto u){
  if(p == NULL)
    return 0;
  int i = 0;
  if(distancia(p->info.coordenada, u) <= 100){
    i = 1;
  }
  return i + poke100m(p->left, u) + poke100m(p->right, u);
}

int pokemons_no_raio(treenodeptr p, ponto u, ponto a[], int &i) {
    if (p == NULL)
        return 0;
    
    int pokemons = 0;
    if (distancia(p->info.coordenada, u) <= 100) {
        a[i] = p->info.coordenada;
        i++;
        pokemons = 1;
    }
    
    pokemons += pokemons_no_raio(p->left, u, a, i);
    pokemons += pokemons_no_raio(p->right, u, a, i);
    
    return pokemons;
}


double area_triangulo(ponto a, ponto b, ponto c){
	return 
		((a.x*b.y) - (a.y*b.x) + 
		(a.y*c.x) - (a.x*c.y) + 
		(b.x*c.y) - (b.y*c.x))/2.0;  
}

int orientacao(ponto a, ponto b, ponto c){
	double area = area_triangulo(a,b,c);
	if(area > 0){
		return 1; 
	} else if(area < 0){
		return -1; 
	} else {
		return 0; 
	}
}



double gift_wraping(ponto points[], int n) {
    if (n < 3)
        return -1;
 
    int next[n];
    for (int i = 0; i < n; i++){
        next[i] = -1;
    }
 
    int l = 0;
    for (int i = 1; i < n; i++){
        if (points[i].x < points[l].x)
            l = i;
    }
   
    int p = l, q;
    do {
        q = (p + 1) % n;
        for (int i = 0; i < n; i++){
            if (orientacao(points[p], points[i], points[q]) == -1)
                q = i;
        }
        next[p] = q; 
        p = q; 
    } while (p != l);
    
    double perimetro = 0;
    for (int i = 0; i < n; i++) {
        if (next[i] != -1){
            perimetro += distancia(points[i], points[next[i]]);
        }
    }
    
    return perimetro;
}

int main() { //função principal

  int var; //variável para escolher a opção

  cout<<"quantas cidades deseja cadastrar? ";
  int num_cidades, num_estradas, codigo = 0;
  cin >> num_cidades;
  cout<<"quantas estradas deseja cadastrar? ";
  cin >> num_estradas;

  Cidade cidades[num_cidades];//variável para a cidade
  pokemon poke;
  treenodeptr arvore = NULL, result;
  string pesquisa;
  ponto point;
  bool cidades_criadas = false;
  ponto encontrados[100];
  int count = 0;
  int num_pokemons;

  while(true){ //loop para escolher a opção

    cout<<"0 - Sair"<<endl;
    cout<<"1 - Cadastrar cidades"<<endl;
    cout<<"2 - Mostrar conteudo"<<endl;
    cout<<"3 - Como chegar ao centro pokemon mais proximo"<<endl;
    cout<<"4 - Cadastrar Pokemon"<<endl;
    cout<<"5 - Informacoes dos Pokemons"<<endl;
    cout<<"6 - Remover Pokemon"<<endl;
    cout<<"7 - Procurar Pokemon"<<endl;
    cout<<"8 - Mostrar Pokemons"<<endl;
    cout<<"9 - Contagem de tipo"<<endl;
    cout<<"10 - Quantidade de pokemons proximos"<<endl;
    cout<<"11 - Perimetro minimo dos pokemons proximos"<<endl;

    cin>>var; //escolhe a opção	
	cout<<endl;
	
    int a;

  switch(var){ //switch para escolher a opção

    case 0:
      return 0;

    case 1: //cria a cidade
      cria_cidade(num_cidades, num_estradas, cidades);
      cidades_criadas = true;
      cout<<endl;
      break;

    case 2: //mostra o conteúdo do Grafo Cidades
    	
	  if(cidades_criadas == true){
      	  mostra_cidades(num_cidades, cidades);
      	  cout<<endl;
	  }
      else
      	  cout<<"insira as cidades antes de mostrar conteudo"<<endl;
        
	  cout<<endl;
      break;

    case 3: //mostra a rota mais próxima até um centro pokemon

      cout<<"em que cidade vc esta ? ";

      cin>>a;

    if(cidades[a].centro_pokemon == 1)
      cout<<"esta cidade ja tem centro pokemon"<<endl;
    else	  	
          dijkstra(cidades, num_cidades, a);
      
      cout<<endl;
      break;

    case 4:
      poke.codigo = codigo;
      codigo++;
      cout<<"nome do pokemon: ";
      cin>>poke.nome;
      cout<<"tipo do pokemon: ";
      cin>>poke.tipo;
      cout<<"coordenada x do pokemon: ";
      cin>>poke.coordenada.x;
      cout<<"coordenada y do pokemon: ";
      cin>>poke.coordenada.y;

      tinsert(arvore,poke);
      
      cout<<endl;
      break;
  
    case 5:
    	
    	emOrdem_info(arvore);
    	
    	cout<<endl<<endl;
    	break;
  
  
  
    case 6:
    	cout<<"pokemon a ser removido: ";
    	cin.ignore();
    	getline(cin, pesquisa);
    	
    	if(tremove(arvore, pesquisa) == true){
			cout<<"pokemon removido"<<endl;
		}else{
			cout<<"pokemon para remocao nao encontrado"<<endl;
		}
		
		cout<<endl;
		break;
    	

    case 7:
      cout<<"Nome do pokemon a ser porcurado: ";
      cin.ignore();
      getline(cin, pesquisa);

      result = tsearch(arvore, pesquisa);

      if(result != NULL){
        cout<<"Pokemon encontrado :D"<<endl;
        cout<<"ele esta na coodenada ("<<result->info.coordenada.x<<", "<<result->info.coordenada.y<<")"<<endl;
      }else{
        cout<<"pokemon nao encontrado :c"<<endl;
      }
      
      cout<<endl;
      break;
    
    case 8:
      emOrdem(arvore);
      cout<<endl;

      
      cout<<endl;
      break;

   
    case 9:
      cout<<"tipo a ser contado: ";
      cin.ignore();
      getline(cin, pesquisa);

      cout<<"quantidade de pokemons do tipo "<<pesquisa<<": "<<poketipos(arvore,pesquisa)<<endl;
      
      cout<<endl;
      break;

    case 10:
 	   cout<<"sua coordenada x: ";
 	   cin>>point.x;
 	   cout<<"sua coordenada y: ";
 	   cin>>point.y;
 	   cout<<"existem "<<poke100m(arvore,point)<<" pokemons perto de voce"<<endl;
 	   
 	   cout<<endl;
 	   break;
    
    case 11:
    cout << "sua coordenada x: ";
    cin >> point.x;
    cout << "sua coordenada y: ";
    cin >> point.y;
    
    count = 0; 
    num_pokemons = pokemons_no_raio(arvore, point, encontrados, count);
    
    if (num_pokemons > 2) { 
        double perimetro = gift_wraping(encontrados, num_pokemons);
        if (perimetro != -1) {
            cout << "Perimetro minimo = " << perimetro <<"m"<< endl;
        } else {
            cout << "Não foi possível calcular o perímetro mínimo." << endl;
        }
    } else {
        cout << "Não há pokémons suficientes dentro do raio para calcular o perímetro." << endl;
    }
    
    cout << endl;
    break;

    
    default: //opção invalida
      cout<<endl;
      break;

  }
}
  return 0;
}