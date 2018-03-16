#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "ConnectedComponents.h"
#include "I_Oheader.h"

int choice ;

//CC MENU
struct image* ConnectedComponentsMenu(struct image *the_image,struct image *out_image){
	do{
		printf("\n-> Please tell me what Connected Component Algorithm you want to apply\n" );
		printf("-> Moore(8neightbors) [1] or Van Neumann(4neightbors) [2] or Quit [0] \n"); 
		scanf("%d",&choice);
		getchar();
		switch (choice){
		case 1 :  
			printf("You have selected the Connected Component with Moore Neighborhood \n" );
			printf("Working. . .\n ");
			Moore_CC(the_image, out_image);
			printf("Done . . . \n");
			choice = 0;
			break;
		case 2 : 
			printf("You have selected the Connected Component with Moore Neighborhood\n" );
			printf("Working. . .\n ");
			VanNeumann_CC(the_image, out_image);
			printf("Done . . . \n");
			choice = 0;
			break;
		default : 
			printf("Invalid Selection. . . Try Again\n" );
			break;		
		}
	}while(choice != 0);
	return out_image;
}

/**********MOORE CONNECTED COMPONENTS***************/
void Moore_CC (struct image *the_image,struct image* out_image ){
	int i , j , neighborhood = 0;
	for (i = 0 ; i < the_image -> height ; i++ ){
		for ( j = 0 ; j < the_image ->width ; j++){
			if (*(*(the_image->imageMatrix + i ) +j) == 1 || *(*(the_image->imageMatrix + i ) +j) == 255){
				if (*(*(out_image->imageMatrix + i ) +j) == 0 ){
					neighborhood ++;
					Moore_pixelFlood ( i , j , the_image , out_image , neighborhood);
				}
			}	
		}
	}
}


void Moore_pixelFlood(int i , int j , struct image *the_image, struct image *out_image , int newNeighbor){

	if (*(*(the_image->imageMatrix + i )+ j) == 0 ){
		return;} //this condition checks if the neightbor pixel is
				// 0 or 1..We use this to avoid seg_fault on recursion 
	if  ( *(*(out_image->imageMatrix + i )+ j) != 0 ){
		return;} //if this condition meets 
				//means that a node has been visites before..

		*(*(out_image -> imageMatrix + i ) +  j) = newNeighbor;
	
	///Recursive Part for neighbot pixels
	if (j -1 > 0 ){ // pixel left
		Moore_pixelFlood (i , j-1 , the_image , out_image , newNeighbor);
	}
	if ( i -1 > 0 ){//pixel up
		Moore_pixelFlood (i -1 , j , the_image , out_image , newNeighbor);
	}
	if (i +1 <  the_image->height  ){ // pixel down
		Moore_pixelFlood ( i+1 , j , the_image , out_image , newNeighbor);
	}
	if (j +1 < the_image ->width  ){ // pixel right
		Moore_pixelFlood (i , j+1 , the_image , out_image , newNeighbor);
	}
	if (j -1 > 0 && i -1 > 0 ){ // pixel top left
		Moore_pixelFlood (i -1 , j -1 , the_image , out_image , newNeighbor);
	}
	if (j +1 < the_image -> width && i -1 > 0 ){ // pixel top right
		Moore_pixelFlood (i -1 , j+1 , the_image , out_image , newNeighbor);
	}
	if (j -1 > 0 && i +1 < the_image ->height  ){ // pixel bottom left 
		Moore_pixelFlood (i +1  , j -1 , the_image , out_image , newNeighbor);
	}
	if (j +1 < the_image->width  && i +1 < the_image -> height ){ // pixel bottom right
		Moore_pixelFlood (i +1  , j + 1 , the_image , out_image , newNeighbor);
	}
}

/**********VAN NEUMANN CONNECTED COMPONENTS***************/
void VanNeumann_CC (struct image *the_image,struct image* out_image ){
	int i , j , neighborhood = 0;
	for (i = 0 ; i < the_image -> height ; i++ ){
		for ( j = 0 ; j < the_image ->width ; j++){
			if (*(*(the_image->imageMatrix + i ) +j) == 1 || *(*(the_image->imageMatrix + i ) +j) == 255){
				if (*(*(out_image->imageMatrix + i ) +j) == 0 ){
					neighborhood ++;
					VN_pixelFlood ( i , j , the_image , out_image , neighborhood);
				}
			}	
		}
	}
}


void VN_pixelFlood(int i , int j , struct image *the_image, struct image *out_image , int newNeighbor){
	if (*(*(the_image->imageMatrix + i )+ j) == 0 ){
		return; //this condition checks if the neightbor pixel is 0 or 1..We use this to avoid seg_fault on recursion
	} 

	if  ( *(*(out_image->imageMatrix + i )+ j) != 0 ){
		return; //if this condition meets means that a node has been visites before..
	}
		*(*(out_image -> imageMatrix + i ) +  j) = newNeighbor;
	
	///Recursive Part for neighbot pixels
	if (j -1 > 0 ){ // pixel left
		VN_pixelFlood (i , j-1 , the_image , out_image , newNeighbor);
	}
	if ( i -1 > 0 ){//pixel up
		VN_pixelFlood (i -1 , j , the_image , out_image , newNeighbor);
	}
	if (i +1 <  the_image->height  ){ // pixel down
		VN_pixelFlood ( i+1 , j , the_image , out_image , newNeighbor);
	}
	if (j +1 < the_image ->width  ){ // pixel right
		VN_pixelFlood (i , j+1 , the_image , out_image , newNeighbor);
	}
}