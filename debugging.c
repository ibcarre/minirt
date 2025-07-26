#include "minirt.h"

void	print_obj_param(t_obj *object)
{
	printf("NEXT: %p\n", object->next);
	printf("AMLIGHT: %p\n", object->amlight);
	printf("CAMERA: %p\n", object->camera);
	printf("LIGHT: %p\n", object->light);
	printf("SPHERE: %p\n", object->sphere);
	printf("PLANE: %p\n", object->plane);
	printf("CYLINDER: %p\n", object->cylinder);
	printf("COL R %i, COL G %i COL B %i\n", object->col.x, object->col.y, object->col.z);
	printf("POS X %i, POS Y %i POS Z %i\n", object->pos.x, object->pos.y, object->pos.z);
}