#include <curl/curl.h>
#include <iostream>

int main() {
  std::cout << "Hello, Curl POST!" << std::endl;
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  std::string url = "http://127.0.0.1:8888/sss";

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS,"xxxxx"); // 指定post内容
    curl_easy_setopt(curl, CURLOPT_URL,url.c_str()); // 指定url
    res = curl_easy_perform(curl);
    std::cout << res << std::endl;
    curl_easy_cleanup(curl);
  }
  return 0;
}