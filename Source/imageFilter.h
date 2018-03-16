#ifndef image_filter_h
#define image_filter_h

struct image * filterMenu (struct image *the_image,struct image *out_image, struct mask *mainMask);
struct image*Erosion (struct image *the_image, struct image* out_image, struct mask*squareMask);
struct image* Dilation(struct image *the_image, struct image* out_image, struct mask*squareMask);


#endif 

