#include "token.h"
#include "libft/libft.h"
#include "stdio.h"


/*
    i will try to psedocode the logic of the lexer 
    the first example would be echo hello world
    it should devide the input to Token 0: "echo" , Token 1: "hello", Token 3: "world"

*/
void    tokenize(const char *input)
{
    // should i use a while loop until check all the index of the input[i] or input[i] = '\0'
    // if the input is ' ' then keep scanning
    // if the next char is printable character go at the next char until found the next space ' '
    // S.O.S i dont know if i can use any help function from my libft

    // t_token *token = NULL;
    int i = 0;
    while(input[i] != '\0')
    if(input[i] == ' ')
        i++;
    {
        if(ft_isalpha(input[i]))
        {
            // token->type = TOKEN_WORD;
            size_t *leng = ft_strlen(input);

            printf("the lenght is %ln\n", leng);
            printf("the class is %c\n", input[i]);
        }
        i++;
    }
}