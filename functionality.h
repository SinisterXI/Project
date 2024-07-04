
 //---Piece Starts to Fall When Game Starts---//
void colorchange(int&); // takes an integer variable as its input parameter by reference (int &).
void deleterow(int);
bool anamoly_shadow(int arr[4][2]); // takes a 2D integer array arr of size 4x2 and returns a boolean value.
bool checkboundary(int&);
bool checkgameover();
void calcualate_score(int&, int);        // The function calculate_score takes two parameters: a reference to an integer variable and an integer value. Its purpose is to update the score of the player based on the value passed as the second parameter. The function adds the value passed as the second parameter to the current score, which is stored in the integer variable passed as the first parameter.
void get_next_piece(int, int, int[4][2]); // generates the next falling piece in a game and provides the coordinates of its blocks to the game engine.
bool get_bombing(float&);
void terrorism_through_bomb(int);
bool limit_check(int, int);
void restart_game();
// using namespace sf;
void fallingPiece(float& timer, float& timer_1, float& delay, int& colorNum, bool* bombing, int& score, int& colorNum_1, int next_piece[4][2])
{
    static int n = rand() % 4; // rand() is a C++ standard library function that generates a sequence of pseudo-random integers,
    // which are uniformly distributed within a range.
    if (timer > delay)
    {
        for (int i = 0; i < 4; i++)
        {
            point_2[i][0] = point_1[i][0];
            point_2[i][1] = point_1[i][1];
            point_1[i][1] += 1; // How much units downward
        }
        bool b = false;
        bool* ptr = &b;
        if (!anamoly() && checkgameover())
        {
            if (!*bombing)
                colorchange(colorNum);
            else
                terrorism_through_bomb(colorNum);
            if (rand() % 10 + 1 == 4)
                *ptr = get_bombing(timer_1); // USING RANDTO GENERATE 1/10 TH POSSIBILTY OF BOMB
            //--- Un-Comment this Part When You Make BLOCKS array---//
            int a = n;
            *bombing = false;
            int r = rand() % 10;
            for (int i = 0; i < 4; i++)
            {
                switch (!b)

                {
                case 1:
                    point_1[i][0] = BLOCKS[a][i] % 2; /// IF BOMB ISN'T GENERATED
                    point_1[i][1] = BLOCKS[a][i] / 2;
                    break;
                case 0:
                    *bombing = true;
                    point_1[i][0] = 0;
                    point_1[i][1] = 0; // IF BOMB IS GENERATED
                    point_1[i][0] += r;
                    break;
                }
            }

            if (!*bombing)
            {
                if (score <= 150)
                    n = rand() % 4; // ACCESIBLE BLOCKS ON THE BASIS OF LEVELS WHICH ARE SCORE BASED
                else
                    n = rand() % 7;

                get_next_piece(n, colorNum, next_piece); // GETTING NEXT BLOCK
            }
        }
        *ptr = false;
        timer = 0;
    }
}
/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///
void terrorism_through_bomb(int color)
{
    if (point_1[0][1] == M)
        gameGrid[19][point_1[0][0]] = 0; // IF BOMB LANDS ON EMPTY SPACE
    else if (gameGrid[point_1[0][1]][point_1[0][0]] == color)
    {
        restart_game(); // IF COLOR MATCHED
    }
    else
    {
        int* ptr = &point_1[0][1], * qtr = &point_1[0][1];
        for (int i = *ptr - 4; i < *qtr + 5; i++)
        {
            int* ptr_1 = &point_1[0][0], * qtr_1 = &point_1[0][0];
            for (int j = *ptr_1 - 4; j < *qtr_1 + 5; j++)
            {
                int* f = &i, * g = &j;
                if (limit_check(i, j)) // IF COLORS MISMATCHED
                    gameGrid[i][j] = 0;
            }
        }
    }
}
void restart_game()
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++) // TO CLEAR THE WHOLE GRID
        {
            gameGrid[i][j] = 0;
        }
    }
}
bool limit_check(int a, int b)
{
    bool flag;
    switch (a > -1 && a < M && b > -1 && b < N)
    {
    case 1:
        flag = true; // CHECKING THE LIMITS OF THE BOMB..
        break;
    case 0:
        flag = false;
        break;
    }
    return flag;
}
void colorchange(int& colorNum)
{
    for (int i = 0; i < 4; i++)
        gameGrid[point_2[i][1]][point_2[i][0]] = colorNum; // ASSIGNING RANDOM COLOR
    colorNum = rand() % 7 + 1;
}
void move(int& a)
{
    if (checkboundary(a))
    {
        for (int i = 0; i < 4; i++)
        {
            point_1[i][0] = point_2[i][0]; // LEFT RIGHT MOVEMENT
        }
    }
}
bool checkboundary(int& a)
{
    for (int i = 0; i < 4; i++)
    {
        point_2[i][0] = point_1[i][0]; // CHECKING IF THERE IS COLLISION
        point_1[i][0] += a;
    }
    a = 0;
    return !anamoly();
}
bool checkgameover()
{
    bool flag = true;
    for (int i = 0; i < N; i++)
    {
        if (gameGrid[1][i] != 0)
        {
            flag = false; // CHECKING FULL GRID
            break;
        }
    }
    return flag;
}
void hard_ddrop(bool& hard_drop)
{
    while (anamoly_shadow(point_1))
    {
        for (int i = 0; i < 4; i++) // LOCKING THE PIECE AT ITS DESIRED POSITION
        {
            point_1[i][1] += 1;
        }
    }
    hard_drop = false;
}
void lineclear(int& score)
{
    int count = 0;
    bool flag;
    for (int i = 0; i < M; i++)
    {
        flag = true;
        for (int j = 0; j < N; j++) // CHECKING IF A LINE IS TO BE CLEARED OR NOT
        {
            if (gameGrid[i][j] == 0)
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            count++;
            deleterow(i);
        }
    }
    if (count != 0)
        calcualate_score(score, count);
}
void calcualate_score(int& a, int b)
{
    switch (b)
    {
    case 1:
        a += 10;
        break;
    case 2:
        a += 30; // SCORE CALCULATIONS
        break;
    case 3:
        a += 60;
        break;
    default:
        a += 100;
    }
}
bool get_bombing(float& timer_1)
{
    timer_1 = 0;
    return rand() % 1 + 1; // GETTING A BOMB
}
void get_level(int& a, int& b, float& delay)
{
    static int i = 0;
    if (i == 0 && a >= 150)
    {
        b++;
        i++; //  GENERATING THE SCORE BASED LEVEL
        delay = 0.15;
    }
    if (i != 0 && a < 150)
        i = 0;
}
void deleterow(int a)
{
    for (int i = 0; i < N; i++) // DELETING FILLED ROW
    {
        gameGrid[a][i] = 0;
    }
}
void rowplacement()
{
    bool flag;
    for (int i = 0; i < M; i++)
    {
        flag = false;
        for (int j = 0; j < N; j++) // MOVING DOWN THE ROWS
        {
            if (gameGrid[i][j] != 0)
            {
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            for (int j = 0; j < N; j++)
            {
                gameGrid[i][j] = gameGrid[i - 1][j];
                gameGrid[i - 1][j] = 0;
            }
        }
    }
}
void rotation(bool& rotate)
{
    for (int i = 0; i < 4; i++)
    {
        int x = point_1[i][1] - point_1[1][1];
        int y = point_1[i][0] - point_1[1][0];
        point_2[i][0] = point_1[i][0];
        point_2[i][1] = point_1[i][1]; // FINDING CENTRE POINTS AND ROTATING ABOUT THEM
        point_1[i][0] = point_1[1][0] - x;
        point_1[i][1] = point_1[1][1] + y;
    }
    if (!anamoly())
    {
        for (int i = 0; i < 4; i++)
        {
            point_1[i][0] = point_2[i][0];
            point_1[i][1] = point_2[i][1];
        }
    }
}

void disp_shadow(int shadow[4][2])
{
    for (int i = 0; i < 4; i++)
    {
        shadow[i][0] = point_1[i][0]; // DISPLAYING SHADOWS
        shadow[i][1] = point_1[i][1];
    }
    while (anamoly_shadow(shadow))
    {
        for (int i = 0; i < 4; i++)
        {
            shadow[i][1] += 1;
        }
    }
}
void get_next_piece(int a, int b, int next_piece[4][2])
{
    for (int i = 0; i < 4; i++)
    {
        next_piece[i][0] = BLOCKS[a][i] % 2; // GETTING NEXT PIECE SHAPE
        next_piece[i][1] = BLOCKS[a][i] / 2;
    }
}
void varreset(int& a)
{
    a = 0;
}
void varreset(bool& a)
{
    a = false; // RESETTING DIFFERENT PARAMETERS
}
void varreset(float& a, int& b)
{
    if (b == 1)
        a = 0.3;
    else
        a = 0.15;
}
///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
#pragma once
