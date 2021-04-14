#include "tree.h"


tree_element::tree_element(data_type data, tree_element* prev, tree_element* left, tree_element* right) :
    data_(data),
    prev_(prev),
    left_(left),
    right_(right)
{
    assert(this && "You passed nullptr to list_elem construct");
}

tree_element::~tree_element()
{
    assert(this && "You passed nullptr to ~tree_element");
    data_ = POISON;

    prev_ = nullptr;
    left_ = nullptr;
    right_ = nullptr;

    if (data_)
    {
        printf("STRANGEAFAGAGGG\n");
        //delete[] data_;
        //data_ = nullptr;
    }
   // if (this)
    //{
     //   delete this;
        //this = nullptr;
    //}

}

tree::tree(const char* name) :
    cur_size_(0),
    error_state_(0),
    name_(name),
    root_(nullptr)
    //buffer_(nullptr)
{
    assert(this && "You passed nullptr to constructor");
    assert(name && "You need to pass name");
}

tree::~tree()
{
    assert(this && "nullptr in desctructor");

    // assert(root_);

    if (root_)
         root_->free_all();
    else
        printf("No free\n");
        /*
    if (buffer_)
    {
        delete[] buffer_;
        buffer_ = nullptr;
    }
    else
        printf("No buffer\n");
        */

    cur_size_ = -1;
    error_state_ = -1;
    name_ = nullptr;
    root_ = nullptr;
}

void tree_element::free_all()
{
    assert(this);
    if (get_left())
        left_->free_all();
    if (get_right())
        right_->free_all();

    if (data_)
    {
        //printf("delete\n");
        //delete data_;
        //data_ = nullptr;
    }
    if (this)
        delete this;
    else
        printf("root is nullptr");

    return;
}

tree_element* tree::add_to_left(tree_element* x, data_type number)
{
    assert(this && "You passed nullptr tree");

    tree_element* tmp = new tree_element;
    assert(tmp && "Can't calloc memory for tree_element");

    if ((x == nullptr) && (cur_size_ == 0))
    {
        root_ = tmp;

        tmp->set_prev(x);
        tmp->set_right(nullptr);
        tmp->set_left(nullptr);
        tmp->set_data(number);

        cur_size_++;
    }
    else if (cur_size_ && tmp)
    {
        tmp->set_prev(x);
        tmp->set_right(nullptr);
        tmp->set_left(nullptr);
        tmp->set_data(number);

        cur_size_++;

        x->set_left(tmp);
    }
    else
        printf("You must pass x\n");

    return tmp;
}

tree_element* tree::add_to_right(tree_element* x, data_type number)
{
    assert(this && "You passed nullptr tree");

    tree_element* tmp = new tree_element;
    assert(tmp && "Can't calloc memory for tree_element");

    if ((x == nullptr) && (cur_size_ == 0))
    {
        root_ = tmp;

        tmp->set_prev(x);
        tmp->set_right(nullptr);
        tmp->set_left(nullptr);
        tmp->set_data(number);

        cur_size_++;
    }
    else if (cur_size_)
    {
        tmp->set_prev(x);
        tmp->set_right(nullptr);
        tmp->set_left(nullptr);
        tmp->set_data(number);

        x->set_right(tmp);

        cur_size_++;
    }
    else
        printf("You must pass x\n");

    return tmp;
}

void tree::print_tree(bool need_graphviz_dump) const
{
    if (need_graphviz_dump)
    {
        graphviz_dump("dump.dot");

        system("iconv.exe -t UTF-8 -f  CP1251 < dump.dot > dump_temp.dot");
       
        system("dot dump_temp.dot -Tpdf -o dump.pdf");
       
        system("del dump.dot");
      
        system("ren dump_temp.dot dump.dot");
 
        system("dump.pdf");

    }

    return;
}

void tree::graphviz_dump(const char* dumpfile_name) const
{
    assert(dumpfile_name && "You passed nullptr dumpfile_name");

    FILE* dump = fopen(dumpfile_name, "wb");
    assert(dump && "Can't open dump.dot");

    fprintf(dump, "digraph %s {\n", name_);
    fprintf(dump, "node [color = Red, fontname = Courier, style = filled, shape=record, fillcolor = purple]\n");
    fprintf(dump, "edge [color = Blue, style=dashed]\n");

    tree_element* tmp = root_;

    print_all_elements(tmp, dump);
    fprintf(dump, "}\n");

    fclose(dump);

    //graphviz_dump("dump.dot");
    //printf("1");

    return;
}

void tree::show_tree() const
{
    graphviz_beauty_dump("beauty_tree.dot");

    system("iconv.exe -t UTF-8 -f  CP1251 < beauty_tree.dot > beauty_tree_temp.dot");
    system("dot beauty_tree_temp.dot -Tpdf -o beauty_dump.pdf");
    system("del beauty_tree.dot");
    system("ren beauty_tree_temp.dot beauty_tree.dot");

    system("beauty_dump.pdf");
}

void tree::graphviz_beauty_dump(const char* dumpfile_name) const
{
    assert(dumpfile_name && "You passed nullptr dumpfile_name");

    FILE* dump = fopen(dumpfile_name, "wb");
    assert(dump && "Can't open dump.dot");

    fprintf(dump, "digraph %s {\n", name_);
    fprintf(dump, "node [color = Red, fontname = Courier, style = filled, shape=ellipse, fillcolor = purple]\n");
    fprintf(dump, "edge [color = Blue, style=dashed]\n");

    tree_element* root = root_;

    print_all_elements_beauty(root, dump);
    fprintf(dump, "}\n");

    fclose(dump);
    return;
}

char* make_buffer(const char* name_file)
{
    FILE* database = fopen("database.txt", "rb");
    assert(database && "Can't open database.txt");

    long file_length = size_of_file(database);

    char* buffer = new char[file_length + 1];
    assert(buffer && "Can't calloc memory for buffer");

    fread(buffer, sizeof(char), file_length, database);
    return buffer;
}

void tree_element::print_elem(FILE* database)
{
    assert(database);
    assert(this);

    fprintf(database, "[\n");

    if (get_left() != nullptr)
    {
        //fprintf(database, "?%.*s?\n", length_, data_);
        get_left()->print_elem(database);
    }

    if (get_right() != nullptr)
        get_right()->print_elem(database);

    if ((get_right() == nullptr) && (get_left() == nullptr))
        //fprintf(database, "`%.*s`\n", length_, data_);

    fprintf(database, "]\n");

    return;
}

void print_all_elements(tree_element* tmp, FILE* dump)
{
    assert(tmp && "tmp is nullptr in print_all_elements");

    if (tmp->get_right())
    {
        print_all_elements(tmp->get_right(), dump);
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"yes\", fontcolor=darkblue]\n", tmp, tmp->get_right());
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"yes\", fontcolor=darkblue]\n", tmp->get_right(), (tmp->get_right())->get_prev());
    }
    if (tmp->get_left())
    {
        print_all_elements(tmp->get_left(), dump);
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"No\", fontcolor=darkblue]\n", tmp, tmp->get_left());
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"No\", fontcolor=darkblue]\n", tmp->get_left(), (tmp->get_left())->get_prev());
    }


    if ((tmp->get_right() == nullptr) && (tmp->get_left() == nullptr))
        if(tmp->get_prev() != nullptr)
            fprintf(dump, "\"%p\" [label = \"<f0> TYPE = [%s] | {<f1> left| <here> prev| right}| {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = lightgreen] \n", tmp, get_type_of_object(tmp->data_->type_of_object), tmp->get_left(), tmp->get_prev(), tmp->get_right());
        else
            fprintf(dump, "\"%p\" [label = \"<f0> TYPE = [%s] | {<f1> left| <here> prev| right}| {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = red] \n", tmp, get_type_of_object(tmp->data_->type_of_object), tmp->get_left(), tmp->get_prev(), tmp->get_right());
    else
       if (tmp->get_prev() == nullptr)
           fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | <here> [%p]} | {<f1> right| <here> prev| left}| {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = red] \n", tmp, get_type_of_object(tmp->data_->type_of_object), tmp, tmp->get_left(), tmp->get_prev(), tmp->get_right());
       else
            fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | <here> [%p]} | {<f1> right| <here> prev| left}| {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = purple] \n", tmp, get_type_of_object(tmp->data_->type_of_object), tmp, tmp->get_left(), tmp->get_prev(), tmp->get_right());


    return;

}

void print_all_elements_beauty(tree_element* tmp, FILE* dump)
{
    assert(tmp && "tmp is nullptr in print_all_elements");

    if (tmp->get_right())
    {
        print_all_elements_beauty(tmp->get_right(), dump);
        //fprintf(dump, "\"%p\" -> \"%p\" [label=\"Yes\", fontcolor=darkblue]\n", tmp, tmp->get_right());
    }
    if (tmp->get_left())
    {
        print_all_elements_beauty(tmp->get_left(), dump);
       // fprintf(dump, "\"%p\" -> \"%p\" [label=\"No\", fontcolor=darkblue]\n", tmp, tmp->get_left());
    }

    //if ((tmp->get_right() == nullptr) && (tmp->get_left() == nullptr))
        //fprintf(dump, "\"%p\" [label = \"%.*s\",style = filled, fillcolor = lightgreen] \n", tmp, tmp->length_, tmp->non_const_get_data());
    //else
        //if (tmp->get_prev() == nullptr)
            //fprintf(dump, "\"%p\" [label = \"%.*s\",style = filled, fillcolor = red] \n", tmp, tmp->length_, tmp->non_const_get_data());
        //else
            //fprintf(dump, "\"%p\" [label = \"%.*s\",style = filled, fillcolor = purple] \n", tmp, tmp->length_, tmp->non_const_get_data());
    return;
}

void tree::fill_tree(struct Objects* main_object)
{
    assert(this && "Nullptr in tree");
    assert(main_object && "nullptr Objects struct");


    tree_element* tmp_element = new tree_element;

    //struct Object* tmp_object= new struct Object;

    //tmp_object->type_of_object = main;
    //tmp_object->type_of_object = main_object->obj[0].value;

    //tmp_element->data_ = &(main_object->obj[0]); //->set_data((main_object->obj)[0]);
  
    //root_ = tmp_element;
    objs_ = main_object;

    root_ = get_expression();

    print_tree();

    //delete tmp_object;
    delete tmp_element;

    return;
}

const char* get_type_of_object(TYPE type)
{
    switch (type)
    {
    case OPERATOR:
        return "Operator";
        break;
    case NUMBER:
        return "Number";
        break;
    case BRACKET:
        return "Bracket";
        break;
    case VARIABLE:
        return "Variable";
        break;
    default:
        return "UNINDENTIFIED TYPE";
        break;
    }
}

tree_element* tree::get_expression()
{
    printf("get_express\n");
    tree_element* tmp_element_1 = nullptr; // new tree_element;
    
    if ((objs_->obj[cur_size_].type_of_object == OPERATOR) && ((objs_->obj[cur_size_].value == OP_MIN_VAL) || (objs_->obj[cur_size_].value == OP_PLUS_VAL)))
    {
        tree_element* tmp_element = new tree_element;
        tmp_element->set_data(&(objs_->obj[cur_size_]));

        tree_element* tmp_element_2 = nullptr;

        cur_size_++;

        tmp_element_2 = get_operator();

        tmp_element->set_left(tmp_element_1);
        tmp_element->set_right(tmp_element_2);
        
        return tmp_element;
    }
    else
    {
        tmp_element_1 = get_operator();
    }

    do
    {
        if (objs_->obj[cur_size_].type_of_object == BRACKET)
        {
            if (objs_->obj[cur_size_].value == R_BRACKET_VAL)
                break;
            else
            {
                printf("BAD BRACKETS in get_express\n");
            }
        }

        if ((objs_->obj[cur_size_].type_of_object == OPERATOR) && ((objs_->obj[cur_size_].value == OP_MIN_VAL) || (objs_->obj[cur_size_].value == OP_PLUS_VAL)))
        {
            tree_element* tmp_element = new tree_element;
            tmp_element->set_data(&(objs_->obj[cur_size_]));

            tree_element* tmp_element_2 = nullptr;

            cur_size_++;

            tmp_element_2 = get_operator();

            tmp_element->set_left(tmp_element_1);
            tmp_element->set_right(tmp_element_2);


            printf("leave from get_express (2)\n");
            return tmp_element;
        }


        

    } while ((objs_->obj[cur_size_].type_of_object == OPERATOR) && ((objs_->obj[cur_size_].value == OP_MIN_VAL) || (objs_->obj[cur_size_].value == OP_PLUS_VAL)));

        

    printf("leave from get_express (1) \n");
    return tmp_element_1;
}


tree_element* tree::get_operator()
{
    printf("get_operator\n");
    tree_element* tmp_element_1 = get_pow();

    if ((objs_->obj[cur_size_].type_of_object == OPERATOR) && ((objs_->obj[cur_size_].value == OP_TIMES_VAL) || (objs_->obj[cur_size_].value == OP_DEL_VAL)))
    {
        tree_element* tmp_element = new tree_element;
        tree_element* tmp_element_2 = nullptr;

        tmp_element->set_data(&(objs_->obj[cur_size_]));

        cur_size_++;

        tmp_element_2 = get_pow();

        tmp_element->set_left(tmp_element_1);
        tmp_element->set_right(tmp_element_2);

        printf("leave from get_operator (2)\n");
        return tmp_element;

    }

    printf("leave from get_operator (1)\n");
    return tmp_element_1;
}

tree_element* tree::get_pow()
{
    printf("get_pow\n");
    tree_element* tmp_element_1 = nullptr;

    tmp_element_1 = get_bracket(); 

    //->set_left(get_bracket());

    if ((objs_->obj[cur_size_].type_of_object == OPERATOR) && (objs_->obj[cur_size_].value == OP_POW_VAL)) // if   "^"
    {
        //tmp_element->set_left(get_bracket()); // get_expression()
        tree_element* tmp_element_2 = nullptr;
        tree_element* tmp_element = new tree_element;

        tmp_element->set_data(&(objs_->obj[cur_size_]));

        cur_size_++;
        

        tmp_element_2 = get_bracket(); //->set_right(get_bracket());
    
        tmp_element->set_left(tmp_element_1);
        tmp_element->set_right(tmp_element_2);
        
        printf("leave from get_pow (2)");
        return tmp_element;
    }

    printf("leave from get_pow (1)");
    return tmp_element_1;

}

tree_element* tree::get_bracket()
{
    printf("get_bracket\n");
    tree_element* tmp_element = nullptr;

    if (objs_->obj[cur_size_].type_of_object == BRACKET)
    {
        cur_size_++;

        tmp_element = get_expression();

        if (objs_->obj[cur_size_].type_of_object != BRACKET)
            printf("ERROR IN BRACKETS!! WARNING!!!!\n");
        else
            cur_size_++;
    }
    else
        tmp_element = get_number();

    printf("leave from get_braket");
    return tmp_element;
}

tree_element* tree::get_number()
{
    printf("get_number\n");
    tree_element* tmp_element = new tree_element;
    
    //tmp_element = objs_->obj[cur_size];

    tmp_element->set_data(&(objs_->obj[cur_size_]));

    cur_size_++;

    printf("leave from get_number\n");
    return tmp_element; //tmp_element;
}