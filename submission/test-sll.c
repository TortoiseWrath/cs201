   #include <stdio.h>
   #include <stdlib.h>
   #include "sll.h"
   // #include "integer.h"

   static void showItems(SLL *items)
       {
       printf("The items are ");
       displaySLL(items,stdout);
       printf(".\n");
       printf("The items (debugged) are ");
       displaySLLdebug(items,stdout);
       printf(".\n");
       }


void fr(void *v) {
	//free(v);
	return;
}

void di(void *v, FILE *fp) {
	//fputs((char *) v,fp);
	fprintf(fp,"%s",(char*)v);
}


	   int main() {
		   SLL *items = newSLL(di, fr);
		   showItems(items);
		   insertSLL(items,0,"ABC");
		   insertSLL(items,1,"DEF");
		   insertSLL(items,1,"GHI");
		   setSLL(items,1,"GHJ");
		   insertSLL(items,1,"GHI");
		   insertSLL(items,2,"IJK");
		   showItems(items);
		   printf(removeSLL(items,3));
		   printf(removeSLL(items,3));
		   showItems(items);
		   insertSLL(items,2,"IJK");
		   insertSLL(items,3,"yeeeeeeeeeee");
		   printf(getSLL(items,3));
		   freeSLL(items);
		   return 0;
	   }
