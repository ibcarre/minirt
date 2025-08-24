#include "../minirt.h"

void	print_obj_param(t_obj *object)
{
	printf("TYPE : %i\n", object->type);
	switch (object->type)
	{
	case 0:
		printf("AMLIGHT RATIO: %f\n", object->amlight->ratio);
		break;
	case 1:
		printf("LIGHT RATIO: %f\n", object->light->ratio);
		break;
	case 2:
		printf("DIAMETER: %f\n", object->sphere->diameter);
		break;
	case 3:
		printf("PLANE NORMAL: %f;%f;%f\n", object->plane->normal.x, object->plane->normal.y, object->plane->normal.z);
		break;
	case 5:
		printf("CYL DIAM: %f HEIGHT %f NORMAL %f;%f;%f\n", object->cylinder->diameter, object->cylinder->height, object->cylinder->normal.x, object->cylinder->normal.y, object->cylinder->normal.z);
		break;
	case 4:
		printf("CAM FOV: %i ORIENTATION %f;%f;%f\n", object->camera->fov, object->camera->orientation.x, object->camera->orientation.y, object->camera->orientation.z);
		break;
	}
	printf("NEXT: %p\n", object->next);
	printf("AMLIGHT: %p\n", object->amlight);
	printf("CAMERA: %p\n", object->camera);
	printf("LIGHT: %p\n", object->light);
	printf("SPHERE: %p\n", object->sphere);
	printf("PLANE: %p\n", object->plane);
	printf("CYLINDER: %p\n", object->cylinder);
	printf("COL R %i, COL G %i COL B %i\n", object->col.x, object->col.y, object->col.z);
	printf("POS X %f, POS Y %f POS Z %f\n", object->pos.x, object->pos.y, object->pos.z);
	printf("\n\n\n");
}