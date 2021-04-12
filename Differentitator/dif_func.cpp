#include "dif.h"

//_CRT_SECURE_NO_WARNINGS

struct Objects* fill_structures(FILE* text)
{
	assert(text && "Nullptr file in fill_structures");

	int space_counter = 0;

	char* buffer = make_buffer(text); // !!! calloc memory by new char[..];

	printf("buffer = [%s]\n", buffer);
	printf("strlen = [%d]\n", strlen(buffer));
	if(buffer[strlen(buffer)] == '\0')
		printf("last is a zero\n");
	else printf("last isNOT a  zero\n");

	int i = 0;
	while (buffer[i] != '\0')
	{
		//printf("[%c]", buffer[i]);
		if (isspace(buffer[i]))
		{
			printf("[[%d]]\n", buffer[i]);
			space_counter++;
			i++;
		}
		else i++;
	}
	printf("Number of spaces = %d\n", space_counter);
	printf("Another symbols = %d\n", strlen(buffer) - space_counter);	// GOOD
	struct Object* obj = new Object[strlen(buffer) - space_counter] ;	//(Object*) calloc(number_of_objects, sizeof(Object));
	assert(obj && "Can't new[] memory for *obj");
	
	int obj_counter = 0;

	printf("buffer = [%s]\n", buffer);


	for (int i = 0; buffer[i] != '\0'; i++)
	{
		printf("i = %d\nbuffer[%d] = [%c]\n\n", i, i, buffer[i]);
		if (isspace(buffer[i]))
			continue;
		else if (buffer[i] == ')')
		{
			printf("))))))))))))))))\n");
			obj[obj_counter].type_of_object = BRACKET;
			obj[obj_counter++].value = R_BRACKET_VAL;
		}
		else if (buffer[i] == '(')
		{
			printf("((((((((((((((\n");
			obj[obj_counter].type_of_object = BRACKET;
			obj[obj_counter++].value = L_BRACKET_VAL;
		}
		else if (buffer[i] == '+')
		{
			printf("++++++++++++\n");
			//printf("here buffer[%d] = [%c]\n", i, buffer[i]);
			obj[obj_counter].type_of_object = OPERATOR;
			obj[obj_counter++].value = OP_PLUS_VAL;
		}
		else if (buffer[i] == '-')
		{
			printf("--------\n");
			obj[obj_counter].type_of_object = OPERATOR;
			obj[obj_counter++].value = OP_MIN_VAL;
		}
		else if (buffer[i] == '*')
		{
			printf("**********\n");
			obj[obj_counter].type_of_object = OPERATOR;
			obj[obj_counter++].value = OP_TIMES_VAL;
		}
		else if (buffer[i] == '/')
		{
			printf("/////////////\n");
			obj[obj_counter].type_of_object = OPERATOR;
			obj[obj_counter++].value = OP_DEL_VAL;
		}
		else if (buffer[i] == '^')
		{
			printf("^^^^^^^^^^^\n");
			obj[obj_counter].type_of_object = OPERATOR;
			obj[obj_counter++].value = OP_POW_VAL;
		}
		else if (buffer[i] == '+')
		{
			printf("in PLUUUUUUS\n");
			obj[obj_counter].type_of_object = OPERATOR;
			obj[obj_counter++].value = OP_PLUS_VAL;
		}
		else if (buffer[i] == 'x')
		{
			printf("VARIABLE\n");
			obj[obj_counter].type_of_object = VARIABLE;
			obj[obj_counter++].value = 666;
		}
		else if (isdigit(buffer[i]))
		{
			printf("DIGIT\n");
			obj[obj_counter].type_of_object = NUMBER;
			obj[obj_counter++].value = atoi(&buffer[i]);

			while (isdigit(buffer[i]))
			{
				printf("number = %d\n", buffer[i]);
				i++;
			}
			i--;
		}
		else
		{
			printf("Error\n");
		}


	}

	obj_counter;

	printf("obj_counter = %d\n", obj_counter);
 

	delete[] buffer;
	//delete[] obj;

	Objects* objs = new Objects[1];

	objs->obj = obj;
	objs->number_of_objects = obj_counter;

	return objs;
}

void print_objects(Objects* object)
{
	assert(object && "U passed nullptr object to print_objects()");
	printf("\n\n");

	for (int i = 0; i < object->number_of_objects; i++)
	{
		switch (object->obj[i].type_of_object)
		{
		case OPERATOR:
			printf("%d. type is OPERATOR, value is %d\n", i, object->obj[i].value);
			break;
		case NUMBER:
			printf("%d. type is NUMBER, value is %d\n", i, object->obj[i].value);
			break;
		case BRACKET:
			printf("%d. type is BRACKET, value is %d\n", i, object->obj[i].value);
			break;
		case VARIABLE:
			printf("%d. type is VARIABLE, value is %d\n", i, object->obj[i].value);
			break;
		default:
			printf("UNINDENTIFIED TYPE\n");
			break;
		}
	}



	return;
}

long size_of_file(FILE* user_code)
{
	assert(user_code);

	fseek(user_code, 0, SEEK_END);
	long file_length = ftell(user_code);
	fseek(user_code, 0, SEEK_SET);

	return file_length;
}

char* make_buffer(FILE* file)
{
	//FILE* database = nullptr;// fopen("database.txt", "rb")
	//fopen_s(&database, name_file, "rb");
	
	assert(file && "file in nullptr in make_buffer");

	long file_length = size_of_file(file);

	char* buffer = new char[file_length + 1] {0};
	assert(buffer && "Can't calloc memory for buffer");

	fread(buffer, sizeof(char), file_length, file);

	//buffer[file_length - 1] = '\0';
	return buffer;
}