#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include "Includes.h"

#define POISON nullptr

using data_type = struct Object*;
const int MAX_QUESTION_SIZE = 30;

class tree_element
{
private:

	tree_element* prev_ = nullptr;

	tree_element* left_ = nullptr;
	tree_element* right_ = nullptr;


public:

	data_type data_ = POISON;

	tree_element(data_type data = 0, tree_element* prev = nullptr,
		tree_element* left = nullptr, tree_element* right = nullptr);

	~tree_element();


	void set_data(data_type new_data) { data_ = new_data; };

	void set_left(tree_element* new_left) { left_ = new_left; };
	void set_right(tree_element* new_right) { right_ = new_right; };

	void set_prev(tree_element* new_prev) { prev_ = new_prev; };

	const data_type& get_data()     const { assert(this && "You passed nullptr to get_data()"); return data_; };

	const tree_element* get_left()  const { assert(this && "nullptr tree_element in get_next()"); return left_; };
	const tree_element* get_right() const { assert(this && "nullptr tree_element in get_next()"); return right_; };
	const tree_element* get_prev()  const { assert(this && "nullptr tree_element in get_prev()"); return prev_; };

	data_type non_const_get_data() { assert(this && "You passed nullptr to get_data()"); return data_; };

	data_type& get_data() { assert(this && "You passed nullptr to get_data()"); return data_; };

	VALUE get_data_value() { return data_->value; };
	TYPE get_data_type() { return data_->type_of_object; };

	tree_element* get_left() { assert(this && "nullptr tree_element in get_next()"); return left_; };
	tree_element* get_right() { assert(this && "nullptr tree_element in get_next()"); return right_; };
	tree_element* get_prev() { assert(this && "nullptr tree_element in get_prev()"); return prev_; };

	void build_prev_connections(tree_element* root);

	void print_elem(FILE* database);

	void free_all();

	bool get_user_answer();

	tree_element* copy_subtree(tree_element* start_element);

	tree_element* copy_left_subtree(tree_element* start_element);

	tree_element* copy_right_subtree(tree_element* start_element);

	tree_element* add_to_left(tree_element* new_element);

	tree_element* add_to_right(tree_element* new_element);

};

class tree:tree_element
{
private:

	size_t cur_size_ = 0;
	size_t error_state_ = 0;
	const char* name_ = nullptr;

	tree_element* root_ = nullptr;

public:
	struct Objects* objs_ = nullptr;

	
	tree(const char* name = "differenciator");
	~tree();

	void set_cur_size(int number) { cur_size_ = number; };
	int get_cur_size() { return cur_size_; };

	tree_element* add_to_right(tree_element* x, data_type number);
	tree_element* add_to_left(tree_element* x, data_type number);

	tree_element* add_to_left(tree_element* x, tree_element* new_element);
	tree_element* add_to_right(tree_element* x, tree_element* new_element);


	tree_element* get_root() { return root_; };
	void		  set_root(tree_element* new_root) { root_ = new_root; };

	void print_tree(bool need_graphviz_dump = true)
		const;

	void graphviz_dump(const char* dumpfile_name = "dump.dot")
		const;

	void graphviz_beauty_dump(const char* dumpfile_name)
		const;


	void show_tree() const;

	void fill_tree(Objects* main_object);

	tree_element* get_expression();

	tree_element* get_operator();

	tree_element* get_pow();

	tree_element* get_bracket();

	tree_element* get_func();

	tree_element* get_number();

	tree_element* differenciate(tree_element* new_root);

};


void print_all_elements_beauty(tree_element* tmp, FILE* dump);

long size_of_file(FILE* user_code);
char* make_buffer(const char* name_file);

void free_all(tree_element* root);

void print_all_elements(tree_element* tmp, FILE* dump, struct Objects* objs);

const char* get_type_of_object(TYPE type);
const char* get_value_of_object(struct Objects* objs, struct Object* obj);

#endif // TREE_H_INCLUDED