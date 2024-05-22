#define pietoni_red 3
#define pietoni_green 5
#define pietoni_blue 6
#define masini_red 9
#define masini_green 10
#define masini_blue 11
#define intermitent 8
#define short_delay 1000
#define middle_delay 2000
#define long_delay 5000

//State global pentru gestionarea starilor 1,2,3
char State = 'N';
//Salvam culoarea precedenta intr-o variabila globala 
char culoarePrecedenta = 'G';
//Sub-state pentru gestionarea sub-starilor de la starea 3
char state = '1' ;

//Functie pentru setarea culorilor pentru pietoni
void setColorPietoni(int redValue, int greenValue,  int blueValue) {
	analogWrite(pietoni_red, redValue);
    analogWrite(pietoni_green,  greenValue);
    analogWrite(pietoni_blue, blueValue);
}

//Functie pentru setarea culorilor pentru masini
void setColorMasini(int redValue, int greenValue,  int blueValue) {
	analogWrite(masini_red, redValue);
    analogWrite(masini_green,  greenValue);
    analogWrite(masini_blue, blueValue);
}

//Oprim pinii pentru ledurile de la semafoarele pietonilor
void opresteStareaPietoni(){
	analogWrite(pietoni_red, 0);
    analogWrite(pietoni_green, 0);
    analogWrite(pietoni_blue, 0);
}

//Oprim pinii pentru ledurile de la semafoarele masinilor
void opresteStareaMasini(){
    analogWrite(masini_red, 0);
    analogWrite(masini_green, 0);
    analogWrite(masini_blue, 0);
}

void setup()
{
 Serial.begin(5000);
  pinMode(pietoni_red, OUTPUT);
  pinMode(pietoni_green, OUTPUT);
  pinMode(pietoni_blue, OUTPUT);
  pinMode(intermitent,OUTPUT);
  pinMode(masini_red, OUTPUT);
  pinMode(masini_green, OUTPUT);
  pinMode(masini_blue, OUTPUT);
}

void citeste_val(){

   char state_old = State;
   if(Serial.available() > 0){
   State = Serial.read();
   if((state_old == 'N' || state_old == 'B') && (State == 'V' || State == 'R' || State == 'G' || State == 'T' || State=='S' || State == 'X'))
      {
      	State = state_old;
      }
   }
}

void adjust_logic_action(){
  //Normal (Starea 1)
  if(State == 'N'){
  	setColorPietoni(0,255,0);
    setColorMasini(255,0,0);
    delay(long_delay);
    setColorPietoni(255,0,0);
    delay(short_delay);
    setColorMasini(255,255,0);
    delay(short_delay);
    setColorMasini(0,255,0);
    delay(long_delay);
  }
  //Blinking (Starea 2)
  else if(State == 'B'){
  setColorPietoni(255,255,0);
  setColorMasini(255,255,0);
  digitalWrite(intermitent,HIGH);
  delay(short_delay);
  opresteStareaPietoni();
  opresteStareaMasini();
  digitalWrite(intermitent,LOW);
  delay(short_delay);
  }
  
  
  
  
  //Diagnoza (Starea 3)
  if(State == 'D'){
    if(state == '1') {
   opresteStareaMasini();
   opresteStareaPietoni();
   if(Serial.available() > 0) state = Serial.read();
    }
	
    //Logica pentru gestionarea sub-starilor aplicat pe toate cazuri necesare
   
    if(Serial.available() > 0 || state != '1'){

      //Modalitate de a iesi din starea D
      if(state == 'N' || state == 'B') {State=state; state='1';}
      else{
  		if(state == 'S'){ 
   			 opresteStareaPietoni();
     		 opresteStareaMasini();
   		     digitalWrite(intermitent,LOW);
             if(Serial.available() > 0) state = Serial.read();
    
  		}
        // Sub-starea X - semafoarele trec prin toate culorile
        if(state == 'X'){
         opresteStareaPietoni();
     	 opresteStareaMasini();
         digitalWrite(intermitent,LOW);
         delay(middle_delay);
          
         setColorPietoni(255,0,0); 
         setColorMasini(255,0,0);
         delay(middle_delay);
         digitalWrite(intermitent,HIGH);
         opresteStareaPietoni();
         setColorMasini(255,255,0);
         delay(middle_delay);
         digitalWrite(intermitent,LOW);
         setColorPietoni(0,255,0); 
         setColorMasini(0,255,0);
         delay(middle_delay);
         if(Serial.available() > 0) state = Serial.read();
        }
        
        // Sub-starea R - full rosu
        if (state == 'R')   { 
          					setColorPietoni(255,0,0); 
                            setColorMasini(255,0,0);
          					digitalWrite(intermitent,LOW);
          					culoarePrecedenta='R';
          					if(Serial.available() > 0) state = Serial.read();
        					}
        // Sub-starea G - full galben
        if (state == 'G')   { 
          					setColorPietoni(255,255,0); 
                            setColorMasini(255,255,0);
          					digitalWrite(intermitent,HIGH);
          					culoarePrecedenta='G';
          					if(Serial.available() > 0) state = Serial.read();
        					}
        // Sub-starea V - full verde
        if (state == 'V')   { 
          					setColorPietoni(0,255,0); 
                            setColorMasini(0,255,0);
          					digitalWrite(intermitent,LOW);
          					culoarePrecedenta='V';
          					if(Serial.available() > 0) state = Serial.read();
        					}
        // Sub-starea T - aprinder intermitenta ultimei culori setate
        if (state == 'T'){
        
          //verificare culoare precedenta pentru a indeplini sub-starea T
          
          if(culoarePrecedenta=='R'){
          setColorPietoni(255,0,0); 
          setColorMasini(255,0,0);
          digitalWrite(intermitent,LOW);
          delay(short_delay);
          opresteStareaPietoni();
          opresteStareaMasini();
          delay(short_delay);
            if(Serial.available() > 0) state = Serial.read();
          } 
          if(culoarePrecedenta=='G' ){
          setColorPietoni(255,255,0); 
          setColorMasini(255,255,0);
	      digitalWrite(intermitent,HIGH);
          delay(short_delay);
          opresteStareaPietoni();
          opresteStareaMasini();
          digitalWrite(intermitent,LOW);
          delay(short_delay);
            if(Serial.available() > 0) state = Serial.read();
          } 
           if(culoarePrecedenta=='V'){
          setColorPietoni(0,255,0); 
          setColorMasini(0,255,0);
          digitalWrite(intermitent,LOW);
          delay(short_delay);
          opresteStareaPietoni();
          opresteStareaMasini();
          delay(short_delay);
             if(Serial.available() > 0) state = Serial.read();
          } 
          //La fiecare substare se incearca citirea unei noi sub-stari, daca nu se introduce in Serial, codul se executa normal
          
        }
      }
    }
 }
}

void loop()
{
 citeste_val();  
 adjust_logic_action();
}