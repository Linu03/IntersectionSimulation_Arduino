//State global pentru gestionarea starilor 1,2,3
char State = 'N';
//Salvam culoarea precedenta intr-o variabila globala 
char culoarePrecedenta = 'G';
//Sub-state pentru gestionarea sub-starilor de la starea 3
char state = '1' ;

//Functie pentru setarea culorilor pentru pietoni
void setColorPietoni(int redValue, int greenValue,  int blueValue) {
	analogWrite(3, redValue);
    analogWrite(5,  greenValue);
    analogWrite(6, blueValue);
}

//Functie pentru setarea culorilor pentru masini
void setColorMasini(int redValue, int greenValue,  int blueValue) {
	analogWrite(9, redValue);
    analogWrite(10,  greenValue);
    analogWrite(11, blueValue);
}

//Oprim pinii pentru ledurile de la semafoarele pietonilor
void opresteStareaPietoni(){
	analogWrite(3, 0);
    analogWrite(5, 0);
    analogWrite(6, 0);
}

//Oprim pinii pentru ledurile de la semafoarele masinilor
void opresteStareaMasini(){
    analogWrite(9, 0);
    analogWrite(10, 0);
    analogWrite(11, 0);
}

void setup()
{
 Serial.begin(5000);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}


void loop()
{
 
   if(Serial.available() > 0){
   State = Serial.read();
  }
  
  //Normal (Starea 1)
  if(State == 'N'){
  	setColorPietoni(0,255,0);
    setColorMasini(255,0,0);
    delay(5000);
    setColorPietoni(255,0,0);
    delay(1000);
    setColorMasini(255,255,0);
    delay(1000);
    setColorMasini(0,255,0);
    delay(5000);
  }
  
  //Blinking (Starea 2)
  if(State == 'B'){
  setColorPietoni(255,255,0);
  setColorMasini(255,255,0);
  digitalWrite(8,HIGH);
  delay(1000);
  opresteStareaPietoni();
  opresteStareaMasini();
  digitalWrite(8,LOW);
  delay(1000);
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
   		     digitalWrite(8,LOW);
             if(Serial.available() > 0) state = Serial.read();
    
  		}
        // Sub-starea X - semafoarele trec prin toate culorile
        if(state == 'X'){
         opresteStareaPietoni();
     	 opresteStareaMasini();
         digitalWrite(8,LOW);
         delay(2000);
          
         setColorPietoni(255,0,0); 
         setColorMasini(255,0,0);
         delay(2000);
         digitalWrite(8,HIGH);
         opresteStareaPietoni();
         setColorMasini(255,255,0);
         delay(2000);
         digitalWrite(8,LOW);
         setColorPietoni(0,255,0); 
         setColorMasini(0,255,0);
         delay(2000);
         if(Serial.available() > 0) state = Serial.read();
        }
        
        // Sub-starea R - full rosu
        if (state == 'R')   { 
          					setColorPietoni(255,0,0); 
                            setColorMasini(255,0,0);
          					digitalWrite(8,LOW);
          					culoarePrecedenta='R';
          					if(Serial.available() > 0) state = Serial.read();
        					}
        // Sub-starea G - full galben
        if (state == 'G')   { 
          					setColorPietoni(255,255,0); 
                            setColorMasini(255,255,0);
          					digitalWrite(8,HIGH);
          					culoarePrecedenta='G';
          					if(Serial.available() > 0) state = Serial.read();
        					}
        // Sub-starea V - full verde
        if (state == 'V')   { 
          					setColorPietoni(0,255,0); 
                            setColorMasini(0,255,0);
          					digitalWrite(8,LOW);
          					culoarePrecedenta='V';
          					if(Serial.available() > 0) state = Serial.read();
        					}
        // Sub-starea T - aprinder intermitenta ultimei culori setate
        if (state == 'T'){
        
          //verificare culoare precedenta pentru a indeplini sub-starea T
          
          if(culoarePrecedenta=='R'){
          setColorPietoni(255,0,0); 
          setColorMasini(255,0,0);
          digitalWrite(8,LOW);
          delay(1000);
          opresteStareaPietoni();
          opresteStareaMasini();
          delay(1000);
            if(Serial.available() > 0) state = Serial.read();
          } 
          if(culoarePrecedenta=='G' ){
          setColorPietoni(255,255,0); 
          setColorMasini(255,255,0);
	      digitalWrite(8,HIGH);
          delay(1000);
          opresteStareaPietoni();
          opresteStareaMasini();
          digitalWrite(8,LOW);
          delay(1000);
            if(Serial.available() > 0) state = Serial.read();
          } 
           if(culoarePrecedenta=='V'){
          setColorPietoni(0,255,0); 
          setColorMasini(0,255,0);
          digitalWrite(8,LOW);
          delay(1000);
          opresteStareaPietoni();
          opresteStareaMasini();
          delay(1000);
             if(Serial.available() > 0) state = Serial.read();
          } 
          //La fiecare substare se incearca citirea unei noi sub-stari, daca nu se introduce in Serial, codul se executa normal
          
        }
      }
    }
 }
}