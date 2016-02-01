// ==========================================================================
// Barebones OpenGL Core Profile Boilerplate
//    using the GLFW windowing system (http://www.glfw.org)
//
// Loosely based on
//  - Chris Wellons' example (https://github.com/skeeto/opengl-demo) and
//  - Camilla Berglund's example (http://www.glfw.org/docs/latest/quick.html)
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string.h>
#define GLFW_INCLUDE_GLCOREARB
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <math.h>

# include <cstdlib>
# include <iostream>

using namespace std;

using namespace std;

// --------------------------------------------------------------------------
// OpenGL utility and support function prototypes

void QueryGLVersion();
bool CheckGLErrors();

string LoadSource(const string &filename);
GLuint CompileShader(GLenum shaderType, const string &source);
GLuint LinkProgram(GLuint vertexShader, GLuint fragmentShader);
vector<float> vertices;
vector<float> colors;
vector<int> elements;
vector<char> dragonCurveList;

// --------------------------------------------------------------------------
// Functions to set up OpenGL shader programs for rendering

struct MyShader
{
    // OpenGL names for vertex and fragment shaders, shader program
    GLuint  vertex;
    GLuint  fragment;
    GLuint  program;

    // initialize shader and program names to zero (OpenGL reserved value)
    MyShader() : vertex(0), fragment(0), program(0)
    {}
};

// load, compile, and link shaders, returning true if successful
bool InitializeShaders(MyShader *shader)
{
    // load shader source from files
    string vertexSource = LoadSource("vertex.glsl");
    string fragmentSource = LoadSource("fragment.glsl");
    if (vertexSource.empty() || fragmentSource.empty()) return false;

    // compile shader source into shader objects
    shader->vertex = CompileShader(GL_VERTEX_SHADER, vertexSource);
    shader->fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

    // link shader program
    shader->program = LinkProgram(shader->vertex, shader->fragment);

    // check for OpenGL errors and return false if error occurred
    return !CheckGLErrors();
}

// deallocate shader-related objects
void DestroyShaders(MyShader *shader)
{
    // unbind any shader programs and destroy shader objects
    glUseProgram(0);
    glDeleteProgram(shader->program);
    glDeleteShader(shader->vertex);
    glDeleteShader(shader->fragment);
}

// --------------------------------------------------------------------------
// Functions to set up OpenGL buffers for storing geometry data

struct MyGeometry
{
    // OpenGL names for array buffer objects, vertex array object
    GLuint  vertexBuffer;
    GLuint  colourBuffer;
    GLuint  vertexArray;
    GLsizei elementCount;

    // initialize object names to zero (OpenGL reserved value)
    MyGeometry() : vertexBuffer(0), colourBuffer(0), vertexArray(0), elementCount(0)
    {}
};

// create buffers and fill with geometry data, returning true if successful
bool InitializeGeometry(MyGeometry *geometry)
{
    // these vertex attribute indices correspond to those specified for the
    // input variables in the vertex shader
    const GLuint VERTEX_INDEX = 0;
    const GLuint COLOUR_INDEX = 1;

    // create an array buffer object for storing our vertices
    glGenBuffers(1, &geometry->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, geometry->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 100000, NULL, GL_STATIC_DRAW);

    // create another one for storing our colours
    glGenBuffers(1, &geometry->colourBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, geometry->colourBuffer);
    glBufferData(GL_ARRAY_BUFFER, 100000, NULL, GL_STATIC_DRAW);

    // create a vertex array object encapsulating all our vertex attributes
    glGenVertexArrays(1, &geometry->vertexArray);
    glBindVertexArray(geometry->vertexArray);

    // associate the position array with the vertex array object
    glBindBuffer(GL_ARRAY_BUFFER, geometry->vertexBuffer);
    glVertexAttribPointer(VERTEX_INDEX, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(VERTEX_INDEX);

    // assocaite the colour array with the vertex array object
    glBindBuffer(GL_ARRAY_BUFFER, geometry->colourBuffer);
    glVertexAttribPointer(COLOUR_INDEX, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(COLOUR_INDEX);

    // unbind our buffers, resetting to default state
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // check for OpenGL errors and return false if error occurred
    return !CheckGLErrors();
}

// deallocate geometry-related objects
void DestroyGeometry(MyGeometry *geometry)
{
    // unbind and destroy our vertex array object and associated buffers
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &geometry->vertexArray);
    glDeleteBuffers(1, &geometry->vertexBuffer);
    glDeleteBuffers(1, &geometry->colourBuffer);
}

/**
 * ================================================================================================
 * ================================================================================================
 *================================================================================================
 *
 * The following code section targets assignment solution
 *
 * ================================================================================================
 * ================================================================================================
 * ================================================================================================
 */
bool PART_ONE = false;
bool PART_TWO = false;
bool PART_THREE = false;
bool B_2 = false;

int BASE_TRIANGLE = 0;
int LEFT = 1;
int UP = 2;
int RIGHT = 3;

struct Point
{
     float x;
     float y;
};

struct Line
{
   Point startPoint;
   Point endPoint;
};

struct Triangle
{
    Line leftLine;
    Line rightLine;
    Line LowerLine;
};

struct Square
{
    Line leftLine;
    Line upperLine;
    Line rightLine;
    Line LowerLine;
};

/**
 * ================================================================================================
 * ================================================================================================
 *
 * The following code section targets part one of the assignment
 *
 * ================================================================================================
 * ================================================================================================
 */

/**
 * @brief getSquare
 * @param value
 * @return Reurns square cornered with points provided
 */
Square getSquare(Point P1, Point P2, Point P3, Point P4)
{
    Square baseSquare;
    baseSquare.leftLine.startPoint.x = P1.x;
    baseSquare.leftLine.startPoint.y = P1.x;
    baseSquare.leftLine.endPoint.x = P2.x;
    baseSquare.leftLine.endPoint.y = P2.y;

    baseSquare.upperLine.startPoint.x = P2.x;
    baseSquare.upperLine.startPoint.y = P2.y;
    baseSquare.upperLine.endPoint.x = P3.x;
    baseSquare.upperLine.endPoint.y = P3.y;

    baseSquare.rightLine.startPoint.x = P3.x;
    baseSquare.rightLine.startPoint.y = P3.y;
    baseSquare.rightLine.endPoint.x = P4.x;
    baseSquare.rightLine.endPoint.y = P4.y;

    baseSquare.LowerLine.startPoint.x = P4.x;
    baseSquare.LowerLine.startPoint.y = P4.y;
    baseSquare.LowerLine.endPoint.x = P1.x;
    baseSquare.LowerLine.endPoint.y = P1.y;

    return baseSquare;
}

void bufferLine(float x1, float y1, float x2, float y2)
{
    vertices.push_back(x1);
    vertices.push_back(y1);

    vertices.push_back(x2);
    vertices.push_back(y2);
}

void bufferColorsOfLine(float r, float g, float b)
{
    colors.push_back(r);
    colors.push_back(g);
    colors.push_back(b);

    colors.push_back(r);
    colors.push_back(g);
    colors.push_back(b);
}

void bufferSquareLine(float x1, float y1, float x2, float y2, bool isDiamond, float Dcolor)
{
    bufferLine(x1, y1, x2, y2);
    if(isDiamond)
    {
        //Diamond
        bufferColorsOfLine(0.001, 0.001, Dcolor);
    }

    else{
        //Square
        bufferColorsOfLine(Dcolor, Dcolor, Dcolor);
    }
}

void displaySquare(Square sqr, int isDiamond, float Dcolor)
{
    bufferSquareLine(sqr.leftLine.startPoint.x, sqr.leftLine.startPoint.y,
                     sqr.leftLine.endPoint.x, sqr.leftLine.endPoint.y, isDiamond, Dcolor);
    bufferSquareLine(sqr.upperLine.startPoint.x, sqr.upperLine.startPoint.y,
                     sqr.upperLine.endPoint.x, sqr.upperLine.endPoint.y, isDiamond, Dcolor);
    bufferSquareLine(sqr.rightLine.startPoint.x, sqr.rightLine.startPoint.y,
                     sqr.rightLine.endPoint.x, sqr.rightLine.endPoint.y, isDiamond, Dcolor);
    bufferSquareLine(sqr.LowerLine.startPoint.x, sqr.LowerLine.startPoint.y,
                     sqr.LowerLine.endPoint.x, sqr.LowerLine.endPoint.y, isDiamond, Dcolor);
}

Square getNextSquare(Square oldSquare)
{
    Square nextSquare;
    nextSquare.leftLine.startPoint.x = (oldSquare.leftLine.startPoint.x + oldSquare.leftLine.endPoint.x)/ 2;
    nextSquare.leftLine.startPoint.y = (oldSquare.leftLine.startPoint.y + oldSquare.leftLine.endPoint.y)/ 2;
    nextSquare.leftLine.endPoint.x = (oldSquare.upperLine.startPoint.x + oldSquare.upperLine.endPoint.x)/ 2;
    nextSquare.leftLine.endPoint.y = (oldSquare.upperLine.startPoint.y + oldSquare.upperLine.endPoint.y)/ 2;

    nextSquare.upperLine.startPoint.x = (oldSquare.upperLine.startPoint.x + oldSquare.upperLine.endPoint.x)/ 2;
    nextSquare.upperLine.startPoint.y = (oldSquare.upperLine.startPoint.y + oldSquare.upperLine.endPoint.y)/ 2;
    nextSquare.upperLine.endPoint.x = (oldSquare.rightLine.startPoint.x + oldSquare.rightLine.endPoint.x)/ 2;
    nextSquare.upperLine.endPoint.y = (oldSquare.rightLine.startPoint.y + oldSquare.rightLine.endPoint.y)/ 2;

    nextSquare.rightLine.startPoint.x = (oldSquare.rightLine.startPoint.x + oldSquare.rightLine.endPoint.x)/ 2;
    nextSquare.rightLine.startPoint.y = (oldSquare.rightLine.startPoint.y + oldSquare.rightLine.endPoint.y)/ 2;
    nextSquare.rightLine.endPoint.x = (oldSquare.LowerLine.startPoint.x + oldSquare.LowerLine.endPoint.x)/ 2;
    nextSquare.rightLine.endPoint.y = (oldSquare.LowerLine.startPoint.y + oldSquare.LowerLine.endPoint.y)/ 2;

    nextSquare.LowerLine.startPoint.x = (oldSquare.LowerLine.startPoint.x + oldSquare.LowerLine.endPoint.x)/ 2;
    nextSquare.LowerLine.startPoint.y = (oldSquare.LowerLine.startPoint.y + oldSquare.LowerLine.endPoint.y)/ 2;
    nextSquare.LowerLine.endPoint.x = (oldSquare.leftLine.startPoint.x + oldSquare.leftLine.endPoint.x)/ 2;
    nextSquare.LowerLine.endPoint.y = (oldSquare.leftLine.startPoint.y + oldSquare.leftLine.endPoint.y)/ 2;

    return nextSquare;
}

void renderSquaresAndDiamonds(int level)
{
    //Construct the points for the base square
    Point one, two, three, four;
    one.x = -0.9f; one.y = -0.9f;
    two.x = -0.9f; two.y = 0.9f;
    three.x = 0.9f; three.y = 0.9f;
    four.x = 0.9f; four.y = -0.9f;

    //Get the base square and dispaly it
    Square baseSqr = getSquare(one, two, three, four);

    Square nextSquare = baseSqr;
    float ChangeInColor = 0.1;

    for(int i = 0; i < level; i++)
    {
        float Dcolor = ((float)i * ChangeInColor) + ChangeInColor;

        //Display square
        displaySquare(nextSquare, false, Dcolor);
        nextSquare = getNextSquare(nextSquare);

        //Display the diamond
        displaySquare(nextSquare, true, 1 - Dcolor - 0.01);
        nextSquare = getNextSquare(nextSquare);
    }
}



/**
 * ================================================================================================
 * ================================================================================================
 *
 * The following code section targets part two of the assignment
 *
 * ================================================================================================
 * ================================================================================================
 */

void addColors(float i, float maximum_value)
{
    colors.push_back(0.f);
    colors.push_back(0.f);
    colors.push_back(1 * (i/maximum_value));

    colors.push_back(0.f);
    colors.push_back(0.f);
    colors.push_back(1 * (i/maximum_value));
}

void doPartTwo(int rotationNumbers)
{
    float maximum_value = (rotationNumbers * 360) * (M_PI/180);

    for (float i = 0; i < maximum_value; i+=0.01)
    {
        float x1 = (i * cos(i)) / maximum_value;
        float y1 = (-i * sin(i)) / maximum_value;

        float increment_i = i + 0.01;
        float x2 = (increment_i * cos(increment_i)) / maximum_value;
        float y2 = (-increment_i * sin(increment_i)) / maximum_value;

        bufferLine(x1, y1, x2, y2);
        addColors(i, maximum_value);
    }
}


/**
 * ================================================================================================
 * ================================================================================================
 *
 * The following code section targets part three of the assignment
 *
 * ================================================================================================
 * ================================================================================================
 */

Triangle getLeftTriangle(Triangle oldTriangle)
{
    Triangle leftTriangle;
    leftTriangle.leftLine.startPoint.x = oldTriangle.leftLine.startPoint.x;
    leftTriangle.leftLine.startPoint.y = oldTriangle.leftLine.startPoint.y;
    leftTriangle.leftLine.endPoint.x = (oldTriangle.leftLine.startPoint.x + oldTriangle.leftLine.endPoint.x)/2;
    leftTriangle.leftLine.endPoint.y = (oldTriangle.leftLine.startPoint.y + oldTriangle.leftLine.endPoint.y)/2;

    leftTriangle.rightLine.startPoint.x = (oldTriangle.leftLine.startPoint.x + oldTriangle.leftLine.endPoint.x)/2;
    leftTriangle.rightLine.startPoint.y = (oldTriangle.leftLine.startPoint.y + oldTriangle.leftLine.endPoint.y)/2;
    leftTriangle.rightLine.endPoint.x = (oldTriangle.LowerLine.startPoint.x + oldTriangle.LowerLine.endPoint.x)/2;
    leftTriangle.rightLine.endPoint.y = (oldTriangle.LowerLine.startPoint.y + oldTriangle.LowerLine.endPoint.y)/2;

    leftTriangle.LowerLine.startPoint.x = (oldTriangle.LowerLine.startPoint.x + oldTriangle.LowerLine.endPoint.x)/2;
    leftTriangle.LowerLine.startPoint.y = (oldTriangle.LowerLine.startPoint.y + oldTriangle.LowerLine.endPoint.y)/2;
    leftTriangle.LowerLine.endPoint.x = oldTriangle.leftLine.startPoint.x;
    leftTriangle.LowerLine.endPoint.y = oldTriangle.leftLine.startPoint.y;

    return leftTriangle;
}

Triangle getUpperTriangle(Triangle oldTriangle)
{
    Triangle upperTriangle;

    upperTriangle.leftLine.startPoint.x = (oldTriangle.leftLine.startPoint.x + oldTriangle.leftLine.endPoint.x)/2;
    upperTriangle.leftLine.startPoint.y = (oldTriangle.leftLine.startPoint.y + oldTriangle.leftLine.endPoint.y)/2;
    upperTriangle.leftLine.endPoint.x = oldTriangle.leftLine.endPoint.x;
    upperTriangle.leftLine.endPoint.y = oldTriangle.leftLine.endPoint.y;

    upperTriangle.rightLine.startPoint.x = oldTriangle.rightLine.startPoint.x;
    upperTriangle.rightLine.startPoint.y = oldTriangle.rightLine.startPoint.y;
    upperTriangle.rightLine.endPoint.x = (oldTriangle.rightLine.startPoint.x + oldTriangle.rightLine.endPoint.x)/2;
    upperTriangle.rightLine.endPoint.y = (oldTriangle.rightLine.startPoint.y + oldTriangle.rightLine.endPoint.y)/2;

    upperTriangle.LowerLine.startPoint.x = (oldTriangle.rightLine.startPoint.x + oldTriangle.rightLine.endPoint.x)/2;
    upperTriangle.LowerLine.startPoint.y = (oldTriangle.rightLine.startPoint.y + oldTriangle.rightLine.endPoint.y)/2;
    upperTriangle.LowerLine.endPoint.x = (oldTriangle.leftLine.startPoint.x + oldTriangle.leftLine.endPoint.x)/2;
    upperTriangle.LowerLine.endPoint.y = (oldTriangle.leftLine.startPoint.y + oldTriangle.leftLine.endPoint.y)/2;

    return upperTriangle;
}

Triangle getRightTriangle(Triangle oldTriangle)
{
    Triangle rightTriangle;

    rightTriangle.leftLine.startPoint.x = (oldTriangle.LowerLine.startPoint.x + oldTriangle.LowerLine.endPoint.x)/2;
    rightTriangle.leftLine.startPoint.y = (oldTriangle.LowerLine.startPoint.y + oldTriangle.LowerLine.endPoint.y)/2;
    rightTriangle.leftLine.endPoint.x = (oldTriangle.rightLine.startPoint.x + oldTriangle.rightLine.endPoint.x)/2;
    rightTriangle.leftLine.endPoint.y = (oldTriangle.rightLine.startPoint.y + oldTriangle.rightLine.endPoint.y)/2;

    rightTriangle.rightLine.startPoint.x = (oldTriangle.rightLine.startPoint.x + oldTriangle.rightLine.endPoint.x)/2;
    rightTriangle.rightLine.startPoint.y = (oldTriangle.rightLine.startPoint.y + oldTriangle.rightLine.endPoint.y)/2;
    rightTriangle.rightLine.endPoint.x = oldTriangle.rightLine.endPoint.x;
    rightTriangle.rightLine.endPoint.y = oldTriangle.rightLine.endPoint.y;

    rightTriangle.LowerLine.startPoint.x = oldTriangle.rightLine.endPoint.x;
    rightTriangle.LowerLine.startPoint.y = oldTriangle.rightLine.endPoint.y;
    rightTriangle.LowerLine.endPoint.x = (oldTriangle.LowerLine.startPoint.x + oldTriangle.LowerLine.endPoint.x)/2;
    rightTriangle.LowerLine.endPoint.y = (oldTriangle.LowerLine.startPoint.y + oldTriangle.LowerLine.endPoint.y)/2;

    return rightTriangle;
}

Triangle getMiddleTriangle(Triangle oldTriangle)
{
    Triangle middleTriangle;

    middleTriangle.LowerLine.startPoint.x = (oldTriangle.leftLine.startPoint.x + oldTriangle.leftLine.endPoint.x)/2;
    middleTriangle.LowerLine.startPoint.y = (oldTriangle.leftLine.startPoint.y + oldTriangle.leftLine.endPoint.y)/2;
    middleTriangle.LowerLine.endPoint.x = (oldTriangle.rightLine.startPoint.x + oldTriangle.rightLine.endPoint.x)/2;
    middleTriangle.LowerLine.endPoint.y = (oldTriangle.rightLine.startPoint.y + oldTriangle.rightLine.endPoint.y)/2;

    middleTriangle.rightLine.startPoint.x = (oldTriangle.rightLine.startPoint.x + oldTriangle.rightLine.endPoint.x)/2;
    middleTriangle.rightLine.startPoint.y = (oldTriangle.rightLine.startPoint.y + oldTriangle.rightLine.endPoint.y)/2;
    middleTriangle.rightLine.endPoint.x = (oldTriangle.LowerLine.startPoint.x + oldTriangle.LowerLine.endPoint.x)/2;
    middleTriangle.rightLine.endPoint.y = (oldTriangle.LowerLine.startPoint.y + oldTriangle.LowerLine.endPoint.y)/2;

    middleTriangle.leftLine.startPoint.x = (oldTriangle.LowerLine.startPoint.x + oldTriangle.LowerLine.endPoint.x)/2;
    middleTriangle.leftLine.startPoint.y = (oldTriangle.LowerLine.startPoint.y + oldTriangle.LowerLine.endPoint.y)/2;
    middleTriangle.leftLine.endPoint.x = (oldTriangle.leftLine.startPoint.x + oldTriangle.leftLine.endPoint.x)/2;
    middleTriangle.leftLine.endPoint.y = (oldTriangle.leftLine.startPoint.y + oldTriangle.leftLine.endPoint.y)/2;

    return middleTriangle;
}

void displayTriangle(Triangle triangle)
{
    vertices.push_back(triangle.leftLine.startPoint.x);
    vertices.push_back(triangle.leftLine.startPoint.y);

    vertices.push_back(triangle.rightLine.startPoint.x);
    vertices.push_back(triangle.rightLine.startPoint.y);

    vertices.push_back(triangle.LowerLine.startPoint.x);
    vertices.push_back(triangle.LowerLine.startPoint.y);
}

void addColorsToTriangles(float r, float g, float b)
{
        colors.push_back(r);
        colors.push_back(g);
        colors.push_back(b);

        colors.push_back(r);
        colors.push_back(g);
        colors.push_back(b);

        colors.push_back(r);
        colors.push_back(g);
        colors.push_back(b);
}

float nextRColor = 0.4f;
float nextGColor = 0.4f;
float nextBColor = 0.4f;

void displaySierpinskiTriangle(int level, Triangle tr, int whichSide)
{
    if(level == 1 && whichSide == BASE_TRIANGLE)
    {
        displayTriangle(tr);
        addColorsToTriangles(0.41f, 0.41f, 0.41f);
    }
    else if(level == 1)
    {
        displayTriangle(tr);

        if(whichSide == LEFT)
        {
            nextRColor += 0.009f;
            cout<<"Next rcolor = "<<nextRColor<<endl;
            addColorsToTriangles(nextRColor ,0.f,0.f);
        }
        if(whichSide == RIGHT)
        {
            nextGColor += 0.009f;
            cout<<"Next gcolor = "<<nextGColor<<endl;
            addColorsToTriangles(0.f, nextGColor, 0.f);
        }if(whichSide == UP)
        {
            nextBColor += 0.009f;
            cout<<"Next bcolor = "<<nextBColor<<endl;
            addColorsToTriangles(0.f,0.f, nextBColor);
        }
        return;
    }
    else
    {
        if(whichSide == BASE_TRIANGLE){
            displaySierpinskiTriangle(level -1, getLeftTriangle(tr), LEFT);
            displaySierpinskiTriangle(level - 1, getUpperTriangle(tr), UP);
            displaySierpinskiTriangle(level - 1, getRightTriangle(tr), RIGHT);
        }else{
            displaySierpinskiTriangle(level -1, getLeftTriangle(tr), whichSide);
            displaySierpinskiTriangle(level - 1, getUpperTriangle(tr), whichSide);
            displaySierpinskiTriangle(level - 1, getRightTriangle(tr), whichSide);
        }

    }
}

void drawSierpinskiTriangle(int level)
{
    cout<<"draw seirp is called"<<endl;

    //draw the main triangle
    Triangle baseTriangle;
    baseTriangle.leftLine.startPoint.x = -0.5;
    baseTriangle.leftLine.startPoint.y = -0.5;
    baseTriangle.leftLine.endPoint.x = 0;
    baseTriangle.leftLine.endPoint.y = 0.5;

    baseTriangle.rightLine.startPoint.x = 0;
    baseTriangle.rightLine.startPoint.y = 0.5;
    baseTriangle.rightLine.endPoint.x = 0.5;
    baseTriangle.rightLine.endPoint.y = -0.5;

    baseTriangle.LowerLine.startPoint.x = 0.5;
    baseTriangle.LowerLine.startPoint.y = -0.5;
    baseTriangle.LowerLine.endPoint.x = -0.5;
    baseTriangle.LowerLine.endPoint.y = -0.5;

    displaySierpinskiTriangle(level, baseTriangle, BASE_TRIANGLE);
}

/**
 * ================================================================================================
 * ================================================================================================
 *
 * The following code section targets part three of the assignment
 *
 * ================================================================================================
 * ================================================================================================
 */

void drawSnowFlake (int level, float x1, float y1, float x5, float y5){
    float deltaX, deltaY, x2, y2, x3, y3, x4, y4;

    if (level == 0){
        bufferLine(x1, y1, x5, y5);
        bufferColorsOfLine(0.f, 0.f, 0.f);
    }
    else{
        deltaX = x5 - x1;
        deltaY = y5 - y1;

        x2 = x1 + deltaX / 3;
        y2 = y1 + deltaY / 3;

        x3 = (float) (0.5 * (x1+x5) + sqrt(3) * (y1-y5)/6);
        y3 = (float) (0.5 * (y1+y5) + sqrt(3) * (x5-x1)/6);

        x4 = x1 + 2 * deltaX /3;
        y4 = y1 + 2 * deltaY /3;

        drawSnowFlake (level-1, x1, y1, x2, y2);
        drawSnowFlake (level-1, x2, y2, x3, y3);
        drawSnowFlake (level-1, x3, y3, x4, y4);
        drawSnowFlake (level-1, x4, y4, x5, y5);
   }
}

void doBounsOne(int level)
{
    Triangle baseTriangle;
    baseTriangle.leftLine.startPoint.x = -0.5;
    baseTriangle.leftLine.startPoint.y = -0.5;
    baseTriangle.leftLine.endPoint.x = 0;
    baseTriangle.leftLine.endPoint.y = 0.5;

    baseTriangle.rightLine.startPoint.x = 0;
    baseTriangle.rightLine.startPoint.y = 0.5;
    baseTriangle.rightLine.endPoint.x = 0.5;
    baseTriangle.rightLine.endPoint.y = -0.5;

    baseTriangle.LowerLine.startPoint.x = 0.5;
    baseTriangle.LowerLine.startPoint.y = -0.5;
    baseTriangle.LowerLine.endPoint.x = -0.5;
    baseTriangle.LowerLine.endPoint.y = -0.5;

    drawSnowFlake(level,-0.5f, -0.5f, 0.f, 0.5f);
    drawSnowFlake(level,0.f, 0.5f, 0.5f, -0.5f);
    drawSnowFlake(level, 0.5f, -0.5f, -0.5f, -0.5f);
}


void drawMengerSponge (int level, Square sqr)
{
    if (level == 0) {
        return;
    }

    Square one;
    one.leftLine.startPoint.x = sqr.leftLine.startPoint.x;
    one.leftLine.startPoint.y = sqr.leftLine.startPoint.y;
    one.leftLine.endPoint.x = (sqr.leftLine.startPoint.x + sqr.leftLine.endPoint.x)/3;
    one.leftLine.endPoint.y = (sqr.leftLine.startPoint.y + sqr.leftLine.endPoint.y)/3;

    one.upperLine.startPoint.x = one.leftLine.endPoint.x;
    one.upperLine.startPoint.y = one.leftLine.endPoint.y;
    one.upperLine.endPoint.x = (sqr.upperLine.startPoint.x + sqr.upperLine.endPoint.x)/3;
    one.upperLine.endPoint.y = (sqr.upperLine.startPoint.y + sqr.upperLine.endPoint.y)/3;

    one.rightLine.startPoint.x = one.upperLine.endPoint.x;
    one.rightLine.startPoint.y = one.upperLine.endPoint.y;
    one.rightLine.endPoint.x = (sqr.LowerLine.startPoint.x + sqr.LowerLine.endPoint.x)/3;
    one.rightLine.endPoint.y = (sqr.LowerLine.startPoint.y + sqr.LowerLine.endPoint.y)/3;

    one.LowerLine.startPoint.x = one.rightLine.endPoint.x;
    one.LowerLine.startPoint.y = one.rightLine.endPoint.y;
    one.LowerLine.endPoint.x = one.leftLine.startPoint.x;
    one.leftLine.endPoint.y = one.leftLine.startPoint.y;

    //Square two;
    //two.LowerLine = one.upperLine;

    drawMengerSponge(level - 1, one);

}

void doBounsTwo (int level)
{   //Construct the points for the base square
    Point one, two, three, four;
    one.x = -0.9f; one.y = -0.9f;
    two.x = -0.9f; two.y = 0.9f;
    three.x = 0.9f; three.y = 0.9f;
    four.x = 0.9f; four.y = -0.9f;

    //Get the base square and dispaly it
    Square baseSqr = getSquare(one, two, three, four);


    drawMengerSponge(1, baseSqr);
}





/**
 * ================================================================================================
 * ================================================================================================
 *
 * The following code section targets part main code
 * ================================================================================================
 * ================================================================================================
 */


void RenderScene(MyGeometry *geometry, MyShader *shader)
{
    // bind our shader program and the vertex array object containing our
    // scene geometry, then tell OpenGL to draw our geometry
    glUseProgram(shader->program);

    //buffer vertex data
    glBindVertexArray(geometry->vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, geometry->vertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*vertices.size(), &vertices[0]);

    //buffer color data
    glBindBuffer(GL_ARRAY_BUFFER, geometry->colourBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*colors.size(), &colors[0]);

    //draw and clear
    if(PART_ONE || PART_TWO)
       glDrawArrays(GL_LINES, 0, vertices.size()/2);

    if(PART_THREE)
        glDrawArrays(GL_TRIANGLES, 0, vertices.size()/2);

    vertices.clear();
    colors.clear();

    // reset state to default (no shader or geometry bound)
    glBindVertexArray(0);
    glUseProgram(0);

    // check for and report any OpenGL errors
    CheckGLErrors();
}

// --------------------------------------------------------------------------
// GLFW callback functions

// reports GLFW errors
void ErrorCallback(int error, const char* description)
{
    cout << "GLFW ERROR " << error << ":" << endl;
    cout << description << endl;
}


void F()
{
    dragonCurveList.push_back('F');
}

void L(){
    dragonCurveList.push_back('L');
}

void R()
{
    dragonCurveList.push_back('R');
}

void dragon(int n) {
    int k;
    if (n == 0)
        F();
    else {
        dragon(n-1);
        L();
        for (k = n-2; k >=0; k--) {
            dragon(k);
            R();
        }
        F();
    }
}

void displayCurve(float x, float y)
{
    float oldX = x;
    float oldY = y;
    float newX = x;
    float newY = y + 0.01f;
    bool FORWARD_LEFT = false;
    bool FORWARD_RIGHT = true;

    float incrementation = (1.0f) / 10.0f;

    bool moved_up = true;
    bool moved_right = false;

    for(int i = 0; i<dragonCurveList.size(); i++)
    {
        if(dragonCurveList[i] == 'F')
        {
            if(FORWARD_LEFT)
            {
                if(moved_right)
                {
                    cout<<"FORWARDING [LEFT] Up screen"<<endl;
                    newY += incrementation;
                    moved_up = true;
                }
                else
                {
                    cout<<"FORWARDING [LEFT] down screen"<<endl;
                    newY -= incrementation;
                    moved_up = false;
                }


                if(moved_up)
                {
                     cout<<"FORWARDING [LEFT] left screen"<<endl;
                     newX -= incrementation;
                     moved_right = false;
                } else{
                    cout<<"FORWARDING [LEFT] right screen"<<endl;
                    newX += incrementation;
                    moved_right = true;
                }

            }

            else if(FORWARD_RIGHT)
            {
                if(moved_right)
                {
                    cout<<"FORWARDING [RIGHT] down screen"<<endl;
                    newY -= incrementation;
                    moved_up = false;
                } else{
                    cout<<"FORWARDING [RIGHT] up screen"<<endl;
                    newY += incrementation;
                    moved_up = true;
                }

                if(moved_up)
                {
                    cout<<"FIRST"<<endl;
                    cout<<"FORWARDING [RIGHT] right screen"<<endl;
                    newX += incrementation;
                    moved_right = true;

                } else {

                    cout<<"FORWARDING [RIGHT] left screen"<<endl;
                    newX -= incrementation;
                    moved_right =false;
                }
            }

            bufferLine(oldX, oldY, newX, newY);
            oldX = newX;
            oldY = newY;
        }
        else if(dragonCurveList[i] == 'L')
        {
            FORWARD_LEFT = true;
            FORWARD_RIGHT = false;

        }
        else if(dragonCurveList[i] == 'R')
        {
            FORWARD_RIGHT = true;
            FORWARD_LEFT = false;
        }
    }
}

void drawDragonCurve(int level)
{
    dragon(level);

    //Dispalycurve
    cout<<"Displayng dragonCurveList elements"<<endl;
    for(int i = 0; i<dragonCurveList.size(); i++){
        cout<<dragonCurveList[i]<<endl;
    }

    displayCurve(0.5f, 0.5f);
}

// handles keyboard input events
int PART_ONE_LEVELS = 1;
int PART_TWO_LEVELS = 1;
int PART_THREE_LEVELS = 1;

void handleLeftRightKeys(){
    if(PART_ONE)
    {
        renderSquaresAndDiamonds(1);
    }
    else if(PART_TWO)
    {
        doPartTwo(1);
    }
    else if(PART_THREE)
    {
        drawSierpinskiTriangle(1);
        nextRColor = 0.4f;
        nextGColor = 0.4f;
        nextBColor = 0.4f;
    }
}

void handleUpDowntKeys(){
    if(PART_ONE)
    {
        renderSquaresAndDiamonds(PART_ONE_LEVELS);
    }
    else if(PART_TWO)
    {
        doPartTwo(PART_TWO_LEVELS);
    }
    else if(PART_THREE)
    {
        cout<<"RENDERING PART THREE"<<endl;
        drawSierpinskiTriangle(PART_THREE_LEVELS);
        nextRColor = 0.4f;
        nextGColor = 0.4f;
        nextBColor = 0.4f;
    }
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if(key == GLFW_KEY_B && action == GLFW_PRESS)
    {
       doBounsTwo(1);
    }

    if(key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        PART_ONE = true;
        handleLeftRightKeys();
    }
    if(key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        cout<<"CLIKED IN THE LEFT KEY"<<endl;

        if(PART_ONE == true)
        {
            PART_ONE = false;
            PART_TWO = false;
            PART_THREE = true;
            cout<<"NEXT IS PART THREE "<<PART_THREE<<endl;
        }
        else if(PART_TWO == true)
        {
            PART_ONE = true;
            PART_TWO = false;
            PART_THREE = false;
        }
        else if(PART_THREE == true)
        {
            PART_ONE = false;
            PART_TWO = true;
            PART_THREE = false;
        }
        handleLeftRightKeys();
    }
    if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        cout<<"CLIKED IN THE LEFT KEY"<<endl;

        if(PART_ONE == true)
        {
            PART_ONE = false;
            PART_TWO = true;
            PART_THREE = false;
        }
        else if(PART_TWO == true)
        {
            PART_ONE = false;
            PART_TWO = false;
            PART_THREE = true;
        }
        else if(PART_THREE == true)
        {
            PART_ONE = true;
            PART_TWO = false;
            PART_THREE = false;
        }
        handleLeftRightKeys();
    }
    if(key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        if(PART_ONE)
        {
            PART_ONE_LEVELS += 1;
        }
        else if(PART_TWO)
        {
            PART_TWO_LEVELS += 1;
        } else if(PART_THREE)
        {
            PART_THREE_LEVELS += 1;
        }
        handleUpDowntKeys();
    }
    if(key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        if(PART_ONE)
        {
            if(PART_ONE_LEVELS != 0)
                PART_ONE_LEVELS -= 1;
        }
        else if(PART_TWO)
        {
            if(PART_TWO_LEVELS != 0)
                PART_TWO_LEVELS -= 1;
        } else if(PART_THREE)
        {
            if(PART_THREE_LEVELS != 0)
                PART_THREE_LEVELS -= 1;
        }
        handleUpDowntKeys();
    }
}


// ==========================================================================
// PROGRAM ENTRY POINT

int main(int argc, char *argv[])
{
    // initialize the GLFW windowing system
    if (!glfwInit()) {
        cout << "ERROR: GLFW failed to initilize, TERMINATING" << endl;
        return -1;
    }
    glfwSetErrorCallback(ErrorCallback);

    // attempt to create a window with an OpenGL 4.1 core profile context
    GLFWwindow *window = 0;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(512, 512, "CPSC 453 OpenGL Boilerplate", 0, 0);
    if (!window) {
        cout << "Program failed to create GLFW window, TERMINATING" << endl;
        glfwTerminate();
        return -1;
    }

    // set keyboard callback function and make our context current (active)
    glfwSetKeyCallback(window, KeyCallback);
    glfwMakeContextCurrent(window);

    // query and print out information about our OpenGL environment
    QueryGLVersion();

    // call function to load and compile shader programs
    MyShader shader;
    if (!InitializeShaders(&shader)) {
        cout << "Program could not initialize shaders, TERMINATING" << endl;
        return -1;
    }

    // call function to create and fill buffers with geometry data
    MyGeometry geometry;
    if (!InitializeGeometry(&geometry))
        cout << "Program failed to intialize geometry!" << endl;

    // run an event-triggered main loop
    while (!glfwWindowShouldClose(window))
    {
        // call function to draw our scene
        RenderScene(&geometry, &shader);

        // scene is rendered to the back buffer, so swap to front for display
        glfwSwapBuffers(window);

        // sleep until next event before drawing again
        glfwWaitEvents();
    }

    // clean up allocated resources before exit
    DestroyGeometry(&geometry);
    DestroyShaders(&shader);
    glfwDestroyWindow(window);
    glfwTerminate();

    cout << "Goodbye!" << endl;
    return 0;
}

// ==========================================================================
// SUPPORT FUNCTION DEFINITIONS

// --------------------------------------------------------------------------
// OpenGL utility functions

void QueryGLVersion()
{
    // query opengl version and renderer information
    string version  = reinterpret_cast<const char *>(glGetString(GL_VERSION));
    string glslver  = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
    string renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));

    cout << "OpenGL [ " << version << " ] "
         << "with GLSL [ " << glslver << " ] "
         << "on renderer [ " << renderer << " ]" << endl;
}

bool CheckGLErrors()
{
    bool error = false;
    for (GLenum flag = glGetError(); flag != GL_NO_ERROR; flag = glGetError())
    {
        cout << "OpenGL ERROR:  ";
        switch (flag) {
        case GL_INVALID_ENUM:
            cout << "GL_INVALID_ENUM" << endl; break;
        case GL_INVALID_VALUE:
            cout << "GL_INVALID_VALUE" << endl; break;
        case GL_INVALID_OPERATION:
            cout << "GL_INVALID_OPERATION" << endl; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            cout << "GL_INVALID_FRAMEBUFFER_OPERATION" << endl; break;
        case GL_OUT_OF_MEMORY:
            cout << "GL_OUT_OF_MEMORY" << endl; break;
        default:
            cout << "[unknown error code]" << endl;
        }
        error = true;
    }
    return error;
}

// --------------------------------------------------------------------------
// OpenGL shader support functions

// reads a text file with the given name into a string
string LoadSource(const string &filename)
{
    string source;

    ifstream input(filename);
    if (input) {
        copy(istreambuf_iterator<char>(input),
             istreambuf_iterator<char>(),
             back_inserter(source));
        input.close();
    }
    else {
        cout << "ERROR: Could not load shader source from file "
             << filename << endl;
    }

    return source;
}

// creates and returns a shader object compiled from the given source
GLuint CompileShader(GLenum shaderType, const string &source)
{
    // allocate shader object name
    GLuint shaderObject = glCreateShader(shaderType);

    // try compiling the source as a shader of the given type
    const GLchar *source_ptr = source.c_str();
    glShaderSource(shaderObject, 1, &source_ptr, 0);
    glCompileShader(shaderObject);

    // retrieve compile status
    GLint status;
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint length;
        glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &length);
        string info(length, ' ');
        glGetShaderInfoLog(shaderObject, info.length(), &length, &info[0]);
        cout << "ERROR compiling shader:" << endl << endl;
        cout << source << endl;
        cout << info << endl;
    }

    return shaderObject;
}

// creates and returns a program object linked from vertex and fragment shaders
GLuint LinkProgram(GLuint vertexShader, GLuint fragmentShader)
{
    // allocate program object name
    GLuint programObject = glCreateProgram();

    // attach provided shader objects to this program
    if (vertexShader)   glAttachShader(programObject, vertexShader);
    if (fragmentShader) glAttachShader(programObject, fragmentShader);

    // try linking the program with given attachments
    glLinkProgram(programObject);

    // retrieve link status
    GLint status;
    glGetProgramiv(programObject, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint length;
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &length);
        string info(length, ' ');
        glGetProgramInfoLog(programObject, info.length(), &length, &info[0]);
        cout << "ERROR linking shader program:" << endl;
        cout << info << endl;
    }

    return programObject;
}
// ==========================================================================
