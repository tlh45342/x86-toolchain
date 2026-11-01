int check_literal(void) { const char *s = "ABC"; return s[0]=='A' && s[1]=='B' && s[2]=='C'; }
int main(void) { return check_literal() ? 42 : 1; }
