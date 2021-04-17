#include "tree.h"

const double exp_value = 2.7182818284;

bool is_free_objs = false;

#define PRINT_UNDEFINE_OP_VALUE                                 \
    printf("Undefined OP value = [%s]\n", get_value_of_object(objs_, start_root->get_data()))

#define PRINT_UNDEFINE_TYPE                                     \
    printf("Undefined type of object = [%s]\n", get_type_of_object(start_root->get_data()->type_of_object))

#define PRINT_UNDEFINE_FUNC                                     \
    printf("Undefinied func = [%s]\n", get_value_of_object(objs_, start_root->get_data()))

#define ADD_OR_SUB(obj, left, right)                            \
    create_root(obj, left, right)

#define ADDITION(left, right)                                   \
    create_root(CR_ADD, left, right)

#define MULTIPLY(left, right)                                   \
    create_root(CR_MUL, left, right)

#define EXPONENTIATION(left, right)                             \
    create_root(CR_MUL, left, right)

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

#define copyF                                                   \
    copy_subtree(start_root)

#define CR_LN                                                   \
    create_object(FUNCTION, LN_VAL)

#define CR_MUL                                                  \
    create_object(OPERATOR, OP_TIMES_VAL)

#define CR_ADD                                                  \
    create_object(OPERATOR, OP_PLUS_VAL)
    
#define CR_NUMBER(value)                                        \
    create_root(create_object(NUMBER, value))

#define GET_VAL                                                 \
    start_root->get_data_value()

#define GET_TYPE                                                \
    start_root->get_data_type()

void tree::make_article()
{
    assert(this && "Can't do article without tree");

    FILE* tex = fopen("main.tex", "wb");
    assert(tex && "Can't open main.tex file");

    print_title(tex);
    print_1_section(tex);
    print_2_section(tex);

    //!! main_print(tex);

    print_conclusion(tex);

    print_used_books(tex);

    fprintf(tex, "\\end{document}\n");

    fclose(tex);

    system("iconv.exe -t UTF-8 -f CP1251 < main.tex > temp_main.tex");
    system("del main.tex");
    system("ren temp_main.tex main.tex");
    system("pdflatex main.tex");
    system("start main.pdf");

   
    return;

}

void print_title(FILE* tex)
{
    assert(tex);

    fprintf(tex, "\\documentclass[a4paper,12pt]{article} \n"
        "\n"
        "\n"
        "\n"
        "\\usepackage[utf8]{inputenc}\n"
        "\\usepackage[english, russian]{babel}\n"
        "\\usepackage{caption}\n"
        "\\usepackage{listings}\n"
        "\\usepackage{amsmath,amsfonts,amssymb,amsthm,mathtools }\n"
        "\\usepackage{wasysym}\n"
        "\\usepackage{graphicx}\n"
        "\\usepackage{float} \n"
        "\\usepackage{wrapfig} \n"
        "\\usepackage{fancyhdr} \n"
        "\\usepackage{lscape}\n"
        "\\usepackage{xcolor}\n"
        "\\usepackage[normalem]{ ulem }\n"
        "\\usepackage{hyperref}\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\\hypersetup\n"
        "{\n"
        "    colorlinks = true,\n"
        "    linkcolor = blue,\n"
        "    filecolor = magenta,\n"
        "    urlcolor = blue\n"
        "}\n"
        "\n"
        "\n"
        "\\pagestyle{fancy}\n"
        "\\fancyhead{}\n"
        "\\fancyhead[L]{ 2.2.8 }\n"
        "\\fancyhead[R]{ Талашкевич Даниил, 2 положительная группа крови}\n"
        "\\fancyfoot[C]{ \\thepage }\n"
        "\n"
        "\n"
        "\n"
        "\\begin{document}\n"
        "\n"
        "\n"
        "\\begin{titlepage}\n"
        "\n"
        "\\newpage\n"
        "\\begin{center}\n"
        "\\normalsize Московский физико - технический институт //госудраственный университет)\n"
        "\\end{center}\n"
        "\n"
        "\\vspace{6em}\n"
        "\n"
        "\\begin{center}\n"
        "\\Large Домашняя работа по Физической культуре\\\\\n"
        "\\end{center}\n"
        "\n"
        "\\vspace{1em}\n"
        "\n"
        "\\begin{center}\n"
        "\\large \\textbf{ Исследование термических эффектов,\n"
        "возникающих при упругих деформациях[2.2.8] }\n"
        "\\end{center}\n"
        "\n"
        "\\vspace{2em}\n"
        "\n"
        "\\begin{center}\n"
        "\\large П$ ^ 3$ : Полная Полтрашка Патриковна и Талашкевич Даниил Александрович \\\\\n"
        "Группа Б01 - \\href{ https://vk.com/rt_kiska }{\\textbf{Гладим киску каждый день}}\n"
        "\\end{center}\n"
        "\n"
        "\\vspace{\\fill}\n"
        "\n"
        "\\begin{center}\n"
        "    \\large Иерусалим \\\\ 2 век до н.э.\n"
        "\\end{center}\n"
        "\n"
        "\\end{titlepage}\n"
        "\n"
        "\n"
        "\n"
        "    \\thispagestyle{empty}\n"
        "    \\newpage\n"
        "    \\tableofcontents\n"
        "    \\newpage\n"
        "    \\setcounter{page}{1}\n"
        "\n"
        "\n");


    return;
}

void print_1_section(FILE* tex)
{
    assert(tex);

    fprintf(tex, "\\section{Введение в историю Иерусалима}\n\n"
        "Древнейшая часть Иерусалима была заселена в 4 - м тысячелетии до н.э.,"
        " что делает его одним из древнейших городов мира.За свою долгую историю,"
        " Иерусалим был как минимум дважды разрушен, 23 раза осаждён, 52 раза атакован"
        " и 44 раза завоёван либо вновь отвоёван.В разное время городом владели Израильское царство,"
        " Иудейское царство, Вавилон, Персидская империя и империя Александра Македонского, Египет Птолемеев,"
        " Сирия Селевкидов.После еврейского восстания во II веке до н.э.на некоторое время было восстановлено"
        " Иудейское Царство, но уже в 6 году н.э.на месте него была провозглашена римская провинция Иудея."
        " Вслед за распадом Римской империи, Иерусалим отошёл к Византии.После Византии город принадлежал"
        " арабским халифатам, крестоносцам, государствам Айюбидов и мамлюков, Османской и затем Британской"
        " империям, Иордании и, наконец, Израилю. Учитывая центральное место, отводимое Иерусалиму как"
        " еврейским(сионизм), так и палестинским национализмом, на избирательность, неизбежную при"
        " резюмировании более чем 5000 - летней истории его населённости, часто накладывается идеологическая"
        " предвзятость или предшествующий опыт авторов.Еврейские периоды истории города важны для израильских"
        " националистов, дискурс которых предполагает, что современные евреи происходят от израэлитов и"
        " Маккавеев в то время как исламский, христианский и другие нееврейские периоды его истории важны"
        " для палестинского национализма, дискурс которого производит современных палестинцев от всех"
        " разнообразных народов, населявших регион В результате каждая из сторон утверждает, что история"
        " города была политизирована оппонентами, дабы подкрепить притязания последних на город, и что это"
        " подтверждается разностью акцентов, придаваемых различными авторами разнообразным событиям и эрам в истории города.\n\n");


    return;
}

void print_2_section(FILE* tex)
{
    assert(tex);

    fprintf(tex, "\\section{Как древние греки считали производные}\n"
        "Для того, чтобы вычислять производную греки поступили очень умно :"
        " они построили машину времени, переместились в 2021 год н.э., затем"
        " на крысичях украли мой \textbf{ exe } - шник и данную статью с подробнейшим"
        " описанием как искать ее в 2021 году, затем вернулись обратно и сковозь долгие"
        " годы они научились все - таки ее брать.Вы наверное подумаете, что это все чисто"
        " воды обман и выдумка, но у меня есть на то доказательства : \\newpage\n"
        "\n \\begin{figure}[h]\n"
        " \\center{ \\includegraphics[scale = 1]{proof.jpg} }\n"
        " \\label{ photo1:1 }\n"
        " \\end{figure}\n\n"
        " На данном фото видно, как они внаглую просто переписывают мой код!!!!"
        " P.S.Фото взято из архивов национального музея наследний ЮНЕСКО\n\n");

    return;
}

void print_conclusion(FILE* tex)
{
    assert(tex);

    fprintf(tex, "\\section{Заключение}\n"
        " При выполнение домашней работы по физической культуре"
        " я узнал про историю Иерусалима, познакомился с тем,"
        " как греки считали производные, а так же сам научился"
        " считать производную по шагам!\n");

    return;
}

void print_used_books(FILE* tex)
{
    assert(tex);

    fprintf(tex, "\\section{Используемые тренажеры}\n"
        " \\begin{enumerate}\n"
        " \\item Скакалка\n"
        " \\item Эскандер\n"
        " \\item Крижометр (отдельное спасибо Крижовичу за то, что предоставил его мне!)\n"
        " \\item Коксовая дорожка\n"
        " \\end{enumerate}\n");

    return;
}

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
                    return ADDITION(MULTIPLY(dL, copyR), MULTIPLY(dR, copyL));

                case OP_POW_VAL: // NOW ITS GENERAL. Am I need add not only general method but differ cases to 2^x, x^2, x^f(x) ...
                    return EXPONENTIATION(differenciate(create_root(CR_MUL, copyR, create_root(CR_LN, copyL))), copyF);
                
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

    struct Object* obj = new Object;
    obj->type_of_object = start_element->get_data()->type_of_object;
    obj->value = start_element->get_data()->value;

    new_start->set_data(obj);

    if ((start_element->get_left() == nullptr) && (start_element->get_right() == nullptr))
    {
        return new_start;
    }
    if (start_element->get_left() != nullptr)
    {
        tree_element* left_subtree = copy_subtree(start_element->get_left());
        new_start->set_left(left_subtree);
        left_subtree->set_prev(new_start);
    }
    if (start_element->get_right() != nullptr)
    {
        tree_element* right_subtree = copy_subtree(start_element->get_right());
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

    this->set_right(tmp);

    return tmp;
}

tree_element::tree_element(data_type data, tree_element* prev, tree_element* left, tree_element* right) :
    data_(data),
    prev_(prev),
    left_(left),
    right_(right)
{
}

tree_element::~tree_element()
{
    assert(this && "You passed nullptr to ~tree_element");
    data_ = POISON;

    prev_ = nullptr;
    left_ = nullptr;
    right_ = nullptr;
    
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
    if (!is_free_objs)
    {
        Objs_destructor(objs_);
        is_free_objs = true;
    }
   
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

    print_all_elements_beauty(root, dump, objs_);
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
    }
    if (tmp->get_right())
    {
        print_all_elements(tmp->get_right(), dump, objs);
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"Right\", fontcolor=darkblue]\n", tmp, tmp->get_right());
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

void print_all_elements_beauty(tree_element* tmp, FILE* dump, struct Objects* objs)
{
    assert(tmp && "tmp is nullptr in print_all_elements");

    if (tmp->get_left())
    {
        print_all_elements_beauty(tmp->get_left(), dump, objs);
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"Left\", fontcolor=darkblue]\n", tmp, tmp->get_left());
    }
    if (tmp->get_right())
    {
        print_all_elements_beauty(tmp->get_right(), dump, objs);
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"Right\", fontcolor=darkblue]\n", tmp, tmp->get_right());
    }

    if ((tmp->get_right() == nullptr) && (tmp->get_left() == nullptr))
    {
            if (tmp ->get_data()->type_of_object != NUMBER)
                fprintf(dump, "\"%p\" [label = \"%s\",style = filled, fillcolor = lightgreen] \n", tmp, get_value_of_object(objs, tmp->get_data()));
            else
                fprintf(dump, "\"%p\" [label = \"%d\",style = filled, fillcolor = lightgreen] \n", tmp, tmp->get_data()->value);
    }
    else
    {
        if (tmp->get_prev() == nullptr)
        {
            if (tmp->get_data()->type_of_object != NUMBER)
                fprintf(dump, "\"%p\" [label = \"%s\",style = filled, fillcolor = red] \n", tmp, get_value_of_object(objs, tmp->get_data()));
            else
                fprintf(dump, "\"%p\" [label = \"%d\",style = filled, fillcolor = red] \n", tmp, tmp->get_data()->value);
        }
        else
        {
            if ((tmp->get_data()->type_of_object == OPERATOR) && (tmp->get_data()->value == OP_TIMES_VAL))
                fprintf(dump, "\"%p\" [label = \"%s\",style = filled, fillcolor = lightblue] \n", tmp, get_value_of_object(objs, tmp->get_data()));
            else if (tmp->get_data()->type_of_object != NUMBER)
                fprintf(dump, "\"%p\" [label = \"%s\",style = filled, fillcolor = purple] \n", tmp, get_value_of_object(objs, tmp->get_data()));
            else
                fprintf(dump, "\"%p\" [label = \"%d\",style = filled, fillcolor = purple] \n", tmp, tmp->get_data()->value);
        }
    }

    return;
}

void tree::fill_tree(struct Objects* main_object, bool need_print)
{
    assert(this && "Nullptr in tree");
    assert(main_object && "nullptr Objects struct");

    objs_ = main_object;

    root_ = get_expression();

    if(need_print)
        show_tree();

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
            case EXP_VAL:
                return "exp";
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

                new_tmp_element->set_left(tmp_element);
                tmp_element->set_prev(new_tmp_element);

                tree_element* tmp_element_2 = nullptr;
                
                cur_size_++;

                tmp_element_2 = get_operator();

                new_tmp_element->set_right(tmp_element_2);
                tmp_element_2->set_prev(new_tmp_element);

                tree_element* swap = tmp_element;
                tmp_element = new_tmp_element;
                new_tmp_element = swap;
            }
            else if ((tmp_element->get_left() == nullptr) && (tmp_element->get_right() == nullptr))
            {
                tmp_element->set_data(&(objs_->obj[cur_size_]));

                tmp_element->set_left(tmp_element_1);
                tmp_element_1->set_prev(tmp_element);
                
                cur_size_++;
                tree_element* tmp_element_2 = nullptr;
                tmp_element_2 = get_operator();

                tmp_element->set_right(tmp_element_2);
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