#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <termios.h>
#include <unistd.h>

#include "IHM.h"
#include "grille.h"
#include "player.h"
#include "jeux.h"
#include "ia_easy.h"

static void ia_easy_play();
static bool print_game();
static void player_2_play();

int main()
{
	bool choix_game = print_game();
	if(choix_game==0){ia_easy_play();};
	if(choix_game==1){player_2_play();};
}



static void ia_easy_play()
{
    jeux my_jeux;
	grille my_grille;
	IHM my_ihm;
	ia_easy my_ia_easy;
	int choix = 0;
	while(1)
	{
		system("clear");
		choix = 3;
		my_grille.afficher_choix(choix,'O');
		my_grille.afficher_grille(my_jeux.lire_buffer());
		while(choix < 10){
				choix += my_ihm.choose_line();
				if(choix < 0){choix=0;}
				if(choix > 6 && choix < 9){choix=6;}
				system("clear");
				my_grille.afficher_choix(choix,'O');
				my_grille.afficher_grille(my_jeux.lire_buffer());
		}
		my_jeux.update_buffer(choix-10,1);
		my_grille.afficher_grille(my_jeux.lire_buffer());
		if(my_jeux.check_victory()){
				system("clear");
				my_grille.afficher_choix(0,'X');
				my_grille.afficher_grille(my_jeux.lire_buffer());
				cout << "\x1b[31m" <<"Player 1 WIN" << "\x1b[0m" << endl;
				while(1);
		}
		choix = my_ia_easy.check_V_in_1(my_jeux.lire_buffer());
		my_jeux.update_buffer(choix,2);
		if(my_jeux.check_victory()){
				system("clear");
				my_grille.afficher_choix(0,'X');
				my_grille.afficher_grille(my_jeux.lire_buffer());
				cout << "\x1b[34m" <<"Bot WIN" << "\x1b[0m" << endl;
				while(1);
		}


		
	}
}

static void player_2_play()
{
	jeux my_jeux;
	grille my_grille;
	IHM my_ihm;
	int choix = 0;
	while(1)
	{
		system("clear");
		choix = 3;
		my_grille.afficher_choix(choix,'O');
		my_grille.afficher_grille(my_jeux.lire_buffer());
		while(choix < 10){
				choix += my_ihm.choose_line();
				if(choix >= 10 && my_jeux.check_full(choix-10)==1){
					choix = 3;
				}
				if(choix < 0){choix=0;}
				if(choix > 6 && choix < 9){choix=6;}
				system("clear");
				my_grille.afficher_choix(choix,'O');
				my_grille.afficher_grille(my_jeux.lire_buffer());
		}
		my_jeux.update_buffer(choix-10,1);
		my_grille.afficher_grille(my_jeux.lire_buffer());
		if(my_jeux.check_victory()){
				system("clear");
				my_grille.afficher_choix(0,'X');
				my_grille.afficher_grille(my_jeux.lire_buffer());
				cout << "\x1b[31m" <<"Player 1 WIN" << "\x1b[0m" << endl;
				while(1);
		}
		//Joueur 2
		system("clear");
		choix = 3;
		my_grille.afficher_choix(choix,'X');
		my_grille.afficher_grille(my_jeux.lire_buffer());
		while(choix < 10){
				choix += my_ihm.choose_line();
				if(choix >= 10 && my_jeux.check_full(choix-10)==1){
					choix = 3;
				}
				if(choix < 0){choix=0;}
				if(choix > 6 && choix < 9){choix=6;}
				system("clear");
				my_grille.afficher_choix(choix,'X');
				my_grille.afficher_grille(my_jeux.lire_buffer());
		}
		my_jeux.update_buffer(choix-10,2);
		my_grille.afficher_grille(my_jeux.lire_buffer());
		if(my_jeux.check_victory()){
				system("clear");
				my_grille.afficher_choix(0,'O');
				my_grille.afficher_grille(my_jeux.lire_buffer());
				cout << "\x1b[34m" <<"Player 2 WIN" << "\x1b[0m" << endl;
				while(1);
		}
	}
}


static char getch() {
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);         // lire config terminal
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);       // désactiver mode canonique et echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // appliquer
    char c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restaurer
    return c;
}

static bool print_game()
{
	int select = 0;
	bool choix = 0;
	while(choix!=1){
		system("clear");

		cout << "     ******************     " << endl;
		cout << "    ***              ***    " << endl;
		cout << "    *** PUISSANCE 4  ***    " << endl;
		cout << "    ***     by :     ***    " << endl;
		cout << "    *** Pierre       ***    " << endl;
		cout << "    ***     Bouckson ***    " << endl;
		cout << "   ****              ****    " << endl;
		cout << "  ****  Select Game   ****   " << endl;
		cout << "  ***                  ***   " << endl;
		if(select == 0){
			cout << "  ***  \033[30;47mBot\033[0m   2 player  ***" << endl; 
		}
		if(select == 1){
			cout << "  ***  Bot   \033[30;47m2 player\033[0m  ***" << endl;  
		}
		cout << "   ***                ***    " << endl;
		cout << "    ********************    " << endl;
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    	cout << " q =   <--   ||    j =   <-- " << endl;
    	cout << " d =   -->   ||    l =   --> " << endl;
    	cout << " z = select  ||    i = select" << endl;

		string touche;
		touche = getch();
		if(touche=="z" || touche=="i") {choix = 1;};
		if(touche=="q" || touche=="j") {select = 0;};
		if(touche=="d" || touche=="l") {select = 1;};
	}
	return select;

}