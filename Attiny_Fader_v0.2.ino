// Not tested on Attiny

int val = 0;
int target = 20 ;
int tmp;
int w;
int delta = 2
;
void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  Serial.begin(115200);
}

void position(){
  val = (analogRead(A1));
   
    if (val > (target + delta)){
      w = (val - target);
      digitalWrite(3, HIGH);
      digitalWrite(2, LOW);
      delay(1);
      digitalWrite(3, LOW);
      digitalWrite(2, LOW);  
    }
    
    else {
      w = (target - val);
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      delay(1);
      digitalWrite(3, LOW);
      digitalWrite(2, LOW);     
    }  
    //Serial.println(val);
 }
 
void loop() {
//target = analogRead(A3);
//  tmp=Serial.parseInt();
//  if(tmp > 0){
//    target = tmp;
//  }
  val = analogRead(A1);
  //Serial.println(val);
  
  while ((val > (target + delta)) || (val < (target - delta)))
  {
    position();
  }
}
