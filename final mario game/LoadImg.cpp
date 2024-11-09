#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <windows.h> // Include Windows API for PlaySound


// Forward declarations
void update(int value);

// Window dimensions
const int windowWidth = 800;
const int windowHeight = 600;

// Structure to hold RGBA data for each pixmap
struct RGBAPixmap {
    int width, height;
    unsigned char* pixels = nullptr;

    bool loadBMP(const char* filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Failed to open BMP file: " << filename << std::endl;
            return false;
        }
        std::cerr << "Successfully opened BMP file: " << filename << std::endl;  // Debugging

        unsigned char header[54];
        file.read(reinterpret_cast<char*>(header), 54);
        if (header[0] != 'B' || header[1] != 'M') {
            std::cerr << "Not a valid BMP file: " << filename << std::endl;
            return false;
        }

        width = *(int*)&header[18];
        height = *(int*)&header[22];

        int row_padded = (width * 3 + 3) & (~3);
        unsigned char* row_data = new unsigned char[row_padded];
        pixels = new unsigned char[width * height * 4];

        for (int y = 0; y < height; y++) {
            file.read(reinterpret_cast<char*>(row_data), row_padded);
            for (int x = 0; x < width; x++) {
                int bmp_index = x * 3;
                int pix_index = ((height - 1 - y) * width + x) * 4;
                unsigned char red = row_data[bmp_index + 2];
                unsigned char green = row_data[bmp_index + 1];
                unsigned char blue = row_data[bmp_index];

                pixels[pix_index] = red;
                pixels[pix_index + 1] = green;
                pixels[pix_index + 2] = blue;
                // Set alpha to 0 for white background, otherwise 255
                pixels[pix_index + 3] = (red == 255 && green == 255 && blue == 255) ? 0 : 255;
            }
        }

        delete[] row_data;
        file.close();
        return true;
    }

    ~RGBAPixmap() {
        if (pixels) {
            delete[] pixels;
        }
    }
};

// Spider data
RGBAPixmap marioPixmaps[5];
float marioX = 100.0f;
float marioY = 270.0f;
float marioVelocityX = 2.0f;
float marioVelocityY = 4.0f;
float marioWidth = 50.0f;
float marioHeight = 50.0f;




// Game state


bool gameOver = false;
int currentMarioImage = 0;

// Function to load spider images
void loadMarioPixmaps() {
    marioPixmaps[0].loadBMP("MarioStanding.bmp");
    marioPixmaps[1].loadBMP("MarioRun1.bmp");
    marioPixmaps[2].loadBMP("MarioRun2.bmp");
    marioPixmaps[3].loadBMP("MarioRun3.bmp");
    marioPixmaps[4].loadBMP("MarioJump.bmp");

}



// Draw the spider
void drawSpider(float x, float y, int index) {
    RGBAPixmap& pixmap = marioPixmaps[index];
    glRasterPos2f(x, windowHeight - (y + pixmap.height));
    glDrawPixels(pixmap.width, pixmap.height, GL_RGBA, GL_UNSIGNED_BYTE, pixmap.pixels);
}




//Rest the game state when player press "R" 
void resetGame() {
    marioX = 300.0f;
    marioY = 100.0f;
    marioVelocityX = 2.0f;
    marioVelocityY = 4.0f;
    gameOver = false;
    currentMarioImage = 0;
}



void drawGun(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    // Draw the gun's main body (larger rectangle with gradient)
    glColor3f(124.0f / 255.0f, 252.0f / 255.0f, 0 / 255.0f); // Dark gray
    glBegin(GL_QUADS);
    glVertex2f(-400, -50);  // Bottom-left
    glVertex2f(400, -50);   // Bottom-right
    glVertex2f(400, 150);   // Top-right
    glVertex2f(-400, 150);  // Top-left
    glEnd();

    glPopMatrix();
}



// Display the game
void display() {
    glClear(GL_COLOR_BUFFER_BIT);


    // Draw spider based on game state
    
    drawSpider(marioX, marioY, currentMarioImage);

    drawGun(400.0f, 50.0f);

    if (gameOver) {
        glColor3f(1.0f, 1.0f, 0.0f); // Red text
        glRasterPos2f(windowWidth / 2 - 50, windowHeight / 2);
        const char* message = "Game Over! Press 'R' to play again.";
        for (const char* c = message; *c; ++c) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }
    }

    glutSwapBuffers();
}



// Handle key presses
void handleKeyPress(unsigned char key, int x, int y) {
    switch (key) {
    case 27: // ESC key to quit
        exit(0);
        break;
    }
}


void updateSpider() {

    if (currentMarioImage == 0) {
        currentMarioImage = 1;
    }
    else if (currentMarioImage == 1) {
        currentMarioImage = 2;
    }
    else if (currentMarioImage == 2) {
        currentMarioImage = 3;
    }
    else if (currentMarioImage == 3) {
        currentMarioImage = 1;
    }
    else if (currentMarioImage == 4) {
        currentMarioImage = 0;
    }
}


// Handle special key presses (e.g., arrow keys)
void handleSpecialKeyPress(int key, int x, int y) {
    const float moveStepX = 15.0f; // Movement step size
    const float moveStepY = 40.0f; // Movement step size


    const float jumpHeight = 40.0f; // Maximum jump height
    const int jumpDelay = 20; // Delay in milliseconds

    static bool isJumping = false;
    static float initialMarioY = windowHeight / 2.0f;
    static int jumpStartTime = 0; // Store the start time of the jump



    switch (key) {
    case GLUT_KEY_LEFT:

        updateSpider();
        drawSpider(marioX, marioY, currentMarioImage);
        marioX -= moveStepX;

        if (marioX < 0) {
            marioX = 0; // Prevent gun from moving out of the left boundary
        }
        break;

    case GLUT_KEY_RIGHT:

        updateSpider();
        drawSpider(marioX, marioY, currentMarioImage);
        marioX += moveStepX;
        if (marioX + marioWidth > windowWidth) {
            marioX = windowWidth - marioWidth; // Prevent gun from moving out of the right boundary
        }
        break;


    case GLUT_KEY_UP:
        //int tempSpiderImage = currentSpiderImage;
        if (!isJumping) {
            isJumping = true;
            initialMarioY = marioY;
            jumpStartTime = glutGet(GLUT_ELAPSED_TIME); // Record the start time
        }
        currentMarioImage = 4;
        drawSpider(marioX, marioY, currentMarioImage);
        break;
    }

    // Handle the jump logic
    if (isJumping) {
        marioY -= moveStepY;
        

        // Prevent going above the top boundary
        if (marioY < 0) {
            marioY = 0;
        }

        // Check if the jump is complete and reset position
        if (marioY <= initialMarioY - jumpHeight) {
            int elapsedTime = glutGet(GLUT_ELAPSED_TIME) - jumpStartTime;
            if (elapsedTime >= jumpDelay) {
                isJumping = false;
                marioY = initialMarioY;
            }
        }
    }
}




// Update game logic
void update(int value) {
    if (!gameOver) {
        glutPostRedisplay();
        glutTimerFunc(16, update, 0); // Call update every 16ms (60 FPS)
    }
}

// Initialize OpenGL settings
void initGL() {
    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background
    glClearColor(173.0f / 255.0f, 216.0f / 255.0f, 230.0f / 255.0f, 0.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Enable alpha blending
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main(int argc, char** argv) {
    loadMarioPixmaps();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Shooting Game");



    initGL();


    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeyPress);
    glutSpecialFunc(handleSpecialKeyPress); // Handle special keys like arrow keys
    //glutKeyboardUpFunc(handleKeyRelease);
    glutTimerFunc(25, update, 0); // Start the update function

    glutMainLoop();
    return 0;
}

