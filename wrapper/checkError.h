#pragma once

#ifdef DEBUG
#define GL_CALL(func) func; checkError();
#else
#define GL_CALL_RET(func) func;
#endif

void checkError();

