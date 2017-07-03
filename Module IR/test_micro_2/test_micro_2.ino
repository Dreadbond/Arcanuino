
//
//    FILE: nearestSearchInArray.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: demo
//    DATE: 2013-12-27
//     URL:
//
// Released to the public domain
//

int ar[5] = {
  100, 300, 500, 700, 900 };

void setup()
{
  Serial.begin(115200);
  Serial.println("Start ");
}

void loop()
{
  int x = analogRead(A0);

  int y = search(x);
  Serial.print(x);
  Serial.print(" -> ");
  Serial.println(y);
}

int search(int x)
{
  // initially the first one is the best.
  int idx = 0;
  int minDistance = abs(x - ar[0]);
  for (int i=0; i<5; i++)
  {
    int d = abs(x - ar[i]);
    if (d < minDistance)
    {
      idx = i;
      minDistance = d;
    }
  }
  return ar[idx]; // minDistance;  // or idx;  if you want the index
}

