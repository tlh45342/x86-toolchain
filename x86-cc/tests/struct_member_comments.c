struct pair {
    /* comment before first member */
    int a;
    /* comment between members */
    int b;
};
int main(void)
{
    struct pair p;
    p.a = 20;
    p.b = 22;
    return p.a + p.b;
}
