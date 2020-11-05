#include "encstrset.h"
#include <iostream>
#include <cstring>
#include <cassert>
#include <optional>
#ifdef NDEBUG
constexpr bool DEBUG = false;
#else
constexpr bool DEBUG = true;
#endif

#define print_debug(v) if(DEBUG) std::cerr<<v;

namespace {
bool is_value_valid(const char* value){
  return value != nullptr;
}

std::optional<std::string> encode(const char *value, const char *key) {
  if(!is_value_valid(value)){
    return {};
  }
  std::string encoded(value);
  if (key) {
    const size_t key_len = strlen(key);

    for (size_t i = 0; i < encoded.size(); i++) {
      encoded[i] ^= key[i % key_len];
    }
  }
  return encoded;
}
}

namespace jnp1 {
void encstrset_delete(unsigned long id) {

}
size_t encstrset_size(unsigned long id) {
  return 0;
}
bool encstrset_insert(unsigned long id, const char *value, const char *key) {
  return false;
}
bool encstrset_remove(unsigned long id, const char *value, const char *key) {
  return false;
}
bool encstrset_test(unsigned long id, const char *value, const char *key) {
  return false;
}
void encstrset_clear(unsigned long id) {

}
void encstrset_copy(unsigned long src_id, unsigned long dst_id) {

}
}
