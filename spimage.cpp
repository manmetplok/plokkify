#include "spimage.h"


void image_loaded(sp_image *image, void *userdata){
    spc.ImageLoaded(image,userdata);
}
