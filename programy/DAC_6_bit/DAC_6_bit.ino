//DAC 6-bit
//generating sinus

const byte wartosci[] = {31,34,37,40,43,46,49,51,53,55,57,59,60,61,62,62,62,62,61,60,59,58,56,54,52,50,47,44,41,38,35,32,29,26,23,20,17,15,12,10,8,6,4,3,1,1,0,0,0,1,1,2,4,5,7,9,11,14,17,19,22,25,28,32};

void setup() {
  for (int i = 8; i < 14; i++)
  pinMode(i, OUTPUT);
}

int x = 0;

void loop() {
  for(int i=0;i<63;i++)
  wpisz(wartosci[i]);
}

void wpisz(byte wartosc)
{
  digitalWrite(8, (wartosc & (1 << 5)));
//  delayMicroseconds(x);
  digitalWrite(9, (wartosc & (1 << 4)));
//  delayMicroseconds(x);
  digitalWrite(10, (wartosc & (1 << 3)));
//  delayMicroseconds(x);
  digitalWrite(11, (wartosc & (1 << 2)));
//  delayMicroseconds(x);
  digitalWrite(12, (wartosc & (1 << 1)));
//  delayMicroseconds(x);
  digitalWrite(13, (wartosc & (1 << 0)));
//  delayMicroseconds(x);
}
