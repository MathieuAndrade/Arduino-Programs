//************************************************************
//*** Lecture des caracteres en provenance d un client web **
//************************************************************
#include <SPI.h> 
#include <Ethernet.h> 
#include <SD.h>
//--- Declarations ---
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02  }; //-- Addresse MAC à adapter
IPAddress ip(192,168,1,16);                           //-- Adresse IP à adapter
EthernetServer serveurHTTP(4200);                       //-- objet serveur utilisant le port 80 = port HTTP
String msg="";                                        //-- pour réception chaine requete
File webFile;                                         //-- pour afficher la page HTML     

//--- Setup ---
void setup() { 
	Serial.begin(9600); 
    //-- Initialisation de la carte SD
    Serial.println("Initializing SD card...");
    if (!SD.begin(4)) {
        Serial.println("ERREUR - La carte SD est indisponible!");
        return;}
    Serial.println("Carte SD OK");
    if (!SD.exists("mapage.htm")) {
        Serial.println("ERREUR - Fichier mapage.html absent !");
        return;}
    Serial.println("Fichier mapage.html OK");
	//---- initialise le serveur ----
	Ethernet.begin(mac, ip); 
	delay(1000); 
	Serial.print("Shield Ethernet OK : L'adresse IP du shield Ethernet est : " );
	Serial.println(Ethernet.localIP());
	serveurHTTP.begin();
	Serial.println("Serveur Ethernet OK : Ecoute sur port 80 (http)");
} 

//--- Traitement ---
void loop(){ 
	EthernetClient client = serveurHTTP.available(); //-- Objet Client Web
	if (client) { //-- Si un navigateur interroge l'URL de la carte Arduino
	   Serial.println ("... Reception demande client...");	
	   ////////////////// Réception requete //////////////////////////
	   boolean currentLineIsBlank = true;
	   msg=""; 
	   while (client.connected()) { 
		if (client.available()) { //-- Si octets disponibles en lecture
		   char c = client.read(); 
		   msg+=c; 
                   if (c == '\n' && currentLineIsBlank) {	//--Dernière ligne du client reçue est vide	
		       Serial.println ("Reception requete terminee");
		       //-- Analyse de la requete reçue 
		       Serial.println("------------ Analyse ------------"); 
		       requeteOk(client);
		       if (msg.indexOf("ajax_switch") > -1) {
			  Serial.println ("Requete GET AJAX valide !");
			  //-- envoi de la réponse HTTP ---
			  envoiReponse(client);
			  Serial.println("La reponse Ajax envoyee au client distant...");} 	
		       else { //-- si pas la chaine souhaitée on envoie page entiere
			  Serial.println("Envoi mapage.html");
			  webFile = SD.open("mapage.htm");
                          if (webFile) {while(webFile.available()) {
                             client.write(webFile.read());}} //-- Envoi de la page web au client                         
                          webFile.close();}
			   //-- Affichage de la requete HTTP sur le port série
                       Serial.print(msg);
                       msg = "";           
                       break;}
                //-- Chaque ligne de texte reçue se termine par \r\n
                if (c == '\n') { //-- Fin de ligne reçue
                   currentLineIsBlank = true;} 
                else if (c != '\r') { //-- Un caractère en provenance du client est reçu
                   currentLineIsBlank = false;}}}
	//-- fermeture de la connexion avec le client après envoi réponse
	delay(1); 
	client.stop();
	Serial.println("------------ Fermeture de la connexion avec le client ------------"); 
	Serial.println ("");
	} 
} 
//------------------------------------------------------
// Texte HTML à envoyer pour signifier que tout est ok		
//-----------------------------------------------------
void requeteOk(EthernetClient client){
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: keep-alive");
    client.println();}
//------------------------------------------------------
// Chaine à envoyer au client en réponse à une requête	
//-----------------------------------------------------	
 void envoiReponse(EthernetClient client){  
    //-- Envoi au client en fonction de l'état d'une broche
    if (digitalRead(3)) {client.println("Switch state: ON");}
    else {client.println("Switch state: OFF");}
    } 
