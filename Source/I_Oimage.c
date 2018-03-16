#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include<errno.h>
#include "I_Oheader.h"

struct image*  scanSize(struct image *the_image, char *fileName){
	int i = 1;
	int j = 1;
	char parser ; 
	FILE *fp;
	/*****************IMAGE READING*****************************/
	the_image -> height = 0;
	the_image -> width = 0;
	fp = fopen(fileName, "r");
	if (fp == NULL){
		printf("Error opening the file . . .\n");
		printf(strerror(errno));
		printf("\n\n");
	}
	else{
		parser = getc(fp);
		printf("Successfully Opening the image...\n");
		do{
			parser = fgetc(fp);
				if(i ==1 && parser == '\t' ){j +=1;}
				if(parser == '\n'){i +=1;}
		}while (parser !=EOF );
		if(feof(fp))
			printf("End of image reached.. All image has been parsed\n");
		else
			printf("Image wasn't successfully parsed\n");
		fclose(fp);

		the_image -> height = i;
		the_image -> width = j;
		printf("the scanned has a size of %d x %d \n", the_image->height, the_image->width);
	}
	return the_image;
}
struct image* readImage (struct image *the_image, char *fileName , int*binary){
	int h,w;
	int data;
	FILE *fp = NULL;
	if(the_image!= NULL){//if height and width has been modifies from above the struct will not be null cause image 's been  successfully read
		fp = fopen(fileName, "r");
		printf("Importing Image . . . \n");
		the_image->imageMatrix  = (unsigned short**)malloc(the_image->height*sizeof(unsigned short*));
		for (h = 0; h < the_image->height ; h++)
		{
			*(the_image->imageMatrix + h) = (unsigned short*)malloc(the_image->width*sizeof(unsigned short));
			for (w = 0; w < the_image->width; w++){
				//data = getc(fp);
				fscanf(fp, "%d", &data);
				if ((data < 255 && data > 1)||  data > 255 ){
					*binary = 1;
				}
				else{
					*binary = 0;
				}
				*(*(the_image->imageMatrix + h) + w) = data;
			}
		}
	}
	fclose(fp);
	return the_image;
}

struct image *initOut_image(struct image*out_image , struct image *the_image){
	int i , j ;
	out_image->height = the_image->height;
	out_image->width = the_image->width;
	
	out_image ->imageMatrix = (unsigned short**)malloc(the_image->height*sizeof(unsigned short*));
	for(i = 0 ; i < out_image->height; i++){
		*(out_image->imageMatrix + i) = (unsigned short*)malloc(the_image->width*sizeof(unsigned short));
		for(j =0 ; j < out_image->width; j++){
			*(*(out_image->imageMatrix + i ) + j) = 0;
		}
	}
	return out_image;
}

void writeImage(struct image* out_image, char *fileNameOut ){
	int i,j;
	FILE *fp;
	fp = fopen(fileNameOut,"w");
	if (fp == NULL){
		printf("Error opening the file . . .\n");
		printf(strerror(errno));
		printf("\n\n");
	}
	else{
			for(i = 0 ; i < out_image->height; i++){
				for(j =0 ; j < out_image->width; j++){
					fprintf(fp,"%d\t",*(*(out_image->imageMatrix + i) + j));
				}
				fprintf(fp,"\n");
			}
			printf("%s image has been successfully produced \n" , fileNameOut);
	}
	fclose(fp);
}

	// I/O Menu
struct image* importStaff(struct image*the_image , struct image *out_image , int*binary){
	char fileName[32];
	do{
		fflush(stdin);
		printf("-> Write name/path of the image you want to open . . . \n"); 
		printf("-> Some available choices for connencted components are : \n1.image.txt (bin)\n2.letters.txt(bin)\n3.shapes.txt(bin)\n4.crosses.txt \n\n");
		printf("-> Or for grayscale images some available choices are :\n1.test2.txt (gray)\n2.big1.txt\n3.mySynth.txt \n");
		printf("-> Or give me another name that exist in the directory\n");
		gets(fileName);
		the_image = scanSize(the_image, fileName);//scans size of image
		if (the_image->height != 0){
			the_image = readImage(the_image , fileName , binary);//scans the image
			out_image = initOut_image(out_image, the_image);
		}
	}while (the_image ->height == 0);
	return the_image;
	}

struct image* copyImage(struct image* the_image, struct image* out_image){
	int i,j;
	for(i = 0 ; i < out_image->height; i++){
		for(j =0 ; j < out_image->width; j++){
			*(*(the_image->imageMatrix + i) + j) = *(*(out_image->imageMatrix + i) + j);
		}
	}
	return the_image;
}

		/********** TEST PRINTING***************************
	for (i = 0; i < the_image-> height; i++){
		for (j = 0; j < the_image-> width; j++){
			printf("%d\t", *(*(the_image->imageMatrix + i) + j));
		}
		printf("\n");
	}
	printf("\n\n");
	for (i = 0; i < the_image-> height; i++){
		for (j = 0; j < the_image-> width; j++){
			printf("%d\t", *(*(out_image->imageMatrix + i) + j));
		}
		printf("\n");
	}*/
