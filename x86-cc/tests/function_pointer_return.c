char *identity(char *p)
{
    return p;
}

int main(void)
{
    char text[2];
    char *p;
    text[0] = 42;
    text[1] = 0;
    p = identity(text);
    return *p;
}
