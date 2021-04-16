#include "tree.h"

void Objs_destructor(struct Objects* objs);

tree_element* tree::differenciate(tree_element* start_root)
{
    //tree* dif_tree = new tree;// ("update tree");
    //dif_tree->objs_ = objs_;

    switch (start_root->get_data()->type_of_object)
    {
    case OPERATOR:
    {
        switch (start_root->get_data()->value)
        {
        case OP_MIN_VAL:
        case OP_PLUS_VAL:
        {
            //tree_element* root = dif_tree.add_to_left(nullptr, root_->get_data());
            tree_element* root = new tree_element;

            //root->set_data(start_root->get_data());
            struct Object* obj = new Object;

            obj->type_of_object = OPERATOR;
            obj->value = start_root->get_data()->value;
            root->set_data(obj);
            //dif_tree->set_root(root);
            //dif_tree->set_cur_size(dif_tree->get_cur_size() + 1);

            
            root->set_left(differenciate(start_root->get_left()));        //(dif_tree->differenciate(start_root->get_left())->get_root());
            root->get_left()->set_prev(root);

            root->set_right(differenciate(start_root->get_right()));  //(dif_tree->differenciate(start_root->get_right())->get_root());
            root->get_right()->set_prev(root);

            return root;//return dif_tree;
            break;
        }
        case OP_TIMES_VAL:
        {
            tree_element* root = new tree_element;

            tree_element* copy_of_left = copy_subtree(start_root->get_left());
            tree_element* copy_of_right = copy_subtree(start_root->get_right());

            tree_element* left_subtree = copy_subtree(start_root->get_left());
            tree_element* right_subtree = copy_subtree(start_root->get_right());

            struct Object* obj = new Object[3];

//            struct Object* plus_op = new Object;

            obj[0].type_of_object = OPERATOR;
            obj[0].value = OP_PLUS_VAL;

            //struct Objects* objs = new Objects;

       
            //= plus_op;
       
            //objs->variables_names = nullptr;

            root->set_data(&obj[0]); // OP +



            //dif_tree->set_root(root);

            tree_element* left_mul = new tree_element;
            tree_element* right_mul = new tree_element;

     //       struct Object* left_mul_op = new Object;

            obj[1].type_of_object = OPERATOR;
            obj[1].value = OP_TIMES_VAL;

           // struct Object* right_mul_op = new Object;

            obj[2].type_of_object = OPERATOR;
            obj[2].value = OP_TIMES_VAL;

            left_mul->set_data(&obj[1]);
            left_mul->set_prev(root);

            right_mul->set_data(&obj[2]);
            right_mul->set_prev(root);
            //objs->obj = obj;
            //objs->number_of_objects = 3;

            //tree_element* left_mul = new tree_element;
            //left_mul->set_data(&obj[1]);
            root->add_to_left(left_mul);

            //tree_element* right_mul = new tree_element;
            //right_mul->set_data(&obj[2]);
            root->add_to_right(right_mul);

            //  /\ GOOD
            //  ||
            tree_element* left_dif = differenciate(start_root->get_left());
            left_mul->set_left(left_dif);        //(dif_tree->differenciate(start_root->get_left())->get_root());
            left_dif->set_prev(left_mul);

           
            //
            //!!!
            left_mul->set_right(right_subtree);
            printf("1.%p , right_data = %d\n", left_mul->get_right(), left_mul->get_right()->get_data()->value);
            //!!!
            right_subtree->set_prev(left_mul);
            printf("2.%p , right_data = %d\n", left_mul->get_right(), left_mul->get_right()->get_data()->value);
            

            // Тут всю хорошо, со след строчки гг <- no
            tree_element* right_dif = differenciate(start_root->get_right());
            right_mul->set_left(right_dif);        //(dif_tree->differenciate(start_root->get_left())->get_root());
            printf("3.%p , right_data = %d\n", left_mul->get_right(), left_mul->get_right()->get_data()->value);


            right_dif->set_prev(right_mul);
            printf("4.%p , right_data = %d\n", left_mul->get_right(), left_mul->get_right()->get_data()->value);
            
            //tree_element* left_subtree = copy_subtree(start_root->get_left());
            
            right_mul->set_right(left_subtree);
            left_subtree->set_prev(right_mul);
            printf("5.%p , right_data = %d\n", left_mul->get_right(), left_mul->get_right()->get_data()->value);
            root->set_left(left_mul);
            root->set_right(right_mul);

           // dif_tree->objs_ = objs;

            return root; //return dif_tree;
            break;
        }
        default:
            printf("Undefined OP = [%s]\n", get_type_of_object(start_root->get_data()->value));
            break;
        }
        break;
    }
    case NUMBER: // MAY BE I NEED TO CREATE FULL NEW ELEMENT
    {    
        tree_element* root = new tree_element;
        
        struct Object* obj = new Object;
        obj->type_of_object = NUMBER;//start_root->get_data()->type_of_object;
        obj->value = 0;
        //root->add_to_right(start_root->get_data());

        //dif_tree->set_cur_size(dif_tree->get_cur_size() + 1);
        root->set_data(obj);
        //root->get_data()->value = 0;

        return root;//return dif_tree;
    }
    case VARIABLE:
    {
        tree_element* root = new tree_element; //dif_tree->add_to_right(nullptr, start_root->get_data());
        
        struct Object* obj = new Object;
        struct Objects* objs = new Objects;

        obj->type_of_object = NUMBER;
        obj->value = 1;

        root->set_data(obj);

        objs->obj = obj;
        objs->number_of_objects = 1;

        //dif_tree->objs_ = objs;
       // root->get_data()->value = 1;
       // root->get_data()->type_of_object = NUMBER;

        //dif_tree->set_root(root);
        
        return root;//return dif_tree;
        
        break;
    }
    default:
        printf("Undefinied type of object\n");
        break;
    }
    
    printf("Something bad in diff\n");
    return nullptr;//return dif_tree;
}

tree_element* tree_element::copy_subtree(tree_element* start_element)
{
    tree_element* new_start = new tree_element;
    //new_start->set_data(start_element->get_data());

    printf("3 if\n");
    //delete new_start;
    struct Object* obj = new Object;
    obj->type_of_object = start_element->get_data()->type_of_object;
    obj->value = start_element->get_data()->value;

    new_start->set_data(obj);

    if ((start_element->get_left() == nullptr) && (start_element->get_right() == nullptr))
    {
        return new_start;
        //new_start->set_prev(start_element->get_prev());
        //return new_start;
    }
    if (start_element->get_left() != nullptr)
    {
        printf("1 if\n");
        tree_element* left_subtree = copy_subtree(start_element->get_left());
        new_start->set_left(left_subtree);
        //new_start->add_to_left(left_subtree);//new_start->set_right(copy_right_subtree(start_element->get_right()));
        left_subtree->set_prev(new_start);
    }
    if (start_element->get_right() != nullptr)
    {
        printf("2 if\n");
        tree_element* right_subtree = copy_subtree(start_element->get_right());
        //new_start->add_to_right(right_subtree);//new_start->set_right(copy_right_subtree(start_element->get_right()));
        new_start->set_right(right_subtree);
        right_subtree->set_prev(new_start);
    }

    return new_start;
}

tree_element* tree_element::add_to_left(tree_element* new_element)
{
    assert(this && "You passed nullptr tree");

    tree_element* tmp = new tree_element;
    assert(tmp && "Can't calloc memory for tree_element");

    tmp->set_prev(this);
    tmp->set_right(nullptr);
    tmp->set_left(nullptr);
    //tmp->set_data(number);

    this->set_left(tmp);

    return tmp;
}

tree_element* tree_element::add_to_right(tree_element* new_element)
{
    assert(this && "You passed nullptr tree");

    tree_element* tmp = new tree_element;
    assert(tmp && "Can't calloc memory for tree_element");

    tmp->set_prev(this);
    tmp->set_right(nullptr);
    tmp->set_left(nullptr);
    //tmp->set_data(number);

    this->set_right(tmp);

    return tmp;
}

tree_element::tree_element(data_type data, tree_element* prev, tree_element* left, tree_element* right) :
    data_(data),
    prev_(prev),
    left_(left),
    right_(right)
{
    //assert(this && "You passed nullptr to list_elem construct");
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
        printf("STRANGE  AFAGAGGG\n");
        //delete[] data_;
        //data_ = nullptr;
    }
    if (false)
    {
        //delete this;
        //this = nullptr;
    }

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
    printf("%s\n", __FUNCSIG__);
    // assert(root_);

    if (root_)
         root_->free_all();
    else
        printf("No free\n");

    if (false)
    {
        delete this;
    }
    if (objs_)
    {
        Objs_destructor(objs_);
    }
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

tree_element* tree::add_to_left(tree_element* x, tree_element* new_element)
{
    assert(this && "You passed nullptr tree");

    //tree_element* tmp = new tree_element;
    //assert(tmp && "Can't calloc memory for tree_element");

    if ((x == nullptr) && (cur_size_ == 0))
    {
        root_ = new_element;

        new_element->set_prev(x);
        new_element->set_right(nullptr);
        new_element->set_left(nullptr);
        //new_element->set_data(number);

        cur_size_++;
    }
    else if (cur_size_ && new_element)
    {
        new_element->set_prev(x);
        new_element->set_right(nullptr);
        new_element->set_left(nullptr);
        //tmp->set_data(number);

        cur_size_++;

        x->set_left(new_element);
    }
    else
        printf("You must pass x\n");

    return new_element;
}

tree_element* tree::add_to_right(tree_element* x, tree_element* new_element)
{
    assert(this && "You passed nullptr tree");

    //tree_element* tmp = new tree_element;
    //assert(tmp && "Can't calloc memory for tree_element");

    if ((x == nullptr) && (cur_size_ == 0))
    {
        root_ = new_element;

        new_element->set_prev(x);
        new_element->set_right(nullptr);
        new_element->set_left(nullptr);
        //new_element->set_data(number);

        cur_size_++;
    }
    else if (cur_size_ && new_element)
    {
        new_element->set_prev(x);
        new_element->set_right(nullptr);
        new_element->set_left(nullptr);
        //tmp->set_data(number);

        cur_size_++;

        x->set_right(new_element);
    }
    else
        printf("You must pass x\n");

    return new_element;
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

    //tree_element* tmp = root_;

    print_all_elements(root_, dump, objs_);
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

void print_all_elements(tree_element* tmp, FILE* dump, struct Objects* objs)
{
    assert(tmp && "tmp is nullptr in print_all_elements");

    
    if (tmp->get_left())
    {
        print_all_elements(tmp->get_left(), dump, objs);
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"Left\", fontcolor=darkblue]\n", tmp, tmp->get_left());
        //fprintf(dump, "\"%p\" -> \"%p\" [label=\"Right\", fontcolor=darkblue]\n", tmp->get_left(), (tmp->get_left())->get_prev());
    }
    if (tmp->get_right())
    {
        print_all_elements(tmp->get_right(), dump, objs);
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"Right\", fontcolor=darkblue]\n", tmp, tmp->get_right());
        //fprintf(dump, "\"%p\" -> \"%p\" [label=\"Left\", fontcolor=darkblue]\n", tmp->get_right(), (tmp->get_right())->get_prev());
    }

    if ((tmp->get_right() == nullptr) && (tmp->get_left() == nullptr))
    {
        if (tmp->get_prev() != nullptr)
        {
            if (tmp->get_data()->type_of_object != NUMBER)
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%s]}| {<f1> left| <here> prev| right}| {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = lightgreen] \n", tmp, get_type_of_object(tmp->data_->type_of_object), get_value_of_object(objs, tmp->get_data()), tmp->get_left(), tmp->get_prev(), tmp->get_right());
            else
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%d]}| {<f1> left| <here> prev| right}| {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = lightgreen] \n", tmp, get_type_of_object(tmp->data_->type_of_object), tmp->get_data()->value, tmp->get_left(), tmp->get_prev(), tmp->get_right());
        }
        else
        {
            if (tmp->get_data()->type_of_object != NUMBER)
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%s]}| {<f1> left| right}| {<f2> [%p]| [%p]}\",style = filled, fillcolor = red] \n", tmp, get_type_of_object(tmp->data_->type_of_object), get_value_of_object(objs, tmp->get_data()), tmp->get_left(), tmp->get_right());
            else
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%d]}| {<f1> left| right}| {<f2> [%p]| [%p]}\",style = filled, fillcolor = red] \n", tmp, get_type_of_object(tmp->data_->type_of_object), tmp->get_data()->value, tmp->get_left(), tmp->get_right());
        }
    }
    else
    {
        if (tmp->get_prev() == nullptr)
        {
            if (tmp->get_data()->type_of_object != NUMBER)
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%s]}| {<f1> left| right}| {<f2> [%p]| [%p]}\",style = filled, fillcolor = red] \n", tmp, get_type_of_object(tmp->data_->type_of_object), get_value_of_object(objs, tmp->get_data()), tmp->get_left(), tmp->get_right());
            else
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%d]}| {<f1> left| right}| {<f2> [%p]| [%p]}\",style = filled, fillcolor = red] \n", tmp, get_type_of_object(tmp->data_->type_of_object), tmp->get_data()->value, tmp->get_left(), tmp->get_right());
        }
        else
        {
            if ((tmp->get_data()->type_of_object == OPERATOR) && (tmp->get_data()->value == OP_TIMES_VAL))
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%s]}| {<f1> left| <here> prev| right}| {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = lightblue] \n", tmp, get_type_of_object(tmp->data_->type_of_object), get_value_of_object(objs, tmp->get_data()), tmp->get_left(), tmp->get_prev(), tmp->get_right());
            else if (tmp->get_data()->type_of_object != NUMBER)
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%s]}| {<f1> left| <here> prev| right}| {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = purple] \n", tmp, get_type_of_object(tmp->data_->type_of_object), get_value_of_object(objs, tmp->get_data()), tmp->get_left(), tmp->get_prev(), tmp->get_right());
            else
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%d]}| {<f1> left| <here> prev| right}| {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = purple] \n", tmp, get_type_of_object(tmp->data_->type_of_object), tmp->get_data()->value, tmp->get_left(), tmp->get_prev(), tmp->get_right());
        }
    }

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


    //tree_element* tmp_element = new tree_element;

    //struct Object* tmp_object= new struct Object;

    //tmp_object->type_of_object = main;
    //tmp_object->type_of_object = main_object->obj[0].value;

    //tmp_element->data_ = &(main_object->obj[0]); //->set_data((main_object->obj)[0]);
  
    //root_ = tmp_element;
    objs_ = main_object;

    root_ = get_expression();
    //printf("\n\n root = %p\n\n", root_);
    print_tree();

    //delete tmp_object;
    //delete tmp_element;

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

const char* get_value_of_object(struct Objects* objs, struct Object* obj) 
{
    //const char* message = {};//nullprt;
    
    if (obj->type_of_object == VARIABLE)
    {
        return objs->variables_names[obj->value];
    }
    else
    {
        switch (obj->value)
        {
        case L_BRACKET_VAL:
        {
           // message = "(";
            return "(";
            break;
        }
        case R_BRACKET_VAL:
        {
            return ")";
            break;
        }
        case OP_PLUS_VAL:
        {
            return "+";
            break;
        }
        case OP_MIN_VAL:
        {
            return "-";
            break;
        }
        case OP_TIMES_VAL:
        {
            return "*";
            break;
        }
        case OP_DEL_VAL:
        {
            return "/";
            break;
        }
        case OP_POW_VAL:
        {
            return "^";
            break;
        }
        default:
        {
            return "UNINDENTIFIED TYPE";
            break;
        }
        }
    }

}

tree_element* tree::get_expression()
{
    //printf("Total size is =  %d , cur_size = %d\n", objs_->number_of_objects, cur_size_);
    //printf("get_express\n");
    tree_element* tmp_element_1 = nullptr; // new tree_element;
    
    if ((objs_->obj[cur_size_].type_of_object == OPERATOR) && ((objs_->obj[cur_size_].value == OP_MIN_VAL) || (objs_->obj[cur_size_].value == OP_PLUS_VAL)))
    {
        //printf("first operator\n");
        tree_element* tmp_element = new tree_element;
        tmp_element->set_data(&(objs_->obj[cur_size_]));

        tree_element* tmp_element_2 = nullptr;

        cur_size_++;

        tmp_element_2 = get_operator();

        tmp_element->set_right(tmp_element_1);
        tmp_element->set_left(tmp_element_2);
        
        return tmp_element;
    }
    else
    {
        //printf("no +/- , go to get_op\n");
        //printf("probably value is [%d]\n", objs_->obj[cur_size_].value);
        tmp_element_1 = get_operator();
        //printf("leave from no +/- . tmp_1 = [%d]\n", tmp_element_1->get_data()->value);
        //cur_size_++;
    }
    if (cur_size_ >= objs_->number_of_objects)
        return tmp_element_1;
    tree_element* tmp_element = new tree_element;

    do
    {
        //printf("In DO\n");
        if (objs_->obj[cur_size_].type_of_object == BRACKET)
        {
            //printf("find leave bracket. LEAVE\n");
            if (objs_->obj[cur_size_].value == R_BRACKET_VAL)
            {
                if ((tmp_element->get_left() == nullptr) && (tmp_element->get_right() == nullptr))
                {
                    //delete tmp_element;
                    tmp_element = tmp_element_1;
                    //printf("leave from get_express(1) because of )\n");
                    return tmp_element;
                }
                else
                {
                    //printf("leave from get_express(2) because of )\n");
                    return tmp_element;
                }
            }
            else
            {
                printf("BAD BRACKETS in get_express\n");
            }
        }

        if ((objs_->obj[cur_size_].type_of_object == OPERATOR) && ((objs_->obj[cur_size_].value == OP_MIN_VAL) || (objs_->obj[cur_size_].value == OP_PLUS_VAL)))
        {
            //printf("find +/-\n");
            
            if ((tmp_element->get_left() != nullptr) && (tmp_element->get_right() != nullptr))
            {
                //printf("L and R isNOT nullptr\n");
                tree_element* new_tmp_element = new tree_element;

                //tmp_element->set_data(&(objs_->obj[cur_size_]));

                new_tmp_element->set_data(&(objs_->obj[cur_size_])); //set_left(tmp_element);
                //printf("new_tmp = [%s]\n", get_value_of_object(objs_, &(objs_->obj[cur_size_])));

                new_tmp_element->set_right(tmp_element);
                tmp_element->set_prev(new_tmp_element);

                tree_element* tmp_element_2 = nullptr;
                
                cur_size_++;

                tmp_element_2 = get_operator();
                //printf("tmp_2 = [%s]\n", get_value_of_object(objs_, &(objs_->obj[cur_size_])));

                new_tmp_element->set_left(tmp_element_2);
                tmp_element_2->set_prev(new_tmp_element);

                tree_element* swap = tmp_element;
                tmp_element = new_tmp_element;
                new_tmp_element = swap;
            }
            else if ((tmp_element->get_left() == nullptr) && (tmp_element->get_right() == nullptr))
            {
               // printf("L and R nullptr\n");
                tmp_element->set_data(&(objs_->obj[cur_size_]));

                tmp_element->set_right(tmp_element_1);
                tmp_element_1->set_prev(tmp_element);
                
                //printf("tmp = [%s]\n", get_value_of_object(objs_, &(objs_->obj[cur_size_])));

                cur_size_++;
                tree_element* tmp_element_2 = nullptr;
                tmp_element_2 = get_operator();
                //printf("tmp_2 = [%p]\n", tmp_element_2);
                //printf("tmp_2 = [%d]\n", tmp_element_2->get_data()->value);

                tmp_element->set_left(tmp_element_2);
                tmp_element_2->set_prev(tmp_element);

            }
            else
            {
                printf("I HAVE BAD LOGIC(((\n");
                //printf("right = %p , left = %p\n", tmp_element->get_left(), tmp_element->get_right());
            }
        }
        else
        {
            printf("NEED cur_Size_++\n");
            //cur_size_++;
            break;
        }
        

    } while ((objs_->obj[cur_size_].type_of_object == OPERATOR) && ((objs_->obj[cur_size_].value == OP_MIN_VAL) || (objs_->obj[cur_size_].value == OP_PLUS_VAL)));
    
    //printf("objs_->[cur_size_].type_of_object = %d\nvalue = %d\n", objs_->obj[cur_size_].type_of_object, objs_->obj[cur_size_].value);
        
    //printf("tmp_elem = %p\n", tmp_element);
    //printf("tmp_elem->left = %p, value = %d\n", tmp_element, tmp_element->get_left()->get_data()->value);
   // printf("tmp_elem->right = %p, value = %d\n", tmp_element, tmp_element->get_right()->get_data()->value);
    //printf("leave from get_express (2) \n");
    return tmp_element;
}

tree_element* tree::get_operator()
{
    //printf("get_operator\n");
    tree_element* tmp_element_1 = get_pow();
    tree_element* tmp_element = new tree_element;

    if ((objs_->obj[cur_size_].type_of_object == OPERATOR) && ((objs_->obj[cur_size_].value == OP_TIMES_VAL) || (objs_->obj[cur_size_].value == OP_DEL_VAL)))
    {
        //tmp_element->set_data(objs_->obj[cur_size_]);
        //tree_element* tmp_element = new tree_element;
        tmp_element->set_right(tmp_element_1);
        tmp_element_1->set_prev(tmp_element);
        //printf("will * or /\n");
    }
    else
    {
        delete tmp_element;
        //printf("else\n");
        //printf("return tmp_element.data = %d\n", (tmp_element_1->get_data())->value);
        //printf("tmp_1 = [%p]\n", tmp_element_1);
        //printf("leave from get_operator (1)\n");
        return tmp_element_1;
    }

    while ((objs_->obj[cur_size_].type_of_object == OPERATOR) && ((objs_->obj[cur_size_].value == OP_TIMES_VAL) || (objs_->obj[cur_size_].value == OP_DEL_VAL)))
    {
        //printf("find * or /\n");
        if ((tmp_element->get_left() != nullptr))
        {
            tree_element* new_tmp_element = new tree_element;
           // printf("set data !=nullptr\n");
            new_tmp_element->set_data(&(objs_->obj[cur_size_])); //set_left(tmp_element);
            new_tmp_element->set_right(tmp_element);
            tmp_element->set_prev(new_tmp_element);

            tree_element* tmp_element_2 = nullptr;

            cur_size_++;

            tmp_element_2 = get_pow();

            new_tmp_element->set_left(tmp_element_2);
            tmp_element_2->set_prev(new_tmp_element);

            tree_element* swap = tmp_element;
            tmp_element = new_tmp_element;
            new_tmp_element = swap;
        }
        else
        {
            //printf("set data == nullptr\n");
            tmp_element->set_data(&(objs_->obj[cur_size_]));
            
            //tmp_element->set_right(tmp_element_1);
            //tmp_element_1->set_prev(tmp_element);

            cur_size_++;
            tree_element* tmp_element_2 = nullptr;
            tmp_element_2 = get_pow();

            tmp_element->set_left(tmp_element_2);
            tmp_element_2->set_prev(tmp_element);

        }

        /*tree_element* tmp_element = new tree_element;
        tree_element* tmp_element_2 = nullptr;

        tmp_element->set_data(&(objs_->obj[cur_size_]));
        printf("is *? [%s]\n", get_value_of_object(objs_, &(objs_->obj[cur_size_])));
        cur_size_++;

        tmp_element_2 = get_pow();

        tmp_element->set_right(tmp_element_1);
        tmp_element->set_left(tmp_element_2);

        printf("leave from get_operator (2)\n");
        return tmp_element;*/

    }

   // printf("return tmp_element.data = %d\n", (tmp_element->get_data())->value);
   // printf("tmp = [%p]\n", tmp_element);
    //printf("leave from get_operator (2)\n");
    return tmp_element;
}

tree_element* tree::get_pow()
{
    //printf("get_pow\n");
    tree_element* tmp_element_1 = nullptr;

    tmp_element_1 = get_bracket(); 
    //cur_size_++;
    //->set_left(get_bracket());

    if ((objs_->obj[cur_size_].type_of_object == OPERATOR) && (objs_->obj[cur_size_].value == OP_POW_VAL)) // if   "^"
    {
        //printf("find pow oper\n");
        //tmp_element->set_left(get_bracket()); // get_expression()
        tree_element* tmp_element_2 = nullptr;
        tree_element* tmp_element = new tree_element;

        tmp_element->set_data(&(objs_->obj[cur_size_]));

        cur_size_++;
        
       // printf("tmp_2 before get_expression\n");
        tmp_element_2 = get_pow(); //->set_right(get_bracket());
        //printf("tmp_2 after get_expression\n");

        tmp_element->set_right(tmp_element_1);
        tmp_element->set_left(tmp_element_2);

        tmp_element_1->set_prev(tmp_element);
        tmp_element_2->set_prev(tmp_element);


        //printf("leave from get_pow (2)\n");
        return tmp_element;
    }

    //printf("leave from get_pow (1), value = %d\n", tmp_element_1->get_data()->value);
   // printf("tmp_1 = [%p]\n", tmp_element_1);
    return tmp_element_1;

}

tree_element* tree::get_bracket()
{
    //printf("get_bracket\n");
    tree_element* tmp_element = nullptr;

    if (objs_->obj[cur_size_].type_of_object == BRACKET)
    {
       // printf("find bracket\n");
        cur_size_++;

        tmp_element = get_expression();
        //printf("AFTER FULL BRACKET\n");
        
        if (objs_->obj[cur_size_].type_of_object != BRACKET)
            printf("ERROR IN BRACKETS!! WARNING!!!!\n");
        else
            cur_size_++;

        //printf("leave from get_bracket (hard)\n");
        return tmp_element;
    }
    else
    {
        //printf("leave from get_bracket (simple)\n");
        return get_number();
    }
    //printf("tmp_element = [%p]");
    //printf("leave from get_braket\n");
    //return tmp_element;
}

tree_element* tree::get_number()
{
    //printf("get_number\n");
    tree_element* tmp_element = new tree_element;
    
    //tmp_element = objs_->obj[cur_size];

    tmp_element->set_data(&(objs_->obj[cur_size_]));

    cur_size_++;

    //printf("leave from get_number, value = %d\n", tmp_element->get_data()->value);
    //printf("type is [%s]\n", get_type_of_object(tmp_element->get_data()->type_of_object));
    return tmp_element; //tmp_element;
}