#include "tree.h"

#define PRINT_UNDEFINE_OP_VALUE                                    \
    printf("Undefined OP value = [%s]\n", get_value_of_object(objs_, start_root->get_data()))

#define PRINT_UNDEFINE_TYPE                                     \
    printf("Undefined type of object = [%s]\n", get_type_of_object(start_root->get_data()->type_of_object))

#define PRINT_UNDEFINE_FUNC                                     \
    printf("Undefinied func = [%s]\n", get_value_of_object(objs_, start_root->get_data()))



#define ADD_OR_SUB(obj, left, right)                            \
    create_root(obj, left, right)

#define ADDITION(obj, left, right)                              \
    create_root(obj, left, right)

#define MULTIPLY(obj, left, right)                              \
    create_root(obj, left, right)

#define dR                                                      \
    differenciate(start_root->get_right())

#define dL                                                      \
    differenciate(start_root->get_left())

#define POWER()                                                 \
    create_root()

#define copyL                                                   \
    copy_subtree(start_root->get_left())

#define copyR                                                   \
    copy_subtree(start_root->get_right())

#define CR_ADD                                                  \
    create_object(OPERATOR, OP_PLUS_VAL)
    
#define CR_NUMBER(value)                                        \
    create_root(create_object(NUMBER, value))

#define GET_VAL                                                 \
    start_root->get_data_value()

#define GET_TYPE                                                \
    start_root->get_data_type()

void Objs_destructor(struct Objects* objs);

Object* create_object(int type, int value);

tree_element* create_root(struct Object* obj, tree_element* left = nullptr, tree_element* right = nullptr, tree_element* prev = nullptr);

Object* create_object(int type, int value)
{
    struct Object* obj = new Object;

    obj->type_of_object = type;
    obj->value = value;

    return obj;
}

tree_element* create_root(struct Object* obj, tree_element* left, tree_element* right, tree_element* prev)
{
    tree_element* root = new tree_element;
    
    root->set_left(left);

    if(left)
        left->set_prev(root);

    root->set_right(right);
    
    if(right)
        right->set_prev(root);

    root->set_data(obj);

    root->set_prev(prev);

    return root;
}

tree_element* tree::differenciate(tree_element* start_root)
{
    switch (GET_TYPE)
    {
        case OPERATOR:
        {
            switch (GET_VAL)
            {
                case OP_MIN_VAL:
                case OP_PLUS_VAL:
                    return ADD_OR_SUB(create_object(OPERATOR, GET_VAL), dL, dR);
                
                case OP_TIMES_VAL:
                    return ADDITION(CR_ADD, 
                                    MULTIPLY(create_object(OPERATOR, OP_TIMES_VAL), dL, copyR), 
                                    MULTIPLY(create_object(OPERATOR, OP_TIMES_VAL), dR, copyL) 
                                   );
                case OP_POW_VAL: // WORKD ONLY IF 2^x, not for x^2. I NEED TO ADD DIFFERENT CASES OR 1 GENERAL
                {
                    printf("%p\n", start_root);
                    tree_element* tmp = create_root(create_object(OPERATOR, OP_TIMES_VAL),
                        create_root(create_object(OPERATOR, OP_TIMES_VAL), differenciate(copyR), create_root(create_object(FUNCTION, LN_VAL), copyL)),
                        copy_subtree(start_root));
                    return tmp;
                }
                default:
                    PRINT_UNDEFINE_OP_VALUE;
            }
            break;
        }
        case NUMBER:
            return CR_NUMBER(0);

        case VARIABLE:
            return CR_NUMBER(1);
        case FUNCTION:
        {
            switch (GET_VAL)
            {
                case LN_VAL:
                    return create_root(create_object(OPERATOR, OP_DEL_VAL), differenciate( copy_subtree(start_root->get_left()) ), copy_subtree(start_root->get_left())   );

                default:
                    PRINT_UNDEFINE_FUNC;
            }
        }
        default:
            PRINT_UNDEFINE_TYPE;
    }
    
    printf("Something bad in diff\n");
    return nullptr;
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
        case NUMBER:
            return "Number";
        case BRACKET:
            return "Bracket";
        case VARIABLE:
            return "Variable";
        case FUNCTION:
            return "Function";
        default:
            return "UNINDENTIFIED TYPE";
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
                return "(";
            case R_BRACKET_VAL:
                return ")";
            case OP_PLUS_VAL:
                return "+";
            case OP_MIN_VAL:
                return "-";
            case OP_TIMES_VAL:
                return "*";
            case OP_DEL_VAL:
                return "/";
            case OP_POW_VAL:
                return "^";
            case SIN_VAL:
                return "sin";
            case COS_VAL:
                return "cos";
            case LN_VAL:
                return "ln";
            default:
                return "UNINDENTIFIED TYPE";
        }
    }

}

tree_element* tree::get_expression()
{
    tree_element* tmp_element_1 = nullptr;
    
    if ((objs_->obj[cur_size_].type_of_object == OPERATOR) && ((objs_->obj[cur_size_].value == OP_MIN_VAL) || (objs_->obj[cur_size_].value == OP_PLUS_VAL)))
    {
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
        tmp_element_1 = get_operator();
    }

    if (cur_size_ >= objs_->number_of_objects)
        return tmp_element_1;

    tree_element* tmp_element = new tree_element;

    do
    {
        if (objs_->obj[cur_size_].type_of_object == BRACKET)
        {
            if (objs_->obj[cur_size_].value == R_BRACKET_VAL)
            {
                if ((tmp_element->get_left() == nullptr) && (tmp_element->get_right() == nullptr))
                {
                    tmp_element = tmp_element_1;
                    return tmp_element;
                }
                else
                {
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
            if ((tmp_element->get_left() != nullptr) && (tmp_element->get_right() != nullptr))
            {
                tree_element* new_tmp_element = new tree_element;

                new_tmp_element->set_data(&(objs_->obj[cur_size_])); 

                new_tmp_element->set_right(tmp_element);
                tmp_element->set_prev(new_tmp_element);

                tree_element* tmp_element_2 = nullptr;
                
                cur_size_++;

                tmp_element_2 = get_operator();

                new_tmp_element->set_left(tmp_element_2);
                tmp_element_2->set_prev(new_tmp_element);

                tree_element* swap = tmp_element;
                tmp_element = new_tmp_element;
                new_tmp_element = swap;
            }
            else if ((tmp_element->get_left() == nullptr) && (tmp_element->get_right() == nullptr))
            {
                tmp_element->set_data(&(objs_->obj[cur_size_]));

                tmp_element->set_right(tmp_element_1);
                tmp_element_1->set_prev(tmp_element);
                
                cur_size_++;
                tree_element* tmp_element_2 = nullptr;
                tmp_element_2 = get_operator();

                tmp_element->set_left(tmp_element_2);
                tmp_element_2->set_prev(tmp_element);

            }
            else
            {
                printf("I HAVE BAD LOGIC(((\n");
            }
        }
        else
        {
            printf("NEED cur_Size_++\n");
            printf("type = %d\nvalue = %d\n", objs_->obj[cur_size_].type_of_object, objs_->obj[cur_size_].value);
            break;
        }
        

    } while ((objs_->obj[cur_size_].type_of_object == OPERATOR) && ((objs_->obj[cur_size_].value == OP_MIN_VAL) || (objs_->obj[cur_size_].value == OP_PLUS_VAL)));

    return tmp_element;
}

tree_element* tree::get_operator()
{
    tree_element* tmp_element_1 = get_pow();
    tree_element* tmp_element = new tree_element;

    if ((objs_->obj[cur_size_].type_of_object == OPERATOR) && ((objs_->obj[cur_size_].value == OP_TIMES_VAL) || (objs_->obj[cur_size_].value == OP_DEL_VAL)))
    {
        tmp_element->set_right(tmp_element_1);
        tmp_element_1->set_prev(tmp_element);
    }
    else
    {
        delete tmp_element;
        return tmp_element_1;
    }

    while ((objs_->obj[cur_size_].type_of_object == OPERATOR) && ((objs_->obj[cur_size_].value == OP_TIMES_VAL) || (objs_->obj[cur_size_].value == OP_DEL_VAL)))
    {
        if ((tmp_element->get_left() != nullptr))
        {
            tree_element* new_tmp_element = new tree_element;
         
            new_tmp_element->set_data(&(objs_->obj[cur_size_])); 
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
            tmp_element->set_data(&(objs_->obj[cur_size_]));

            cur_size_++;
            tree_element* tmp_element_2 = nullptr;
            tmp_element_2 = get_pow();

            tmp_element->set_left(tmp_element_2);
            tmp_element_2->set_prev(tmp_element);

        }
    }

    return tmp_element;
}

tree_element* tree::get_pow()
{
    tree_element* tmp_element_1 = nullptr;

    tmp_element_1 = get_bracket(); 

    if ((objs_->obj[cur_size_].type_of_object == OPERATOR) && (objs_->obj[cur_size_].value == OP_POW_VAL)) // if   "^"
    {
        tree_element* tmp_element_2 = nullptr;
        tree_element* tmp_element = new tree_element;

        tmp_element->set_data(&(objs_->obj[cur_size_]));

        cur_size_++;
        
        tmp_element_2 = get_pow(); 

        tmp_element->set_left(tmp_element_1);
        tmp_element->set_right(tmp_element_2);

        tmp_element_1->set_prev(tmp_element);
        tmp_element_2->set_prev(tmp_element);

        return tmp_element;
    }

    return tmp_element_1;

}

tree_element* tree::get_bracket()
{
    tree_element* tmp_element = nullptr;

    if (objs_->obj[cur_size_].type_of_object == BRACKET)
    {
        cur_size_++;

        tmp_element = get_expression();
        
        if (objs_->obj[cur_size_].type_of_object != BRACKET)
            printf("ERROR IN BRACKETS!! WARNING!!!!\n");
        else
            cur_size_++;

        return tmp_element;
    }
    else
    {
        tmp_element = get_func();

        if (tmp_element == nullptr) // Не выделилась память в get_func
            return nullptr;
    }

}

tree_element* tree::get_func()
{
    tree_element* tmp_element = nullptr;

    if ((objs_->obj[cur_size_].type_of_object == NUMBER) || (objs_->obj[cur_size_].type_of_object == VARIABLE))
    {
        tmp_element = get_number();
    }
    else if (objs_->obj[cur_size_].type_of_object == FUNCTION)
    {
        switch (objs_->obj[cur_size_].value)
        {
        case LN_VAL:
        {
            tmp_element = create_root(create_object(FUNCTION, objs_->obj[cur_size_++].value), get_bracket());
            break;
        }
        default:
            printf("Undefined type of function\ntype = %d\n", objs_->obj[cur_size_].value);
            return nullptr;
        }

        
    }
    else
    {
        printf("Troubles in get_func()\n");
        return nullptr;
    }

    return tmp_element;
}

tree_element* tree::get_number()
{
    tree_element* tmp_element = new tree_element;
    
    tmp_element->set_data(&(objs_->obj[cur_size_]));

    cur_size_++;

    return tmp_element; 
}