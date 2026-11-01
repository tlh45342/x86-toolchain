# define ENABLE 0
# if defined ENABLE && ENABLE
# include <this_header_must_not_exist.h>
# endif
int main(void){ return 42; }
