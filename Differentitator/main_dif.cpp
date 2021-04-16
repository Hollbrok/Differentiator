#include "dif.h"
#include "tree.h"

int main(int argc, int argv[])
{
	FILE* text = fopen("text.txt", "r");
	//fopen_s(&text, "text.txt", "rb");

	assert(text && "Can't open text.txt file");


	Objects* objs = fill_structures(text);

	//Objects* obj = objs->obj;

	print_objects(objs);

	tree dif_tree("main_differenciator");

	dif_tree.fill_tree(objs);
	
	tree_element* new_tree_root = dif_tree.differenciate(dif_tree.get_root());

	tree* new_tree = new tree;

	new_tree->set_root(new_tree_root);
	new_tree->objs_ = dif_tree.objs_;

	new_tree->print_tree();

	//Objs_destructor(objs);

	return 0;
}