#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main ()
{
   const int cnMaxline = 1024;

   char** apszStorage;

   int nNoofStrings = 0;

   char* pszInput = NULL;

   char acInputline[cnMaxline] = "";

   while ((pszInput = fgets(acInputline, cnMaxline, stdin)) != NULL) {
      if (
	    ( apszStorage[nNoofStrings] = 
	       (char *) 
	       malloc 
	       (
		  (
		     sizeof(char) * 
		     (strlen(acInputline) + 1)
		  )
	       )
	    ) != NULL
	 )
	 strcpy (apszStorage[nNoofStrings++], acInputline);
   }

   fprintf(stdout, "No. of input lines: %d\n",nNoofStrings);

   int n = 0;
   while (n < nNoofStrings)
      fprintf(stdout, "%s", apszStorage[n++]);

   fprintf(stdout, "No. of output lines: %d\n",n);

   return 0;
}
