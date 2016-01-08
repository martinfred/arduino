#define STBY 8

#define AIN1 4
#define AIN2 2
#define PWMA 3

#define BIN1 5
#define BIN2 7
#define PWMB 6

#define CNYG A0
#define CNYD A1
#define SHARP A2

#define vitesseG 65
#define vitesseD 35

int cny_D; 
int cny_G;
int dist;

int sensRotation = 0; //si 1 -> gauche, sinon droite

void setup() {
  
  pinMode(STBY,OUTPUT);
  
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(PWMA,OUTPUT);
  
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(PWMB,OUTPUT);
  

  pinMode(CNYG, INPUT);
  pinMode(CNYD, INPUT);
  pinMode(SHARP,INPUT);
    

  Serial.begin (9600);

  digitalWrite(STBY,HIGH);
    
  moteurG(0);
  moteurD(0);
  
 delay(3000);
  
}

void loop() {
  
  cny_D = analogRead(CNYD) ; 
  cny_G = analogRead(CNYG) ;
  dist = analogRead(SHARP) ;
   
  Serial.println(cny_G); 
  
//  while(1){
//    
//     moteurG(2*vitesseG);
//     moteurD(2*vitesseD);
//    
//  }
// 
  
   if( cny_D > 200 || cny_G > 200){
      
      //-------------------------------------
      //   On est au bord de la piste
      //-------------------------------------
      
      if( cny_D > 200 && cny_G > 200){
       
        moteurG(-2*vitesseG);
        moteurD(-2*vitesseD);
       
        delay(500);
       
      } else {
        
        if( cny_D > 200){
          
          sensRotation = 1;
          
          moteurG(0);
          moteurD(3*vitesseD);
        
        }
        
        if( cny_G > 200){
          
          sensRotation = 0;
          
          moteurG(3*vitesseG);
          moteurD(0);
        
        }
      }
    
    } else {

      //-------------------------------------
      //   On n'est pas au bord de la piste
      //-------------------------------------
    
      if(dist < 150){
        
        //-------------------------------------
        //   Aucun robot en face
        //-------------------------------------
        
        if(0 == sensRotation){ 
     
          moteurG(vitesseG);
          moteurD(-vitesseD);
        
        }else{
        
          moteurG(-vitesseG);
          moteurD(vitesseD);
          
        }
        
      } else {
        
       //-------------------------------------
      //   On est face à un robot
      //-------------------------------------
     
       moteurG(2*vitesseG);
       moteurD(2*vitesseD);
       
      }
    
    
    }
    
}


void moteurG(int v){
 
 if(v >= 0){
   
    digitalWrite(AIN2,HIGH);
    digitalWrite(AIN1,LOW);
    
    analogWrite(PWMA,v);
   
 } else {
 
    digitalWrite(AIN2,LOW);
    digitalWrite(AIN1,HIGH);
    
    analogWrite(PWMA,-v);
  
 }
 
} 

void moteurD(int v){
 
 if(v >= 0){
   
    digitalWrite(BIN2,HIGH);
    digitalWrite(BIN1,LOW);
    
    analogWrite(PWMB,v);
   
 } else {
 
    digitalWrite(BIN2,LOW);
    digitalWrite(BIN1,HIGH);
    
    analogWrite(PWMB,-v);
  
 }
 
} 
