#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#ifdef __AVR__
 #include <avr/power.h>
#endif
#define PIN 5 
#define NUMPIXELS 270 
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
DFRobotDFPlayerMini myDFPlayer;
byte gol_check = 0;
byte trn_cnt = 0;
//SoftwareSerial mySerial2(8, 9); // RX, TX
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
#define DELAYVAL 0

byte is_double = 0;
byte player1_final=0;
byte player2_final=0;

byte matrix[24][15] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //A1
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //A2
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //A3
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //A4
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //A5
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //A6
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //B1
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //B2
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //B3
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //B4
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //B5
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //B6
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //C1
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //C2
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //C3
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //C4
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //C5
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //C6
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //D1
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //D2
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //D3
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //D4
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //D5
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} //D6
};

byte bar1[15]={
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
byte bar2[15]={
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void trace_pole(uint32_t pl1_color, uint32_t pl2_color){
  //A1-A6
  pixels.clear();
  for(byte j=0; j<6; j++) {
    for(byte i=0; i<15; i++) {
      if(matrix[j][i]==1){
        pixels.setPixelColor((20-i-1)+20*j, pl1_color);
      }
      if(matrix[j][i]==2){
        pixels.setPixelColor((20-i-1)+20*j, pl2_color);
      }
    }
  }
  //B1-B6
  for(byte j=6; j<12; j++) {
    for(byte i=0; i<15; i++) {
      if(matrix[j][i]==1){
        pixels.setPixelColor((20-i-1+30)+20*j, pl1_color);
      }
      if(matrix[j][i]==2){
        pixels.setPixelColor((20-i-1+30)+20*j, pl2_color);
      }
    }
  }

  //C1-C6
  for(byte j=12; j<18; j++) {
    for(byte i=0; i<15; i++) {
      if(matrix[j][i]==1){
        pixels.setPixelColor((i+30)+20*(23-j), pl1_color);
      }
      if(matrix[j][i]==2){
        pixels.setPixelColor((i+30)+20*(23-j), pl2_color);
      }
    }
  }

  //D1-D6
  for(byte j=18; j<24; j++) {
    for(byte i=0; i<15; i++) {
      if(matrix[j][i]==1){
        pixels.setPixelColor((i)+20*(23-j), pl1_color);
      }
      if(matrix[j][i]==2){
        pixels.setPixelColor((i)+20*(23-j), pl2_color);
      }
    }
  }

  for(byte i=0; i<15; i++) {
    if(bar1[i]==1){
      pixels.setPixelColor(120+i, pl1_color);
    }
    if(bar1[i]==2){
      pixels.setPixelColor(120+i, pl2_color);
    }
    if(bar2[i]==1){
      pixels.setPixelColor(135+i, pl1_color);
    }
    if(bar2[i]==2){
      pixels.setPixelColor(135+i, pl2_color);
    }
  }


  pixels.show();
}

bool is_power_on = false;



void rainbow() {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels.show();
    delay(0);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

byte curent_player_turn = 1;

void setup() {
  //mySerial2.begin(9600);
  pixels.begin();
  pixels.setBrightness(100);
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.show();
  //Инициализация портов и плеера
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);
  

  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println(F("No player."));
    while (true);
  }

  //Некоторые настройки плеера
  myDFPlayer.setTimeOut(500); //Timeout serial 500ms
  myDFPlayer.volume(20); //Громкость
  myDFPlayer.EQ(0); //Эквализация
 
}

void sound(byte n, int d=0){
  myDFPlayer.play(n);
  delay(d);
}

void final_check(){
  //Для первого игрока
  byte tmp_cnt=0;
  if(player1_final==0){
    for(byte j=18; j<24; j++) {
      for(byte i=0; i<15; i++) {
        if(matrix[j][i]==1){
          tmp_cnt+=1;
        }
      }
    }
    if(tmp_cnt==15){
      player1_final=1;
      sound(18,3000);
    }
  }
  if(player2_final==0){
    tmp_cnt=0;
    for(byte j=6; j<12; j++) {
      for(byte i=0; i<15; i++) {
        if(matrix[j][i]==2){
          tmp_cnt+=1;
        }
      }
    }
    if(tmp_cnt==15){
      player2_final=1;
      sound(19,3000);
    }
  }
}

byte make_turn(byte player, byte hod_p, byte option = 0){
  //if(player==1){
  if(option > 0){
    if(player == 1){
      if(option == 41){
        matrix[0][14] = 0;
        matrix[0][13] = 0;
        matrix[8][0] = player;
        matrix[8][1] = player;
      }
      if(option == 3){
        matrix[0][14] = 0;
        matrix[0][13] = 0;
        matrix[4][0] = player;
        matrix[8][0] = player;
      }
      if(option == 6){
        matrix[0][14] = 0;
        matrix[0][13] = 0;
        matrix[6][0] = player;
        matrix[6][1] = player;
      }
      return 1;
    }
    if(player == 2){
      if (option == 42){
        if (matrix[20][0] > 0){
          matrix[12][14] = 0;
          matrix[16][0] = player;
        }else{

          matrix[12][14] = 0;
          matrix[12][13] = 0;
          matrix[20][0] = player;
          matrix[20][1] = player;
        }
      }
      if(option == 3){
        matrix[12][14] = 0;
        matrix[12][13] = 0;
        matrix[15][0] = player;
        matrix[21][0] = player;
      }
      if(option == 6){
        matrix[12][14] = 0;
        matrix[12][13] = 0;
        matrix[18][0] = player;
        matrix[18][1] = player;
      }
      return 1;
    }
  }else{
    char p_col1 =' ';
    Serial.print(1);
    while(true){
      p_col1 =' ';
      while (Serial.available() > 0){
        Serial.print(2);
        p_col1 = Serial.read();
      }
      //Serial.print(3);
      if(p_col1=='a' || p_col1=='b' || p_col1=='c' || p_col1=='d'){
        if(make_turn2(player, p_col1, hod_p)==1){
          if(player1_final+player2_final<2){
            final_check();
          }
          return 1;
        }
      }else{
        if(p_col1=='z'){
          return 1;
        }
      }
    }
  }
  //}
}
void loop() {
  if(is_power_on){
    uint32_t seed = 0;
    for (byte i = 0; i < 16; i++) {
      seed *= 4;
      seed += analogRead(A0) & 3;
      randomSeed(seed);
    }
    pixels.clear();
    pixels.show();
    sound(2);
    Serial.println("choose mode pls...");
    byte n_mode = choiceNardiyType();
    if(n_mode==2){
    clear_pole();
    Serial.println("color 1p...");
    uint32_t p1_color = choiceNardiyColor(1);
    Serial.println("color 2p...");
    uint32_t p2_color = choiceNardiyColor(2);
    Serial.println("Игра начинается!!!");
    sound(7, 2000); //Игра начинается
      golova();
      trace_pole(p1_color, p2_color); //поле фишек
      while(true){
        trn_cnt += 1; gol_check = 0; 
        sound(8, 1850);//Кубики кидаются для игрока (со звуком)
        byte hod_1kub = random(6);  byte hod_2kub = random(6);
        
        pixels.clear();
        render_kub(hod_1kub+1,curent_player_turn,1);
        render_kub(hod_2kub+1,curent_player_turn,2);
        pixels.show();
        is_double = 0;
        if(hod_1kub==hod_2kub){
          is_double = 1;
          delay(500);
          sound(23, 3500);
        }else{
          delay(1500);
        }
        
        //отображаются числа, озвучиваются числа
        //Числа пропадают
        trace_pole(p1_color, p2_color);
        
        

        if(is_double){
          if((trn_cnt == 1 || trn_cnt == 2) && (hod_1kub == 2 || hod_1kub == 3 || hod_1kub == 4 )){
            if(hod_1kub == 3){
              if(make_turn(curent_player_turn, hod_1kub+1, 3)==1){
                trace_pole(p1_color, p2_color);
              }
            }
            if(hod_1kub == 4 && trn_cnt == 1){
              if(make_turn(curent_player_turn, hod_1kub+1, 41)==1){
                trace_pole(p1_color, p2_color);
              }
            }
            if(hod_1kub == 4 && trn_cnt == 2){
              if(make_turn(curent_player_turn, hod_1kub+1, 42)==1){
                trace_pole(p1_color, p2_color);
              }
            }
            if(hod_1kub == 6){
              if(make_turn(curent_player_turn, hod_1kub+1, 6)==1){
                trace_pole(p1_color, p2_color);
              }
            }
          }else{
            for(byte j=0; j<4; j++){
              if(curent_player_turn==1){
                sound(15, 3500); //Игрок 1, назовите координату фишки для перемещения на...
              }
              if(curent_player_turn==2){
                sound(16, 3500); //Игрок 2, назовите координату фишки для перемещения на...
              }
              sound(hod_1kub+9); //*кубик*
              if(make_turn(curent_player_turn, hod_1kub+1)==1){
                trace_pole(p1_color, p2_color);
              }    
            }
          }
        }else{
          if(curent_player_turn==1){
            sound(15, 3500); //Игрок 1, назовите координату фишки для перемещения на...
          }
          if(curent_player_turn==2){
            sound(16, 3500); //Игрок 2, назовите координату фишки для перемещения на...
          }
          sound(hod_1kub+9); //*кубик*
          if(make_turn(curent_player_turn, hod_1kub+1)==1){
            trace_pole(p1_color, p2_color);
          };

          if(curent_player_turn==1){
            sound(15, 3500); //Игрок 1, назовите координату фишки для перемещения на...
          }
          if(curent_player_turn==2){
            sound(16, 3500); //Игрок 2, назовите координату фишки для перемещения на...
          }
          myDFPlayer.play(hod_2kub+9); //*кубик 2*
          if(make_turn(curent_player_turn, hod_2kub+1)==1){
            trace_pole(p1_color, p2_color);
          };
        }



        if(curent_player_turn==1){
          curent_player_turn=2;
        }else{
          curent_player_turn=1;
        }
      }
    }else if(n_mode==1){
      //Короткие нарды
    }else if (n_mode == 3){
      //pixels.Color(255, 255, 255);
      clear_pole();
      sound(24,0); //bla bla
      rainbow();
      rainbow();
      delay(5000);
      
      sound(25); // dom 1p
      dom1();
        
      
      sound(26); //dom 2p
      dom2();
      
            
      sound(27); //dvor1
      dvor1();
      
      
      sound(28); //dvor2
      dvor2();
      

      sound(29); //столбички
      golova();
      delay(9000);
      pixels.clear();

      sound(30,3000); 
      sound(8, 1850);//Кубики кидаются для игрока (со звуком)
      pixels.clear();
      curent_player_turn = 1;
      byte hod_1kub=2;
      byte hod_2kub=4;
      render_kub(hod_1kub+1,curent_player_turn,1);
      render_kub(hod_2kub+1,curent_player_turn,2);
      pixels.show();
      delay(2000);
      sound(31,7000);
      trace_pole(pixels.Color(255, 0, 0),pixels.Color(0, 0, 255));
      if(curent_player_turn==1){
        sound(15, 3500); //Игрок 1, назовите координату фишки для перемещения на...
      }
      sound(hod_1kub+9); //*кубик*
      if(make_turn(curent_player_turn, hod_1kub+1)==1){
        trace_pole(pixels.Color(255, 0, 0),pixels.Color(0, 0, 255));
      };
      if(curent_player_turn==1){
        sound(15, 3500); //Игрок 1, назовите координату фишки для перемещения на...
      }
      myDFPlayer.play(hod_2kub+9); //*кубик 2*
      if(make_turn(curent_player_turn, hod_2kub+1)==1){
        trace_pole(pixels.Color(255, 0, 0),pixels.Color(0, 0, 255));
      };
      sound(32,4000);
      
      curent_player_turn=2;
      
      sound(8, 1850);//Кубики кидаются для игрока (со звуком)
      pixels.clear();
      hod_1kub=2;
      hod_2kub=2;
      render_kub(hod_1kub+1,curent_player_turn,1);
      render_kub(hod_2kub+1,curent_player_turn,2);
      pixels.show();
      delay(2000);
      sound(33,5000);

      if(make_turn(curent_player_turn, hod_1kub+1, hod_1kub+1)==1){
        trace_pole(pixels.Color(255, 0, 0),pixels.Color(0, 0, 255));
      };
      delay(6000);
      curent_player_turn = 1;
      sound(8, 1850);//Кубики кидаются для игрока (со звуком)
      pixels.clear();
      hod_1kub=0;
      hod_2kub=0;
      render_kub(hod_1kub+1,curent_player_turn,1);
      render_kub(hod_2kub+1,curent_player_turn,2);
      pixels.show();
      delay(2000);
      sound(34,4000);
      pixels.clear();
      trace_pole(pixels.Color(255, 0, 0),pixels.Color(0, 0, 255));
      delay(5500);
      gol_check=0;
      for(byte j=0; j<4; j++){
        if(curent_player_turn==1){
          sound(15, 3500); //Игрок 1, назовите координату фишки для перемещения на...
        }
        if(curent_player_turn==2){
          sound(16, 3500); //Игрок 2, назовите координату фишки для перемещения на...
        }
        sound(hod_1kub+9); //*кубик*
        if(make_turn(curent_player_turn, hod_1kub+1)==1){
          trace_pole(pixels.Color(255, 0, 0),pixels.Color(0, 0, 255));
        }    
      }
      sound(35);
      final_sit();
      for(byte i=0;i<15;i++){
        bar1[i]=1;
        bar2[i]=2;
      }
      trace_pole(pixels.Color(255, 0, 0),pixels.Color(0, 0, 255));
      delay(1000);
      for(byte i=0;i<15;i++){
        bar1[i]=0;
        bar2[i]=0;
      }
      trace_pole(pixels.Color(255, 0, 0),pixels.Color(0, 0, 255));
      delay(1000);
      for(byte i=0;i<15;i++){
        bar1[i]=1;
        bar2[i]=2;
      }
      trace_pole(pixels.Color(255, 0, 0),pixels.Color(0, 0, 255));
      delay(1000);
      for(byte i=0;i<15;i++){
        bar1[i]=0;
        bar2[i]=0;
      }
      trace_pole(pixels.Color(255, 0, 0),pixels.Color(0, 0, 255));
      sound(36,4000);

      curent_player_turn = 1;
      sound(8, 1850);//Кубики кидаются для игрока (со звуком)
      pixels.clear();
      hod_1kub=5;
      hod_2kub=1;
      render_kub(hod_1kub+1,curent_player_turn,1);
      render_kub(hod_2kub+1,curent_player_turn,2);
      pixels.show();
      delay(2000);
      trace_pole(pixels.Color(255, 0, 0),pixels.Color(0, 0, 255));
      if(curent_player_turn==1){
        sound(15, 3500); //Игрок 1, назовите координату фишки для перемещения на...
      }
      sound(hod_1kub+9); //*кубик*
      if(make_turn(curent_player_turn, hod_1kub+1)==1){
        trace_pole(pixels.Color(255, 0, 0),pixels.Color(0, 0, 255));
      };
      if(curent_player_turn==1){
        sound(15, 3500); //Игрок 1, назовите координату фишки для перемещения на...
      }
      myDFPlayer.play(hod_2kub+9); //*кубик 2*
      if(make_turn(curent_player_turn, hod_2kub+1)==1){
        trace_pole(pixels.Color(255, 0, 0),pixels.Color(0, 0, 255));
      };

      sound(37,5000); // 
      sound(38);
      rainbow();
      delay(4000);
      is_power_on = false;
    }

  }else{
    pixels.clear();
    sound(23);
    rainbow();
    //pixels.show();
    delay(1000);
    is_power_on = true;
  }
}

void dvor2(){
  //clear_pole();
  pixels.clear();
  matrix[0][0] = 2;
  matrix[1][0] = 2;
  matrix[2][0] = 2;
  matrix[3][0] = 2;
  matrix[4][0] = 2;
  matrix[5][0] = 2;
  trace_pole(pixels.Color(255, 0, 0),pixels.Color(0, 0, 255));
  delay(2000);
  pixels.clear();
}
void dvor1(){
  //clear_pole();
  pixels.clear();
  matrix[12][0] = 1;
  matrix[13][0] = 1;
  matrix[14][0] = 1;
  matrix[15][0] = 1;
  matrix[16][0] = 1;
  matrix[17][0] = 1;
  trace_pole(pixels.Color(255, 0, 0),pixels.Color(0, 0, 255));
  delay(2000);
  pixels.clear();
}

void clear_pole(){
  for (byte i=0; i<24; i++){
    for (byte j=0; j<15; j++){
      matrix[i][j]=0;
    }
  }
  for(byte i=0; i<15; i++) {
      bar1[i]=0;
      bar2[i]=0;
  }
}

void dom1(){
  //clear_pole();
  pixels.clear();
  matrix[18][0] = 1; 
  matrix[19][0] = 1;
  matrix[20][0] = 1;
  matrix[21][0] = 1;
  matrix[22][0] = 1;
  matrix[23][0] = 1;
  matrix[18][1] = 1;
  matrix[19][1] = 1;
  matrix[20][1] = 1;
  matrix[21][1] = 1;
  matrix[22][1] = 1;
  matrix[23][1] = 1;
  trace_pole(pixels.Color(255, 0, 0),pixels.Color(0, 0, 255));
  delay(2000);
  pixels.clear();
}
void dom2(){
  //clear_pole();
  pixels.clear();
  matrix[6][0] = 2;
  matrix[7][0] = 2;
  matrix[8][0] = 2;
  matrix[9][0] = 2;
  matrix[10][0] = 2;
  matrix[11][0] = 2;
  matrix[6][1] = 2;
  matrix[7][1] = 2;
  matrix[8][1] = 2;
  matrix[9][1] = 2;
  matrix[10][1] = 2;
  matrix[11][1] = 2;
  trace_pole(pixels.Color(255, 0, 0),pixels.Color(0, 0, 255));
  delay(2000);
  pixels.clear();
}

void golova(){
  clear_pole();
  pixels.clear();
  matrix[0][0]=1;
  matrix[0][1]=1;
  matrix[0][2]=1;
  matrix[0][3]=1;
  matrix[0][4]=1;
  matrix[0][5]=1;
  matrix[0][6]=1;
  matrix[0][7]=1;
  matrix[0][8]=1;
  matrix[0][9]=1;
  matrix[0][10]=1;
  matrix[0][11]=1;
  matrix[0][12]=1;
  matrix[0][13]=1;
  matrix[0][14]=1;

  matrix[12][0]=2;
  matrix[12][1]=2;
  matrix[12][2]=2;
  matrix[12][3]=2;
  matrix[12][4]=2;
  matrix[12][5]=2;
  matrix[12][6]=2;
  matrix[12][7]=2;
  matrix[12][8]=2;
  matrix[12][9]=2;
  matrix[12][10]=2;
  matrix[12][11]=2;
  matrix[12][12]=2;
  matrix[12][13]=2;
  matrix[12][14]=2;

  trace_pole(pixels.Color(255, 0, 0),pixels.Color(0, 0, 255));
}
void final_sit(){
  clear_pole();
  pixels.clear();
  player1_final=1;
  player2_final=1;
  matrix[20][0]=1;
  matrix[20][1]=1;
  matrix[20][2]=1;
  matrix[20][3]=1;
  matrix[20][4]=1;
  matrix[19][0]=1;
  matrix[19][1]=1;
  matrix[19][2]=1;
  matrix[18][0]=1;
  matrix[18][1]=1;
  matrix[18][2]=1;
  matrix[18][3]=1;
  matrix[18][4]=1;
  matrix[21][0]=1;
  matrix[21][1]=1;

  matrix[6][0]=2;
  matrix[6][1]=2;
  matrix[6][2]=2;
  matrix[7][0]=2;
  matrix[7][1]=2;
  matrix[7][2]=2;
  matrix[7][3]=2;
  matrix[8][0]=2;
  matrix[9][0]=2;
  matrix[9][1]=2;
  matrix[9][2]=2;
  matrix[9][3]=2;
  matrix[9][4]=2;
  matrix[10][0]=2;
  matrix[10][1]=2;

  trace_pole(pixels.Color(255, 0, 0),pixels.Color(0, 0, 255));
  delay(6000);
  pixels.clear();
}
byte make_turn2(byte player, char col, byte hod_p){
  Serial.print(col);
  char p_col = ' ';
  byte p_col2 = 0;
  while(true){
    p_col = ' ';
    while (Serial.available() > 0){
      p_col = Serial.read();
    }
    if(p_col=='1' || p_col=='2' || p_col=='3' || p_col=='4' || p_col=='5' || p_col=='6'){
      break;
    }
  }
    if(p_col=='1'){
      p_col2 = 1;
    }
    if(p_col=='2'){
      p_col2 = 2;
    }
    if(p_col=='3'){
      p_col2 = 3;
    }
    if(p_col=='4'){
      p_col2 = 4;
    }
    if(p_col=='5'){
      p_col2 = 5;
    }
    if(p_col=='6'){
      p_col2 = 6;
    }
    byte i = 0;
    if(col == 'a'){
      i = p_col2 - 1;
    }
    if(col == 'b'){
      i = 6 + p_col2 - 1;
    }
    if(col == 'c'){
      i = 12 + p_col2 - 1;
    }
    if(col == 'd'){
      i = 18 + p_col2 - 1;
    }
    byte del1 = 0;

    if(player==1){
      if((matrix[i][0]==player && i > 0) || (matrix[i][0]==player && gol_check == 0 && i == 0)){
        for(byte j=0; j<15; j++){
          if(matrix[i][j]==player){
            del1=j;
          }
        }

        if(i+hod_p < 24 && (matrix[i+hod_p][0]==player || matrix[i+hod_p][0]==0)){
          for(byte j=0; j<15; j++){
            if(matrix[i+hod_p][j]!=player){
              matrix[i+hod_p][j]=player;
              break;
            }
          }
          matrix[i][del1]=0;
          if(i == 0){
            gol_check += 1;
          }
          return 1;
        }else{
          if(player1_final==1 and i+hod_p>23){
            for(byte j=0; j<15; j++){
              if(bar1[j]==0){
                bar1[j]=player;
                matrix[i][del1]=0;
                sound(22,1000);
                if(j==14){
                  sound(20,3000);//ПОБЕДА 1
                }
                return 1;
              }
            }
          }
        }
      }
    }
    if(player==2){
      if((matrix[i][0]==player && i != 12) || (matrix[i][0]==player && gol_check == 0 && i == 12)){
        for(byte j=0; j<15; j++){
          if(matrix[i][j]==player){
            del1=j;
          }
        }
        byte new_i=i+hod_p;
        if(col=='d' && i+hod_p>23){
          new_i=(i+hod_p)-24;
        }
        if(col=='b' && i+hod_p>11){
          
          if(player2_final==1){
            for(byte j=0; j<15; j++){
              if(bar2[j]==0){
                bar2[j]=player;
                matrix[i][del1]=0;
                sound(22,1000);
                if(j==14){
                  sound(21,3000);//ПОБЕДА 2
                }
                return 1;
              }
            }
          }else{
            //ПОПРОБУЙ ЕЩЁ РАЗ!!!!!!!
            sound(17,1500);
            Serial.println(777);
            return 0;
          }
          
        }
        if(matrix[new_i][0]==player || matrix[new_i][0]==0){
          for(byte j=0; j<15; j++){
            if(matrix[new_i][j]!=player){
              matrix[new_i][j]=player;
              break;
            }
          }
          matrix[i][del1]=0;
          if (i == 12){
            gol_check += 1;
          }
          return 1;
        }
      }
    }

    //ПОПРОБУЙ ЕЩЁ РАЗ!!!!!!!
    sound(17,1500);
    Serial.println(666);
    return 0;
}

byte choiceNardiyType(){
  while(true){
    while (Serial.available() > 0){
      char mode = Serial.read();
      if (mode =='1'){
        myDFPlayer.play(3);
        delay(3000);
        return(1);
        }
      if (mode =='2'){
        myDFPlayer.play(4);
        delay (3000);
        return(2);
        }
      if (mode=='3'){
        sound(42, 3000); //you need dat!!!
        return(3);
      }
    }
  }
}
uint32_t choiceNardiyColor(byte p_num){
  if (p_num ==1){
    myDFPlayer.play(5);
  }
  if (p_num ==2){
    myDFPlayer.play(6);
  }
  //delay(3000);
  while(true){
    while (Serial.available() > 0){
      char p_col = Serial.read();
      if(p_col=='1'){
        return(pixels.Color(255, 255, 255));
      }
      if(p_col=='2'){
        return(pixels.Color(255, 0, 0));
      }
      if(p_col=='3'){
        return(pixels.Color(0, 0, 255));
      }
      if(p_col=='4'){
        return(pixels.Color(0, 255, 0));
      }
      if(p_col=='5'){
        return(pixels.Color(255, 150, 0));
      }
      if(p_col=='6'){
        return(pixels.Color(150, 0, 255));
      }
      if(p_col=='7'){
        return(pixels.Color(0, 255, 255));
      }
    }
  }
}
void render_kub(byte digit, byte player, byte side){
  byte j=0;
  byte i=0;
  //byte dd=0;
  byte dd[6][15]={0};
  if(digit==1){
    
    /*byte dd[6][15]={//1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };*/
    dd[2][1]=1;
    dd[2][2]=1;
    dd[2][3]=1;
    dd[2][4]=1;
    dd[2][5]=1;
    dd[2][6]=1;

  };
  if(digit==2){
   /*
    byte dd[6][15]= {//2
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    */
    dd[1][1]=1;
    dd[1][2]=1;
    dd[1][3]=1;
    dd[1][4]=1;
    dd[1][7]=1;
    dd[2][1]=1;
    dd[2][4]=1;
    dd[2][7]=1;
    dd[3][1]=1;
    dd[3][4]=1;
    dd[3][5]=1;
    dd[3][6]=1;
    dd[3][7]=1;
  };
  if(digit==3){
    /*
    byte dd[6][15]={ //3
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    */
    dd[1][1]=1;
    dd[1][4]=1;
    dd[1][7]=1;
    dd[2][1]=1;
    dd[2][4]=1;
    dd[2][7]=1;
    dd[3][1]=1;
    dd[3][2]=1;
    dd[3][3]=1;
    dd[3][4]=1;
    dd[3][5]=1;
    dd[3][6]=1;
    dd[3][7]=1;
  };
  if(digit==4){
    /*
    byte dd[6][15]={ //4
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    */
    dd[1][4]=1;
    dd[1][5]=1;
    dd[1][6]=1;
    dd[1][7]=1;
    dd[2][4]=1;
    dd[3][1]=1;
    dd[3][2]=1;
    dd[3][3]=1;
    dd[3][4]=1;
    dd[3][5]=1;
    dd[3][6]=1;
    dd[3][7]=1;
  };
  if(digit==5){
    /*
    byte dd[6][15]={ //5
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    */
    dd[1][1]=1;
    dd[1][4]=1;
    dd[1][5]=1;
    dd[1][6]=1;
    dd[1][7]=1;
    dd[2][1]=1;
    dd[2][4]=1;
    dd[2][7]=1;
    dd[3][1]=1;
    dd[3][2]=1;
    dd[3][3]=1;
    dd[3][4]=1;
    dd[3][7]=1;
  };
  if(digit==6){
    /*
    byte dd[6][15]={ //6
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };*/
    dd[1][1]=1;
    dd[1][2]=1;
    dd[1][3]=1;
    dd[1][4]=1;
    dd[1][5]=1;
    dd[1][6]=1;
    dd[1][7]=1;
    dd[2][1]=1;
    dd[2][4]=1;
    dd[2][7]=1;
    dd[3][1]=1;
    dd[3][2]=1;
    dd[3][3]=1;
    dd[3][4]=1;
    dd[3][7]=1;

  };
  
  if(player == 1 && side == 1){
    for(j=0; j<6; j++) {
      for(i=0; i<15; i++) {
        if(dd[j][i]==1){
          pixels.setPixelColor((20-i-1)+20*j, pixels.Color(0, 255, 0));
        }
        
      }
      
    }
  }
  if(player == 1 && side == 2){
    for(int j=0; j<6; j++) {
      for(int i=0; i<15; i++) {
        if(dd[j][i]==1){
          pixels.setPixelColor((20-i-1+30)+20*(j+6), pixels.Color(0, 255, 0));
        }
      }
    }
  }
  if(player == 2 && side == 1){
    for(int j=0; j<6; j++) {
      for(int i=0; i<15; i++) {
        if(dd[j][i]==1){
          pixels.setPixelColor((i+30)+20*(11-j), pixels.Color(0, 255, 0));
        }
      }
    }
  }
  if(player == 2 && side == 2){
    for(int j=0; j<6; j++) {
      for(int i=0; i<15; i++) {
        if(dd[j][i]==1){
          pixels.setPixelColor((i)+20*(5-j), pixels.Color(0, 255, 0));
        }
      }
    }
  }
  
  pixels.show();
}
