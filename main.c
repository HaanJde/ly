/*
 * main.c file
 */

#include "Expression.h"
#include "Parser.h"
#include "Lexer.h"

#include <stdio.h>
#include <stdlib.h>

const int cnMaxInputlineSize = 10240;

int yyparse(SExpression **expression, yyscan_t scanner);

SExpression *getAST(const char *expr)
{
    SExpression *expression;
    yyscan_t scanner;
    YY_BUFFER_STATE state;

    if (yylex_init(&scanner)) {
        /* could not initialize */
        return NULL;
    }

    state = yy_scan_string(expr, scanner);

    if (yyparse(&expression, scanner)) {
        /* error parsing */
        return NULL;
    }

    yy_delete_buffer(state, scanner);

    yylex_destroy(scanner);

    return expression;
}

int evaluate(SExpression *e)
{
    switch (e->type) {
        case eVALUE:
            return e->value;
        case eMULTIPLY:
            return evaluate(e->left) * evaluate(e->right);
        case eADD:
            return evaluate(e->left) + evaluate(e->right);
        default:
            /* should not be here */
            return 0;
    }
}

char* getsource (
   FILE* in
)
{
   char acInputline[cnMaxInputlineSize] = "";
   char* apszOutputlines[];
   int nNumberoflines = 0;
   while (fgets(acInputline, cnMaxInputlineSize, in) != NULL)
      {
         if ((apszOutputlines[nNumberoflines] = (char *) malloc (sizeof(char) * (strlen(acInputline) + 1))) != NULL)
            strcpy (apszOutputlines[nNumberoflines++], acInputline);
           else {
              fprintf (stderr, "Error: out of memory\n");
              exit 1;
           }
      }
   return apszOutputlines;
}

int main (
   int nArgc,
   char* apszArgument[]
)
{
   int nReturnCode = 0;

   char* test[] = getsource(stdin);
   SExpression *e = getAST(test);
   int result = evaluate(e);
   printf("Result of '%s' is %d\n", test, result);
   deleteExpression(e);

   return nReturnCode;
}
