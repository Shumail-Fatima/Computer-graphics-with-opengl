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
RGBAPixmap spiderPixmaps[3];
float spiderX = 100.0f;
float spiderY = 300.0f;
float spiderVelocityX = 2.0f;
float spiderVelocityY = 4.0f;
float spiderWidth = 50.0f;
float spiderHeight = 50.0f;

// Gun data
float gunX = 400.0f;
const float gunY = 50.0f;
const float gunWidth = 50.0f;
const float gunHeight = 20.0f;
const float gunSpeed = 20.0f;  // Increased speed

// Bullet data
struct Bullet {
    float x, y;
    bool active;
};

std::vector<Bullet> bullets;
const float bulletSpeed = 5.0f;
const int maxBullets = 5;

// Game state
bool gameOver = false;
bool spiderHit = false;
bool spiderDead = false;
int currentSpiderImage = 0;
int hitFrameCount = 0;

// Function to load spider images
void loadSpiderPixmaps() {
    spiderPixmaps[0].loadBMP("spider_alive.bmp");
    spiderPixmaps[1].loadBMP("spider_hit.bmp");
    spiderPixmaps[2].loadBMP("spider_dead.bmp");
}

// Function to play bullet sound
void playBulletSound() {
    PlaySound(TEXT("bullet_fire.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

// Update spider position and check boundaries
void updateSpiderPosition() {
    if (!gameOver && !spiderDead) {
        spiderX += spiderVelocityX;
        spiderY += spiderVelocityY;

        if (spiderX <= 0 || spiderX + spiderWidth >= windowWidth) {
            spiderVelocityX = -spiderVelocityX;
        }
        if (spiderY <= 0 || spiderY + spiderHeight >= windowHeight) {
            spiderVelocityY = -spiderVelocityY;
        }
    }
}

// Update bullets
void updateBullets() {
    for (auto& bullet : bullets) {
        if (bullet.active) {
            bullet.y += bulletSpeed;
            if (bullet.y > windowHeight) {
                bullet.active = false;
            }
            if (bullet.x >= spiderX && bullet.x <= spiderX + spiderWidth &&
                bullet.y >= spiderY && bullet.y <= spiderY + spiderHeight) {
                spiderHit = true;
                bullet.active = false;
                hitFrameCount = 10;  // Show hit image for a short time
            }
        }
    }
    // Remove inactive bullets
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](const Bullet& b) { return !b.active; }),
        bullets.end());
}

// Draw the spider
void drawSpider(float x, float y, int index) {
    RGBAPixmap& pixmap = spiderPixmaps[index];
    glRasterPos2f(x, windowHeight - (y + pixmap.height));
    glDrawPixels(pixmap.width, pixmap.height, GL_RGBA, GL_UNSIGNED_BYTE, pixmap.pixels);
}

// Draw the gun
void drawGun(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    // Draw the gun's main body (larger rectangle with gradient)
    glColor3f(92.0f/225.0f, 64.0f/225.0f, 51.0f/225.0f); // Dark gray
    glBegin(GL_QUADS);
    glVertex2f(-15, -5);  // Bottom-left
    glVertex2f(15, -5);   // Bottom-right
    glVertex2f(15, 10);   // Top-right
    glVertex2f(-15, 10);  // Top-left
    glEnd();

    glColor3f(150.0f / 225.0f, 75.0f / 225.0f, 0.0f / 225.0f); // Red
    glBegin(GL_TRIANGLES);
    glVertex2f(-15.0f, 10.0f); // Base (left)
    glVertex2f(15.0f, 10.0f);  // Base (right)
    glVertex2f(0.0f, 30.0f);   // Top
    glEnd();

   /* // Draw the gun's barrel (rectangular with shading)
    glColor3f(0.3f, 0.3f, 0.3f); // Medium gray
    glBegin(GL_QUADS);
    glVertex2f(-12, 10);   // Bottom-left
    glVertex2f(12, 10);    // Bottom-right
    glVertex2f(12, 20);    // Top-right
    glVertex2f(-12, 20);   // Top-left
    glEnd();*/

    // Draw the gun's trigger
    glColor3f(0.1f, 0.1f, 0.1f); // Black
    glBegin(GL_QUADS);
    glVertex2f(-5, -5);     // Bottom-left
    glVertex2f(5, -5);      // Bottom-right
    glVertex2f(1, -15);     // Top-right
    glVertex2f(-1, -15);    // Top-left
    glEnd();

    /*
    // Draw the gun's stock (rectangle)
    glColor3f(0.2f, 0.2f, 0.2f); // Dark gray
    glBegin(GL_QUADS);
    glVertex2f(-20, -5);   // Bottom-left
    glVertex2f(-15, -5);   // Bottom-right
    glVertex2f(-15, 5);    // Top-right
    glVertex2f(-20, 5);    // Top-left
    glEnd();*/

    // Draw the gun's sight (triangle)
    glColor3f(0.3f, 0.3f, 0.3f); // Red
    glBegin(GL_TRIANGLES);
    glVertex2f(-2.0f, 30.0f); // Base (left)
    glVertex2f(2.0f, 30.0f);  // Base (right)
    glVertex2f(0.0f, 40.0f);   // Top
    glEnd();

    glPopMatrix();
}


// Draw a bullet
void drawBullet(float x, float y) {
    glColor3f(1.0f, 0.0f, 0.0f); // Red bullet
    glRectf(x - 2, y, x + 2, y + 10);
}

// Draw all bullets
void drawBullets() {
    for (const auto& bullet : bullets) {
        if (bullet.active) {
            drawBullet(bullet.x, bullet.y);
        }
    }
}

//Rest the game state when player press "R" 
void resetGame() {
    spiderX = 100.0f;
    spiderY = 300.0f;
    spiderVelocityX = 2.0f;
    spiderVelocityY = 4.0f;
    spiderDead = false;
    spiderHit = false;
    gameOver = false;
    bullets.clear(); // Clear existing bullets
    hitFrameCount = 0;
    currentSpiderImage = 0;
}




// Display the game
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the gun
    drawGun(gunX, gunY);

    // Draw bullets
    drawBullets();

    // Draw spider based on game state
    if (spiderHit) {
        if (!spiderDead && hitFrameCount > 0) {
            currentSpiderImage = 1; // Show hit image
            hitFrameCount--;
        }
        else {
            currentSpiderImage = 2; // Show dead image
            spiderDead = true; // Spider is dead
            gameOver = true;  // End game
        }
    }
    else if (spiderDead) {
        currentSpiderImage = 2; // Show dead image
    }
    else {
        currentSpiderImage = 0; // Show alive image
    }
    drawSpider(spiderX, spiderY, currentSpiderImage);

    if (gameOver) {
        glColor3f(0.0f, 0.0f, 0.0f); // Red text
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
    case ' ':
        if (!gameOver && bullets.size() < maxBullets) {
            Bullet newBullet;
            newBullet.x = gunX;
            newBullet.y = gunY + gunHeight;
            newBullet.active = true;
            bullets.push_back(newBullet);
            playBulletSound(); // Play sound when firing a bullet
        }
        break;
    case 'r': // Press 'R' to restart the game
    case 'R':
        if (gameOver) {
            resetGame();
            glutPostRedisplay(); // Redraw the game after resetting
            glutTimerFunc(16, update, 0); // Restart the game loop
        }
        break;
    }
}


// Handle special key presses (e.g., arrow keys)
void handleSpecialKeyPress(int key, int x, int y) {
    const float moveStep = 10.0f; // Movement step size

    switch (key) {
    case GLUT_KEY_LEFT:
        gunX -= moveStep;
        if (gunX < 0) {
            gunX = 0; // Prevent gun from moving out of the left boundary
        }
        break;
    case GLUT_KEY_RIGHT:
        gunX += moveStep;
        if (gunX + gunWidth > windowWidth) {
            gunX = windowWidth - gunWidth; // Prevent gun from moving out of the right boundary
        }
        break;
    }
}

// Handle key releases
void handleKeyRelease(unsigned char key, int x, int y) {
    // Nothing to do for key release events in this example
}

// Update game logic
void update(int value) {
    if (!gameOver) {
        updateSpiderPosition();
        updateBullets();
        glutPostRedisplay();
        glutTimerFunc(16, update, 0); // Call update every 16ms (60 FPS)
    }
}

// Initialize OpenGL settings
void initGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Black background
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Enable alpha blending
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main(int argc, char** argv) {
    loadSpiderPixmaps();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Shooting Game");

    initGL();

    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeyPress);
    glutSpecialFunc(handleSpecialKeyPress); // Handle special keys like arrow keys
    glutKeyboardUpFunc(handleKeyRelease);
    glutTimerFunc(25, update, 0); // Start the update function

    glutMainLoop();
    return 0;
}

