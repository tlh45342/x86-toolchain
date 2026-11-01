/* Regression: addresses of local aggregates and pointers to aggregates. */
struct node { int value; struct node *next; };
int take_node(struct node *p) { return p->value; }
int take_result(struct node **out) { return out != 0; }
int main(void) {
    struct node item;
    struct node *result;
    item.value = 42;
    result = &item;
    if (take_node(&item) != 42) return 1;
    if (take_result(&result) != 1) return 2;
    return 0;
}
