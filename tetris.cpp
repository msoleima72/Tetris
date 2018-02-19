// Two-Dimensional Sierpinski Gasket       
// Generated using randomly selected vertices and bisection

//#include "tetris_func.h"
#include "Angel.h"
#include <cstdlib>

//It is nice to define and use a color pallete on your software. You can put this information on another utility file.
static vec3  base_colors[] = {
                                     // Shape:      // Index
		vec3( 0.6, 0.6, 0.0 ),       // O           // 0
        vec3( 0.0, 0.298, 0.6 ),     // I           // 1
		vec3( 0.0, 0.6, 0.298 ),     // S           // 2
		vec3( 0.0, 0.6, 0.0 ),       // Z           // 3
        vec3( 0.298, 0.0, 0.6 ),     // L           // 4
        vec3( 0.0, 0.6, 0.6 ),       // J           // 5
        vec3( 0.298, 0.6, 0.0 ),     // T           // 6

		vec3( 0.0, 0.0, 0.0 ),       //black        // 7
        vec3( 1.0, 1.0, 1.0 ),       //white        // 8
        vec3( 0.5, 0.5, 0.5 )        //grey         // 9
};

// Boundary check boolians
bool move_right=false;
bool move_left=false;
bool ground=false;

// Keyboard boolians
bool quit=false;

// random shape picker
int shape_index=0;

//width and height of window
const int width = 300;
const int height= 600;

// number of points in a 10X20 grid
const int grid_num = 63;
const int grid_block_num=200;

//three triangles
const int NumPoints = 3;

//number of points in a square 
const int square_num=6;

//length of shapes array;
const int total_numof_shapes=7;
const int shapes_num=24*total_numof_shapes ;
const int one_shape_num=24;
const int all_possible_points=2400;

// Static shapes
int shapes_dropped=0;
int current_static_points_num=0;

//vertex array for the triangles, lines, grid respectively
GLuint grid_vao, shapes_vao, current_shape_vao, static_shapes_vao;

//line points and colors for the grid
vec2 grid[grid_num];
vec3 grid_color[grid_num];

//line points and colors for the grid
vec2 grid_block[21][11];
vec3 grid_block_color[grid_block_num];

//test
vec2 square_shape[square_num];
vec3 square_color[square_num];

//All shapes
vec2 shapes[shapes_num];
vec3 shapes_color[shapes_num];

//Static shapes
vec2 static_shapes[all_possible_points];
vec3 static_shapes_color[all_possible_points];

// current shape
vec2 current_shape[one_shape_num];
vec3 current_shape_color[one_shape_num];


// Drawing Variable
static vec2 left_top_point= vec2(0.0,-1.0);
static vec2 left_border = vec2(1.0,0.0);
static vec2 right_border =vec2(0.0,0.0);

//move variables
static vec2 down_step = vec2( 0.0, -0.1 );
static vec2 up_step = vec2( 0.0, 0.1 );
static vec2 right_step = vec2( 0.2, 0.0 );
static vec2 left_step = vec2( -0.2, 0.0 );

//rotation variable
GLfloat angle = M_PI / 2;
static mat2 rotate10degccw = mat2 ( cos(angle), sin(angle), -sin(angle), cos(angle) );

//---------------------------------------------------------------------------
void initGridBlocks(void){  

    grid_block[0][0]=vec2(-1.0,1.0);


    for (int i=1;i<=20;i++)
        grid_block[i][0]=grid_block[i-1][0]+down_step;
    
        std::cout<< std::endl;

    for(int i =0;i<=20;i++){
        for (int j=1;j<=10;j++)
            grid_block[i][j]=grid_block[i][j-1]+ right_step;
    }
  
    // Print the grid
    for(int i =0;i<=20;i++){
        for (int j=0;j<=10;j++)
            std::cout<< i << "," <<j<< " : " <<grid_block[i][j] << " " ;
        std::cout<< std::endl;
    }  
}

int randomShapePicker(void){
    int index;
    srand(time(NULL));
    index= rand() % total_numof_shapes;
    shape_index=index*one_shape_num;

   // std::cout<< "shape index randomly generated is: "<< index <<std::endl;
    return shape_index;
}

void addSquare(int index, vec2 left_top_point, vec3 color , vec2 *shapes, vec3 *shapes_color){
    square_shape[0] = vec2(0.0,0.0);
    square_shape[1] = vec2(0.2,0.0);
    square_shape[2] = vec2(0.0,0.1);
    square_shape[3] = vec2(0.2,0.0);
    square_shape[4] = vec2(0.0,0.1);
    square_shape[5] = vec2(0.2,0.1);

    int j = 0;

    for(int i=index;j<6;i++){
        shapes[i]=square_shape[j]-left_top_point;
        shapes_color[i]=color;
        j++;
    }

    return;
}

void initShapeO( int index, vec2 left_top_point, vec3 color,vec2 * shapes,vec3* shapes_color){
    

    addSquare(index, left_top_point, color,shapes,shapes_color);

    left_top_point+=right_step;
    //std::cout<< left_top_point<<std::endl;
    
    addSquare(index+square_num, left_top_point, color,shapes,shapes_color);

    left_top_point+=down_step;
    //std::cout<< left_top_point<<std::endl;

    addSquare(index+(2*square_num), left_top_point, color,shapes,shapes_color);
   
    left_top_point+=left_step;
    //std::cout<< left_top_point<<std::endl;

    addSquare(index+(3*square_num), left_top_point, color,shapes,shapes_color);
}

void initshapeI( int index, vec2 left_top_point, vec3 color,vec2 *shapes, vec3 *shapes_color){


    addSquare(index, left_top_point, color, shapes,shapes_color);

    left_top_point+=right_step;
    
    addSquare(index+square_num, left_top_point, color,shapes,shapes_color);

    left_top_point+=right_step;

    addSquare(index+(2*square_num), left_top_point, color,shapes,shapes_color);
   
    left_top_point+=right_step;

    addSquare(index+(3*square_num), left_top_point, color,shapes,shapes_color);
}

void initShapeS( int index, vec2 left_top_point, vec3 color,vec2 * shapes,vec3* shapes_color){
    

    addSquare(index, left_top_point, color,shapes,shapes_color);

    left_top_point+=right_step;
    //std::cout<< left_top_point<<std::endl;
    
    addSquare(index+square_num, left_top_point, color,shapes,shapes_color);

    left_top_point=left_top_point + left_step + down_step;
    //std::cout<< left_top_point<<std::endl;

    addSquare(index+(2*square_num), left_top_point, color,shapes,shapes_color);
   
    left_top_point+=left_step;
    //std::cout<< left_top_point<<std::endl;

    addSquare(index+(3*square_num), left_top_point, color,shapes,shapes_color);
}

void initShapeZ( int index, vec2 left_top_point, vec3 color,vec2 * shapes,vec3* shapes_color){
    

    addSquare(index, left_top_point, color,shapes,shapes_color);

    left_top_point+=right_step;
    //std::cout<< left_top_point<<std::endl;
    
    addSquare(index+square_num, left_top_point, color,shapes,shapes_color);

    left_top_point+=down_step;
    //std::cout<< left_top_point<<std::endl;

    addSquare(index+(2*square_num), left_top_point, color,shapes,shapes_color);
   
    left_top_point+=right_step;
    //std::cout<< left_top_point<<std::endl;

    addSquare(index+(3*square_num), left_top_point, color,shapes,shapes_color);
}

void initShapeL( int index, vec2 left_top_point, vec3 color,vec2 * shapes,vec3* shapes_color){
    

    addSquare(index, left_top_point, color,shapes,shapes_color);

    left_top_point+=down_step;
    
    addSquare(index+square_num, left_top_point, color,shapes,shapes_color);

    left_top_point+=down_step;

    addSquare(index+(2*square_num), left_top_point, color,shapes,shapes_color);
   
    left_top_point+=right_step;

    addSquare(index+(3*square_num), left_top_point, color,shapes,shapes_color);
}

void initShapeJ( int index, vec2 left_top_point, vec3 color,vec2 * shapes,vec3* shapes_color){
    

    addSquare(index, left_top_point, color,shapes,shapes_color);

    left_top_point+=down_step;
    
    addSquare(index+square_num, left_top_point, color,shapes,shapes_color);

    left_top_point+=down_step;

    addSquare(index+(2*square_num), left_top_point, color,shapes,shapes_color);
   
    left_top_point+=left_step;

    addSquare(index+(3*square_num), left_top_point, color,shapes,shapes_color);
}

void initShapeT( int index, vec2 left_top_point, vec3 color,vec2 * shapes,vec3* shapes_color){
    

    addSquare(index, left_top_point, color,shapes,shapes_color);

    left_top_point+=right_step;
    
    addSquare(index+square_num, left_top_point, color,shapes,shapes_color);

    left_top_point+=right_step;

    addSquare(index+(2*square_num), left_top_point, color,shapes,shapes_color);
   
    left_top_point=left_top_point+left_step+down_step;

    addSquare(index+(3*square_num), left_top_point, color,shapes,shapes_color);
}

void initStaticShapes(){
    
    for (int i=0;i<all_possible_points;i+=square_num)
        addSquare(i,vec2(0.0,0.0), base_colors[1], static_shapes, static_shapes_color);   
}

void initCurrentShape(void){

    int index;
    index=randomShapePicker(); //redturns an index which is the starting point in one shape
    //std::cout<<index<<std::endl;
    for (int i=0;i<one_shape_num;i++){
        current_shape[i]= shapes[index];
        //std::cout<< "current point at " << index << " is: " << current_shape[i] << std::endl; 
        current_shape_color[i]=shapes_color[index];
         //std::cout<< "current color point at " << index << " is: " << current_shape_color[i] << std::endl;
        index++;
    }
}

void initShapes(void){

    initGridBlocks();
    initShapeO(0, grid_block[20][10], base_colors[0], shapes,shapes_color);
    initshapeI(one_shape_num, grid_block[20][10], base_colors[1], shapes,shapes_color);  
    initShapeS(2*(one_shape_num), grid_block[20][10], base_colors[2], shapes,shapes_color); 
    initShapeZ(3*(one_shape_num), grid_block[20][10], base_colors[3], shapes,shapes_color);
    initShapeL(4*(one_shape_num), grid_block[20][10], base_colors[4], shapes,shapes_color); 
    initShapeJ(5*(one_shape_num), grid_block[20][10], base_colors[5], shapes,shapes_color); 
    initShapeT(6*(one_shape_num), grid_block[20][10], base_colors[6], shapes,shapes_color);
}

void initGrid (void){

    // Initializing points for the grid


    // Middle lines: vertical line and horizantal line in the middle
    grid[0] = vec2( 0.0, 1.0 );
    grid[1] = vec2( 0.0,-1.0 );
    grid[2] = vec2( 1.0, 0.0 );
    grid[3] = vec2( -1.0, 0.0 );
    //std::cout << grid[0] << " , " << grid[1] << " , " << grid[2] << " , " << grid[3] << std::endl;
 
    // First 20 points for the horizontal lines
    float scale=2.0;
    for (unsigned int i=4;i<=20;i+=4){
        // left side vertical lines
        grid[i] = vec2( scale*(-0.1),-1.0 );
        grid[i+1] = vec2( scale*(-0.1), 1.0 );
        
        // right side vertical lines
        grid[i+2] = vec2( scale*(0.1),-1.0 );
        grid[i+3] = vec2( scale*(0.1), 1.0 );
        scale+=2;

        //std::cout << i << " : " << grid[i] << " , " << grid[i+1] << " , " << grid[i+2] << " , " << grid[i+3] << std::endl;
    }

    // The other 40 points for the vertical lines
    scale = 1.0;
    for (unsigned int i=24;i<=60;i+=4){
        // left side vertical lines
        grid[i] = vec2( -1.0, scale*(-0.1) );
        grid[i+1] = vec2( 1.0, scale*(-0.1) );
        
        // right side vertical lines
        grid[i+2] = vec2( -1.0, scale*(0.1));
        grid[i+3] = vec2(  1.0, scale*(0.1));
        scale+=1;
        //std::cout << i << " : " << grid[i] << " , " << grid[i+1] << " , " << grid[i+2] << " , " << grid[i+3] << std::endl;

    }


    // Set the colour
    for (unsigned int i=0;i<grid_num;i++){
         grid_color[i] = base_colors[9];
    }
    return;
}

void CreateVAOshapes(void){


    glGenVertexArrays( 1, &shapes_vao );
    glBindVertexArray( shapes_vao );

    // Create and bind a buffer object
    GLuint buffer_shapes;
    glGenBuffers( 1, &buffer_shapes );
    glBindBuffer( GL_ARRAY_BUFFER, buffer_shapes );
    

    //glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );
    glBufferData( GL_ARRAY_BUFFER, sizeof(shapes) + sizeof(shapes_color), shapes, GL_STATIC_DRAW );


    // Next, we load the real data in parts.  We need to specify the
    //   correct byte offset for placing the color data after the point
    //   data in the buffer.  Conveniently, the byte offset we need is
    //   the same as the size (in bytes) of the points array, which is
    //   returned from "sizeof(points)".
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(shapes), shapes );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(shapes), sizeof(shapes_color), shapes_color );
    

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program );

    // Initialize the vertex position attribute from the vertex shader
    // Keep in mind that the second parameter is associated with the length of the array sent to opengl (1D,2D,3D or 4D).
    // The last parameter is the offset where the data is stored on the buffer.
    GLuint loc_shapes = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc_shapes );
    glVertexAttribPointer( loc_shapes, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );


    // Likewise, initialize the vertex color attribute.  Once again, we
    //    need to specify the starting offset (in bytes) for the color
    //    data.  Just like loading the array, we use "sizeof(points)"
    //    to determine the correct value.
    GLuint vColor_shapes = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor_shapes );
    glVertexAttribPointer( vColor_shapes, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(sizeof(shapes)) );

  

    return;
}

void CreateVAOstaticShapes(void){

    glGenVertexArrays( 1, &static_shapes_vao );
    glBindVertexArray( static_shapes_vao );

    // Create and bind a buffer object
    GLuint buffer_static_shapes;
    glGenBuffers( 1, &buffer_static_shapes );
    glBindBuffer( GL_ARRAY_BUFFER, buffer_static_shapes );
    

    //glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );
    glBufferData( GL_ARRAY_BUFFER, sizeof(static_shapes)+ sizeof(static_shapes_color), static_shapes, GL_STATIC_DRAW );


    // Next, we load the real data in parts.  We need to specify the
    //   correct byte offset for placing the color data after the point
    //   data in the buffer.  Conveniently, the byte offset we need is
    //   the same as the size (in bytes) of the points array, which is
    //   returned from "sizeof(points)".
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(static_shapes), static_shapes );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(static_shapes), sizeof(static_shapes_color), static_shapes_color );
    

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program );

    // Initialize the vertex position attribute from the vertex shader
    // Keep in mind that the second parameter is associated with the length of the array sent to opengl (1D,2D,3D or 4D).
    // The last parameter is the offset where the data is stored on the buffer.
    GLuint loc_static_shapes = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc_static_shapes );
    glVertexAttribPointer( loc_static_shapes, 2, GL_FLOAT, GL_FALSE, 0,
                            BUFFER_OFFSET(0) );


    // Likewise, initialize the vertex color attribute.  Once again, we
    //    need to specify the starting offset (in bytes) for the color
    //    data.  Just like loading the array, we use "sizeof(points)"
    //    to determine the correct value.
    GLuint vColor_static_shapes = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor_static_shapes );
    glVertexAttribPointer( vColor_static_shapes, 3, GL_FLOAT, GL_FALSE, 0,
                             BUFFER_OFFSET(sizeof(static_shapes)) );

  

    return;
}

void CreatVAOGrid(void){

    // Creat VAO
    glGenVertexArrays( 1, &grid_vao );
    glBindVertexArray( grid_vao );

    // Create and bind a buffer object
    GLuint buffer_G;
    glGenBuffers( 1, &buffer_G );
    glBindBuffer( GL_ARRAY_BUFFER, buffer_G );
    

    //glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );
    glBufferData( GL_ARRAY_BUFFER, sizeof(grid) + sizeof(grid_color), grid, GL_STATIC_DRAW );


    // Next, we load the real data in parts.  We need to specify the
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(grid), grid );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(grid), sizeof(grid_color),grid_color);
    

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program );

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc_grid = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc_grid );
    glVertexAttribPointer( loc_grid, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );


    // Likewise, initialize the vertex color attribute.  Once again, we
    GLuint vColor_grid = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor_grid );
    glVertexAttribPointer( vColor_grid, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(grid)) );

    return;
}

void CreateVAOcurrentShape(void){

    // Create VAO
    glGenVertexArrays( 1, &current_shape_vao );
    glBindVertexArray( current_shape_vao );

    // Create and bind a buffer object
    GLuint buffer_current_shape;
    glGenBuffers( 1, &buffer_current_shape );
    glBindBuffer( GL_ARRAY_BUFFER, buffer_current_shape );
   
    // Size of the buffer
    glBufferData( GL_ARRAY_BUFFER, sizeof(current_shape) + sizeof(current_shape_color), current_shape, GL_STATIC_DRAW );


    // Next, we load the real data in parts
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(current_shape),current_shape );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(current_shape), sizeof(current_shape_color),current_shape_color);
    

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program );

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc_current_shape = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc_current_shape );
    glVertexAttribPointer( loc_current_shape, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );


    // Likewise, initialize the vertex color attribute.  Once again, we
    GLuint vColor_current_shape= glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor_current_shape );
    glVertexAttribPointer( vColor_current_shape, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(current_shape)) );

    return;  
}


void newShapeDrop(void){
    initCurrentShape();
    CreateVAOcurrentShape();
    return;
}

void saveStaticShapes(void){
    

    std::cout<< "enter saveStaticShapes" << std::endl;

    int start_index=shapes_dropped*one_shape_num;

    for (int i=start_index;i<one_shape_num;i++){
        static_shapes[i]=current_shape[i];
        static_shapes_color[i]=current_shape_color[i];
    }    

    std::cout<< "end saveStaticShapes" << std::endl;
}

void init( void ){

    initGrid();
    CreatVAOGrid();

   
    initShapes();

    initCurrentShape();

    initStaticShapes();

    glClearColor( 0.0, 0.0, 0.0, 1.0 ); // white background
}

//----------------------------------------------------------------------------

void display( void ){  
 
   // CreateVAOshapes();
    CreateVAOcurrentShape();
    CreateVAOstaticShapes();


    glClear( GL_COLOR_BUFFER_BIT );     // clear the window
    
    // Draw grid
    // glLineWidth(1.0); 
    glBindVertexArray( grid_vao );
    glDrawArrays( GL_LINES, 0, grid_num );

    // Draw static shapes
    // glLineWidth(1.0); 
    glBindVertexArray( static_shapes_vao );
    //glDrawArrays( GL_TRIANGLES, 0, current_static_points_num );
    glDrawArrays( GL_TRIANGLES, 0, 6 );     

    // Draw current shape
    glBindVertexArray(current_shape_vao );
    glDrawArrays( GL_TRIANGLES, 0, one_shape_num );
 

    // Need a VAO to store static shapes (once reached current bottom)


    //Causes all issued commands to be executed as quickly as they are accepted by the actual rendering engine
    glFlush();
}

//----------------------------------------------------------------------------
int LeftPositionCheck(void){
    
    //std::cout << "enter left positionCheck" << std::endl;
    

    // Left boundary
    for (int i =0;i<one_shape_num;i++){
        if (current_shape[i].x <= -0.9){
            move_left=false;
           // std::cout<< "the shape is out of left bound" << "and move left is : " << move_left <<std::endl;
            return 0;
        }

    }
     //       std::cout<< "the shape is in bound from left side" << "and move left is : " << move_left <<std::endl;
        
    return 1;
}

int RightPositionCheck(void){
    //std::cout << "enter right positionCheck" << std::endl;
    // Left boundary
    for (int i =0;i<one_shape_num;i++){
        if (current_shape[i].x >= 0.9){
            move_right=false;
            //std::cout<< "the shape is out of right bound" << "and move left is : " << move_right <<std::endl;
            return 0;
        }
    }
    //std::cout<< "the shape is in bound from right side" << "and move left is : " << move_right <<std::endl;
    return 1;
} 
 
int Ground(void){
    
    for (int i =0;i<one_shape_num;i++){ 
       // std::cout<< "the shape is not on of ground because point is: " << current_shape[i] <<std::endl;
        if (current_shape[i].y <= -1.0){
           // std::cout<< "the shape is on of ground because point is: " << current_shape[i] <<std::endl;
            ground=true;
            return 1;
        }

    }
    return 0;
}

void moveDown(int num){

        //std::cout << "enter ground positionCheck" << std::endl;
        if (Ground()) {
           // saveStaticShapes();
            std::cout<< "it is on ground" << std::endl;
            initCurrentShape();
            std::cout<< "passed current_shape" << std::endl;
            CreateVAOcurrentShape();
            std::cout<< "passed CreateVAOcurrentShapes" << std::endl;
            CreateVAOstaticShapes();
            std::cout<< "passed CreateVAOstaticShapes" << std::endl;

            shapes_dropped++;
            current_static_points_num=shapes_dropped*one_shape_num;
            //display();
            return;
        }
        for ( int i = num; i < one_shape_num; ++i )
            current_shape[i] = current_shape[i] + down_step;
        glutPostRedisplay();
        //std::cout << "continues downward" << std::endl;

        //if collision detected
        //update array -> static VAO 
        glutTimerFunc( 1000.0, moveDown, 0);
}

void moveLeft(int shape_index){

        if (!LeftPositionCheck()) return;
        for ( int i = shape_index; i < one_shape_num; ++i )
            current_shape[i] = current_shape[i] + left_step;
        glutPostRedisplay();
}

void moveRight(int shape_index){
        //if (!move_right) return;
        if (!RightPositionCheck()) return;
            for ( int i = shape_index; i < one_shape_num; ++i )
                current_shape[i] = current_shape[i] + right_step;
            glutPostRedisplay();
}

void rotateShape(int index, vec2* shapes){

    vec2 center = vec2(0.2,0.2);

    for ( int i = index; i < one_shape_num; ++i )
        center += shapes[i];

    center = center / one_shape_num;
 
    for ( int i = index;i<one_shape_num;++i)
       shapes[i] = rotate10degccw * (shapes[i] - center) + center; 
}

void rotateDelay(int){

    /*
    vec2 center = vec2(0.0,0.0);
    //rotate triangle
    for ( int i = 0; i < 3; ++i )
        center += points[i];

    center = center / 3;

    for ( int i = 0;i<3;++i)
       points[i] = rotate10degccw * (points[i] - center) + center; 
    
    

    // rotateShape(0);



    //Always remember to update your canvas
    glutPostRedisplay();

    //then we can set another identical event in 1000 miliseconds in the future, that is how we keep the triangle rotating
    glutTimerFunc( 1500.0, rotateDelay, 0);
    */
}

void keyboardSpecial( int key, int x, int y ){
    switch ( key ) {
    //similar to the stuff inside the keyboard class, but applying the translaton only to the third triangle.
    case  GLUT_KEY_DOWN:
         moveDown(0);
         break;
    case  GLUT_KEY_RIGHT:
         moveRight(0);
         break;
    case  GLUT_KEY_LEFT:
         moveLeft(0);
         break;
    }  
}

//bind most keys on your keyboard to this function
void keyboard( unsigned char key, int x, int y ){
    switch ( key ) {
    //r pressed
    case 114:
        printf("r pressed!\n");
        //clear static VAO and recall current piece
        exit(1);
        break;

    //Esc pressed!
    case 033:
        quit=true;
        exit( EXIT_SUCCESS );
        break;

    // q pressed
    case 113:
    exit( EXIT_SUCCESS );
    break;
    }    
}

//----------------------------------------------------------------------------
void tetris(){
  // generateGridPoint(width,height,*grid);

    glutInitWindowSize( width,height);

    // If you are using freeglut, the next two lines will check if 
    // the code is truly 3.2. Otherwise, comment them out
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );

    //Title of your screen, change accordingly
    glutCreateWindow( "Tetris" );
  
    
    // Iff you get a segmentation error at line 34, please uncomment the line below
    glewExperimental = GL_TRUE; 
    glewInit();

    //this is the initialization function for your data.
    init();

    //Here we bind the function "display" to the OpenGL handler that will render your data
    glutDisplayFunc( display );

    //Similarly, we can also bind a function that will be executed 1000 miliseconds later. We bind this to the function rotateDelay.
    // We then bind this to the function "rotateDelay". The 0 in the end is the input of the rotateDelay class, it can only be an integer.
    //glutTimerFunc(1000.0, rotateDelay, 1000);
    glutTimerFunc(1000.0, moveDown, 0);

    //Finally, we bind the keyboard events inside the class "keyboard" using the line below
    glutKeyboardFunc( keyboard );

    //If you really want to use F1 ~ F9 keys, or the arrow keys, then use the line of code below.
    glutSpecialFunc( keyboardSpecial );

   // glutMainLoop();  
}

int main( int argc, char **argv ) {
    


    //while(!quit);
      
    glutInit( &argc, argv );
    //We explicitly tell OpenGL that we are using the RGBA mode. When we start working with 3D resources there will be changes here.
    glutInitDisplayMode( GLUT_RGBA );

    tetris();
    /*
    //second try to resize
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, float(width)/float(height), 0.1, 100.0);
    //Change the size of the screen here. Keep in mind that the coordinates will also change accordingly
    //so, if you want to keep your points on the rendering canvas undisturbed you need a square screen.
    */
   /*
    glutInitWindowSize( width,height);

    // If you are using freeglut, the next two lines will check if 
    // the code is truly 3.2. Otherwise, comment them out
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );

    //Title of your screen, change accordingly
    glutCreateWindow( "Tetris" );
  
    // Try to resize
    //glutReshapeFunc(resize);
    
    // Iff you get a segmentation error at line 34, please uncomment the line below
    glewExperimental = GL_TRUE; 
    glewInit();

    //this is the initialization function for your data.
    init();

    //Here we bind the function "display" to the OpenGL handler that will render your data
    glutDisplayFunc( display );

    //Similarly, we can also bind a function that will be executed 1000 miliseconds later. We bind this to the function rotateDelay.
    // We then bind this to the function "rotateDelay". The 0 in the end is the input of the rotateDelay class, it can only be an integer.
    glutTimerFunc(1000.0, rotateDelay, 1000);
    glutTimerFunc(1000.0, moveDown, 0);

    //Finally, we bind the keyboard events inside the class "keyboard" using the line below
    glutKeyboardFunc( keyboard );

    //If you really want to use F1 ~ F9 keys, or the arrow keys, then use the line of code below.
    glutSpecialFunc( keyboardSpecial );

    */
    glutMainLoop();  
          
    return 0;

}
