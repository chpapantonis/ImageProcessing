#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "imageFilter.h"
#include "I_Oheader.h"
#include "maskHeader.h"

struct image* filterMenu (struct image *the_image,struct image *out_image, struct mask * mainMask){
	char choice = '*';

	do {
		fflush(stdin);
		printf("Choose the filtering process you want to apply : \n");
		printf("Erosion [1] , Dilation [2] , Open [3] , Close [4] \n");
		scanf("%c",&choice);
		getchar();
		switch(choice){
		case '1' : 
			printf("You have chosen Erosion . . .  \n");
			printf("Working. . .\n");
			out_image = Erosion (the_image , out_image, mainMask);
			printf("Done . . . \n");
			choice = '0';
			break;
		case '2' : 
			printf("You have chosen Dilation . . .  \n");
			printf("Working. . .\n");
			out_image = Dilation (the_image , out_image, mainMask);
			printf("Done . . . \n");
			choice = '0';
			break;
		case '3' :
			printf("You have chosen Open . . .  \n");
			printf("Working. . .\n");
			out_image = Erosion (the_image , out_image, mainMask);
			the_image = copyImage(the_image , out_image);
			out_image = initOut_image(out_image , the_image);
			out_image = Dilation (the_image , out_image, mainMask);
			printf("Done . . . \n");
			choice = '0';
			break;
		case '4' : 
			printf("You have chosen Close . . .  \n");
			printf("Working. . .\n");
			out_image = Dilation (the_image , out_image, mainMask);
			the_image = copyImage(the_image , out_image);
			out_image = initOut_image(out_image , the_image);
			out_image = Erosion (the_image , out_image, mainMask);
			printf("Done . . . \n");
			choice = '0';
			break;
		default:
			printf("Your choice is wrong...Retry\n");
			break;
		}
	}while (choice != '0');
	return out_image;
}


struct image* Erosion(struct image *the_image, struct image* out_image, struct mask*mainMask){
	int i, j,a,b;
	int min;

	for (i = 0; i < the_image->height ; i++){//2 loops for parsing image
		for (j = 0; j < the_image->width; j++){
			min = 1000000;
			for (a = -mainMask->O; a <= mainMask->O; a++){//2 loops for mask
				for (b =  -mainMask->O; b <=  mainMask->O; b++){
					if( (i +a) >= 0 && (i + a) <  the_image->height &&  ( j + b ) >= 0 && (j +b) < the_image->width){///checks boundaries with mask
						if (mainMask->maskArray[a +  mainMask->O][b +  mainMask->O] == 1){	//checks whether mask's element value is 1 
							if (*(*(the_image->imageMatrix + i + a)+ j + b) < min){ //compares the element value with the minimum value of the mask
								min = *(*(the_image->imageMatrix + i + a)+ j + b);
							}
						}
					} /* ends if mask == 1 */
				} /* ends loop over b */
			} /* ends loop over a */
			//printf("%d\n",min);
			out_image->imageMatrix[i][j] = min;
		} /* ends loop over j */
	} /* ends loop over i */
	return out_image;
}

struct image* Dilation(struct image *the_image, struct image* out_image, struct mask*mainMask){
	int i, j,a,b;
	int max;

	for (i = 0; i < the_image->height ; i++){//2 loops for parsing image
		for (j = 0; j < the_image->width; j++){
			max = 0;
			for (a = -mainMask->O; a <= mainMask->O; a++){//2 loops for mask
				for (b =  -mainMask->O; b <=  mainMask->O; b++){
					if( (i +a) >= 0 && (i + a) <  the_image->height &&  ( j + b ) >= 0 && (j +b) < the_image->width){///checks boundaries with mask
						if (mainMask->maskArray[a +  mainMask->O][b +  mainMask->O] == 1){	//checks whether mask's element value is 1 
							if (*(*(the_image->imageMatrix + i + a)+ j + b) > max){ //compares the element value with the minimum value of the mask
								max = *(*(the_image->imageMatrix + i + a)+ j + b);
							}
						}
					} /* ends if mask == 1 */
				} /* ends loop over b */
			} /* ends loop over a */
			//printf("%d\n",min);
			out_image->imageMatrix[i][j] = max;
		} /* ends loop over j */
	} /* ends loop over i */
	return out_image;
}	
