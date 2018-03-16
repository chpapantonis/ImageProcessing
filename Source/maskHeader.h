#ifndef maskHeader
#define maskHeader

struct mask
{
	int ** maskArray; // array of the filter mask
	int O; //Order of growth from center 
	int centerX;
	int centerY;
};
	
struct mask *maskMenu();
struct mask *squareMaskConstructor(struct mask* squareMask, int aktina);
struct mask *circleMaskConstructor (struct mask* circleMask , int aktina);
struct mask *diamondMaskConstructor (struct mask* diamondMask , int aktina );


#endif
