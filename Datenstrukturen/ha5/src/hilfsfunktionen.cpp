#include "../include/hilfsfunktionen.hpp"

int length(const char *string)
{
    int i = 0;
    while (string[i])
        ++i;
    return i;
}

char *char2str(const char c)
{
    char *string = new char[2];
    string[0] = c;
    string[1] = '\0';
    return string;
}

char *int2str(const int n)
{
    if (n == 0) {
        return char2str('0');
    }
    bool negative = (n < 0);
    int len = 0;
    for (int m = n; m != 0; len++)
        m /= 10;
    char *string;
    if (negative) {
        string = new char[len + 2];
        for (int i = 0, mod = 0, m = n; m != 0; ++i, m /= 10) {
            mod = m % 10;
            string[len - i] = mod + '0';
        }
        string[0] = '-';
        string[len + 1] = '\0';
    } else {
        string = new char[len + 1];
        for (int i = 0, mod = 0, m = n; m != 0; ++i, m /= 10) {
            mod = m % 10;
            string[len - i - 1] = mod + '0';
        }
        string[len] = '\0';
    }
    return string;
}

int str2int(const char *string)
{
    int result = 0;
    int i = 0;
    bool negative = false;
    if (string[i] == '-') {
        ++i;
        negative = true;
    }
    for (; string[i]; ++i) {
        result = result * 10 + string[i] - '0';
    }
    result = (negative) ? -1 * result : result;
    return result;
}

bool isEqual(const char *string1, const char *string2)
{
    int len1 = length(string1);
    int len2 = length(string2);
    if (len1 != len2)
        return false;
    for (int i = 0; i < len1; ++i) {
        if (string1[i] != string2[i])
            return false;
    }
    return true;
}

char *negateReprStr(const char *string)
{
    int len;
    int pos;
    if (string[0] == '-') {  // negativ zu positiv
        len = length(string) - 1;
        pos = 0;
    } else {
        len = length(string) + 1;
        pos = 1;
    }
    char *result = new char[len];
    for (int i = pos; i < len; ++i) {
        result[i] = string[i + (pos) ? -1 : 1];
    }
    if (pos)
        result[0] = '-';
    result[len] = '\0';
    return result;
}
