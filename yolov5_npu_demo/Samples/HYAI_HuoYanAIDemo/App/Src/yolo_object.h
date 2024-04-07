#ifndef _YOLO_OBJECT_3516_H_
#define _YOLO_OBJECT_3516_H_

#include "dhop_type_def.h"

typedef struct {
    DH_Int32        id;
    DH_Int32        state;
    DH_Rect16       rect;
    DH_Rect16       actual;
    DH_Int32        classId;
    float   conf;
} obj_info_t;

extern const char *g_yolo_object_list[14];

extern char g_modelfile[];

void fillBuffer(char* buffer, int* len);

#endif
