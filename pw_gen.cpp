#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include "pw_gen.h"
#include "settings.h"
void gen_pw(char*);
int mod_success(char*);

using namespace std;
int main(void) {
    char pw_str[MAX_LEN+1];
    srand((unsigned)time(NULL));
    while (True) {
        gen_pw(pw_str);
        cout << pw_str << endl;
        cin.ignore();
    }
}

void gen_pw(char* str) {
    str[MAX_LEN] = '\0';
    int i = 0;
    while (True) {
        if (i == MAX_LEN) {
            if (mod_success(str)) {
                break;
            }
            i = 0;
        }
        str[i++] = (char)(rand() % ('z'-'a') + 'a');
    }
}

int mod_success(char* str) {
    enum {low=0, spcl, uppr, digit};
    const int n_spcl = (int)strlen(SPECIAL_CHARS);
    const int n_ambchr = (int)strlen(AMBIGUOUS_CHARS);
    int lv[MAX_LEN] = {0};
    int c = 1;

    // choose where to modify
    for (int i = 0; i < NUM_SPEC_CHARS + NUM_UPPER_CASE + NUM_DIGITS; ++i) {
        if (i == NUM_SPEC_CHARS || i == NUM_SPEC_CHARS + NUM_UPPER_CASE) {
            ++c;
        }
        int iloc = rand() % (MAX_LEN-2) + 1;    // beg, end: lower case
        while (lv[iloc]) {
            iloc = rand() % (MAX_LEN-2) + 1;
        }
        lv[iloc] = c;
    }

    // apply modding
    for (int i = 0; i < MAX_LEN; ++i) {
        switch (lv[i]) {
            case spcl:
                str[i] = SPECIAL_CHARS[rand() % n_spcl];
                break;
            case uppr:
                str[i] += 'A'-'a';
                break;
            case digit:
                str[i] = rand() % ('9'-'0') + '0';
                break;
            case low:
                break;
            default:
                ;
        }

        /* validate NO ambiguous chars */
        for (int k = 0; k < n_ambchr; ++k) {
            if (str[i] == AMBIGUOUS_CHARS[k]) {
                return False;
            }
        }
    }

    // validate NO duplicative chars
    int dup_cnt[MAX_LEN] = {0};
    char prev_chr = 0;
    for (int i = 0; i < MAX_LEN; ++i) {
        if (prev_chr == str[i]) {
            return False;
        }
        prev_chr = str[i];
        if (dup_cnt[i]) {
            continue;
        }
        int cnt = 0;
        for (int j = i; j < MAX_LEN; ++j) {
            if (str[i] == str[j]) {
                dup_cnt[i] |= 1;
                dup_cnt[j] |= 1;
                ++cnt;
            }
        }
        if (cnt > ALLOWED_DUP_CHAR) {
            return False;
        }
    }
    return True;
}