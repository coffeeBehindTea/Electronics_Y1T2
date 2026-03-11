#include "DUMMY.h"

int DUMMY_temp_read(char t)
{
    return t == 'h' ? 50 : 30;
}

float DUMMY_weight_read(char cup)
{
    return cup == 'y' ? 12345.0 : 0.0;
}