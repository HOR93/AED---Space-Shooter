#include <iostream>
#include <conio.h> // biblioteca para funções de controle na tela do terminal
#include <windows.h> // coordenadas
#include <vector>
#include <list> // listar os jogadores
#include <string>
#include <set>
#include <fstream> // para gravar o save


using namespace std;

// Projeto Computacional - Starbreaker - Space Shooter - AED 2022
// Henrique Oliveira da Rocha - 202066910
// Victor Augusto Araújo dias - 211027527

// terminal 80x50 para funcionar no tamanho correto
/*         0     1    2     3   4      5      6      7         8  */

//------------------------------------------ Alternando cores do projeto --------------------------------------------
typedef enum{BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,DARKGRAY,   /* nome das cores */
LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE} COLORS;
/*  9         10         11        12        13         14    15 */

static int __BACKGROUND = 1/*BLACK*/;/*pode ser o numero ou o nome da cor*/
static int __FOREGROUND = LIGHTGRAY;



void textcolor (int letras, int fundo){/*para mudar a cor de fundo mude o background*/
    __FOREGROUND = letras;
    __BACKGROUND = fundo;
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
    letras + (__BACKGROUND << 4));
}

//----------------------------------------------- Classe | CORDENADAS | para mecanica geral do Jogo ----------------------------------
class cordenadas {
	public:

	void gotoxy (int x, int y){ // posicionar as cordenadas na tela pelo windows.h
	HANDLE jogo;
	COORD dwPos;
    jogo = GetStdHandle(STD_OUTPUT_HANDLE); // tomando controle da posição de saida
    dwPos.X = x; // cada cordenada x e y segue onde esta o gotoxy
    dwPos.Y = y;
    SetConsoleCursorPosition(jogo, dwPos); // atributos interpretados como coordenadas

}

void textcolor (int letras, int fundo){/*para mudar a cor de fundo mude o background*/
    __FOREGROUND = letras;
    __BACKGROUND = fundo;
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
    letras + (__BACKGROUND << 4));
}


	void ocultar_cursor(){

	HANDLE jogo;
	CONSOLE_CURSOR_INFO cursor;
    jogo = GetStdHandle(STD_OUTPUT_HANDLE);
    cursor.dwSize = 1; // tamanho do cursor
    cursor.bVisible = FALSE;
    // cursor.bVisible = false;  para nao aparecer o cursor ou true pra mostrar
   SetConsoleCursorInfo(jogo, &cursor);

   }

   void limite_aresta(){

    for(int i = 2; i<78; i++){ // linha reta
    	gotoxy(i,3);
		textcolor(12,0); //reta por cima
		cout <<"" << char(196); // limite cima e baixo 
    	gotoxy(i,33);
    	textcolor(12,0);
		cout <<"" << char(196);
	}

	for(int i = 4; i<33; i++){
		gotoxy(2,i);
		textcolor(12,0);
		cout <<"" << char(179); // limite lados
		gotoxy(77,i);
		textcolor(12,0);
		cout <<"" << char(179);
	}
	gotoxy(2,3);
	textcolor(12,0);
	cout <<"" << char(218); // arestas
	gotoxy(2,33);
	textcolor(12,0);
	cout <<"" << char(192);
	gotoxy(77,3);
	textcolor(12,0); 
	cout <<"" << char(191);
	gotoxy(77,33);
	textcolor(12,0); 
	cout <<"" << char(217);
}



};

//--------------------------------------------- Classe | NAVE | e suas mecanicas  -----------------------------------------------
class nave: public cordenadas {
private:
int x, y;
int coracao;
int combustivel;

public:
	nave(int x_nv, int y_nv, int coracao_nv, int combustivel_nv){ // parametros
		x = x_nv;
		y = y_nv;
		coracao = coracao_nv;
		combustivel = combustivel_nv;
	}
	void set_x_nv( int x_nv){
        x =  x_nv;
	}
	int X(){ // parametro para o hitbox
		return x;
	}
	void set_y_nv( int y_nv){
        y =  y_nv;
	}
	int Y(){ // parametro para o hitbox
		return y;	
	}
	void coracao_decremento(){
	coracao--;
    }
	void set_comb( int comb){
        combustivel = comb;
	}
	int comb(){
		return combustivel;
	}


void criando_nave();
void excluir_nave();	
void movimento_nave();
void criar_vida();
void explosao_nave();		

};

void nave::criando_nave(){
	gotoxy(x,y);
	textcolor(13,0); 
	cout << "   " << char(245); // char para criar a nave
	gotoxy(x, y+1); // +1 depois do y é para sinalizar que esta na parte em baixo
	cout << "  " << char(40) << char(207) << char(41);
	gotoxy(x, y+2); 
	cout <<" " << char(30) << " " << char(30) << " " << char(30);
}

void nave:: excluir_nave(){ // metodo para apagar os rastros da nave
	gotoxy(x,y);
	cout <<"        "; // abrindo espaços para apagar
	gotoxy(x, y+1); 
	cout <<"        ";
	gotoxy(x, y+2); 
	cout <<"        ";
}

void nave::movimento_nave(){

	if ( kbhit() ){ // kbhit do conio, função que detecta se a tecla foi pressionada
		char tecla = getch(); // getch do windows le e retorna o caractere e nao mostra na tela
        excluir_nave(); // metodo para apagar os rastros da nave
		if (tecla == 75 && x > 3)
		 x--; //    x-- significa que vai para esquerda && para o limite do cenario
		if (tecla == 77 && x+6 < 77)
		 x++; //x++ significa que vai para direita e 6 para a quantidade de chars
		criando_nave();
		criar_vida();

    }
}

void nave::criar_vida(){
	int i;
	textcolor(13,0);
	gotoxy(1, 2);
	cout <<" |Combustivel da nave: " << combustivel << endl; //32 em baixo
	textcolor(9,16);
	gotoxy(25, 2); 
	cout <<"  >>>|| STARBREAKER ||<<<"<< endl;
	textcolor(13,0);
	gotoxy(63, 2); 
	cout << "Energia:  " << endl; // inserir coração no topo da tela
	gotoxy(70, 2); 
	cout << "      ";
	while (i<coracao){
		textcolor(12,0);
		gotoxy(71+i, 2); // i para cada lado do coracao quando for saindo

		cout << "" << char(3); // char coração
		i++;
	}

}

void nave::explosao_nave(){
	if (coracao == 0){
		excluir_nave();
		gotoxy(x,y); 
		cout <<" PERDENDO COMBUSTIVEL!";
		gotoxy(x,y+1); 
		cout <<"   AHHH nave! sofreu! dano!    ";
		gotoxy(x,y+2); 
		cout <<">> > * ## ## #";
		Sleep(100);
		gotoxy(x,y); 
		cout <<"                       ";
		gotoxy(x,y+1); 
		cout <<"                               ";
		gotoxy(x,y+2); 
		cout <<"               ";

		excluir_nave();
		gotoxy(x,y); 
		cout <<" PERDENDO COMBUSTIVEL! ";
		gotoxy(x,y+1); 
		cout <<"   AHHH nave! sofreu! dano!    ";
		gotoxy(x,y+2); 
		cout <<"              ";
		Sleep(100);
		gotoxy(x,y); 
		cout <<"                       ";
		gotoxy(x,y+1); 
		cout <<"                               ";
		gotoxy(x,y+2); 
		cout <<"               ";
		excluir_nave();
		combustivel--;
		coracao = 3; // reseta e volta para 3 mais uma vez
		criar_vida(); // retorna a vida 
		criando_nave();
	}
}

//----------------------------------------------- Classe | ALIENS | e seus metodos --------------------------------------------
class aliens: public cordenadas { // classe para os aliens
cordenadas c;
	int x,y;
	public:

	aliens(int n_x, int n_y){
		x = n_x;
		y = n_y;
	}




	void criar_aliens();
	void mover_aliens();
	void hitbox_aliens(nave &n); // passando como parametro nave N, modificando os valores

	void set_ax(int n_x){
		x = n_x;
	}
	int X_a(){ // chamando para as cordenadas X
		return x;
	}
	void set_ay(int n_y){
		y = n_y;
	}
	int Y_a(){ // chamando para as cordenadas Y
		return y;
	}


void apagar_aliens(){
	gotoxy(x,y);
	cout << " " ;


}


};

void aliens::criar_aliens(){
	gotoxy(x,y);

	   c.textcolor(4,0);

	cout << "" << char(157);


}
void aliens::mover_aliens(){
	gotoxy(x,y);
	cout <<" ";
	y++;
	if(y>32){ // atÃ© onde vai cair
		x = rand()%71 + 5; // aliens vai sair dentro de um limite entre direita e esquerda, e o +5 e pra evitar os aliens sair fora do padrÃ£o da tela
		y = 4; // para ficar caindo na tela no limite cordenada 4 do terminal
	}
	criar_aliens();
}

void aliens::hitbox_aliens(nave &n){ // pegando o parametro e passando com n.X
	if (x >= n.X() && x < n.X()+6 && y >= n.Y() && y<=n.Y()+2){ // X= cordenadas nave, se x for maior ou igual a X da nave, +6 para o valor dos caracteres da nave
		n.coracao_decremento();    // para tirar coraÃ§Ã£o                               
		n.excluir_nave();
		n.criando_nave();
		n.criar_vida();
		x = rand()%71 + 4; // 71 + 4
		y = 4;
	}
}

//----------------------------------------- Classe | TIRO |  e suas mecanicas -----------------------------------------------------
class TIRO: public cordenadas {
	int x, y;
	cordenadas c;
	public:
	TIRO(int _x, int _y){
		x = _x;
		y = _y;
	}
		int X_t(){ // parametro para o hitbox
		return x;
	}
		int Y_t(){ // parametro para o hitbox
		return y;
	}

void atirar();
bool limite();

};
void TIRO::atirar(){
		   c.textcolor(9,0);

	gotoxy(x,y) ; 	cout << " " ;
	if(y>4 && y<32) {y--; // 32
	gotoxy(x,y); cout<< char(215);

	}
}


bool TIRO::limite(){
	if(y<1){
		return true;
	}else{
		return false;
	}
}
// ------------------------------------------------ classe Jogar | Menu | instruções | gameplay | ----------------------------------------------
class jogar : public cordenadas{
public:
list<int> recorde;
list <string > lista_jogo;
set <string > nome;
set <int > level_jogador;
string nick;
int level = 1;
void gameplay(){

    int x,y;	
fstream save;	
cordenadas c;
c.gotoxy(x,y);
c.ocultar_cursor();
c.limite_aresta();

gotoxy(13,11);
cout <<  "                    `. ___";
gotoxy(13,12);
cout <<"                     __,' __`.                _..----....____";
gotoxy(13,13);
cout <<"        __...--.'``;.   ,.   ;``--..__     .'    ,-._    _.-' ";
gotoxy(13,14);
cout <<"  _..-''-------'   `'   `'   `'     O ``-''._   (,;') _,'";
gotoxy(13,15);
cout <<",'________________                           `-._`-','";
gotoxy(13,16);
cout <<" `._              ```````````------...___   '-.._'-:";
gotoxy(13,17);
cout <<"    ```--.._      ,.                     ````--...__-.";
gotoxy(13,18);
cout <<"            `.--. `-`                       ____    |  |`";
gotoxy(13,19);
cout <<"               `. `. -- STARBREAKER --     ,'`````.  ;  ;`";
gotoxy(13,20);
cout <<"              `. `.                       ,'`````.  ;  ;`";
gotoxy(13,21);
cout <<"                `._`.        __________   `.      \'__/`";
gotoxy(13,22);
cout <<"                   `-:._____/______/___/____`.     |  `";
gotoxy(13,23);
cout <<"                               `._________`-.   `.   `.___";
gotoxy(26,34);

cout << "Nome do piloto(a): ";
cin >> nick;
lista_jogo.push_back(nick);
nome.insert(nick);

gotoxy(13,11);
cout <<  "                          ";
gotoxy(13,12);
cout <<"                                                             ";
gotoxy(13,13);
cout <<"                                                              ";
gotoxy(13,14);
cout <<"                                                         ";
gotoxy(13,15);
cout <<"                                                      ";
gotoxy(13,16);
cout <<"                                                    ";
gotoxy(13,17);
cout <<"                                                      ";
gotoxy(13,18);
cout <<"                                                         ";
gotoxy(13,19);
cout <<"                                                          ";
gotoxy(13,20);
cout <<"                                                         ";
gotoxy(13,21);
cout <<"                                                        ";
gotoxy(13,22);
cout <<"                                                       ";
gotoxy(13,23);
cout <<"                                                          ";

nave n(37,30, 5, 3); // passando a localização da nave, e outras variaveis da classe nave
n.criando_nave();

		vector <aliens> ovn;
		for(int i=0; i<10 ; i++){
			ovn.push_back(aliens(rand()%75 + 3, rand()%5 + 4));
		}

		vector <TIRO> balas;



   bool gameplay = false;
   int pontos = 0;
   c.textcolor(0,0);
   while (!gameplay){  // controlando caracteres no terminal enquanto for negada
   
  
   cout << endl;
   cout << endl;
   c.textcolor(14,0);
   c.gotoxy(32,6); 
   cout<<"|-------------------|"<< endl;
   c.gotoxy(23,7);
   cout<<"|------------------------------------|"<< endl;
   c.gotoxy(18,8);
   cout<<"|-------------------------------------------------|"<< endl;
   c.gotoxy(9,9);
   cout<<"|--------------------------------------------------------------|"<< endl;
   c.gotoxy(9,10);
   cout<<"|----|####|------------|####|------|####|------------|####|----|"<< endl;
   c.gotoxy(9,11);
   cout<<"|----|####|------------|####|------|####|------------|####|----|"<< endl;
   c.gotoxy(9,12);
   cout<<"|----|####|------------|####|------|####|------------|####|----|"<< endl;
   c.gotoxy(18,13);
   cout<<"|-------------------------------------------------|"<< endl;
   c.gotoxy(23,14);
   cout<<"|------------------------------------|"<< endl;
   c.gotoxy(32,15); 
   cout <<"|-------| |--------|"<< endl;
    cout << endl;
    cout << endl;
   c.gotoxy(3,18); 
   cout     <<"       _____        _____                        __     __                "<< endl;
   c.gotoxy(3,19);
   cout     <<"       |___|        |___|         ___            ||     ()                "<< endl;
   c.gotoxy(3,20);
   cout     <<"       |___|        |___|         |_|            ||     ()                "<< endl;
   c.gotoxy(3,21);
   cout     <<"_______|   |________|   |_________| |____________||_____()________________"<< endl;
   cout << endl;
   cout << endl;
   c.gotoxy(3,24);
   cout     <<"     _____                                   __        ________           "<< endl;
   c.gotoxy(3,25);
   cout     <<"     |___|                 ___    ___        ||        ||____||           "<< endl;
   c.gotoxy(3,26);
   cout     <<"     |___|                 |_|    |_|        ||        ||    ||           "<< endl;
   c.gotoxy(3,27);
   cout     <<"_____|   |_________________| |____| |________||________||____||___________"<< endl;

   c.gotoxy(51,2); 
   c.textcolor(13,0);
   cout <<"||level: " << level;

	if(kbhit())	{
		char tecla = getch();
		switch(tecla){
			case 32:
			balas.push_back(TIRO(n.X()+3, n.Y() - 1));
			break;
		}

	}


	for(int i=0; i< ovn.size(); i++){
		ovn[i].mover_aliens();
		ovn[i].hitbox_aliens(n);
	}

   	for(int i=0 ; i <balas.size(); i++){
		balas[i].atirar();
		if(balas[i].limite()){
			balas.erase(balas.begin() + i);
		}
	}

    for(int i=0; i< ovn.size(); i++){
 		for(int j=0 ; j <balas.size(); j++){
			if(ovn[i].X_a() == balas[j].X_t() && (ovn[i].Y_a() == balas[j].Y_t() || ovn[i].Y_a()+1 == balas[j].Y_t() ) ){ // metodo de colisao( sobtrposiçao de objetos)
					ovn.erase(ovn.begin() + i);
					ovn.push_back(aliens(rand()%75 + 3, rand()%5 + 4));
					pontos++;
					level = pontos/10;
				recorde.push_back(level);
                level_jogador.insert(level);
			}

		}
	}


   
    if ( n.comb() == 0)
	gameplay = true;
    n.explosao_nave();
    n.movimento_nave();
    Sleep(30); // menos interações


	}
		x=9; y=6;
c.textcolor(4,15);	
c.gotoxy(x, y);    cout <<" ________________________________________________________  ";
c.gotoxy(x, y+1);  cout <<"/                                                       |  ";
c.gotoxy(x, y+2);  cout <<"|                GAME OVER!                             |  ";
c.gotoxy(x, y+3);  cout <<"|_________              _______________________________/   ";
c.gotoxy(x, y+4);  cout <<"          |_         __/    ___---------__                 ";
c.gotoxy(x, y+5);  cout <<"            |      _/      /              |_               ";
c.gotoxy(x, y+6);  cout <<"            |    /       /                 |               ";
c.gotoxy(x, y+7);  cout <<"             |  /       | _    _ |          |              ";
c.gotoxy(x, y+8);  cout <<"             | |       / / |  / | |          |             ";
c.gotoxy(x, y+9);  cout <<"             | |       || * || * ||           |            ";
c.gotoxy(x, y+10); cout <<"             | |       ||_// \\_/ |            |            ";
c.gotoxy(x, y+11); cout <<"             | |       |_| (||)   |_______|    |           ";
c.gotoxy(x, y+12); cout <<"             | |         |  ||     | _  / /   |            ";
c.gotoxy(x, y+13); cout <<"             | |         |_________|| |/ /   /             ";
c.gotoxy(x, y+14); cout <<"             | |         |_|_|_|_|/|  _/___/               ";
c.gotoxy(x, y+15); cout <<"             | |         |_|_|_|_||| |/ /                  ";
c.gotoxy(x, y+16); cout <<"             | |         |_|_|_|_|_|| |/ /                 ";
c.gotoxy(x, y+17); cout <<"             | |         |_|_|_|_|_|| |/ /                 ";
c.gotoxy(x, y+18); cout <<"             | |         |_|_|_|_|_|| |/ /                 ";
c.gotoxy(x, y+19); cout <<"             ------------|_|_|_|_|_|| |/ /                 ";
c.gotoxy(x, y+20); cout <<"             ------------|_|_|_|_|_|| |/ /                 ";
c.gotoxy(x, y+21); cout <<"                         |_|_|_|_|_|| |/ /                 ";
c.gotoxy(x, y+22); cout <<"                         ###########                       ";

 Sleep(3000);
	getch();

save.open("save_ss.txt", ios::in | ios::app);

				save << lista_jogo.front() << "\n";
				save << recorde.back() << "\n";

				save.close();
    }


void instrucao(){
    char ch;
	system("cls");

	system("color F0");
    cout<<"\n\n>>>>>>>>>>>>>>>>>>>>>>>>  ||MANUAL||  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
    cout<<"\n ** Objetivo: Sobreviver o maximo possivel a uma horda de aliens." << endl;
    cout <<"\n--------------------------------------------------------------------------\n\n";

    cout<<"\n\n>>>>>>>>>>>>>>>>>>>>> ||TECLAS DE CONTROLE|| <<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
    cout << "\n ** Setas do teclado direcionam a nave tanto para a Esquerda e Direita\n" << endl;
    cout << "\n ** Aperte a tecla SPACE para atirar\n" << endl;
    cout <<"\n---------------------------------------------------------------------------\n\n";
    cout<<"\n\nPressione qualquer tecla para voltar ao menu";
	getch();

    }

void apagar_menu(){

    int x,y;
	cordenadas a;
	a.gotoxy(x,y);
	a.gotoxy(13,5);
	cout <<"                                                              "; 
	a.gotoxy(13,6);
	cout <<"                                                              "; 
	a.gotoxy(13,7);
	cout <<"                                                              ";
	a.gotoxy(13,8);
	cout <<"                                                              ";
	a.gotoxy(13,9);
	cout<<"                                                              ";	 
	a.gotoxy(13,10);
	cout <<"                                                              ";
	a.gotoxy(13,11);
	cout <<"                                                              ";
	a.gotoxy(29,16);
	cout <<"             ";
	a.gotoxy(29,17);
	cout<<"              ";
    a.gotoxy(29,18);
	cout<<"                           ";
	a.gotoxy(29,19);
	cout<<"                    ";
	a.gotoxy(29,23);
	cout<<"             ";	

}

void recordes(){
	system("cls");
int m;
cout<<"\n\n>>>>>>>>>>>  || Procure seu nome ou recorde nesta SESSAO! ||  <<<<<<<<<<<<<<<<<<\n\n";

    cout <<"|| -- (1) para nome do seu piloto(a) | (2) para seu level\n||" << endl;
	cout <<"|| -- (3) para ver todos os nomes    | (4) para todos os levels\n" << endl;
    cin >> m;
    if (m == 1){
      cout<<"\n\nDigite Seu nickname: " << endl;
    cin >> nick;
    if (nome.find(nick)!=nome.end()){
				cout << "O Piloto(a) " << nick << " encontrado" << endl;
			}
			else{
				cout << "O Piloto(a) " << nick << " não esta nessa sessao" << endl;
			  }  
    }
    if (m == 2){
      cout<<"\n\nDigite Seu Level: " << endl;
    cin >> level;
    if (level_jogador.find(level)!=level_jogador.end()){
				cout << "O Level " << level << " foi encontrado" << endl;
			}
			else{
				cout << "O Level" << level << " não esta nessa sessao" << endl;
			  }  
    }if ( m == 3) {
            cout << "\nNomes ordenados: " << endl; // fazendo ordenação
            cout << endl;
			for(set<string>::iterator it = nome.begin(); it!=nome.end(); it++){
				cout << *it << "  --->  ";
			 }
            }
            if ( m == 4) {
            cout << "\nLevels ordenados: " << endl;    
			cout << endl;
            for(set<int>::iterator it2 = level_jogador.begin(); it2!=level_jogador.end(); it2++){
				cout << *it2 << "  --->  ";
			 }
            }

	getch();

}

};



int main(){
	int x,y;

    cordenadas s;
    jogar gp;
	s.gotoxy(x,y);
	do{
		s.textcolor(9,16);
		system("cls");
		s.gotoxy(13,5);cout <<"±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±"; 
		s.gotoxy(13,6);cout <<"±    _____                    _____ _           _            ±";
		s.gotoxy(13,7);cout <<"±   |   __|___ ___ ___ ___   |   __| |_ ___ ___| |_ ___ ___  ±";
		s.gotoxy(13,8);cout <<"±   |__   | . | .'|  _| -_|  |__   |   | . | . |  _| -_|  _| ±";
		s.gotoxy(13,9);cout <<"±   |_____|  _|__,|___|___|  |_____|_|_|___|___|_| |___|_|   ±";
		s.gotoxy(13,10);cout <<"±         |_|                                                ±";
		s.gotoxy(13,11);cout <<"±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±";

		s.gotoxy(29,16);  
		s.textcolor(15,3);
		cout <<"| 1 - JOGAR |";
		s.gotoxy(29,17); 
		s.textcolor(15,13);
		cout<<"| 2 - MANUAL |";
        s.gotoxy(29,18);
		s.textcolor(15,9); 
		cout <<"| 3 - Jogadores da sessao |";	 
		s.gotoxy(29,19);
		s.textcolor(15,2); 
		cout <<"| 4 - SAIR DO JOGO |";
		s.gotoxy(29,23);
		s.textcolor(15,0);
		cout <<"Selecione:  ";
		char op = getche();



		if( op=='1') {
		gp.apagar_menu();
		gp.gameplay();
		}
		else if( op=='2'){
		gp.instrucao();
	}
    else if( op=='3'){
		gp.recordes();
	}
		else if( op=='4')
		exit(0);
		cout <<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	} while(2);


return 0;

}
