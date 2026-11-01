#define GL_INLINE static inline
#define C_INLINE GL_INLINE
#define WRAPPED_INLINE C_INLINE
WRAPPED_INLINE int helper(int x)
{
    return x;
}
int main(void)
{
    return helper(42);
}
