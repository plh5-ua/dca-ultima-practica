// DNI 51775490Y, PABLO LECOCQ HERNANDIS

#include <iostream>
#include <cstdlib> // Para rand(), srand() y atoi()
#include <string>
#include <cstring>

using namespace std;

const int KNAME=32;
const int KENEMIES=5;
const int KPOINTS=200;
const int KDICE=20; // Número de caras del dado

struct Core{
  int attack;
  int defense;
  int hp;
};

enum Breed{
  AXOLOTL,
  TROLL,
  ORC,
  HELLHOUND,
  DRAGON
};

struct Enemy{
  Breed name;
  Core features;
};

struct Hero{
  char name[KNAME];
  Core features;
  bool special;
  int runaways;
  int exp;
  int kills[KENEMIES];
};

int rollDice(){
  return rand()%KDICE+1;
}

void startHero(Hero &hero){
	hero.special = true;
	hero.exp = 0;
	hero.runaways = 3;
	for(int i = 0; i < KENEMIES; i++){
		hero.kills[i] = 0;		
	}	
}

void asignName(Hero &hero){
	string nameH;
	bool stop = false;
	
	do{
		cout << "Enter hero name: ";
		getline(cin, nameH);
		
		if((nameH[0] < 'A' || nameH[0] > 'Z') && (nameH[0] < 'a' || nameH[0] > 'z')){	// Si el primer caracter NO es una letra:
				cout << "ERROR: wrong name" << endl;											// Además, la condición de "nombre en blanco" se descarta con este if tb.
		}
		else{
			// Comprobamos que contiene alfanumericos y espacios:
			stop = true;
			for(int i = nameH.length()-1; i >= 0; i--){	//Recorremos invertido el nombre
				if(nameH[i] != ' ' && (nameH[i] < '0' || nameH[i] > '9') && 
					(nameH[i] < 'A' || nameH[i] > 'Z') && (nameH[i] < 'a' || nameH[i] > 'z')){
						cout << "ERROR: wrong name" << endl;
						stop = false;
				}
			}
		}
		
	}while(stop == false);
	
	strcpy(hero.name, nameH.c_str());
}

void asignStats(Hero &hero){
	
	string attackTotal;
	string defenseTotal;
	int att, def;
	bool stop = false;
	
	do{
		stop = true;
		
		cout << "Enter attack/defense: ";
		getline(cin, attackTotal, '/');
		att = stoi(attackTotal);
		getline(cin, defenseTotal);
		def = stoi(defenseTotal);
		
		// La suma de ataque y defensa tiene que ser 100
		if(att + def != 100 || (att <= 0) || (def <= 0)){
			cout << "ERROR: wrong distribution" << endl;
			stop = false;
		}
		
	}while(stop == false);
	hero.features.attack = att * KPOINTS / 100;
	hero.features.defense = def * KPOINTS / 100;
	hero.features.hp = def * 2 * KPOINTS /100;
	
	startHero(hero);
}

Hero createHero(Hero hero){
	asignName(hero);
	asignStats(hero);
	return hero;
}

void showEnemy(int typeEnemy, Enemy enemy){
	cout << endl << "[Enemy]" << endl
		 << "Breed: ";
	
	switch(typeEnemy){
		case(0):
			cout << "Axolotl" << endl;
			break;
		case(1):
			cout << "Troll" << endl;
			break;
		case(2):
			cout << "Orc" << endl;
			break;
		case(3):
			cout << "Hellhound" << endl;
			break;
		case(4):
			cout << "Dragon" << endl;
			break;
	}
	 
	cout << "Attack: " << enemy.features.attack << endl
         << "Defense: " << enemy.features.defense << endl 
         << "Health points: " << enemy.features.hp << endl << endl;
	  
}

Enemy createEnemy(Enemy enemy){
	int nEnemy, typeEnemy;
	nEnemy = rollDice();
//	cout << "El dado da: " << nEnemy << endl;
	
	if(nEnemy >= 1 && nEnemy <= 6){
		typeEnemy = 0;
		enemy.features.attack = 40;
		enemy.features.defense = 40;
		enemy.features.hp = enemy.features.defense * 2;	
	}
	if(nEnemy >= 7 && nEnemy <= 11){
		typeEnemy = 1;
		enemy.features.attack = 60;
		enemy.features.defense = 80;
		enemy.features.hp = enemy.features.defense * 2;			
	}
	if(nEnemy >= 12 && nEnemy <= 15){
		typeEnemy = 2;
		enemy.features.attack = 80;
		enemy.features.defense = 120;
		enemy.features.hp = enemy.features.defense * 2;	
	}
	if(nEnemy >= 16 && nEnemy <= 18){
		typeEnemy = 3;
		enemy.features.attack = 120;
		enemy.features.defense = 100;
		enemy.features.hp = enemy.features.defense * 2;
	}
	if(nEnemy >= 19 && nEnemy <= 20){
		typeEnemy = 4;
		enemy.features.attack = 160;
		enemy.features.defense = 140;
		enemy.features.hp = enemy.features.defense * 2;
	}
	showEnemy(typeEnemy, enemy);		
	return enemy;
}

int calculateDamage(Core featuresAtt, Core featuresDef, int &attackTotal, int &defenseTotal, bool special, int &contSpecial){	
	int hitPoints;
//	special = false;								// Con esta linea se comprobaba que el special funcionaba (lo mete con todo tipo de ataques)
	if(special == false && contSpecial == 0){
//		cout << endl << endl << "SPECIAL ATTACK!!!!" << endl << endl; 		// Linea para comprobar que efectivamente entramos en el special
		attackTotal = featuresAtt.attack + 5*rollDice()*3;
		contSpecial++;														// A partir del primer special, contSpecial no vuelve a ser 0 -> no vuelve a hacer special más
	}
	else{
		attackTotal = featuresAtt.attack + 5*rollDice();
	}
	defenseTotal = featuresDef.defense + 5*rollDice();
	hitPoints = attackTotal - defenseTotal;
	if(hitPoints < 0){
		hitPoints = 0;
	}
	return hitPoints;
}

void showFight(Core featuresAtt, Core featuresDef, int attackTotal, int defenseTotal, int turn, int hitPoints){
	cout << endl << endl;
	
	switch(turn){
		case 0:
			cout << "[Hero -> Enemy]" << endl;
			break;
		case 1:
			cout << "[Enemy -> Hero]" << endl;
			break;
	}
	
/*	cout << "features.attack = " << featuresAtt.attack << endl
		 << "attackTotal = " << attackTotal << endl << "attackTotal - features.attack" << attackTotal - featuresAtt.attack << endl;		// couts para comprobar valores porque tengo el gdb oxidado xD
	*/
	cout << "Attack: " << featuresAtt.attack << " + " << attackTotal - featuresAtt.attack << endl
		 << "Defense: " << featuresDef.defense << " + " << defenseTotal - featuresDef.defense << endl
		 << "Hit points: " << hitPoints << endl;
	
	switch(turn){
		case 0:
	//		cout << "Pre: " << featuresDef.hp << endl;
			featuresDef.hp -= hitPoints;
			if(featuresDef.hp < 0){
				featuresDef.hp = 0;
			}
	//		cout << "Post: " << featuresDef.hp << endl;
			cout << "Enemy health points: " << featuresDef.hp << endl;
			if(featuresDef.hp <= 0){
				cout << endl << "Enemy killed" << endl;
			}
			break;
		case 1:
			featuresDef.hp -= hitPoints;
			if(featuresDef.hp < 0){
				featuresDef.hp = 0;
			}
			cout << "Hero health points: " << featuresDef.hp << endl;
			if(featuresDef.hp <= 0){
				cout << endl << "You are dead" << endl;
			}
			break;
	}	
}

void sumXPandKills(Hero &hero, Enemy enemy){
	switch(enemy.features.attack){
		case 40:
			hero.exp += 100;
			hero.kills[0]++;
			break;
		case 60:
			hero.exp += 150;
			hero.kills[1]++;
			break;
		case 80:
			hero.exp += 200;
			hero.kills[2]++;
			break;
		case 120:
			hero.exp += 300;
			hero.kills[3]++;
			break;
		case 160:
			hero.exp += 400;
			hero.kills[4]++;
			break;
	}	
}

void fight(Hero &hero,Enemy &enemy, int &contSpecial){
	int attackTotal, defenseTotal, turn = 0, hitPoints;
	bool aliveH = true, aliveM = true;
	
	do{
		switch(turn){
			case 0:
				hitPoints = calculateDamage(hero.features, enemy.features, attackTotal, defenseTotal, hero.special, contSpecial);
				showFight(hero.features, enemy.features, attackTotal, defenseTotal, turn, hitPoints);
				
				if(enemy.features.hp - hitPoints <= 0){
					enemy.features.hp = 0;
					aliveM = false;
					sumXPandKills(hero, enemy);
				}
				else{
					enemy.features.hp = enemy.features.hp - hitPoints;
				}				
				break;
			
			case 1:
				hitPoints = calculateDamage(enemy.features, hero.features, attackTotal, defenseTotal, true, contSpecial);
				showFight(enemy.features, hero.features, attackTotal, defenseTotal, turn,hitPoints);
				if(hero.features.hp - hitPoints <= 0){
					hero.features.hp = 0;
					aliveH = false;
				}
				else{
					hero.features.hp = hero.features.hp - hitPoints;
				}
				break;
		}
		
		turn++;
		attackTotal = 0;
		defenseTotal = 0;												// Reinicializo valores por si acaso, aunque no debería ser necesario porque cada vez que llamo a la funcion deberían estar vacios
	}while(turn <= 1 && aliveH == true && aliveM == true);
}

void report(const Hero &hero){
	int total = 0;
	cout << "[Report]" << endl
		 << "Name: " << hero.name << endl
		 << "Attack: " << hero.features.attack << endl
		 << "Defense: " << hero.features.defense << endl
		 << "Health points: " << hero.features.hp << endl
		 << "Special: ";
	if(hero.special == true){
		cout << "yes" << endl;
	}
	else{
		cout << "no" << endl;
	}
	
	cout << "Runaways: " << hero.runaways << endl
		 << "Exp: " << hero.exp << endl
		 << "Enemies killed:" << endl;
		 
	for(int i = 0; i <= 4; i++){
		switch(i){
			case 0:
				cout << "- Axolotl: ";
				break;
			
			case 1:
				cout << "- Troll: ";
				break;
			
			case 2:
				cout << "- Orc: ";
				break;
			
			case 3:
				cout << "- Hellhound: ";
				break;
			
			case 4:
				cout << "- Dragon: ";
				break;	
		}
		cout << hero.kills[i] << endl;
		total += hero.kills[i];
	}
	cout << "- Total: " << total << endl;
}

void showMenu(){
  cout << "[Options]" << endl
       << "1- Fight" << endl
       << "2- Run away" << endl
       << "3- Special" << endl 
       << "4- Report" << endl
       << "q- Quit" << endl
       << "Option: ";
}

char selectOption(){
	string opt;
	char option;
	bool stop;
	
	do{
		showMenu();
		getline(cin, opt);
		stop = false;
		
		if(opt.length() != 1){
			cout << "ERROR: wrong option" << endl << endl;
		}
		else{
			if((opt[0] < '1' || opt[0] > '4') && opt[0] != 'q'){
				cout << "ERROR: wrong option" << endl << endl;
			}
			else{
				stop = true;
			}
		}
	}while(stop == false);
	
	option = opt[0];
	return option;
}


int main(int argc,char *argv[]){
  if(argc!=2){ // Si los parámetros no son correctos, el programa termina inmediatamente
    cout << "Usage: " << argv[0] << " <seed>" << endl;
  }
  else{
    srand(atoi(argv[1])); // Introducimos la semilla para generar números aleatorios
    
    // Aquí vendrá todo tu código del "main"...
    Hero hero;
    Enemy enemy;
    char option;
    bool end = false, stop, posibleRunAway = true;
    int contSpecial = 0;
    
    hero = createHero(hero);
    
    do{
		cout << endl << "--------------" << endl;
		enemy = createEnemy(enemy);
		
		do{
			stop = false;
			cout << endl << "--------------" << endl;	
			option = selectOption();
						
			switch(option){
				case('q'):
					end = true;
					stop = true;
					break;	
				
				case('1'):
					fight(hero, enemy, contSpecial);
					posibleRunAway = true;
					break;
					
				case('2'):
					if(hero.runaways == 0 || posibleRunAway == false){
						cout << endl << "ERROR: cannot run away" << endl << endl;
					}
					else{
						cout << endl << "You run away" << endl;
						posibleRunAway = false;
						stop = true;						// Linea que permite salir del bucle de este enemy y crear uno nuevo
						hero.runaways--;
					}
					break;
					
				case('3'):
					// Redirigir a case 1 pero con pequeña modificacion (x3 al lanzado de dados)
					if(hero.special == true){
						hero.special = false;
						fight(hero, enemy, contSpecial);
						posibleRunAway = true;
					}
					else{
						cout << endl << "ERROR: special not available" << endl << endl;
					}
					break;
					
				case('4'):
					cout << endl << endl;	
					report(hero);
					cout << endl << endl;
					break;
			}
			
			
			if(hero.features.hp <= 0 || enemy.features.hp <= 0){
				stop = true;
			}
			
		}while(stop == false);
		
	  //  cout << "Opcion elegida: " << option << endl;
		if(hero.features.hp <= 0){
			end = true;
			report(hero);
		}
		
	}while(end == false);
//	cout << "La aventura ha terminado" << endl;
  }
}

