//initialize variables
int ECG_amp_pin = A1;
int ECG_comp_pin = A2;
// the period in ms between beats to have a certain heart rate
float LRI = 2307; //value changes for the various tests LRI for frog 2307
float VRP  = 300;
int ECG_amp = 0;
int ECG_comp =0;
unsigned long t_curr=0;
unsigned long t_prev=0;
int current_state=0;
int prev_state=0;
int hr_count =0;
unsigned long RR = 0;
float RR_s = 0.0;
int hr_rate=0;
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(11,INPUT);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  
}

// the loop routine runs over and over again forever:

void loop()
{
  // test to see when comparator output becomes HIGH
  
  if (digitalRead(11)==1 && prev_state==0)
  {
     
     t_prev = t_curr;
     t_curr=millis();
     RR = (t_curr - t_prev);
     RR_s = RR * 1.0/1000;
     hr_rate=60*(1/RR_s);
     Serial.println("beat detected");
     Serial.print("Heart rate in bpm =");
     Serial.println(hr_rate);
     prev_state=1;

  }
  // note when comparator provides a LOW signal
  if (digitalRead(11)==0)
  {
    prev_state=0;
  }
  // create a stimulus if too much time has occured between beats
  if (millis()-t_curr >LRI)
  {
    digitalWrite(13,HIGH);
    delay(8);
    digitalWrite(13,LOW);
    Serial.println("stimulus happened");
    t_prev = t_curr;
    t_curr=millis();
     RR = (t_curr - t_prev);
     RR_s = RR * 1.0/1000;
     hr_rate=60*(1/RR_s);
     Serial.print("Heart rate in bpm =");
     Serial.println(hr_rate);
  }
  
// create sampling frequency of 200 Hz

 delay(5); 
 
}

