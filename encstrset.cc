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

    inline string val(const char* x) {
        if (x == nullptr) {
            return "NULL";
        } else {
            cerr << "\"" << x << "\"";
            return "";
        }
    }

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

    unordered_map<unsigned long, unordered_set<string>> sets;
    unsigned long next_id = 0;

    unsigned long encstrset_new() {
        print_debug(__func__ << "()\n");
        unordered_set<string> new_set;
        sets.insert({next_id, new_set});
        ++next_id;
        print_debug(__func__ << ": set #" << next_id - 1 << " created\n");
        return next_id - 1;
    }

    void encstrset_delete(unsigned long id) {
        print_debug(__func__ << "(" << id << ")\n");
        sets.erase(id);
        print_debug(__func__ << ": set #" << id << " deleted\n");
    }

    size_t encstrset_size(unsigned long id) {
        print_debug(__func__ << "(" << id << ")\n");
        try {
            size_t size = sets.at(id).size();
            print_debug(__func__ << ": set #" << id << " contains " << size << " element(s)\n");
            return size;
        } catch (const out_of_range& e) {
            print_debug(__func__ << ": set #" << id << " does not exist\n");
            return 0;
        }
    }

    bool encstrset_insert(unsigned long id, const char* value, const char* key) {
        print_debug(__func__ << "(" << id << ", " << val(value) << ", " << val(key) << ")\n");
        string encrypted_text = encode(value, key);
        try {
            bool inserted = sets.at(id).insert(encrypted_text).second;
            if (inserted) {
                print_debug(__func__ << ": set #" << id << ", cypher \"" << encrypted_text << "\" inserted\n");
            } else {
                print_debug(__func__ << ": set #" << id << ", cypher \"" << encrypted_text << "\" was already present\n");
            }
            return inserted;
        } catch (const out_of_range& e) {
            print_debug(__func__ << ": set #" << id << " does not exist\n");
            return false;
        }
    }

    bool encstrset_remove(unsigned long id, const char* value, const char* key) {
        print_debug(__func__ << "(" << id << ", " << val(value) << ", " << val(key) << ")\n");
        string encrypted_text = encode(value, key);
        try {
            bool removed = sets.at(id).erase(encrypted_text) > 0;
            if (removed) {
                print_debug(__func__ << ": set #" << id << ", cypher \"" << encrypted_text << "\" removed\n");
            } else {
                print_debug(__func__ << ": set #" << id << ", cypher \"" << encrypted_text << "\" was not present\n");
            }
            return removed;
        } catch (const out_of_range& e) {
            print_debug(__func__ << ": set #" << id << " does not exist\n");
            return false;
        }
    }

    bool encstrset_test(unsigned long id, const char* value, const char* key) {
        print_debug(__func__ << "(" << id << ", " << val(value) << ", " << val(key) << ")\n");
        string encrypted_text = encode(value, key);
        try {
            unordered_set<string> set = sets.at(id);
            bool present = set.find(encrypted_text) != set.end();
            if (present) {
                print_debug(__func__ << ": set #" << id << ", cypher \"" << encrypted_text << "\" is present\n");
            } else {
                print_debug(__func__ << ": set #" << id << ", cypher \"" << encrypted_text << "\" is not present\n");
            }
            return present;
        } catch (const out_of_range& e) {
            print_debug(__func__ << ": set #" << id << " does not exist\n");
            return false;
        }
    }

    void encstrset_clear(unsigned long id) {
        print_debug(__func__ << "(" << id << ")\n");
        try {
            sets.at(id).clear();
            print_debug(__func__ << ": set #" << id << " cleared\n");
        } catch (const out_of_range& e) {
            print_debug(__func__ << ": set #" << id << " does not exist\n");
        }
    }

    void encstrset_copy(unsigned long src_id, unsigned long dst_id) {
        print_debug(__func__ << "(" << src_id << ", " << dst_id << ")\n");
        auto src_set = sets.find(src_id);
        auto dst_set = sets.find(dst_id);
        if (src_set != sets.end() && dst_set != sets.end()) {
            for (const string& s : (*src_set).second) {
                bool inserted = (*dst_set).second.insert(s).second;
                if (inserted) {
                    print_debug(__func__ << ": cypher \"" << s << "\" copied from set #" << src_id << " to set #" << dst_id << "\n");
                } else {
                    print_debug(__func__ << ": copied cypher \"" << s << "\" was already present in set #" << dst_id << "\n");
                }
            }
        }
    }

}
