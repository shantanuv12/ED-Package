/*Header file containing all the functions required for printing data on screen for OpenGL Windows*/

void printv(va_list args, const char* format);
void print(const char* format, ...);
void printAt(int x, int y, const char* format, ...);
void errCheck(char* where);
