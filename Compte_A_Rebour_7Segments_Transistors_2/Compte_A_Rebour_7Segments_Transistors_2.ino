//définition des broches du décodeur 7 segments (vous pouvez changer les numéros si bon vous semble)
const int bit_A = 2;
const int bit_B = 3;
const int bit_C = 4;
const int bit_D = 5;

//définitions des broches des transistors pour chaque afficheur (dizaines et unités)
const int alim_dizaine = 6;
const int alim_unite = 7;

void setup()
{
	//Les broches sont toutes des sorties
	pinMode(bit_A, OUTPUT);
	pinMode(bit_B, OUTPUT);
	pinMode(bit_C, OUTPUT);
	pinMode(bit_D, OUTPUT);
	pinMode(alim_dizaine, OUTPUT);
	pinMode(alim_unite, OUTPUT);
	
	//Les broches sont toutes mises à l'état bas
	digitalWrite(bit_A, LOW);
	digitalWrite(bit_B, LOW);
	digitalWrite(bit_C, LOW);
	digitalWrite(bit_D, LOW);
	digitalWrite(alim_dizaine, LOW);
	digitalWrite(alim_unite, LOW);
}

void loop() //fonction principale
{
	for(char i = 0; i<100; i++) //boucle qui permet de compter de 0 à 99 (= 100 valeurs)
	{
		afficher_nombre(i); //appel de la fonction affichage avec envoi du nombre à afficher
	}
}

//fonction permettant d'afficher un nombre sur deux afficheurs
void afficher_nombre(char nombre)
{
	long temps; //variable utilisée pour savoir le temps écoulé...
	char unite = 0, dizaine = 0; //variable pour chaque afficheur

	if(nombre > 9) //si le nombre reçu dépasse 9
        {
		dizaine = nombre / 10; //on récupère les dizaines
        }

	unite = nombre - (dizaine*10); //on récupère les unités

	temps = millis(); //on récupère le temps courant

	// tant qu'on a pas affiché ce chiffre pendant au moins 500 millisecondes
        // permet donc de pouvoir lire le nombre affiché
	while((millis()-temps) < 500)
	{
		//on affiche le nombre

		//d'abord les dizaines pendant 10 ms
		digitalWrite(alim_dizaine, HIGH); /* le transistor de l'afficheur des dizaines est saturé,
                                                    donc l'afficheur est allumé */
		afficher(dizaine); //on appel la fonction qui permet d'afficher le chiffre dizaine
                digitalWrite(alim_unite, LOW); // l'autre transistor est bloqué et l'afficheur éteint
                delay(10);

		//puis les unités pendant 10 ms
                digitalWrite(alim_dizaine, LOW); //on éteint le transistor allumé
		afficher(unite); //on appel la fonction qui permet d'afficher le chiffre unité
		digitalWrite(alim_unite, HIGH); //et on allume l'autre
                delay(10);
	}
}

//fonction écrivant sur un seul afficheur
//on utilise le même principe que vu plus haut
void afficher(char chiffre)
{
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

//le code est terminé
