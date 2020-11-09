#include "encstrset.h"
#include <iostream>
#include <cstring>
#include <optional>
#include <unordered_set>
#include <unordered_map>

#ifdef NDEBUG
constexpr bool DEBUG = false;
#else
constexpr bool DEBUG = true;
#endif

#define print_debug(v) if(DEBUG) std::cerr << v

namespace {

    inline std::string val(const char* x) {
        if (x == nullptr) {
            return "NULL";
        } else {
            return '"' + std::string(x) + '"';
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

    std::unordered_map<unsigned long, std::unordered_set<std::string>> sets;
    unsigned long next_id = 0;

    unsigned long encstrset_new() {
        print_debug(__func__ << "()\n");
        std::unordered_set<std::string> new_set;
        sets[next_id] = new_set;
        print_debug(__func__ << ": set #" << next_id << " created\n");
        ++next_id;
        return next_id - 1;
    }

    void encstrset_delete(unsigned long id) {
        print_debug(__func__ << "(" << id << ")\n");
        auto search = sets.find(id);
        if (search == sets.end()) {
            print_debug(__func__ << ": set #" << id << " does not exist\n");
            return;
        }
        sets.erase(id);
        print_debug(__func__ << ": set #" << id << " deleted\n");
    }

    size_t encstrset_size(unsigned long id) {
        print_debug(__func__ << "(" << id << ")\n");
        auto search = sets.find(id);
        if (search == sets.end()) {
            print_debug(__func__ << ": set #" << id << " does not exist\n");
            return 0;
        }
        size_t size = search->second.size();
        print_debug(__func__ << ": set #" << id << " contains " << size
                    << " element(s)\n");
        return size;
    }

    bool encstrset_insert(unsigned long id, const char* value, const char* key) {
        print_debug(__func__ << "(" << id << ", " << val(value) << ", "
                    << val(key) << ")\n");
        std::optional<std::string> encrypted_text = encode(value, key);
        if (!encrypted_text.has_value()) {
            print_debug(__func__ << ": invalid value (NULL)\n");
            return false;
        }
        auto search = sets.find(id);
        if (search == sets.end()) {
            print_debug(__func__ << ": set #" << id << " does not exist\n");
            return false;
        }
        bool inserted = search->second.insert(encrypted_text.value()).second;
        print_debug(__func__ << ": set #" << id << ", cypher \""
                    << encrypted_text.value() << '"');
        if (inserted) {
             print_debug(" inserted\n");
        } else {
            print_debug(" was already present\n");
        }
        return inserted;
    }

    bool encstrset_remove(unsigned long id, const char* value, const char* key) {
        print_debug(__func__ << "(" << id << ", " << val(value) << ", "
                    << val(key) << ")\n");
        std::optional<std::string> encrypted_text = encode(value, key);
        if (!encrypted_text.has_value()) {
            print_debug(__func__ << ": invalid value (NULL)\n");
            return false;
        }
        auto search = sets.find(id);
        if (search == sets.end()) {
            print_debug(__func__ << ": set #" << id << " does not exist\n");
            return false;
        }
        bool removed = search->second.erase(encrypted_text.value()) > 0;
        print_debug(__func__ << ": set #" << id << ", cypher \""
                    << encrypted_text.value() << '"');
        if (removed) {
            print_debug(" removed\n");
        } else {
            print_debug(" was not present\n");
        }
        return removed;
    }

    bool encstrset_test(unsigned long id, const char* value, const char* key) {
        print_debug(__func__ << "(" << id << ", " << val(value) << ", "
                    << val(key) << ")\n");
        std::optional<std::string> encrypted_text = encode(value, key);
        if (!encrypted_text.has_value()) {
            print_debug(__func__ << ": invalid value (NULL)\n");
            return false;
        }
        auto search = sets.find(id);
        if (search == sets.end()) {
            print_debug(__func__ << ": set #" << id << " does not exist\n");
            return false;
        }
        bool present = search->second.find(encrypted_text.value()) != search->second.end();
        print_debug(__func__ << ": set #" << id << ", cypher \""
                    << encrypted_text.value() << '"');
        if (present) {
            print_debug(" is present\n");
        } else {
            print_debug(" is not present\n");
        }
        return present;
    }

    void encstrset_clear(unsigned long id) {
        print_debug(__func__ << "(" << id << ")\n");
        auto search = sets.find(id);
        if (search == sets.end()) {
            print_debug(__func__ << ": set #" << id << " does not exist\n");
            return;
        }
        search->second.clear();
        print_debug(__func__ << ": set #" << id << " cleared\n");
    }

    void encstrset_copy(unsigned long src_id, unsigned long dst_id) {
        print_debug(__func__ << "(" << src_id << ", " << dst_id << ")\n");
        auto src_search = sets.find(src_id);
        auto dst_search = sets.find(dst_id);
        if (src_search == sets.end()) {
            print_debug(__func__ << ": set #" << src_id << " does not exist\n");
            return;
        }
        if (dst_search == sets.end()) {
            print_debug(__func__ << ": set #" << dst_id << " does not exist\n");
            return;
        }
        for (const std::string& s : src_search->second) {
            bool inserted = dst_search->second.insert(s).second;
            if (inserted) {
                print_debug(__func__ << ": cypher \"" << s
                            << "\" copied from set #" << src_id
                            << " to set #" << dst_id << "\n");
            } else {
                print_debug(__func__ << ": copied cypher \"" << s
                            << "\" was already present in set #" << dst_id << "\n");
            }
        }
    }

}
