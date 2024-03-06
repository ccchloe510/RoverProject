void setup() {
   pinMode(A0,INPUT); 
   Serial.begin(9600);

}

void loop() {
  
  float stp =0 ;
  float start = 0;
  float period = 0;
  int VA0;
  int peak_V = 0;
  bool detected = false;
  String age;

  float start_time1 = millis();
  float endtime1 = start_time1;

  //finds voltage at peak
  while ((endtime1 - start_time1) <=10) { 
    VA0 = analogRead(A0);
    if (VA0 > peak_V){
      peak_V = VA0;
      
      
    }
    endtime1 = millis();
  }

  peak_V = peak_V * 0.9;
  

  delay(3);


  VA0 = analogRead(A0);
  
    float start_time2 = millis();
    float endtime2 = start_time2;
    
    while(!detected && (endtime2 - start_time2) <=100 ){
      VA0 = analogRead(A0);
      if (VA0>= peak_V){
        detected = true; 
      }
      endtime2 = millis();
     }
  
  if (detected== true){
    start = micros();
    VA0= analogRead(A0);
    if(VA0 > peak_V){

      while (VA0 > peak_V){
        VA0 = analogRead(A0);
        }
        
      while(VA0 <= peak_V){
         VA0 = analogRead(A0);
         
      }
          
      stp = micros();
      
      period = stp - start;
      }
  }


    else{
      age = "Age not detected";
      Serial.println(age);
    }
    


    
    if ( (period >= 1000)&&(period <= 7470)){
      age = String(period /10) + " years old";
      Serial.println(age);
 
    }
    else{
      age = "Age not detected";
      Serial.println(age);
    }
  
 
}
