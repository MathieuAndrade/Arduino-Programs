byte contador = 0;

void setup() 
{                
  //Configura os pinos digitais 2, 3, 4 e 5 como saída digital
  DDRD = B00111100; 
}


void loop() 
{
  while (contador<=9) //Enquanto contador for menor ou igual a nove
  {
    PORTD = contador<<2;  //Rotaciona 2 vezes para esq. o contador e manda para os pinos de saída 
    delay(1000); //Espera um segundo
    contador++;  //Incrementa a variável contador.
  }     
  contador=0;  //zera o contador e reinicia a contagem 
}

