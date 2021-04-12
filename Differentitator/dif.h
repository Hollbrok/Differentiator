#pragma once

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "dif_config.h"

struct Objects* fill_structures(FILE* text);

void print_objects(Objects* object);

long size_of_file(FILE* user_code);

char* make_buffer(FILE* file);