// End Semester Project for fundamentals of computer programming
// Developed by Ahmad Imran
// Instructor: Jaudat Mamoon
// Libraries utilized
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <string.h>
#include <math.h>

// Function prototypes
void coordinates();
int DisplayMenuChest1( bool *menuOpen, int actualpass1);
int DisplayMenuChest2( bool *menuOpen);
int DisplayMenuChest3( bool *menuOpen, int actualpass2);
int DisplayMenuChest4( bool *menuOpen);
bool IsMouseOverRect(Rectangle rect, int mouseX, int mouseY);
int CheckGuessPass(int guess,int actual);
int CheckGuessWords(int guess,int actual);
void commentsPass(int,int);
void openingMenu(bool *, bool *, Font, Font);

// Constants declaration
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

// Player Settings
typedef struct {
    float speed;
    int dir;
    bool moving;
    int Frame;
} Player;
Player playerGame;
void handlePlayerMovement(Player *player, Rectangle *destPlayer);
void changeSrcPlayer(Rectangle *srcPlayer, Player *player, float manWidth, float manHeight);

// Framecount for player texture update
int FrameCount = 0;

// Required Bools
bool nextMenuChest1 = false;
bool backMenuChest1 = false;

bool nextMenuChest2 = false;
bool backMenuChest2 = false;
bool nextMenuChest2_2 = false;
bool backMenuChest2_2 = false;
bool nextMenuChest2_3 = false;
bool backMenuChest2_3 = false;

bool nextMenuChest3 = false;
bool backMenuChest3 = false;

bool nextMenuChest4 = false;
bool backMenuChest4 = false;
bool nextMenuChest4_2 = false;
bool backMenuChest4_2 = false;
bool nextMenuChest4_3 = false;
bool backMenuChest4_3 = false;

bool ansQues1 = false;
bool ansQues2 = false;
bool ansQues3 = false;

char guessPassChar[5];
int guessPass = 0;

char guessPassChar2[4];
int guessPass2 = 0;

char wordGuess1[7];
char wordGuess2[9];
char wordGuess3[8];
char wordGuess4[9];

char wordGuess4_1[6];
char wordGuess4_2[9];
char wordGuess4_3[8];
char wordGuess4_4[9];

bool ansQues4_1 = false;
bool ansQues4_2 = false;
bool ansQues4_3 = false;

bool showInventory = false;
bool notBack = false;

bool showKey1 = false;
bool showKey2 = false;
bool showKey3 = false;
bool showApple = false;

bool startGame = false;
bool backGame = true;

bool closeAbout = false;
bool openAbout = false;

bool closeInst = false;

// Opening menu line
float timeForLine = 0.0f;
float lineLength = 0.0f;


int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Escape");
    SetTargetFPS(60);  
    // Textures 
    Texture2D prison = LoadTexture("resources/Walls.png");
    Texture2D bed = LoadTexture("resources/bed.png");
    Texture2D player = LoadTexture("resources/prison_jumpsuit-24x32.png");
    Texture2D chest = LoadTexture("resources/treasure_chests_32x32.png"); 
    Texture2D door = LoadTexture("resources/celldoor2.png");
    Texture2D desk = LoadTexture("resources/table1.png");
    Texture2D key1 = LoadTexture("resources/Key 1 - GOLD - .png");
    Texture2D key2 = LoadTexture("resources/Key 6 - GOLD - frame0001.png");
    Texture2D key3 = LoadTexture("resources/Key 11 - GOLD - frame0000.png");
    Texture2D apple = LoadTexture("resources/Texture_pack_Golden_apple.png");

    // Fonts
    Font menuFont = LoadFont("resources/Utopia Font.otf");// 
    Font formalFont = LoadFont("resources/anonymous_pro_bold.ttf");

    // Player Settings
    playerGame.speed = 3.0;
    playerGame.Frame = 0;
    float manWidth = (float)player.width/ 3.0f ; 
    float manHeight = (float)player.height / 4.0f;  
    Rectangle sourcePlayer = { 25, 64, 20, 33 };   
    Rectangle destPlayer = { 400, 250, manWidth*4.5, manHeight*3.5 };  
    Vector2 originPlayer = { 0, 0 }; 
    float rotationAnglePlayer = 0.0f;

    // Chest Settings
    float chestWidth = (float)chest.width / 10.0f;
    float chestHeight = (float)chest.height / 12.0f;
    Rectangle sourceChest1 = { -3, 66, 37, 27 };   
    Rectangle destChest1 = { 423, 40, chestWidth*8,chestHeight*3 }; 
    Rectangle sourceChest2 = { 29, 4, 37, 27 };
    Rectangle destChest2 = { 588, 564, chestWidth*8,chestHeight*3 }; 
    Rectangle sourceChest3 = { 125, 66, 37, 27 };
    Rectangle destChest3 = { 91, 40, chestWidth*8,chestHeight*3 };
    Rectangle sourceChest4 = { 220, 4, 37, 27 };
    Rectangle destChest4 = { 258, 560, chestWidth*8,chestHeight*3 };
    Vector2 originChest = { (chestWidth*3)/2, (chestHeight*3)/2 }; 
    float rotationAngleChest = 0.0f;
    Rectangle destChest2open = { 422, 529, chestWidth*8,chestHeight*3 }; 
    Rectangle destChest4open = { 85, 525, chestWidth*8,chestHeight*3 };

    // Door Setting
    Rectangle sourceDoor = { 0 , 0 , (float)door.width , (float)door.height };
    Rectangle destDoor = { 820, 4, (float)door.width/3, (float)door.height/3 };
    Vector2 originDoor = { 0, 0 }; 
    float rotationAngleDoor = -270.0f;

    // Desk setting
    Rectangle sourceDesk = { 0, 0, (float)desk.width, (float)desk.height };
    Rectangle destDesk = { 824, 175, (float)desk.width/4, (float)desk.height/5 };
    Vector2 originDesk = { 0, 0 }; 
    float rotationAngleDesk = 0.0f;

    // Menu settings
    bool menuOpenChest1 = false;
    bool menuOpenChest2 = false;
    bool menuOpenChest3 = false;
    bool menuOpenChest4 = false;

    // GUI
    GuiLoadStyle("resources/style_cherry.rgs");

    // Passwords for minigame
    int actualPass1 = GetRandomValue(100,999);
    int actualPass2 = GetRandomValue(1,100);

    // Settings for door
    Rectangle doorOpenMenu = { 714, 62, 50, 50 };
    bool doorMenuOpen = false;
    bool doorMenuClose = false;
    bool openDoor = false;

    //GetMouseX()

    while (!WindowShouldClose()) // Game Loop Start
    { 
        BeginDrawing();
        ClearBackground(WHITE);

        if(backGame) // if for opening Menu start
        {
            openingMenu(&startGame, &backGame, menuFont, formalFont);
        } // if for opening Menu end

        if(startGame && !backGame) // Actual Game If start
        { 
            // Drawing Textures
            DrawTexture(prison, 0, 0, WHITE);
            DrawTexture(bed, 850, 4, WHITE);
            DrawTexturePro(player, sourcePlayer, destPlayer, originPlayer, rotationAnglePlayer, WHITE);
            DrawTexturePro(chest, sourceChest1, destChest1, originChest, rotationAngleChest, WHITE);
            DrawTexturePro(chest, sourceChest2, destChest2, originChest, 180.0f, WHITE);
            DrawTexturePro(chest, sourceChest3, destChest3, originChest, rotationAngleChest, WHITE);
            DrawTexturePro(chest, sourceChest4, destChest4, originChest, 180.0f, WHITE);
            DrawTexturePro(desk, sourceDesk, destDesk, originDesk, rotationAngleDesk, WHITE);
            DrawTexturePro(door, sourceDoor, destDoor, originDoor, rotationAngleDoor, WHITE);

            // DrawText(TextFormat("%d\t %d", actualPass1, actualPass2), 446, 310, 35, BLACK); // Enable this for devlopmental purpose only


            if(!closeInst) // if for instruction start
            {
                DrawRectangleGradientEx((Rectangle){244, 90, 500, 250}, BLACK, DARKPURPLE, DARKBLUE, PINK);
                DrawTextPro(formalFont, "Escape if you can by\n\n\nunlocking these chests\n\n\n(click on them)otherwise\n\n\nforever you will abide her\n\n\ne.hahahaha!", (Vector2){260, 125}, (Vector2){0, 0}, 0, 25, 5, WHITE);
                if (GuiButton((Rectangle){640, 90, 105, 40}, "Close"))
                {
                    closeInst = true;
                }                
            } // if for instruction end
                   
            // Inventory Setting start
            if (GuiButton((Rectangle){0, 100, 75, 50}, "I"))
            {
                showInventory = true;
            }
            if(showInventory)
            {
                DrawRectangleLines(0,155,75,50,BLACK);
                DrawRectangleLines(0,205,75,50,BLACK);
                DrawRectangleLines(0,255,75,50,BLACK);
                DrawRectangleLines(0,305,75,50,BLACK);
                if (GuiButton((Rectangle){0, 360, 75, 50}, "C") && !notBack)
                {
                    showInventory = false;
                }
            }
            // End Inventory Settings

            // Function for player movement handling
            handlePlayerMovement(&playerGame,  &destPlayer);

            // Function for player source handling(change player on spritesheet as per input)
            changeSrcPlayer(&sourcePlayer, &playerGame, manWidth, manHeight);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                // code to detect whether a person has clicked a chest or not (start)
                if (IsMouseOverRect(destChest1, GetMouseX(), GetMouseY()))
                {
                    menuOpenChest1 = true;
                }
                else if (IsMouseOverRect(destChest3, GetMouseX(), GetMouseY()))
                {
                    menuOpenChest2 = true;
                }
                else if (IsMouseOverRect(destChest4open, GetMouseX(), GetMouseY()))
                {
                menuOpenChest3 = true;
                }
                else if (IsMouseOverRect(destChest2open, GetMouseX(), GetMouseY()))
                {
                    menuOpenChest4 = true;
                }
                 // code to detect whether a person has clicked a chest or not (end)
            } 

            // Chest menu ifs (start)
            if (menuOpenChest1)
            {
                if(DisplayMenuChest1( &menuOpenChest1, actualPass1))
                {
                    sourceChest1.y = 96;
                    sourceChest1.height = 29;
                    showInventory = true;
                    showKey1 = true;
                    notBack = true;            
                }     
            }

            else if (menuOpenChest2)
            {
                if(DisplayMenuChest2( &menuOpenChest2))
                {
                    sourceChest3.y = 96;
                    sourceChest3.height = 29;
                    DrawRectangleGradientH(244, 90, 500, 450, RED, PINK);
                    DrawText("Congrats\n\n\nKey is in your\n\n\ninventory!", 300, 209, 45, DARKPURPLE);
                    showInventory = true;
                    showKey2 = true;
                    notBack = true;
                    if (GuiButton((Rectangle){640, 90, 105, 40}, "Close"))
                    {
                        menuOpenChest2 = false;
                    }
                }     
            }

            else if (menuOpenChest3)
            {
                if(DisplayMenuChest3( &menuOpenChest3, actualPass2))
                {
                    sourceChest4.y = 96;
                    sourceChest4.height = 29;
                    DrawRectangleGradientH(244, 90, 500, 450, DARKGRAY, PINK);
                    DrawText("Congrats\n\n\nGolden Apple is in\n\n\nyour inventory", 300, 209, 45, RAYWHITE);
                    showInventory = true;
                    showKey3 = true;
                    notBack = true;
                    if (GuiButton((Rectangle){640, 90, 105, 40}, "Close"))
                    {
                        menuOpenChest3 = false;
                    }                
                }     
            }

            else if (menuOpenChest4)
            {
                if(DisplayMenuChest4( &menuOpenChest4))
                {
                    sourceChest2.y = 96;
                    sourceChest2.height = 29;
                    DrawRectangleGradientH(244, 90, 500, 450, RED, PINK);
                    DrawText("Congrats\n\n\napple is in your\n\n\ninventory!", 300, 209, 45, DARKPURPLE);
                    showInventory = true;
                    showApple = true;
                    notBack = true;
                    if (GuiButton((Rectangle){640, 90, 105, 40}, "Close"))
                    {
                        menuOpenChest4 = false;
                    }
                }  
            } // Chest menu ifs (end)

            if(notBack)
            {
                // Shows respective chest element if a person has cracked them
                if(showKey1)
                {
                    DrawTexturePro(key1, (Rectangle){0,0,35,10}, (Rectangle){5, 170, (float)key1.width*2, (float)key1.height*2}, (Vector2){0,0}, 0.0f, WHITE);
                }
                if(showKey2)
                {
                    DrawTexturePro(key2, (Rectangle){0,0,35,15}, (Rectangle){5, 215, (float)key2.width*2, (float)key2.height*2}, (Vector2){0,0}, 0.0f, WHITE);
                }
                if(showKey3)
                {
                    DrawTexturePro(key3, (Rectangle){0,0,25,11}, (Rectangle){5, 270, (float)key2.width*2, (float)key2.height*2}, (Vector2){0,0}, 0.0f, WHITE);
                }
                if(showApple)
                {
                    DrawTexturePro(apple, (Rectangle){0,0,16,16}, (Rectangle){10, 310, (float)apple.width*2, (float)apple.height*2}, (Vector2){0,0}, 0.0f, WHITE);
                }
            }

            // ifs for door menu 

            if(IsMouseOverRect(doorOpenMenu , GetMouseX(), GetMouseY()) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                doorMenuOpen = true;
                doorMenuClose = false;
                openDoor = showKey1 && showKey2 && showKey3;
            }

            if(doorMenuOpen && !doorMenuClose)
            {
                DrawRectangleGradientH(244, 90, 500, 450, PINK, DARKPURPLE);
                if(openDoor){
                    DrawText("CONGRATS!!!\n\n\nYou have completed\n\n\nthe game", 280, 150, 45, RAYWHITE);
                }
                else{
                    DrawText("Where are the keys?", 280, 150, 35, WHITE);
                }
                if (GuiButton((Rectangle){640, 90, 105, 40}, "Close"))
                {
                    doorMenuClose = true;
                }
            }

            // Button to go back to opening menu
            if (GuiButton((Rectangle){0, 18, 75, 50}, "B"))
            {
                backGame = true;
            }
        }// Actual Game If end

        //coordinates(); // enable for developmental purposes
        EndDrawing();
    } // Game Loop End
    UnloadTexture(player);
    UnloadTexture(prison);
    UnloadTexture(bed);
    UnloadTexture(chest);
    UnloadTexture(door);
    UnloadTexture(desk);
    UnloadTexture(key1);
    UnloadTexture(key2);
    UnloadTexture(key3);
    UnloadTexture(apple);
    UnloadFont(menuFont);
    UnloadFont(formalFont);
    CloseWindow();

    return 0;
}


void coordinates(){
    // Getting x,y coordinates from mouse location
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    DrawText(TextFormat("Mouse Position: (%d, %d)", mouseX, mouseY), 10, 10, 20, BLACK);
}


bool IsMouseOverRect(Rectangle rect, int mouseX, int mouseY)
{
    // Collision Detection 
    return (CheckCollisionPointRec((Vector2){ (float)mouseX, (float)mouseY }, rect));
}

// Red Chest Functions
int DisplayMenuChest1( bool *menuOpenChest1, int actualpass1)
{
    // Rectangle 
    DrawRectangleGradientH(244, 90, 500, 450, BLACK, RED);
    // Button Close
    if (GuiButton((Rectangle){640, 90, 105, 40}, "Close"))
    {
        *menuOpenChest1 = false;
    }
    // Minigame logic
    DrawText("To open this chest you\n\n\nneed to win a minigame!!!!!",251,201,35,RAYWHITE);
    // Next button
    if (GuiButton((Rectangle){415, 500, 140, 40}, "NEXT"))
    {
        nextMenuChest1 = true;
        backMenuChest1 = false;
    }
    if (nextMenuChest1 && !backMenuChest1)
    {
        DrawRectangleGradientV(244, 90, 500, 450, BLUE, PURPLE);
        DrawText("Prison Guards have a password on it.\n\nGuess it!!!", 280, 150, 25, WHITE);
        DrawRectangleLines(280, 220, 150, 30, BLACK);
        GuiTextBox((Rectangle){280, 220, 150, 30}, guessPassChar, 5, true);
        guessPass = TextToInteger(guessPassChar);
        commentsPass(actualpass1, guessPass);


        if(CheckGuessPass(actualpass1, guessPass))
        {
            if (GuiButton((Rectangle){644, 90, 100, 40}, "X"))
            {
                nextMenuChest1 = false; 
            }
            return 1;
        }
        // Close button for the new menu
        if (GuiButton((Rectangle){644, 90, 100, 40}, "X"))
        {
            nextMenuChest1 = false; 
        }
        // Back Button
        if (GuiButton((Rectangle){244, 90, 100, 40}, "BACK"))
        {
           backMenuChest1 = true;
        }
        return 0;
    }
    return 0;
}

int CheckGuessPass(int guess,int actual)
{
    return guess == actual;
}
void commentsPass(int actualPass1,int GuessPass) 
{  // comments to help the player
    if ( guessPass != 0)
    {
        if (actualPass1 == guessPass)
        {
            DrawText("Congrats\n\n\nkey is in your\n\n\ninventory!", 334, 291, 45, PURPLE);
        }
        else if (actualPass1 > guessPass)
        {
            DrawText("Higher guess\n\n\n might work!!!", 334, 291, 30, RED);
        }
        else if (actualPass1 < guessPass)
        {
            DrawText("Lower guess might\n\n\n work!", 334, 291, 30, RED);
        }
    }
    
}
// Purple Chest Functions
int DisplayMenuChest2( bool *menuOpenChest2)
{
    // Rectangle 
    DrawRectangleGradientH(244, 90, 500, 450, BLACK, DARKPURPLE);
    // Button Close
    if (GuiButton((Rectangle){640, 90, 105, 40}, "Close"))
    {
        *menuOpenChest2 = false;
    }
    // Minigame logic
    DrawText("To open this chest you\n\n\nneed to win a minigame!!!!!",251,201,35,RAYWHITE);
    // Next button
    if (GuiButton((Rectangle){415, 500, 140, 40}, "NEXT"))
    {
        nextMenuChest2 = true;
        backMenuChest2 = false;
    }
    if (nextMenuChest2 && !backMenuChest2)
    {
        if(!ansQues1)
        {
            DrawRectangleGradientV(244, 90, 500, 450, PINK, PURPLE);
            DrawText("Guess these words correctly!!!", 280, 150, 25, WHITE);
            GuiTextBox((Rectangle){370, 220, 250, 30}, wordGuess1, 8, true);
            DrawText("\"yhcrana\"", 370, 260, 50, Fade(GRAY, 0.7f));
        }


        if(strcmp("anarchy", wordGuess1) == 0 )
        {
            if(GuiButton((Rectangle){415, 500, 140, 40}, "NEXT"))
            {
                ansQues1 = true;
                backMenuChest2_2 = false;
                nextMenuChest2_2 = true;
            }   
        }

        if(nextMenuChest2_2 && !backMenuChest2_2 && !ansQues2)
        {
            DrawRectangleGradientH(244, 90, 500, 450, PINK, BLACK);
            GuiTextBox((Rectangle){350, 220, 250, 30}, wordGuess2, 10, true);
            DrawText("\"ehpmonane\"", 350, 260, 50, Fade(WHITE, 0.7f));
        }

        if(strcmp("phenomena", wordGuess2) == 0 )
        {
            if(GuiButton((Rectangle){415, 500, 140, 40}, "NEXT"))
            {
                ansQues2 = true;
                backMenuChest2_3 = false;
                nextMenuChest2_3 = true;
            }   
        }
        if(nextMenuChest2_3 && !backMenuChest2_3 && !ansQues3)
        {
            DrawRectangleGradientH(244, 90, 500, 450, PINK, WHITE);
            GuiTextBox((Rectangle){350, 220, 250, 30}, wordGuess3, 9, true);
            DrawText("\"roabetga\"", 350, 260, 50, Fade(WHITE, 0.7f));
        }
        if(strcmp("abrogate", wordGuess3) == 0 )
        {
            return 1;  
        }
        
        // Close button for the new menu
        if (GuiButton((Rectangle){644, 90, 100, 40}, "X"))
        {
            nextMenuChest2 = false; // Close the new menu when the button is pressed
        }
        // Back Button
        if (GuiButton((Rectangle){244, 90, 100, 40}, "BACK"))
        {
           backMenuChest2 = true;
        }
        return 0;
    }
    return 0;
}
// Black Chest
int DisplayMenuChest3( bool *menuOpenChest3, int actualpass2)
{
    // Rectangle 
    DrawRectangleGradientH(244, 90, 500, 450, BLACK, RAYWHITE);
    // Button Close
    if (GuiButton((Rectangle){640, 90, 105, 40}, "Close"))
    {
        *menuOpenChest3 = false;
    }
    // Minigame logic
    DrawText("To open this chest you\n\n\nneed to win a minigame!!!!!",251,201,35,RAYWHITE);
    // Next button
    if (GuiButton((Rectangle){415, 500, 140, 40}, "NEXT"))
    {
        nextMenuChest3 = true;
        backMenuChest3 = false;
    }
    if (nextMenuChest3 && !backMenuChest3)
    {
        DrawRectangleGradientV(244, 90, 500, 450, BLACK, DARKPURPLE);
        DrawText("Prison Guards have a password on it\n\n(Between 1 and 100) Guess it!!!", 280, 150, 25, WHITE);
        DrawRectangleLines(280, 240, 150, 30, BLACK);
        GuiTextBox((Rectangle){280, 240, 150, 30}, guessPassChar2, 4, true);
        guessPass2 = TextToInteger(guessPassChar2);

        if(CheckGuessPass(actualpass2, guessPass2))
        {
            return 1;
        }
        // Close button for the new menu
        if (GuiButton((Rectangle){644, 90, 100, 40}, "X"))
        {
            nextMenuChest3 = false; 
        }
        return 0;
    }
    return 0;
}
// Blue Chest
int DisplayMenuChest4( bool *menuOpenChest4)
{
    // Rectangle 
    DrawRectangleGradientH(244, 90, 500, 450, DARKGREEN, DARKPURPLE);
    // Button Close
    if (GuiButton((Rectangle){640, 90, 105, 40}, "Close"))
    {
        *menuOpenChest4 = false;
    }
    // Minigame logic
    DrawText("To open this chest you\n\n\nneed to win a minigame!!!!!",251,201,35,RAYWHITE);
    // Next button
    if (GuiButton((Rectangle){415, 500, 140, 40}, "NEXT"))
    {
        nextMenuChest4 = true;
        backMenuChest4 = false;
    }
    if (nextMenuChest4 && !backMenuChest4)
    {
        if(!ansQues4_1)
        {
            DrawRectangleGradientV(244, 90, 500, 450, RED, PURPLE);
            DrawText("Guess these words correctly!!!", 280, 150, 25, WHITE);
            GuiTextBox((Rectangle){370, 220, 250, 30}, wordGuess4_1, 6, true);
            DrawText("Starts with a and\n\n\nends with e (5 letters)", 320, 260, 30, Fade(BLACK, 0.7f));
        }


        if(strcmp("apple", wordGuess4_1) == 0 )
        {
            if(GuiButton((Rectangle){415, 500, 140, 40}, "NEXT"))
            {
                ansQues4_1 = true;
                backMenuChest4_2 = false;
                nextMenuChest4_2 = true;
            }   
        }

        if(nextMenuChest4_2 && !backMenuChest4_2 && !ansQues4_2)
        {
            DrawRectangleGradientH(244, 90, 500, 450, BLACK, BROWN);
            GuiTextBox((Rectangle){350, 220, 250, 30}, wordGuess4_2, 8, true);
            DrawText("Name of a country\n\n\nbeginning and ending\n\n\nwith a", 320, 260, 30, Fade(WHITE, 0.7f));
        }

        if(strcmp("algeria", wordGuess4_2) == 0 )
        {
            if(GuiButton((Rectangle){415, 500, 140, 40}, "NEXT"))
            {
                ansQues4_2 = true;
                backMenuChest4_3 = false;
                nextMenuChest4_3 = true;
            }   
        }

        if(nextMenuChest4_3 && !backMenuChest4_3 && !ansQues4_3)
        {
            DrawRectangleGradientH(244, 90, 500, 450, DARKGREEN, WHITE);
            GuiTextBox((Rectangle){350, 220, 250, 30}, wordGuess4_3, 9, true);
            DrawText("Name of chemical\n\n\nelement begining with p", 320, 260, 30, Fade(DARKGREEN, 0.9f));
        }

        if(strcmp("platinum", wordGuess4_3) == 0 )
        {
            return 1;  
        }
        
        // Close button for the new menu
        if (GuiButton((Rectangle){644, 90, 100, 40}, "X"))
        {
            nextMenuChest2 = false; // Close the new menu when the button is pressed
        }
        return 0;
    }
    return 0;
}
void openingMenu(bool *startGame, bool *backGame,Font mfont, Font ffont)
{
    // Openining menu function
    timeForLine += GetFrameTime();
    lineLength = 250.0f + 100.0f * sin(3.5f * timeForLine);
    DrawTextPro(mfont, "ESCAPE", (Vector2){300, 200}, (Vector2){0, 0}, 0, 75, 10, RED);
    DrawLineEx((Vector2){300, 265}, (Vector2){300 + lineLength, 265}, 4.0f, RED);
    // Adjusted button positions
    if (GuiButton((Rectangle){SCREEN_WIDTH / 2 - 100, 300, 200, 40}, "START") ) {
        *startGame = true;
        *backGame = false;
    }
    if (GuiButton((Rectangle){SCREEN_WIDTH / 2 - 100, 350, 200, 40}, "ABOUT") )
    {
        openAbout = true;
        closeAbout = false;
    }
    if ( openAbout && !closeAbout)
    {
        DrawRectangleGradientH(244, 90, 500, 450, BLACK, RED);
        DrawTextPro(ffont, "Developed by Ahmad Imran\n\n\nAs End Semester Project for\n\n\nFOCP. A young and passionat\n\n\ne developer. Get to know mo\n\n\nre about him", (Vector2){260, 125}, (Vector2){0, 0}, 0, 25, 5, WHITE);
        if (GuiButton((Rectangle){SCREEN_WIDTH / 2 - 100, 350, 200, 40}, "Linkedin") )
        {
            OpenURL("https://www.linkedin.com/in/ahmad-imran-0b2005293/");
        }
        // Button Close
        if (GuiButton((Rectangle){640, 90, 105, 40}, "Close"))
        {
            closeAbout = true;
        }
    }
}

void handlePlayerMovement(Player *player, Rectangle *destPlayer)
{   // Handling player movement and speed
    playerGame.moving = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);
    if(playerGame.moving)
    {
        bool canMoveUp = destPlayer->y - playerGame.speed >= 0;
        bool canMoveDown = destPlayer->y + destPlayer->height + playerGame.speed <= SCREEN_HEIGHT;
        bool canMoveLeft = destPlayer->x - playerGame.speed >= 0;
        bool canMoveRight = destPlayer->x + destPlayer->width + playerGame.speed <= SCREEN_WIDTH;
           // bool runOverChest =  destPlayer.y > 40 ; alternative to solve problem
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        {
            if (canMoveUp )
            {
                playerGame.dir = 0; // Up direction
                destPlayer->y -= playerGame.speed;
            }

        }
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        {
            if (canMoveDown)
            {
                playerGame.dir = 2; // Down direction
                destPlayer->y += playerGame.speed;
            }
        }

        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        {
                // Check if moving left will not exceed the left boundary
            if (canMoveLeft)
            {
                playerGame.dir = 3; // Left direction
                destPlayer->x -= playerGame.speed;
            }
        }

        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        {
                // Check if moving right will not exceed the right boundary
            if (canMoveRight)
            {
                playerGame.dir = 1; // Right direction
                destPlayer->x += playerGame.speed;
            }
        }

        if (FrameCount % 8 == 1)
        {
            playerGame.Frame++;
        }
            
    } // end movement if
} 
void changeSrcPlayer(Rectangle *srcPlayer, Player *player, float manWidth, float manHeight)
{   // Handling player change on spritesheet as per input
    FrameCount++;

    if(playerGame.Frame > 3)
    {
        playerGame.Frame = 0;
    }

    srcPlayer->x =  manWidth * (float)(playerGame.Frame); 
    srcPlayer->y = manHeight * (float)(playerGame.dir);
}