char storage[2];

void *get_storage(void)
{
    return storage;
}

int main(void)
{
    char *p;
    p = get_storage();
    p[0] = 42;
    return p[0];
}
