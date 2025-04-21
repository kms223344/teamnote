int fail[N]; // N : s의 최대 길이
vi kmp(char obj[], char s[]) {
    vi ret;
    for(int i = 1, j = 0; s[i]; i++) {
        fail[i] = 0;
        while(j > 0 and s[i] != s[j]) j = fail[j-1];
        if(s[i] == s[j]) fail[i] = ++j;
    }
    for(int i = 0, j = 0; obj[i]; i++) {
        while(j > 0 and obj[i] != s[j]) j = fail[j-1];
        if(obj[i] == s[j]) {
            if(s[j+1]) j++;
            else ret.push_back(i-j), j = fail[j];
        }
    }
    return ret;
}