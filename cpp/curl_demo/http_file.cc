/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Minhang Huang <huangminhang@trunk.tech>, 2021/12/29 19:40
*/
#include <iostream>
#include <curl/curl.h>


size_t writedata2file(void *ptr, size_t size, size_t nmemb, FILE *stream) {
//  size_t written = fwrite(ptr, size, nmemb, stream);
  return fwrite(ptr, size, nmemb, stream);
}

int download_file(const std::string& from_path, const std::string& to_path){
  CURL *curl;
  FILE *fp;
  CURLcode res;
  /*   调用curl_global_init()初始化libcurl  */
  res = curl_global_init(CURL_GLOBAL_ALL);
  if (CURLE_OK != res)
  {
    printf("init libcurl failed.");
    curl_global_cleanup();
    return -1;
  }
  /*  调用curl_easy_init()函数得到 easy interface型指针  */
  curl = curl_easy_init();
  if (curl) {
    fp = fopen(to_path.c_str(),"wb");

    /*  调用curl_easy_setopt()设置传输选项 */
    res = curl_easy_setopt(curl, CURLOPT_URL, from_path.c_str());
    if (res != CURLE_OK)
    {
      fclose(fp);
      curl_easy_cleanup(curl);
      return -1;
    }
    /*  根据curl_easy_setopt()设置的传输选项，实现回调函数以完成用户特定任务  */
    res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite);
    if (res != CURLE_OK){
      fclose(fp);
      curl_easy_cleanup(curl);
      return -1;
    }
    /*  根据curl_easy_setopt()设置的传输选项，实现回调函数以完成用户特定任务  */
    res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    if (res != CURLE_OK)
    {
      fclose(fp);
      curl_easy_cleanup(curl);
      return -1;
    }

    res = curl_easy_perform(curl);
    // 调用curl_easy_perform()函数完成传输任务
    fclose(fp);
    /* Check for errors */
    if(res != CURLE_OK){
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
      curl_easy_cleanup(curl);
      return -1;
    }

    /* always cleanup */
    curl_easy_cleanup(curl);
    // 调用curl_easy_cleanup()释放内存

  }
  curl_global_cleanup();
  return 0;
}

int main() {
  std::cout << "Hello, Http File!" << std::endl;
  std::string src_path = "http://192.168.11.35:2223/data/testbag1/mini/test_data.tar.gz";
  std::string dest_path = "haha.tar.gz";
  int iDownlaod_Success = download_file(src_path,dest_path);
  if(iDownlaod_Success<0){
    std::cout << "失败" << std::endl;
  }

  return 0;
}
