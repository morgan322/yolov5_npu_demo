#include "yolo_object.h"
#include <stdio.h>

const char *g_yolo_object_list[14] =
{
    "overflow",
    "bottle",
    "bag",
     "paper",
     "bucket",
    "carton",
    "knapsack",
    "others",
    "blue",
    "red",
    "other",
    "person",
    "bicycle",
    "arm"

};

char g_modelfile[] = "./model/Volt_nnie.nnx";

void fillBuffer(char* buffer, int* len)
{
    int length = *len;
    length += sprintf(buffer + length, "{\"id\":0, \"name\":\"person\"},");
    length += sprintf(buffer + length, "{\"id\":1, \"name\":\"car\"},");
    length += sprintf(buffer + length, "{\"id\":2, \"name\":\"motorcycle\"}");
    *len = length;
}