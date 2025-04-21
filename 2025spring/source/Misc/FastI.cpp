#define getint(n) int n; read(n)
#define getll(n) ll n; read(n)
#define inta getint(a)
#define intab getint(a); getint(b)
char get() {
    static char buf[100000], *S=buf, *T=buf;
    if(S == T) {
        S = buf;T = buf + fread(buf, 1, 100000, stdin);
        if(S == T) return EOF;
    }
    return *S++;
}
void read(int& n) {
    n = 0;
    char c; bool neg = false;
    for(c = get(); c < '0'; c=get()) if(c=='-') neg = true;
    for(;c>='0';c=get()) n = n*10+c-'0';
    if(neg) n = -n;
}
void read(ll& n) {
    n = 0;
    char c; bool neg = false;
    for(c = get(); c < '0'; c=get()) if(c=='-') neg = true;
    for(;c>='0';c=get()) n = n*10+c-'0';
    if(neg) n = -n;
}
int read(char s[]) {
    char c; int p = 0;
    while((c = get()) <= ' ');

    s[p++] = c;
    while((c = get()) >= ' ') s[p++] = c;
    s[p] = '\0';

    return p;
}