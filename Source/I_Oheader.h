#ifndef I_Oheader
#define I_Oheader

struct image{
	unsigned short **imageMatrix;
	int width;
	int height;
};


struct image *scanSize(struct image* the_image , char *fileName); 
struct image* readImage(struct image* the_image,char *fileName , int*binary );
struct image *initOut_image(struct image*out_image , struct image *the_image);
void writeImage(struct image*out_image , char *fileName);
struct image *importStaff(struct image*out_image , struct image *the_image , int*binary);
struct image*copyImage(struct image* the_image, struct image* out_image );
#endif // !I_Oheader
