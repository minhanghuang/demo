#include <curl/curl.h>
#include <iostream>

struct FtpFile {
  const char *filename;
  FILE *stream;
};


int my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream) {
  struct FtpFile *out = (struct FtpFile *) stream; // stream指针其实就是指向struct FtpFile ftpfile的
  if (out && !out->stream) {
    out->stream = fopen(out->filename, "wb"); //没有这个流的话就创建一个名字是out->filename.
    if (!out->stream)
      return -1;
  }
  return fwrite(buffer, size, nmemb, out->stream);
}


int main() {
  std::cout << "Hello, Curl!" << std::endl;
  CURL *curl;
  CURLcode res;
  struct FtpFile ftpfile = {"/Users/cox/work/code/github/demo/cpp/curl_demo/haha.bag",NULL};

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL,"ftp://192.168.199.4:8080/opt/file/data/");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl); /* always cleanup */

    if (CURLE_OK != res) {
      std::cout << "失败 " << res << std::endl;
    } else {
      std::cout << "下载成功 " << res << std::endl;
    }
  }

  if (ftpfile.stream) {
    fclose(ftpfile.stream);
  }

  curl_global_cleanup();
  return 0;
}

