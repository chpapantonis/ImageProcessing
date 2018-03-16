#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "maskHeader.h"

/**********************MAIN MENU FOR GAREYSCALE IMAGES*************/
struct mask *maskMenu(){
	int aktina; 
	char nmbr , nmbr2 ;
	struct mask *menuAuxMask;
	menuAuxMask = NULL;
	
	do{
		nmbr = '0';
		fflush(stdin);
		printf("-> Choose the type of mask you want to apply:\n");
		printf("-> Press (1) squareMask , (2) circleMask , (3) diamondMask\n");
		scanf("%c",&nmbr);
		getchar();
		switch(nmbr){
			case '1' :
				printf("You have selected a square mask \n");
				printf("Give the distance from center\n");
				scanf("%d", &aktina);
				menuAuxMask = squareMaskConstructor(menuAuxMask , aktina); 
				break;
			case '2' : 
				printf("You have selected a Circle mask \n");
				printf("Give the distance from center\n");
				scanf("%d", &aktina);
				menuAuxMask = circleMaskConstructor(menuAuxMask , aktina); 
				break;
			case '3':
				printf("You have selected a Diamond mask \n");
				printf("Give the distance from center\n");
				scanf("%d", &aktina);
				menuAuxMask = diamondMaskConstructor(menuAuxMask , aktina); 
				break;
			default:
				printf("Your choice is wrong...Retry\n");
				break;
		}
		if (nmbr == '1' || nmbr == '2' || nmbr == '3' ){
			fflush(stdin);
			printf("-> Do you want to use another mask [1] or apply the selected  [0] ??\n");
			scanf("%c",&nmbr2);
			getchar();
		}
	}while(nmbr2 != '0');
	printf("Creating  the selected mask . . .  \n");
	return menuAuxMask;
}

/*********************CREATES A SQUARE MASK WITH ALL ELEMENTS = 1**************/
struct mask *squareMaskConstructor (struct mask* squareMask, int aktina){
	int i, j;
	squareMask = (struct mask*)malloc(sizeof(struct mask));
	squareMask->O = aktina;
	squareMask->maskArray = (int**)malloc((2 * squareMask->O + 1)*sizeof(int*));
	for (i = 0; i < (2*squareMask-> O + 1); i++){
		*(squareMask->maskArray +i)  = (int*)malloc((2 * squareMask->O + 1)*sizeof(int));
		for (j = 0; j < (2 * squareMask->O + 1); j++){
			*(*(squareMask->maskArray + i) + j) = 1;
		}
	}
	squareMask->centerX = squareMask ->O;
	squareMask->centerY = squareMask ->O;

	printf("Your mask will be looking  like  the following . . .\n");
		for (i = 0; i < (2*squareMask-> O + 1); i++){
			for (j = 0; j < (2 * squareMask->O + 1); j++){
				printf("%d    ", *(*(squareMask->maskArray + i ) + j));
			}
			printf("\n");
		}
	return squareMask;
}

/***************CREATES A CIRCLE MASK WITH THE GIVEN R **************************/
struct mask* circleMaskConstructor (struct mask* circleMask , int aktina){
	int i , j ;
	///mask instantiation
	circleMask = (struct mask*)malloc(sizeof(struct mask));
	circleMask -> O = aktina;
	circleMask ->centerX = circleMask->O;
	circleMask ->centerY = circleMask->O;
	///
	circleMask ->maskArray = (int**)malloc((2*circleMask->O +1)*sizeof(int));
	for (i = 0 ; i < (2*circleMask ->O +1);  i++ ){
		*(circleMask->maskArray +i)  = (int*)malloc((2 * circleMask->O + 1)*sizeof(int));
		for (j = 0 ; j < (2*circleMask ->O +1);  j++ ){
			if ( pow((double)(circleMask-> centerX - j) , 2) + pow((double)(circleMask-> centerY - i) , 2) <= pow((double)circleMask->O , 2)){ // need typecast because pow takes double type input
				*(*(circleMask->maskArray + i) + j) = 1;
			}
			else{
				*(*(circleMask->maskArray + i) + j) = 0;
			}
		}
	}
	printf("Your mask will be looking  like  the following . . .\n");
		for (i = 0; i < (2*circleMask-> O + 1); i++){
			for (j = 0; j < (2 * circleMask->O + 1); j++){
				printf("%d    ", *(*(circleMask->maskArray + i ) + j));
			}
			printf("\n");
		}
	return circleMask;
}

/***************CREATES A DIAMOND MASK WITH THE GIVEN R *********************/

struct mask *diamondMaskConstructor (struct mask* diamondMask , int aktina ){
	int i , j , diam_cntr = -1;

	diamondMask = (struct mask*)malloc(sizeof(struct mask));
	diamondMask ->O = aktina;
	diamondMask->centerX = diamondMask ->O;
	diamondMask->centerY = diamondMask ->O;

	diamondMask ->maskArray = (int**)malloc((2*diamondMask->O +1)*sizeof(int));
	for (i = 0; i < (2*diamondMask-> O + 1); i++){
		if (i <= diamondMask -> O ) {
					diam_cntr += 1;
				}
				else{
					diam_cntr -= 1;
				}
		*(diamondMask->maskArray +i)  = (int*)malloc((2 * diamondMask->O + 1)*sizeof(int));
		for (j = 0; j < (2 * diamondMask->O + 1); j++){
			if (j >= (diamondMask->O - diam_cntr) && j <= (diamondMask ->O + diam_cntr)) { // We use a counter to in every iteration it increments until passes the middle of the array 
				*(*(diamondMask->maskArray + i) + j) = 1;								//then it decrements . This way we create a range area from the middle column. When current  	
			}																				// column is in this range the equivalent element (i,j) becomes 1 otherwise 0  
			else{
				*(*(diamondMask->maskArray + i) + j) = 0;
			}
		}
	}
	printf("Your mask will be looking  like  the following . . .\n");
		for (i = 0; i < (2*diamondMask-> O + 1); i++){
			for (j = 0; j < (2 * diamondMask->O + 1); j++){
				printf("%d    ", *(*(diamondMask->maskArray + i ) + j));
			}
			printf("\n");
		}
	return diamondMask;

}
