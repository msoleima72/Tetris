#include 


void addSquare(int index, vec2 left_top_point, vec3 color , vec2 *shapes, vec3 *shapes_color);

void initshapeI( int index, vec2 left_top_point, vec3 color,vec2 *shapes, vec3 *shapes_color);

void initShapeT( int index, vec2 left_top_point, vec3 color,vec2 * shapes,vec3* shapes_color);

void initShapes(void);

void initLine(void);

void initGrid (void);

void initTriangle (void);

void CreateVAOshapes(void);

void CreatVAOTriangles(void);

void CreatVAOLines(void);

void CreatVAOGrid(void);

void init( void );
//----------------------------------------------------------------------------

void display( void );

//----------------------------------------------------------------------------

void moveDown(int shape_index);

void moveLeft(int shape_index);

void moveRight(int shape_index);


void rotateShape(int index, vec2* shapes);

//timed function. We intended to execute this every one second.
void rotateDelay(int);
//If you want to use arrows, take a look at this function
//It works similarly, but you have no acess to the ASCII keys using it. Please see the link below for details.
//https://www.opengl.org/resources/libraries/glut/spec3/node54.html
void keyboardSpecial( int key, int x, int y );

//bind most keys on your keyboard to this function
void keyboard( unsigned char key, int x, int y );