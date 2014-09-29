char string[] = "test,data";
int x[2];
int i = 0;
String sx ="";

void setup2()
{
 char *p = string;
 char *str;
 Serial.begin(9600);
 while ((str = strtok_r(p, ",", &p)) != NULL){ // delimiter is the comma
   sx += str;
   x[i] = sx.toInt();
   i++;
   sx = "";
}
 
}
void loop2() {
  // put your main code here, to run repeatedly: 
  
}
