#include<cstdint>
#include<time.h>
#include<stdio.h>
#include<unistd.h>
#include<wiringPi.h>
#include<stdio.h>
#include<curl/curl.h>
#include<string>

#define pos 4
#define sig 8

bool sendCommand(bool command)
{
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  std::string on =  "https://maker.ifttt.com/trigger/heater_on/with/key/iuqTik_MlP-QhXazswBCAHrk7_dHrA8-s49EO3lIV2V";
  std::string off = "https://maker.ifttt.com/trigger/heater_off/with/key/iuqTik_MlP-QhXazswBCAHrk7_dHrA8-s49EO3lIV2V";
  std::string cmd = (command) ? on : off;
  
  if (curl)
  {
      curl_easy_setopt(curl, CURLOPT_URL, cmd.c_str());
      res = curl_easy_perform(curl);
      if (res != CURLE_OK)
	{
	  printf("error...%i \n",res);
	}
  }
  curl_easy_cleanup(curl);
}

uint32_t read(void)
{
  uint8_t * data = new uint8_t[5];
  uint8_t laststate = 1;
  uint8_t counter, _count,maxtimings = 0;
  uint8_t j = 0, i;
  clock_t currenttime;
  clock_t _lastreadtime;
  bool firstreading = true;

  // check if sensor was read less than two seconds ago and return early
  // to use last reading.
  currenttime = clock();
  if (currenttime < _lastreadtime) {
    // ie there was a rollover
    _lastreadtime = 0;
  }
  if (!firstreading && ((currenttime - _lastreadtime) < 2000)) {
    return true; // return last correct measurement
    //delay(2000 - (currenttime - _lastreadtime));
  }
  firstreading = false;
  /*
    serial.print("currtime: "); serial.print(currenttime);
    serial.print(" lasttime: "); serial.print(_lastreadtime);
  */
  _lastreadtime = clock_t();

  data[0] = data[1] = data[2] = data[3] = data[4] = 0;


  digitalWrite(sig, HIGH);
  usleep(250);


  pinMode(sig, OUTPUT);
  digitalWrite(sig, LOW);
  usleep(20);
  //??  nointerrupts();
  digitalWrite(sig, HIGH);
  usleep(40);
  pinMode(sig, INPUT);

  for ( i=0; i< maxtimings; i++) {
    counter = 0;
    while (digitalRead(sig) == laststate) {
      counter++;
      usleep(1);
      if (counter == 255) {
	break;
      }
    }
    laststate = digitalRead(sig);

    if (counter == 255) break;

    if ((i >= 4) && (i%2 == 0)) {
      data[j/8] <<= 1;
      if (counter > _count)
	data[j/8] |= 1;
      j++;
    }
  } 
  for (int i = 0; i < 5; i++)
    {
      printf("%d ",data[i]);
    }
}

int main(int argc, char** argv)
{  
  wiringPiSetup();
  uint32_t temp;
  bool state;
  while (true)
    {
      temp = read();
      if (temp < 60){
	sendCommand(!state);
	state = false;
      } else {
	
      }
      printf("state: %d",temp);
      usleep(2000);      
    }
  return 0;
}
