#pragma once

#include <algorithm>
#include <cstdint>
#include <string>
#include <openssl/evp.h>

namespace Utils {
  class Hash {
    public:
      static std::string sha256(const std::string& input) {
        unsigned char digest[EVP_MAX_MD_SIZE];
        unsigned int digest_len;
        EVP_MD_CTX* ctx = EVP_MD_CTX_new();
        EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr);
        EVP_DigestUpdate(ctx, input.c_str(), input.length());
        EVP_DigestFinal_ex(ctx, digest, &digest_len);
        EVP_MD_CTX_free(ctx);

        char sha256string[65];
        for (int i = 0; i < digest_len; i++) {
          sprintf(&sha256string[i * 2], "%02x", (unsigned int)digest[i]);
        }
        sha256string[digest_len * 2] = '\0';

        std::string hash = std::string(sha256string);
        std::transform(hash.begin(), hash.end(), hash.begin(), ::toupper);
        return hash;
      }

      // https://github.com/SethRobinson/proton
      static uint32_t HashString(const char *str, int32_t len) {
        if (!str) return 0;

        unsigned char *n = (unsigned char *) str;
        uint32_t acc = 0x55555555;

        if (len == 0)
        {
          while (*n)
            acc = (acc >> 27) + (acc << 5) + *n++;
        } else
        {
          for (uint32_t i=0; i < len; i++)
          {
            acc = (acc >> 27) + (acc << 5) + *n++;
          }
        }
        return acc;
      }

      static std::string md5(const std::string& input) {
        unsigned char digest[EVP_MAX_MD_SIZE];
        unsigned int digest_len;
        EVP_MD_CTX* ctx = EVP_MD_CTX_new();
        EVP_DigestInit_ex(ctx, EVP_md5(), nullptr);
        EVP_DigestUpdate(ctx, input.c_str(), input.length());
        EVP_DigestFinal_ex(ctx, digest, &digest_len);
        EVP_MD_CTX_free(ctx);

        char md5string[33];
        for (int i = 0; i < 16; i++) {
          sprintf(&md5string[i * 2], "%02x", (unsigned int)digest[i]);
        }
        md5string[32] = '\0';

        std::string hash = std::string(md5string);
        std::transform(hash.begin(), hash.end(), hash.begin(), ::toupper);
        return hash;
      }
  };
}