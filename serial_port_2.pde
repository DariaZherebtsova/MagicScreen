import processing.serial.*;
int wd, step = 1, ii;
int y[] = new int[2000];
int x[] = new int[2000];
int xx, yy;

Serial serial; // создаем объект последовательного порта
String received; // данные, получаемые с последовательного порта

void setup()
{
  size(640, 420);
  frameRate(60);
  String port = Serial.list()[0];
  
  serial = new Serial(this, port, 9600);
  //оси
  translate(width/2,height/2);
  strokeWeight(2);
  //цвет линии
  stroke(254);//белый
  y[0] = 0;
  x[0] = 0;
  ii = 0;
  wd = 0;
  background(0);
}

void draw() {
  //background(0);
  
  if ( serial.available() > 0) { // если есть данные,
    received = serial.readStringUntil('\n'); // считываем данные
  }
  println("kod= ",received); //отображаем данные в консоли
  
  if (received != null)
  {
  
    //ii++;
    //убираем лишние символы
    String s1 = trim(received);
    String[] s2 = split(s1, ',');
    // и переводим в int
    yy = int(s2[0])*2;
    xx = int(s2[1])*2;
    println("y= ", yy);
    println("x= ", xx);
    //перемещаем оси 
    translate(width/2,height/2);
    //translate(0,height/2);
    //цвет для оси
    //stroke(254);
    //горизонтальная ось
    //line(0,0,600,0);
    stroke(#F20C0C);
    fill(#F20C0C);
    //int x = 0;
    //for (int i=1; i<=ii; i=i+3)
   // {
      ellipse(xx,yy,3,3); 
      //line(0+i*5,y[i-1],0+i*5,y[i]);
  //  }
  }  
  
}