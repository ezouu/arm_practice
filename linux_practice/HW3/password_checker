
#include <assert.h>
#include <string.h>

#include "password_checker.h"

bool check_range(char letter, char lower, char upper);


bool check_length(const char *password) {
    bool meets_len_req = strlen(password) >= 10;
    return meets_len_req;
}

bool check_upper(const char *password) {
    for (int i = 0; password[i] != '\0'; i++) {
        if (check_range(password[i], 'A', 'Z')) {
            return true;
        }
    }
    return false;
}

bool check_lower(const char *password) {
    for (int i = 0; password[i] != '\0'; i++) {
        if (check_range(password[i], 'a', 'z')) {
            return true;
        }
    }
    return false;
}

bool check_range(char letter, char lower, char upper) {
    bool is_in_range = letter >= lower && letter <= upper;
    return is_in_range; 
}

bool check_number(const char *password) {
    for (int i = 0; password[i] != '\0'; i++) {
        if (check_range(password[i], '0', '9')) {
            return true;
        }
    }
    return false;
}

bool check_name(const char *first_name, const char *last_name, const char *password) {
    bool unique_name = !(strstr(password, first_name) || strstr(password, last_name));
    return unique_name;
}

bool check_password(const char *first_name, const char* last_name, const char *password) {
  return check_length(password) && 
         check_upper(password) &&
         check_lower(password) &&
         check_number(password) &&
         check_name(first_name, last_name, password);
}
