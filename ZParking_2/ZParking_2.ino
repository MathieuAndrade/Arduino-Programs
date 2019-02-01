//les broches du décodeur 7 segments
const int bit_A = 2;
const int bit_B = 3;
const int bit_C = 4;
const int bit_D = 5;
//les broches des transistors pour l'afficheur des dizaines et celui des unités
const int alim_dizaine = 7;
const int alim_unite = 6;
//les broches des boutons
const int btn_entree = 8;
const int btn_sortie = 9;
//les leds de signalements
const int led_rouge = 12;
const int led_verte = 11;
//les mémoires d'état des boutons
int mem_entree = HIGH;
int mem_sortie = HIGH;
int etat = HIGH; //variable stockant l'état courant d'un bouton

char place_dispo = 10; //contenu des places dispos
bool afficheur = false;
long temps;

void setup()
{
	//Les broches sont toutes des sorties (sauf les boutons)
	pinMode(bit_A, OUTPUT);
	pinMode(bit_B, OUTPUT);
	pinMode(bit_C, OUTPUT);
	pinMode(bit_D, OUTPUT);
	pinMode(alim_dizaine, OUTPUT);
	pinMode(alim_unite, OUTPUT);
	pinMode(btn_entree, INPUT);
	pinMode(btn_sortie, INPUT);
	pinMode(led_rouge, OUTPUT);
	pinMode(led_verte, OUTPUT);
	
	//Les broches sont toutes mises à l'état bas (sauf led rouge éteinte)
	digitalWrite(bit_A, LOW);
	digitalWrite(bit_B, LOW);
	digitalWrite(bit_C, LOW);
	digitalWrite(bit_D, LOW);
	digitalWrite(alim_dizaine, LOW);
	digitalWrite(alim_unite, LOW);
	digitalWrite(led_rouge, HIGH);
	digitalWrite(led_verte, LOW); //vert par défaut
	temps = millis(); //enregistre "l'heure"
}

void loop()
{
	//si ca fait plus de 10 ms qu'on affiche, on change de 7 segments
	if((millis() - temps) > 10)
	{
		//on inverse la valeur de "afficheur" pour changer d'afficheur (unité ou dizaine)
		afficheur = !afficheur;
		//on affiche
		afficher_nombre(place_dispo, afficheur);
		temps = millis(); //on met à jour le temps
	}
	
	//on test maintenant si les boutons ont subi un appui (ou pas)
	//d'abord le bouton plus puis le moins
	etat = digitalRead(btn_entree);
	if((etat != mem_entree) && (etat == LOW))
		place_dispo += 1;
	mem_entree = etat; //on enregistre l'état du bouton pour le tour suivant

	//et maintenant pareil pour le bouton qui décrémente
	etat = digitalRead(btn_sortie);
	if((etat != mem_sortie) && (etat == LOW))
		place_dispo -= 1;
	mem_sortie = etat; //on enregistre l'état du bouton pour le tour suivant
	
	//on applique des limites au nombre pour ne pas dépasser 99 ou 0
	if(place_dispo > 99)
		place_dispo = 99;
	if(place_dispo < 0)
		place_dispo = 0;
		
	//on met à jour l'état des leds
	//on commence par les éteindre
	digitalWrite(led_verte, HIGH);
	digitalWrite(led_rouge, HIGH);
	if(place_dispo == 0) //s'il n'y a plus de place
		digitalWrite(led_rouge, LOW);
	else
		digitalWrite(led_verte, LOW);
}

//fonction permettant d'afficher un nombre
void afficher_nombre(char nombre, bool afficheur)
{
	long temps;
	char unite = 0, dizaine = 0;
	if(nombre > 9)
		dizaine = nombre / 10; //on récupère les dizaines
	unite = nombre - (dizaine*10); //on récupère les unités
	
	if(afficheur)
	{
		//on affiche les dizaines
		digitalWrite(alim_unite, LOW);
		digitalWrite(alim_dizaine, HIGH);
		afficher(dizaine);
	}
	else
	{
		//on affiche les unités
		digitalWrite(alim_dizaine, LOW);
		digitalWrite(alim_unite, HIGH);
		afficher(unite);
	}
}

//fonction écrivant sur un seul afficheur
void afficher(char chiffre)
{
   	//on commence par écrire 0, donc tout à l'état bas
	digitalWrite(bit_A, LOW);
	digitalWrite(bit_B, LOW);
	digitalWrite(bit_C, LOW);
	digitalWrite(bit_D, LOW);

	if(chiffre >= 8)
	{
		digitalWrite(bit_D, HIGH);
		chiffre = chiffre - 8;
	}
	if(chiffre >= 4)
	{
		digitalWrite(bit_C, HIGH);
		chiffre = chiffre - 4;
	}
	if(chiffre >= 2)
	{
		digitalWrite(bit_B, HIGH);
		chiffre = chiffre - 2;
	}
	if(chiffre >= 1)
	{
		digitalWrite(bit_A, HIGH);
		chiffre = chiffre - 1;
	}
}
//Fin du programme
