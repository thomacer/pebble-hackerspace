#include "./globals.h"

Tuple* t_space = NULL;

SensorsArray* sensors_array = NULL;
Contacts* contacts_section = NULL;

SpaceState open_state = Undefined;

char buffer[32];
char* space_name_buffer = buffer;
