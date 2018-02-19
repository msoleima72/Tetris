#include "Angel.h"
#include "vec.h"

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

void initshapeI( int index, vec2 left_top_point, vec3 color,vec2 *shapes, vec3 *shapes_color){


    addSquare(index, left_top_point, color, shapes,shapes_color);

    left_top_point+=right_step;
    
    addSquare(index+square_num, left_top_point, color,shapes,shapes_color);

    left_top_point+=right_step;

    addSquare(index+(2*square_num), left_top_point, color,shapes,shapes_color);
   
    left_top_point+=right_step;

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

void initShapes(void){

    //left_top_point=vec2 (0.0,-1.0); 
    vec3 color = base_colors[2];

    initshapeI(0, left_top_point, color, shapes,shapes_color);  

    color = base_colors[4];
    initShapeT(one_shape_num, vec2 (0.5,0.0), color, shapes,shapes_color);
}

void initLine(void){

    //line starting points and ending points. The first two positions represent one line segment,
    //while the last two positions represent another line segment.
    points1[0] = vec2( -0.25, 0.0 );
    points1[1] = vec2( 0.25, 0.0 );

    points1[2] = vec2( 0.0, -0.5 );
    points1[3] = vec2( 0.0, 0.5 );

    
    //lines can have color too!
    colors1[0] = base_colors[0];
    colors1[1] = base_colors[4];
    colors1[2] = base_colors[3];
    colors1[3] = base_colors[4];
    return;
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
         grid_color[i] = base_colors[5];
    }
    return;
}

void initTriangle (void){
    //Vertex positions for three triangles
    // Three triangles forming a simple Gasket
    points[0] = vec2( -0.2, -0.4 );
    points[1] = vec2( 0.2, -0.0 );
    points[2] = vec2( -0.0, 0.4 );
    
    /*
    points[3] = vec2( 0.0, -1.0 );
    points[4] = vec2( 0.5, 0.0 );
    points[5] = vec2( 1.0, -1.0 );

    points[6] = vec2( 0.0, 1.0 );
    points[7] = vec2( -0.5, 0.0 );
    points[8] = vec2( 0.5, 0.0 );
    */
    //color stuff for each vertex of each of the triangles
    colors[0] = base_colors[0];
    colors[1] = base_colors[4];
    colors[2] = base_colors[1];
    /*
    colors[3] = base_colors[1];
    colors[4] = base_colors[4];
    colors[5] = base_colors[2];

    colors[6] = base_colors[4];
    colors[7] = base_colors[2];
    colors[8] = base_colors[0];
    */
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

void CreatVAOTriangles(void){
    
    

    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and bind a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    

    //glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), points, GL_STATIC_DRAW );


    // Next, we load the real data in parts.  We need to specify the
    //   correct byte offset for placing the color data after the point
    //   data in the buffer.  Conveniently, the byte offset we need is
    //   the same as the size (in bytes) of the points array, which is
    //   returned from "sizeof(points)".
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors );
    

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program );

    // Initialize the vertex position attribute from the vertex shader
    // Keep in mind that the second parameter is associated with the length of the array sent to opengl (1D,2D,3D or 4D).
    // The last parameter is the offset where the data is stored on the buffer.
    GLuint loc = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );


    // Likewise, initialize the vertex color attribute.  Once again, we
    //    need to specify the starting offset (in bytes) for the color
    //    data.  Just like loading the array, we use "sizeof(points)"
    //    to determine the correct value.
    GLuint vColor = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(sizeof(points)) );

    return;
}

void CreatVAOLines(void){
    glGenVertexArrays( 1, &vao1 );
    glBindVertexArray( vao1 );

    // Create and initialize a buffer object
    GLuint buffer1;
    glGenBuffers( 1, &buffer1 );
    glBindBuffer( GL_ARRAY_BUFFER, buffer1 );
    
    //glBufferData( GL_ARRAY_BUFFER, sizeof(points1), points1, GL_STATIC_DRAW );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points1) + sizeof(colors1), points1, GL_STATIC_DRAW );

    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points1), points1 );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points1), sizeof(colors1), colors1 );

    // Load shaders and use the resulting shader program
    GLuint program1 = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program1 );

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc1 = glGetAttribLocation( program1, "vPosition" );
    glEnableVertexAttribArray( loc1 );
    glVertexAttribPointer( loc1, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    GLuint vColor1 = glGetAttribLocation( program1, "vColor" );
    glEnableVertexAttribArray( vColor1 );
    glVertexAttribPointer( vColor1, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(sizeof(points1)) );
    return;
}

void CreatVAOGrid(void){

    //initialize grid


    glGenVertexArrays( 1, &grid_vao );
    glBindVertexArray( grid_vao );

    // Create and bind a buffer object
    GLuint buffer_G;
    glGenBuffers( 1, &buffer_G );
    glBindBuffer( GL_ARRAY_BUFFER, buffer_G );
    

    //glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );
    glBufferData( GL_ARRAY_BUFFER, sizeof(grid) + sizeof(grid_color), grid, GL_STATIC_DRAW );


    // Next, we load the real data in parts.  We need to specify the
    //   correct byte offset for placing the color data after the point
    //   data in the buffer.  Conveniently, the byte offset we need is
    //   the same as the size (in bytes) of the points array, which is
    //   returned from "sizeof(points)".
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(grid), grid );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(grid), sizeof(grid_color),grid_color);
    

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program );

    // Initialize the vertex position attribute from the vertex shader
    // Keep in mind that the second parameter is associated with the length of the array sent to opengl (1D,2D,3D or 4D).
    // The last parameter is the offset where the data is stored on the buffer.
    GLuint loc_grid = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc_grid );
    glVertexAttribPointer( loc_grid, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );


    // Likewise, initialize the vertex color attribute.  Once again, we
    //    need to specify the starting offset (in bytes) for the color
    //    data.  Just like loading the array, we use "sizeof(points)"
    //    to determine the correct value.
    GLuint vColor_grid = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor_grid );
    glVertexAttribPointer( vColor_grid, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(sizeof(grid)) );

    return;
}

void init( void ){

    // Static lines initiated here
    initLine();
    CreatVAOLines();

    initGrid();
    CreatVAOGrid();

    initTriangle();
    initShapes();

    CreateVAOshapes();
    glClearColor( 0.0, 0.0, 0.0, 1.0 ); // white background
}

//----------------------------------------------------------------------------

void display( void ){  
 
    CreateVAOshapes();
    CreatVAOTriangles();

    glClear( GL_COLOR_BUFFER_BIT );     // clear the window
    //Draw triangles
    //Here we are binding back the first vertex array object. Now we can acess all the buffers associated to it and render accordingly
    glBindVertexArray( vao );
    glDrawArrays( GL_TRIANGLES, 0, NumPoints );

    // Draw grid
    //glLineWidth(1.0); 
    glBindVertexArray( grid_vao );
    glDrawArrays( GL_LINES, 0, grid_num );

    /* glLineWidth(5.0);    
    glBindVertexArray( vao1 );
    glDrawArrays( GL_LINES, 0, NumPoints1 );
   */
    glBindVertexArray( shapes_vao );
    glDrawArrays( GL_TRIANGLES, 0, shapes_num );
 

    //Causes all issued commands to be executed as quickly as they are accepted by the actual rendering engine
    glFlush();
}

//----------------------------------------------------------------------------

void moveDown(int shape_index){
        for ( int i = shape_index; i < one_shape_num; ++i )
            shapes[i] = shapes[i] + down_step;
        glutPostRedisplay();
        glutTimerFunc( 1000.0, moveDown, 0);
}

void moveLeft(int shape_index){
        for ( int i = shape_index; i < one_shape_num; ++i )
            shapes[i] = shapes[i] + left_step;
        glutPostRedisplay();
        //glutTimerFunc( 1000.0, moveDown, 0);
}

void moveRight(int shape_index){
        for ( int i = shape_index; i < one_shape_num; ++i )
            shapes[i] = shapes[i] + right_step;
        glutPostRedisplay();
        //glutTimerFunc( 1000.0, moveDown, 0);
}


void rotateShape(int index, vec2* shapes){

    vec2 center = vec2(0.2,0.2);

    for ( int i = index; i < one_shape_num; ++i )
        center += shapes[i];

    center = center / one_shape_num;
 
    for ( int i = index;i<one_shape_num;++i)
       shapes[i] = rotate10degccw * (shapes[i] - center) + center; 

}

//timed function. We intended to execute this every one second.
void rotateDelay(int){

     
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
}

//If you want to use arrows, take a look at this function
//It works similarly, but you have no acess to the ASCII keys using it. Please see the link below for details.
//https://www.opengl.org/resources/libraries/glut/spec3/node54.html
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
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        break;

    //Esc pressed!
    case 033:
        exit( EXIT_SUCCESS );
        break;

    // q pressed
    case 113:
    exit( EXIT_SUCCESS );
    break;
    }    
}
