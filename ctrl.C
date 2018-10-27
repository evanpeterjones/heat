#include <stdio.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <string>
//#include "headers/ctrlr.h"

int main()
{
  std::string url = "http://www.google.com";
  CURL *curl = curl_easy_init();
  if (curl)
  {
    CURLcode response;
    FILE *fp;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    response = curl_easy_perform(curl);
    fclose(fp);
    curl_easy_cleanup(curl);
    //loop to check for updated data
    //setup HTTP headers
  }
  return 0;
}
