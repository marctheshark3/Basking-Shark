char menu;
char subMenu;
bool runOnce = true;
bool menuState = true;
void setup() {
  Serial.begin(115200);
}

void topMenu() {
   
  if (runOnce == true) {
    Serial.println ("                     Main Menu: Would you like to measure Temperature or Humidity?                           ");
    Serial.println (" A) Temperature!  B) Humidity! ");  
    runOnce = false;
    menuState = true;
  }      
}

void sub1Menu() {
  menuState = false; 
  Serial.println ("                      Temp Sub-Menu                               ");
  Serial.println("1) Measure Humidity 2) Quit to Main");
}

void sub2Menu() {
  menuState = false; 
  Serial.println ("                     Humidity Sub-Menu                               ");
  Serial.println("1) Measure Temperature 2) Quit to Main");
}

void loop() {   
   topMenu();   
   while (Serial.available() == 0) {}    
   if (menuState == true) {
    char menu = Serial.read(); 
    if (menu == 'a') {       
      Serial.println ("Measuring Temperature!");
      //add line that brings in the temp measurement
      sub1Menu(); 
    }
    else if (menu == 'b') {       
      Serial.println ("Measuring Humidity!");
      sub2Menu();
    }
    
    else  {
      Serial.println ("Choose Options A through D");
    }      
  }
  if (menuState == false) {
    subMenu = Serial.read();
    if (subMenu == '1'){
      Serial.println("SubMenu = 1");
      topMenu();
      
    }   
    else if (subMenu == '2'){
      Serial.println("SubMenu = 2");
      menu = 'q';
      runOnce = true;
      topMenu();
    }
  } 
} 
