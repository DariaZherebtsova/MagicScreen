
#define pin_R1 10 //правый 1
#define pin_R2 11 //правый 2
#define pin_L1 4  //левый 1
#define pin_L2 5  //левый 2

int EncData_L, EncData_R; //значение
unsigned long currentTime;
unsigned long loopTime;
unsigned char pr_kod_l, pr_kod_r;
//unsigned char encoder_A_prev=0;

void setup() {
  pinMode(pin_R1, INPUT);
  pinMode(pin_R2, INPUT);
  pinMode(pin_L1, INPUT);
  pinMode(pin_L2, INPUT);
  currentTime = millis();
  loopTime = currentTime; 
  Serial.begin(9600);
  Serial.print("Hello World!");
  pr_kod_l = 3;
  pr_kod_r = 3;
}

void loop() {
  currentTime = millis();
  if(currentTime >= (loopTime + 20)){ // проверяем каждые 5*4мс (200 Гц)
    //считываем данные и вычисляем изменения
    EncData_L = read_enc(pin_L1, pin_L2, pr_kod_l, EncData_L, 1);
    EncData_R = read_enc(pin_R1, pin_R2, pr_kod_r, EncData_R, 2);

       //выводим значение
    Serial.print(EncData_L);
    Serial.print(",");
    Serial.println(EncData_R);
    
    loopTime = currentTime;
  }
}

int read_enc(unsigned char pin_1, unsigned char pin_2, unsigned char pr_kod, int EncData, char metka)
{
  unsigned char encoder_1;
  unsigned char encoder_2;
  unsigned char kod;

    encoder_1 = digitalRead(pin_1);     // считываем состояние выхода А энкодера 
    encoder_2 = digitalRead(pin_2);     // считываем состояние выхода B энкодера

    if (encoder_1 == 0)
    {
      if (encoder_2 == 0)
      {
        kod = 0;
      }
      else
      {
        kod = 1;
      }
    }
    else
    {
      if (encoder_2 == 0)
      {
        kod = 2;
      }
      else
      {
        kod = 3;
      }
    }
    //Serial.print(pr_kod);
    //Serial.print(",");
    //Serial.println(kod);

    switch(pr_kod)
    {
    case 2:
      {
      if(kod == 3) EncData++;
      if(kod == 0) EncData--; 
      break;
      }
   
    case 0:
      {
      if(kod == 2) EncData++;
      if(kod == 1) EncData--; 
      break;
      }
    case 1:
      {
      if(kod == 0) EncData++;
      if(kod == 3) EncData--; 
      break;
      }
    case 3:
      {
      if(kod == 1) EncData++;
      if(kod == 2) EncData--; 
      break;
      }
    }
    // сохраняем значение для следующего цикла 
    if (metka == 1) pr_kod_l = kod;    
    if (metka == 2) pr_kod_r = kod; 
     
    return EncData;
}


