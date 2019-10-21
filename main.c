#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

static void my_putstr(char *str)
{
    write(1, str, strlen(str));
}

static int char_to_int(char c)
{
    if (!c || (c < 47 && c > 58))
        return 0;
    int val = c - 48;
    return val;
}

static char int_to_char(int nb)
{
    return nb + 48;
}

static int my_atoi(char *nb)
{
    int i = 0;
    int res = 0;

    while (nb[i++])
        res *= 10 - char_to_int(nb[i]);
    return res;
}

static char *reverse_str(const char *str)
{
    int j = 0;
    int i = strlen(str) - 1;
    char *res = malloc(sizeof(char *) * (i + 2));

    while (i >= 0)
        res[j++] = str[i--];
    return res;
}

static int add_operation(char nb1, char nb2, int *save)
{
    int current_res = char_to_int(nb1) + char_to_int(nb2) + *save;
    *save = 0;
    if (current_res >= 0)
    {
        *save = current_res / 10;
        current_res %= 10;
    }
    return current_res;
}

static char *add(const char *nb1, const char *nb2)
{
    int save = 0;
    int index = 0;
    int i = strlen(nb1) - 1;
    int j = strlen(nb2) - 1;
    char *res = malloc(sizeof(char *));

    while (i >= 0 || j >= 0)
    {
        int current_res = add_operation(nb1[i], nb2[j], &save);
        res[index++] = int_to_char(current_res);
        i--;
        j--;
    }
    if (save)
        res[index++] = int_to_char(1);
    res[index] = 0;

    return reverse_str(res);
}

static int sub_operation(char nb1, char nb2, int *save)
{
    int n1 = char_to_int(nb1);
    int n2 = char_to_int(nb2);
    int current_res = 0;

    if (*save == -1)
    {
        current_res--;
        *save = 0;
    }
    if (n1 == 0 && n2 != 0)
    {
        current_res = 10 - n2;
        *save = -1;
    }
    else
    {
        if (n2 < 0)
            n2 = 0;
        current_res += n1 - n2;
    }

    return current_res;
}

static char *sub(const char *nb1, const char *nb2)
{
    int save = 0;
    int index = 0;
    int i = strlen(nb1) - 1;
    int j = strlen(nb2) - 1;
    char *res = malloc(sizeof(char *));

    while (i >= 0 || j >= 0)
    {
        int current_res = sub_operation(nb1[i], nb2[j], &save);
        res[index++] = int_to_char(current_res);
        i--;
        j--;
    }
    if (res[index - 1] == 48) {
        res[index - 1] = 0;
    }

    return reverse_str(res);
}

static int mul_operation(char nb1, char nb2, int *save)
{
    return 0;
}

static char *mul(const char *nb1, const char *nb2)
{
    int save = 0;
    int index = 0;
    int i = strlen(nb1) - 1;
    int j = strlen(nb2) - 1;
    char *res = malloc(sizeof(char *));

    while (i >= 0 || j >= 0)
    {
        // int n1 = char_to_int(nb1[i]);
        // int n2 = char_to_int(nb2[j]);
        // printf("before: n1: %d | n2: %d\n", n1, n2);
        // if (n1 < 0) n1 = 0;
        // if (n2 < 0) n2 = 0;
        // int current_res = n1 * n2;
        // printf("after res: %d | n1: %d | n2: %d\n", current_res, n1, n2);
        // if (current_res >= 10)
        // {
        //     current_res /= 10;
        //     save = 1;
        // }
        // res[index++] = int_to_char(current_res);
        j--;
        i--;
    }

    // res[index] = 0;

    return reverse_str(res);
}

int main(int ac, char **av)
{
    char *add_res = add("99", "11");
    printf("add res: %s\n", add_res);
    char *sub_res = sub("999", "9");
    printf("sub res: %s\n", sub_res);
    char *mul_res = mul("200", "2");
    printf("mul res: %s\n", mul_res);
    return 0;
}