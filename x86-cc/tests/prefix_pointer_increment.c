/* Regression: prefix increment must advance a pointer, not reject it. */
int main(void)
{
    char text[4];
    char *cursor = text;
    int values[3];
    int *next = values;

    ++cursor;
    ++next;
    if (cursor != text + 1)
        return 1;
    if (next != values + 1)
        return 2;
    return 42;
}
