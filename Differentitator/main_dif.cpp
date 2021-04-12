#include "dif.h"

int main(int argc, int argv[])
{
	FILE* text = fopen("text.txt", "r");
	//fopen_s(&text, "text.txt", "rb");

	assert(text && "Can't open text.txt file");


	Objects* objs = fill_structures(text);

	//Objects* obj = objs->obj;

	print_objects(objs);

	
	
	delete[] objs->obj;
	

	for (int i = 0; i < NUMBER_OF_VARIABLES; i++)
	{
		//printf("p = %p", objs->variables_names[i]);
		delete[] objs->variables_names[i];
	}

	delete[] objs;

	return 0;
}