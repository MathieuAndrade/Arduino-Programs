/* déclaration des constantes pour les nom des broches ; ceci selon le schéma*/
const int btn_minus = 2;
const int btn_plus = 3;
const int led_0 = 10;
const int led_1 = 11;
const int led_2 = 12;
const int led_3 = 13;


/* déclaration des variables utilisées pour le comptage et le décomptage */

int nombre_led = 0; //le nombre qui sera incrémenté et décrémenté
int etat_bouton; //lecture de l'état des boutons (un seul à la fois mais une variable suffit)

int memoire_plus = HIGH; //état relâché par défaut
int memoire_minus = HIGH;


/* initilisation des broches en entrée/sortie */
void setup()
{
    pinMode(btn_plus, INPUT);
    pinMode(btn_minus, INPUT);
    pinMode(led_0, OUTPUT);
    pinMode(led_1, OUTPUT);
    pinMode(led_2, OUTPUT);
    pinMode(led_3, OUTPUT);
}

void loop()
{
    //lecture de l'état du bouton d'incrémentation
    etat_bouton = digitalRead(btn_plus);
    
    //Si le bouton a un état différent que celui enregistré ET que cet état est "appuyé"
    if((etat_bouton != memoire_plus) && (etat_bouton == LOW))
    {
        nombre_led++; //on incrémente la variable qui indique combien de LED devrons s'allumer
    }
    
    memoire_plus = etat_bouton; //on enregistre l'état du bouton pour le tour suivant
    
    
    //et maintenant pareil pour le bouton qui décrémente
    etat_bouton = digitalRead(btn_minus); //lecture de son état
    
    //Si le bouton a un état différent que celui enregistré ET que cet état est "appuyé"
    if((etat_bouton != memoire_minus) && (etat_bouton == LOW))
    {
        nombre_led--; //on décrémente la valeur de nombre_led
    }
    memoire_minus = etat_bouton; //on enregistre l'état du bouton pour le tour suivant
    
    //on applique des limites au nombre pour ne pas dépasser 4 ou 0
    if(nombre_led > 4)
    {
        nombre_led = 4;
    }
    if(nombre_led < 0)
    {
        nombre_led = 0;
    }
    
    //appel de la fonction affiche() que l'on aura créée
    //on lui passe en paramètre la valeur du nombre de LED à éclairer
    affiche(nombre_led); 
}

void affiche(int valeur_recue)
{
    //on éteint toutes les leds
    digitalWrite(led_0, HIGH);
    digitalWrite(led_1, HIGH);
    digitalWrite(led_2, HIGH);
    digitalWrite(led_3, HIGH);
    
    //Puis on les allume une à une
    if(valeur_recue >= 1)
    {
        digitalWrite(led_0, LOW);
    }
    if(valeur_recue >= 2)
    {
        digitalWrite(led_1, LOW);
    }
    if(valeur_recue >= 3)
    {
        digitalWrite(led_2, LOW);
    }
    if(valeur_recue >= 4)
    {
        digitalWrite(led_3, LOW);
    }
}
