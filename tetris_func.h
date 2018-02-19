
#include "Angel.h"
static vec3  base_colors[] = {
        vec3( 1.0, 0.0, 0.0 ),
        vec3( 0.0, 1.0, 0.0 ),
        vec3( 0.0, 0.0, 1.0 ),
        vec3( 0.0, 0.0, 0.0 ), //black
        vec3( 1.0, 1.0, 1.0 ), //white
        vec3( 0.5, 0.5, 0.5 ) //grey
};

//width and height of window
const int width = 300;
const int height= 600;

// number of points in a 10X20 grid
const int grid_num = 63;

//three triangles
const int NumPoints = 3;

//and two lines
const int NumPoints1 = 4;

//number of points in a square 
const int square_num=6;

//length of shapes array;
const int shapes_num=24*2;
const int one_shape_num=24;

// Distance between two points on the grid 
/*vec2 right_step[1];
right_step[0] = vec2 (0.2,0.0);*/

//vertex array for the triangles, lines, grid respectively
GLuint vao, vao1,grid_vao, shapes_vao;

//triangle points and colors arrays
vec2 points[NumPoints];
vec3 colors[NumPoints];

//lines points and colors array
vec2 points1[NumPoints1];
vec3 colors1[NumPoints1];

//line points and colors for the grid
vec2 grid[grid_num];
vec3 grid_color[grid_num];

//test
vec2 square_shape[square_num];
vec3 square_color[square_num];

//shapes
vec2 shapes[shapes_num];
vec3 shapes_color[shapes_num];


// Drawing Variable
static vec2 left_top_point= vec2(0.0,-1.0);
static vec2 left_border = vec2(1.0,0.0);
static vec2 right_border =vec2(0.0,0.0);

//move variables
static vec2 down_step = vec2( 0.0, -0.1 );
static vec2 right_step = vec2( 0.2, 0.0 );
static vec2 left_step = vec2( -0.2, 0.0 );

//rotation variable
GLfloat angle = M_PI / 2;
static mat2 rotate10degccw = mat2 ( cos(angle), sin(angle), -sin(angle), cos(angle) );

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