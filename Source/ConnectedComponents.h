#ifndef image_cc_h
#define image_cc_h

struct image *ConnectedComponentsMenu(struct image *the_image,struct image *out_image);
void Moore_CC(struct image *the_image,struct image *out_image);
void VanNeumann_CC (struct image *the_image,struct image* out_image );
void VN_pixelFlood(int i , int j , struct image *the_image, struct image *out_image , int newNeighbor);
void Moore_pixelFlood(int i , int j , struct image *the_image, struct image *out_image , int newNeighbor);

#endif