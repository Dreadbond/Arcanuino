class A
{
  public:
   int x;
   virtual void f() { x=1; }
};

class B : public A
{
  public:
    int y;
    virtual void f() { x=2; }
};


A *a;
B *b;
const int TEST_PIN = 10;

void setup()
{
   a=new A(); 
   b=new B();
   pinMode(TEST_PIN,OUTPUT);
   Serial.begin(9600);
   Serial.println("Serialport test");
}

void loop()
{
  Serial.write(1);
delay(2500);
}
