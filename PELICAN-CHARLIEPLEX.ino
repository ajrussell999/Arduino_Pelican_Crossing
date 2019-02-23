

  int GREEN = 4;              // GREEN leds Anode pin 4
  int AMBER = 5;               // AMBER leds Anode pin 5
  int RED = 6;                // RED leds Anode pin 6
  int NSCATH = 7;             // NORTH SOUTH leds cathode
  int WECATH = 8;             // WEST EAST leds cathode
  
  int PELICANPRESSB = 2;          // Pin 2, interrupt pin, to PELICAN crossing button.
  int PELICANRED = 10;            // Pedestrian RED signal
  int PELICANGREEN = 11;          // Pedestrian GREEN signal

  int TLABEL = 100;               // VARIABLE integer TO TIME LIGHTS LIT STATE.
  boolean norepeat = false;       // 1 DENY Pelican, 0 PERMIT Pelican.
  unsigned long LASTTIME = 0;     // Time of last Pelican event.
  unsigned long TIMENOW = 0;      // Current time from Millis.In miliseconds. Beware overflow.
  unsigned long PGREENLAST = 0;   // Time pelicangreen changed state
  unsigned long PGREENNOW = 0;    // Time in ms since pelicangreen last state change
 

  volatile boolean toggle_p_green = false;    // Time pelicangreenflash on & off
  volatile boolean WAIT_LIT = false;          // true if pedestrians waiting.
  volatile int PINHIBIT = 30000;              // VARIABLE TO INHIBIT REPEAT PELICAN EVENT, 30000 = 30 seconds.

  
  void setup() {
    Serial.begin (9600);
                                  // Initialise pins High Impedance
  pinMode(RED, INPUT);            // High Impedance on RED leds Anode
  pinMode(AMBER, INPUT);          // High Impedance on AMBER leds Anode
  pinMode(GREEN, INPUT);          // High Impedance on GREEN leds Anode
  pinMode(NSCATH, INPUT);         // NORTH SOUTH Cathode  High Impedance
  pinMode(WECATH, INPUT);         // WEST EAST Cathode High Impedance  
  pinMode(PELICANGREEN, INPUT);   // Pedestrian WALK, PELICAN GREEN Anode High Impedance
  pinMode(PELICANRED, OUTPUT);    // Pedistrian WAIT, PELICAN RED Anode Low Impedance
  digitalWrite(PELICANRED, HIGH); // +5V to PELICAN RED Anode

  LASTTIME = millis();
  
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), BUTTONP, CHANGE); // Interrupt pin 2 for PELICAN push button, ISR BUTTONP.

  }
                          
  
  void REPEATTIME(){
    
    TIMENOW = millis();
    if (TIMENOW - LASTTIME >= 30000){   // Over 30s since last pedestrians crossed ?
    (norepeat) = false ;                 // PERMIT PELICAN event to run.
    }
      else 
        {
         (norepeat) = true ;              // Less than 60 seconds passed , DENY PELICAN event as norepeat now > 0.
        }
    }
        
  void BUTTONP() {                       // Interrupt Service Routine, "ISR" for pin 2, PELICANPRESSB, flag WAIT_LIT. 
        WAIT_LIT = true;                 // WAIT_LIT ON
 // Serial.println(PELICANPRESSB);
  Serial.println(WAIT_LIT);
  Serial.println(norepeat);
  }

  void NSRED(){
  
  pinMode(GREEN, INPUT);      // High Impedance on GREEN leds Anode.
  pinMode(AMBER, INPUT);      // High Impedance on AMBER leds Anode.
  pinMode(WECATH, INPUT);     // WEST EAST Cathode, High Impedance.
  pinMode(RED,OUTPUT);        // Change RED Anode from High Impedance to O/P mode, Low Impedance.
  digitalWrite(RED,HIGH);     // +5V to RED leds Anode, NS and WE.
  pinMode(NSCATH,OUTPUT);     // NORTH SOUTH Cathode (Ground) from High Impedance to O/P mode, Low Impedance.
  digitalWrite(NSCATH,LOW);   // NS Cathode write O/P LOW, sink 40mA, completes circuit on  NS RED. ON.
  delay(5);                   // 5 miliseconds, lit for persistance of vision illusion.
    
  digitalWrite(RED,LOW);      // 0V to RED leds Anode. OFF
  pinMode(RED,INPUT);         // RED leds Anode High Impedance.
  pinMode(NSCATH,INPUT);      // NORTH SOUTH Cathode High Impedance.
  }

  void WERED(){
  
  pinMode(GREEN, INPUT);      // High Impedance on GREEN leds Anode.
  pinMode(AMBER, INPUT);      // High Impedance on AMBER leds Anode.
  pinMode(NSCATH, INPUT);     // NORTH SOUTH CATHODE High Impedance.
  pinMode(RED, OUTPUT);       // Change RED Anode from High Impedance, to O/P mode, Low Impedance.
  digitalWrite(RED, HIGH);    // +5v RED leds Anode NS and WE.
  pinMode(WECATH, OUTPUT);    // WEST EAST Cathode (Ground) from High Impedance to O/P mode, Low Impedance.
  digitalWrite(WECATH,LOW);   // WE Cathode write O/P LOW, sink 40mA, completes circuit. WE RED. ON.
  delay(5);                   // 5 miliseconds, lit for persistance of vision illusion.
  
  digitalWrite(RED, LOW);     // 0V to RED leds Anode. OFF.
  pinMode(RED, INPUT);        // RED leds Anode High Impedance.
  pinMode(WECATH, INPUT);     // WEST EAST Cathode High Impedance.
  }

  void NSREDAMBER(){
  
  pinMode(GREEN, INPUT);      // High Impedance on GREEN leds Anode.
  pinMode(WECATH, INPUT);     // WEST EAST Cathode High Impedance.
  pinMode(RED,OUTPUT);        // Change RED Anode from High Impedance to Low Impedance, O/P mode.
  pinMode(AMBER, OUTPUT);     // Change AMBER Anode from High Impedance to Low Impedance, O/P mode.
  digitalWrite(RED,HIGH);     // +5V to RED leds Anode, NS and WE.
  digitalWrite(AMBER,HIGH);   // +5V to AMBER leds Anode, NS and WE.
  pinMode(NSCATH,OUTPUT);     // NORTH SOUTH Cathode (GROUND) from High Impedance to O/P mode, Low Impedance.
  digitalWrite(NSCATH,LOW);   // NS Cathode write O/P LOW, sink 40mA, completes circuit. NS RED, AMBER. ON.
  delay(5);                   // 5 miliseconds, lit for persistance of vision illusion.

  digitalWrite(RED,LOW);      // 0V to RED leds Anode. OFF.
  digitalWrite(AMBER, LOW);   // 0V to AMBER leds Anode. OFF.
  pinMode(RED,INPUT);         // RED leds Anode High Impedance.
  pinMode(AMBER, INPUT);      // AMBER leds Anode High Impedance.
  pinMode(NSCATH,INPUT);      // NORTH SOUTH Cathode High Impedance.
  }

  void WEREDAMBER(){
 
  pinMode(GREEN, INPUT);      // High Impedance on GREEN leds Anode.
  pinMode(NSCATH, INPUT);     // NORT SOUTH Cathode High Impedance.
  pinMode(RED,OUTPUT);        // Change RED from High Impedance to Low Impedance, O/P mode.
  pinMode(AMBER, OUTPUT);     // Change AMBER from High Impedance to Low Impedance, to O/P mode.
  digitalWrite(RED,HIGH);     // +5V to RED leds, NS and WE.
  digitalWrite(AMBER,HIGH);   // +5V to AMBER leds, NS and WE.
  pinMode(WECATH,OUTPUT);     // WEST EAST Cathode (GROUND) from high Impedance to O/P mode, Low Impedance.
  digitalWrite(WECATH,LOW);   // WEST EAST Cathode write O/P LOW, sink 40mA, completes circuit.  WE RED, AMBER. ON.
  delay(5);                   // 5 miliseconds, lit for persistance of vision illusion.

  digitalWrite(RED,LOW);      // 0V to RED leds Anode. OFF.
  digitalWrite(AMBER, LOW);   // 0V to AMBER leds Anode. OFF.
  pinMode(RED,INPUT);         // RED leds Anode High Impedance.
  pinMode(AMBER, INPUT);      // AMBER leds Anode High Impedance.
  pinMode(WECATH,INPUT);      // WEST EAST Cathode High Impedance.
  }
  
  void NSGREEN(){
  
  pinMode(RED, INPUT);         // High Impedance on RED leds Anode
  pinMode(AMBER, INPUT);       // High Impedance on AMBER leds Anode.
  pinMode(WECATH, INPUT);      // WEST EAST Cathode High Impedance
  pinMode(GREEN, OUTPUT);      // Change GREEN Anode from High Impedance to Low Impedance, O/P mode.
  digitalWrite(GREEN, HIGH);   // +5v GREEN leds Anode NS and WE.
  pinMode(NSCATH, OUTPUT);     // NORTH SOUTH Cathode (GROUND) from High Impedance to O/P mode, Low Impedance.
  digitalWrite(NSCATH,LOW);    // NORTH SOUTH Cathode write O/P LOW, sink 40mA, completes circuit. NS GREEN ON.
  delay(5);                    // 5 miliseconds, lit for persistance of vision illusion.

  digitalWrite(GREEN, LOW);    // 0V to GREEN leds Anode. OFF.
  pinMode(GREEN, INPUT);       // GREEN leds Anode High Impedance.
  pinMode(NSCATH,INPUT);       // NORTH SOUTH Cathode High Impedance.
  }

  void WEGREEN(){
  
  pinMode(RED, INPUT);         // High Impedance on RED leds Anode.
  pinMode(AMBER, INPUT);       // High Impedance on AMBER leds Anode.
  pinMode(NSCATH, INPUT);      // NORTH SOUTH Cathode High Impedance.
  pinMode(GREEN, OUTPUT);      // Change GREEN Anode from High Impedance to Low Impedance, O/P mode.
  digitalWrite(GREEN, HIGH);   // +5v GREEN leds Anode NS and WE.
  pinMode(WECATH, OUTPUT);     // WEST EAST Cathode (GROUND) from High Impedance to O/P mode, Low Impedance.
  digitalWrite(WECATH,LOW);    // WEST EAST Cathode write O/P LOW, sink 40mA, completes circuit. WE GREEN ON.
  delay(5);                    // 5 miliseconds, lit for persistance of vision illusion.

  digitalWrite(GREEN, LOW);    // 0V to GREEN leds Anode. OFF.
  pinMode(GREEN, INPUT);       // GREEN leds Anode High Impedance .
  pinMode(WECATH,INPUT);       // WEST EAST Cathode High Impedance.
  }

  void NSAMBER(){
  
  pinMode(RED, INPUT);          // High Impedance on RED leds Anode.
  pinMode(GREEN, INPUT);        // High Impedance on GREEN leds Anode.
  pinMode(WECATH, INPUT);       // WEST EAST Cathode High Impedance.
  pinMode(AMBER, OUTPUT);       // Change AMBER leds from High Impedance to Low Impedance, O/P mode.
  digitalWrite(AMBER,HIGH);     // +5V to AMBER leds, NS and WE.
  pinMode(NSCATH,OUTPUT);       // NORTH SOUTH Cathode (GROUND) from High Impedance to O/P mode, Low Impedance.
  digitalWrite(NSCATH,LOW);     // NORT SOUTH circuit complete, Cathode sinks 400mA. NS AMBER ON.
  delay(5);                     // 5 miliseconds, lit for persistance of vision illusion.
  
  digitalWrite(AMBER,LOW);      // 0V to AMBER leds Anode
  pinMode(AMBER, INPUT);        // AMBER leds Cathode High Impedance.
  pinMode(NSCATH,INPUT);        // NORTH SOUTH Cathode High Impedance. 
  }

  void WEAMBER(){
  
  pinMode(RED, INPUT);          // High Impedance on RED leds Anode.
  pinMode(AMBER, INPUT);        // High Impedance on AMBER leds Anode.
  pinMode(NSCATH, INPUT);       // NORT SOUTH Cathode High Impedance.
  pinMode(AMBER, OUTPUT);       // Change AMBER leds from High Impedance to Low Impedance, O/P mode.
  digitalWrite(AMBER,HIGH);     // +5V to AMBER leds, NS and WE.
  pinMode(WECATH, OUTPUT);      // WEST EAST Cathode (GROUND) from High Impedance to O/P mode, Low Impedance.
  digitalWrite(WECATH,LOW);     // WEST EAST Cathode write O/P LOW, sink 40mA, completes circuit. WE GREEN ON.
  delay(5);                     // 5 miliseconds, lit for persistance of vision illusion.
  
  digitalWrite(AMBER,LOW);      // 0V to AMBER leds Anode. OFF.
  pinMode(AMBER, INPUT);        // AMBER leds Cathode High Impedance.
  pinMode(WECATH,INPUT);        // WEST EAST Cathode High Impedance.  
  }
  
  void PELICANLITGREEN(){
  
  pinMode(RED, INPUT);              // High Impedance on RED leds Anode.
  pinMode(AMBER, INPUT);            // High Impedance on AMBER leds Anode.
  pinMode(GREEN, INPUT);            // High Impedance on GREEN leds Anode.
  pinMode(PELICANGREEN, OUTPUT);    // Low Impedance on PELICANGREEN Anode.
  digitalWrite(PELICANGREEN,HIGH);  // +5V to PELICANGREEN Anode.
  pinMode(NSCATH, OUTPUT);          // NORTH SOUTH Cathode (GROUND) from High Impedance to O/P mode, Low Impedance.
  digitalWrite(NSCATH, LOW);        // NORTH SOUTH Cathode write O/P LOW, Cathode sinks 400mA. NS PELICANGREEN ON.
  pinMode(WECATH, OUTPUT);          // WEST EAST Cathode (GROUND) from High Impedance to O/P mode, Low Impedance.
  digitalWrite(WECATH, LOW);        // WEST EAST Cathode write O/P LOW, sink 40mA, circuit complete. WE PELICANGREEN ON.
  delay(5);                         // 5 miliseconds, lit for persistance of vision illusion.
  
  digitalWrite(PELICANGREEN, LOW);  // pelican green off
  pinMode(PELICANGREEN, INPUT);
  pinMode(AMBER, INPUT);            // AMBER leds Cathode High Impedance.
  pinMode(WECATH, INPUT);           // WEST EAST Cathode High Impedance.  
  }
  

  void PELICANGREENFLASH(){         // control freen pelican led, on 300ms off 300ms

  pinMode(RED, INPUT);              // High Impedance on RED leds Anode.
  pinMode(AMBER, INPUT);            // High Impedance on AMBER leds Anode.
  pinMode(GREEN, INPUT);            // High Impedance on GREEN leds Anode.
  pinMode(PELICANGREEN, OUTPUT);    // Low Impedance on PELICANGREEN Anode.
  
  PGREENLAST = millis();              // time the green pelican flash started

  TLABEL = 401;                           // 4 seconds.
  for(int x = 0; x < TLABEL; x++){        // Create TLABEL/100 seconds loop for mux´d leds
  PGREENNOW = millis();                   // How many ms has the current pelican flash state been held?
  
  if ((PGREENLAST) - (PGREENNOW) >= 400){
    toggle_p_green = !toggle_p_green;     // toggle the pelican green led state after 400ms.
    PGREENLAST = millis();                // reset the 400ms timer to time now.
    } 
    
  }
  
  
  if (toggle_p_green == false){
    digitalWrite(PELICANGREEN, LOW);      // Toggle the pelican green led state to make it flash
  }
    else {
      digitalWrite(PELICANGREEN, HIGH);
    }
  
  
 
  pinMode(NSCATH,OUTPUT);           // NORTH SOUTH Cathode (GROUND) from High Impedance to O/P mode, Low Impedance.
  digitalWrite(NSCATH,LOW);         // NORTH SOUTH Cathode write O/P LOW, Cathode sinks 400mA. NS PELICANGREEN ON.
  pinMode(WECATH, OUTPUT);          // WEST EAST Cathode (GROUND) from High Impedance to O/P mode, Low Impedance.
  digitalWrite(WECATH,LOW);         // WEST EAST Cathode write O/P LOW, sink 40mA, circuit complete. WE PELICANGREEN ON.
  delay(5);                         // 5 miliseconds, lit for persistance of vision illusion.

  digitalWrite(PELICANGREEN, LOW);
  }
   
  void PELICANLITRED(){
  pinMode(RED, INPUT);              // High Impedance on RED leds Anode.
  pinMode(AMBER, INPUT);            // High Impedance on AMBER leds Anode.
  pinMode(GREEN, INPUT);            // High Impedance on GREEN leds Anode.
  pinMode(PELICANGREEN, INPUT);     // HIGH Impedance on PELICANGREEN Anode.
  pinMode(PELICANRED, OUTPUT);      // LOW Impedance og pelican RED leds Anode.
  digitalWrite(PELICANRED, HIGH);   // +5V on PELICANRED leds Anode.
  pinMode(NSCATH, OUTPUT);          // NORTH SOUTH Cathode (GROUND) from High Impedance to O/P mode, Low Impedance.
  digitalWrite(NSCATH, LOW);        // NORTH SOUTH Cathode write O/P LOW, Cathode sinks 400mA. NS PELICANGREEN ON.
  pinMode(WECATH, OUTPUT);          // WEST EAST Cathode (GROUND) from High Impedance to O/P mode, Low Impedance.
  digitalWrite(WECATH, LOW);        // WEST EAST Cathode write O/P LOW, sink 40mA, circuit complete. WE PELICANGREEN ON.
  delay(5);                         // 5 miliseconds, lit for persistance of vision illusion.

  digitalWrite(PELICANRED, LOW);    // PELICANRED off.
  pinMode(PELICANRED, INPUT);       // PELICANRED High Impedance.
    
  }
  
 void PELICANS1(){                    // Pelican event WAIT LIT in state1
  TLABEL = 100;                       // 1 second.
  for(int x = 0; x < TLABEL; x++){    // Create TLABEL/100 seconds loop for mux´d leds
  NSRED();                            // NORTH SOUTH RED ON.
  WEGREEN();                          // WEST EAST GREEN ON.
  PELICANLITRED();                    // Pelican crossings remain on WAIT.
  }
  PELICANS2(); 
  }                                   // Next sequence to halt traffic

 void PELICANS2(){                    // Pelican event WAIT LIT in state2
  TLABEL = 100;                       // 1 second.
  for(int x = 0; x < TLABEL; x++){    // Create TLABEL/100 seconds loop for mux´d leds
  NSRED();                            // NORTH SOUTH RED ON.
  WEAMBER();                          // WEST EAST AMBER ON
  PELICANLITRED();                    // Pelican crossings remain on WAIT.
  }
  PELICANS3(); 
  }    
 void PELICANS3(){                    // Pelican event WAIT LIT in state3
  TLABEL = 100;                       // 1 second
  for(int x = 0; x < TLABEL; x++){    // Create TLABEL/100 seconds loop for mux´d leds
  NSRED();                            // NORTH SOUTH RED ON.
  WERED();                            // WEST EAST RED ON
  PELICANLITRED();                    // Pelican crossings remain on WAIT, ensures traffic stopped.
  }
  PELICANS4(); 
  }   

 void PELICANS4(){                     // Traffic stopped since 1s, Pelican allows pedestrians
  TLABEL = 500;                        // 5 seconds
  for(int x = 0; x < TLABEL; x++){     // Create TLABEL/100 seconds loop for mux´d leds
  NSRED();                             // NORTH SOUTH RED ON.
  WERED();                             // WEST EAST RED ON
  PELICANLITGREEN();                   // Pelican GREEN ON, allow pedistrians.
  }

  TLABEL = 400;                       // 4 seconds
  for(int x = 0; x < TLABEL; x++){    // Create TLABEL/100 seconds loop for mux´d leds
  NSRED();                            // NORTH SOUTH RED ON.
  WERED();                            // WEST EAST RED ON
  PELICANGREENFLASH();                // Pelican GREEN FLASHING, signal pedistrians warning.
 }

 norepeat = true;                      //set no repeat Pelican event for 1 minute.
 LASTTIME = millis();                  // note time of last PELICAN event.
 WAIT_LIT = false;                     //turn OFF wait 
 }

void loop() {

//STATE 1. NS RED , WE GREEN
 // Serial.println(PELICANPRESSB);
 // Serial.println(WAIT_LIT);
  REPEATTIME();                                 //More than 1 minute since last Pelican event? Update norepeat.
  if ((WAIT_LIT == true) && (norepeat == false)){   // If PELICAN Button prssed, WAIT is lit and > 60s since last PELICAN.
  PELICANS1();                                  // void PELICANS1, sequence 1 to stop traffic and pelican signals.
  }

  TLABEL = 300;                                 // 3 seconds.
  for(int x = 0; x < TLABEL; x++){              // Create TLABEL/100 seconds loop for mux´d leds
  NSRED();                                      // NORTH SOUTH RED ON.
  WEGREEN();                                    // WEST EAST GREEN ON.
  PELICANLITRED();                              // Pelican RED led lit
  }


                        
//STATE 2. NS RED + AMBER, WE AMBER

  REPEATTIME();                                 //More than 1 minute since last Pelican event? Update norepeat.
  if ((WAIT_LIT == true) && (norepeat == false)){   // If PELICAN Button prssed, WAIT is lit and > 60s since last PELICAN.
  PELICANS2();                                  // void PELICANS2, sequence 2 to stop traffic and pelican signals.
  }
  
  TLABEL = 100;                                 // 1 second.
  for(int x = 0; x < TLABEL; x++){              // Create TLABEL/100 seconds loop for mux´d leds
  NSREDAMBER();                                 // NORTH SOUTH RED, AMBER ON.
  WEAMBER();                                    // WEST EAST AMBER ON.
  PELICANLITRED();                              // Pelican RED led lit.
  }

  

//STATE 3. NS GREEN, WE RED

  REPEATTIME();                                   //More than 1 minute since last Pelican event? Update norepeat.
  if ((WAIT_LIT == true) && (norepeat == false)){     // If PELICAN Button prssed, WAIT is lit and > 60s since last PELICAN.
  PELICANS3();                                    // void PELICANS3, sequence 3 to stop traffic and pelican signals.
  }

  TLABEL = 300;                                   // 3 seconds.
  for(int x = 0; x < TLABEL; x++){                //Create TLABEL/100 seconds loop for mux´d leds   
    NSGREEN();                                    // NORTH SOUTH GREEN ON.
    WERED();                                      // WEST EAST RED ON.
    PELICANLITRED();                               // Pelican RED led lit.
  }


//STATE 4. NS AMBER, WE RED & AMBER

  REPEATTIME();                                   //More than 1 minute since last Pelican event? Update norepeat.
  if ((WAIT_LIT == true) && (norepeat == false)){     // If PELICAN Button prssed, WAIT is lit and > 60s since last PELICAN.
  PELICANS4();                                    // void PELICANS4, sequence 4 to stop traffic and pelican signals.
  }
  
  TLABEL = 100;                                   // 1 second.
  for(int x = 0; x < TLABEL; x++){                // Create TLABEL/100 seconds loop for mux´d leds
  NSAMBER();                                      // NORTH SOUTH RED, AMBER ON.
  WEREDAMBER();                                   // WEST EAST AMBER ON.
  PELICANLITRED();                                // Pelican RED led lit.
  }
                            
}
