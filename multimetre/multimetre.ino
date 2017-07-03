int S0 ;
int S1 ;
int S2 ;
int S3 ;
int S4 ;
int S5 ;
int sensValue1 ;
int sens;


void setup() {
Serial.begin(9600);
}



void loop() {
S0 = analogRead(A0);
S1 = analogRead(A1);
S2 = analogRead(A2);
S3 = analogRead(A3);
S4 = analogRead(A4);
S5 = analogRead(A6);

Serial.print(S0);
Serial.print(" ");
Serial.print(S1);
Serial.print(" ");
Serial.print(S2);
Serial.print(" ");
Serial.print(S3);
Serial.print(" ");
Serial.print(S4);
Serial.print(" ");
Serial.println(S5);

sensValue1 = Moyenne(S1);
//delay(50);

}     
/*
int Moyenne(int param1) {//sonde, nombre d'entrées tableau
    int tab[5] ;
    int moyenne ;
  for(int i = 0; i <5 ; i++)  {   // index du tableau 
      tab[i] = param1;       
      moyenne = ( tab[0]+tab[1]+tab[2]+tab[3]+tab[4]) / 5;   
                           }
        return moyenne; */

int Moyenne(int param1) {                //param1 = sonde
    static int tab[5] ;                         //création du tableau
    static int index=0;
    int moyenne ;                     //variable pour la moyenne

    tab[index]=param1;
    index++;
    if (index>=5) index=0;
   
    moyenne = (tab[0]+tab[1]+tab[2]+tab[3]+tab[4]) / 5;   //on calcule la moyenne
    return moyenne ;
}





  

