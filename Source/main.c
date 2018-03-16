#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maskHeader.h"
#include "I_Oheader.h"
#include "imageFilter.h"
#include "ConnectedComponents.h"


void main(){
	char choice = '0';
	char choice_post = '0';
	char fileNameOut[32];
	int i , j, binary = 0;
	struct image* the_image = NULL;
	struct image *out_image =NULL ;
	struct mask *mainMask = NULL;

	//Images Instantiation 
	the_image = (struct image*)malloc(sizeof(struct image*));
	out_image = (struct image*)malloc(sizeof(struct image*));
	printf("\n*******************************************************************************\n");
	printf("WELCOME TO  IMAGE PROCESSING  !!!! \n");
	printf("THIS PROGRAM FILTERS GRAYSCALE IMAGES AND APPLIES CONNECTED ON BINARY \n");
	printf("O_O \n");
	printf("*******************************************************************************\n");

	the_image = importStaff(the_image , out_image , &binary);
	
	do{
		fflush(stdin);
		printf("\n-> Image is ready for processing... Continue [1] or quit [0]\n");
		scanf("%c",&choice);
		getchar();
		choice_post = '0';
		switch (choice){
		case '1' : 
			if (binary == 1) {
				mainMask = maskMenu();
				out_image = filterMenu(the_image, out_image , mainMask);
			}
			else{
				printf("the image you have selected is binary. . . \n");
				printf("I can only apply  Moore or  Van Neumann Connected Components\n");
				out_image = ConnectedComponentsMenu( the_image, out_image);
			}
			printf("Write the name of the file you want to write the processed image . . . \n"); 
			gets(fileNameOut);
			writeImage(out_image, fileNameOut);
			choice_post = '1';
			break;
		default:
			printf("Your choice is wrong...Retry\n");
			break;
		}
		if (choice_post == '1'){
			fflush(stdin);
			printf("\n-> How to you want to continue ?? \n");
			printf("-> Process another image [1] , Process again the created image [2] , Process again the initial image [3]  or quit [0] \n");
			scanf("%c",&choice);
			getchar();
			switch (choice){
			case '1' : 
				importStaff(the_image , out_image , &binary);
				break;
			case '2' : 
				if (binary == 1){
					the_image = copyImage(the_image , out_image);
					out_image = initOut_image(out_image , the_image);
				}
				else{
					out_image = initOut_image(out_image , the_image);
				}
			break;
			case '3' :
				out_image = initOut_image(out_image , the_image);
			break;
			default:
				printf("Your choice is wrong...Retry\n");
				break;
			}
		}
	}while (choice != '0' );
}
