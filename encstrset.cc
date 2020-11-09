#include "encstrset.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <optional>
#include <unordered_set>
#include <unordered_map>

namespace {
#ifdef NDEBUG
    constexpr bool DEBUG = false;
#else
    constexpr bool DEBUG = true;
#endif

#define print_debug(v) if(DEBUG) std::cerr << v
#define print_cypher(s) print_debug(__func__ << ": set #" << id << ", cypher \""); \
                        print_cypher_helper(s);  \
                        print_debug('"');
#define print_not_exists(id) print_debug(__func__ << ": set #" << id << " does not exist"<<std::endl);
#define print_func_entrance() print_debug(__func__ << "("<<id<<")"<<std::endl)
#define print_key_val_func_entrance() print_debug(__func__ << "(" << id << ", " << val(value) << ", "\
                                                        << val(key) << ")"<<std::endl)
#define print_invalid_value() print_debug(__func__ << ": invalid value (NULL)" << std::endl);
    using encset = std::unordered_set<std::string>;
    using encsetmap = std::unordered_map<unsigned long, std::unordered_set<std::string>>;

    inline std::string val(const char *x) {
        if (x == nullptr) {
            return "NULL";
        } else {
            return '"' + std::string(x) + '"';
        }
    }

    inline void print_cypher_helper(const std::string &s) {
        if (s.empty()) {
            return;
        }
        std::ostringstream builder;
        for (size_t i = 0; i < s.size(); i++) {
            char c = s[i];
            print_debug(std::hex << std::setfill('0') << std::setw(2) << std::uppercase << unsigned(c)
                                 << ((i == s.size() - 1) ? "" : " "));
        }
    }

    inline bool is_value_valid(const char *value) {
        return value != nullptr;
    }

    std::optional<std::string> encode(const char *value, const char *key) {
        if (!is_value_valid(value)) {
            return {};
        }
        std::string encoded(value);
        if (key != nullptr && *key != '\0') {
            const size_t key_len = strlen(key);

            for (size_t i = 0; i < encoded.size(); i++) {
                encoded[i] ^= key[i % key_len];
            }
        }
        return encoded;
    }

    inline encsetmap &get_sets() {
        static encsetmap sets;
        return sets;
    }

    inline bool not_exist(const encsetmap::iterator &it) {
        return get_sets().end() == it;
    }

    unsigned long next_id = 0;

}

namespace jnp1 {
    unsigned long encstrset_new() {
        print_debug(__func__ << "()" << std::endl);
        encset new_set;
        get_sets()[next_id] = new_set;
        print_debug(__func__ << ": set #" << next_id << " created" << std::endl);
        ++next_id;
        return next_id - 1;
    }

    void encstrset_delete(unsigned long id) {
        print_func_entrance();
        auto search = get_sets().find(id);
        if (not_exist(search)) {
            print_not_exists(id);
            return;
        }
        get_sets().erase(id);
        print_debug(__func__ << ": set #" << id << " deleted" << std::endl);
    }

    size_t encstrset_size(unsigned long id) {
        print_func_entrance();
        auto search = get_sets().find(id);
        if (not_exist(search)) {
            print_not_exists(id);
            return 0;
        }
        size_t size = search->second.size();
        print_debug(__func__ << ": set #" << id << " contains " << size
                             << " element(s)" << std::endl);
        return size;
    }

    bool encstrset_insert(unsigned long id, const char *value, const char *key) {
        print_key_val_func_entrance();
        std::optional<std::string> encrypted_text = encode(value, key);
        if (!encrypted_text.has_value()) {
            print_invalid_value();
            return false;
        }
        auto search = get_sets().find(id);
        if (not_exist(search)) {

            print_not_exists(id);
            return false;
        }
        bool inserted = search->second.insert(encrypted_text.value()).second;
        print_cypher(encrypted_text.value());
        if (inserted) {
            print_debug(" inserted" << std::endl);
        } else {
            print_debug(" was already present" << std::endl);
        }
        return inserted;
    }

    bool encstrset_remove(unsigned long id, const char *value, const char *key) {
        print_key_val_func_entrance();
        std::optional<std::string> encrypted_text = encode(value, key);
        if (!encrypted_text.has_value()) {
            print_invalid_value();
            return false;
        }
        auto search = get_sets().find(id);
        if (not_exist(search)) {

            print_not_exists(id);
            return false;
        }
        bool removed = search->second.erase(encrypted_text.value()) > 0;
        print_cypher(encrypted_text.value());
        if (removed) {
            print_debug(" removed" << std::endl);
        } else {
            print_debug(" was not present" << std::endl);
        }
        return removed;
    }

    bool encstrset_test(unsigned long id, const char *value, const char *key) {
        print_key_val_func_entrance();
        std::optional<std::string> encrypted_text = encode(value, key);
        if (!encrypted_text.has_value()) {
            print_invalid_value();
            return false;
        }
        auto search = get_sets().find(id);
        if (not_exist(search)) {
            print_not_exists(id);
            return false;
        }
        bool present = search->second.find(encrypted_text.value()) != search->second.end();
        print_cypher(encrypted_text.value());
        if (present) {
            print_debug(" is present" << std::endl);
        } else {
            print_debug(" is not present" << std::endl);
        }
        return present;
    }

    void encstrset_clear(unsigned long id) {
        print_func_entrance();
        auto search = get_sets().find(id);
        if (not_exist(search)) {
            print_not_exists(id);
            return;
        }
        search->second.clear();
        print_debug(__func__ << ": set #" << id << " cleared" << std::endl);
    }

    void encstrset_copy(unsigned long src_id, unsigned long dst_id) {
        print_debug(__func__ << "(" << src_id << ", " << dst_id << ")" << std::endl);
        auto src_search = get_sets().find(src_id);
        auto dst_search = get_sets().find(dst_id);
        if (not_exist(src_search)) {
            print_not_exists(src_id);
            return;
        }
        if (not_exist(dst_search)) {
            print_not_exists(dst_id);
            return;
        }
        for (const std::string &s : src_search->second) {
            bool inserted = dst_search->second.insert(s).second;
            if (inserted) {
                print_debug(__func__ << ": cypher \"");
                print_cypher_helper(s);
                print_debug("\" copied from set #" << src_id
                                                   << " to set #" << dst_id << "" << std::endl);
            } else {
                print_debug(__func__ << ": copied cypher \"");
                print_cypher_helper(s);
                print_debug("\" was already present in set #" << dst_id << "" << std::endl);
            }
        }
    }

}
