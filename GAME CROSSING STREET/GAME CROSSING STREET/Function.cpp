#include "Function.h"

POINT** X; //Mảng chứa xe 
POINT Y; // Người qua đường 
int* YL; // Người qua đường trước đó 
int nYL = 0;
int cnt = 0; //Hỗ trợ tăng tốc
int MOVING; // Xác định hướng di chuyển 
int SPEED; // Tốc độ xe chạy 
int HEIGHT_CONSOLE = 20, WIDTH_CONSOLE = 119;
bool STATE; //Trạng thái người chơi 
int DUNG_MAX = 50; // Dừng xe 
int DUNG = 0;
int DC = 0;
int T = 1;


void PushBackYL(int* &a, int &n, int x)
{
	int m = n + 1;
	int* anew = (int*)realloc(a, m * sizeof(float));
	if (anew != NULL)
	{
		anew[n] = x;
		n++;
		a = anew;
	}
}



void FixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX)& ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ResetData()
{
	MOVING = 'D'; // Qua phải 
	SPEED = 1;
	Y = { 18, 19 };

	//Tạo mảng xe chạy
	if (X == NULL)
	{
		X = new POINT*[MAX_CAR];
		for (int i = 0; i < MAX_CAR; i++)
		{
			X[i] = new POINT[MAX_CAR_LENGTH];
		}
		for (int i = 0; i < MAX_CAR; i++)
		{
			int temp = (rand() % (WIDTH_CONSOLE - MAX_CAR_LENGTH)) + 1;
			for (int j = 0; j < MAX_CAR_LENGTH; j++)
			{
				X[i][j].x = temp + j;
				X[i][j].y = 2 + i;
			}
		}
	}
}



void DrawBoard(int x, int y, int width, int height)
{
	int curPosX = 0;
	int curPosY = 0;

	GotoXY(x, y); cout << 'X';
	for (int i = 1; i < width; i++)cout << 'X';
	cout << 'X';
	GotoXY(x, height + y); cout << 'X';
	for (int i = 1; i < width; i++)cout << 'X';
	cout << 'X';
	for (int i = y + 1; i < height + y; i++)
	{
		GotoXY(x, i); cout << 'X';
		GotoXY(x + width, i); cout << 'X';
	}

	GotoXY(0, HEIGHT_CONSOLE + 2);
	for (int i = 0; i <= 119; i++)cout << 'X';
	for (int i = 0; i <= 7; i++)
	{
		GotoXY(40, HEIGHT_CONSOLE + 2 + i);
		cout << 'X';
	}

	for (int i = 0; i <= 7; i++)
	{
		GotoXY(80, HEIGHT_CONSOLE + 2 + i);
		cout << 'X';
	}

	GotoXY(42, HEIGHT_CONSOLE + 3);
	cout << "NHAN 'L' DE LUU TRO CHOI" << endl;
	GotoXY(42, HEIGHT_CONSOLE + 4);
	cout << "NHAN 'T' DE TAI FILE DA LUU" << endl;
	GotoXY(42, HEIGHT_CONSOLE + 5);
	cout << "NHAN 'P' DE TAM DUNG" << endl;

	GotoXY(curPosX, curPosY);
}

void StartGame()
{
	system("cls");
	GotoXY(3, 2);
	TextColor(1 + rand() % 15);
	printf("        GGGGGGGGGGGGG               AAA               MMMMMMMM               MMMMMMMMEEEEEEEEEEEEEEEEEEEEEE");
	GotoXY(3, 3);
	printf("     GGG::::::::::::G              A:::A              M:::::::M             M:::::::ME::::::::::::::::::::E");
	GotoXY(3, 4);
	printf("   GG:::::::::::::::G             A:::::A             M::::::::M           M::::::::ME::::::::::::::::::::E");
	GotoXY(3, 5);
	printf("  G:::::GGGGGGGG::::G            A:::::::A            M:::::::::M         M:::::::::MEE::::::EEEEEEEEE::::E");
	GotoXY(3, 6);
	printf(" G:::::G       GGGGGG           A:::::::::A           M::::::::::M       M::::::::::M  E:::::E       EEEEEE");
	GotoXY(3, 7);
	printf("G:::::G                        A:::::A:::::A          M:::::::::::M     M:::::::::::M  E:::::E             ");
	GotoXY(3, 8);
	printf("G:::::G                       A:::::A A:::::A         M:::::::M::::M   M::::M:::::::M  E::::::EEEEEEEEEE   ");
	GotoXY(3, 9);
	printf("G:::::G    GGGGGGGGGG        A:::::A   A:::::A        M::::::M M::::M M::::M M::::::M  E:::::::::::::::E   ");
	GotoXY(3, 10);
	printf("G:::::G    G::::::::G       A:::::A     A:::::A       M::::::M  M::::M::::M  M::::::M  E:::::::::::::::E   ");
	GotoXY(3, 11);
	printf("G:::::G    GGGGG::::G      A:::::AAAAAAAAA:::::A      M::::::M   M:::::::M   M::::::M  E::::::EEEEEEEEEE   ");
	GotoXY(3, 12);
	printf("G:::::G        G::::G     A:::::::::::::::::::::A     M::::::M    M:::::M    M::::::M  E:::::E             ");
	GotoXY(3, 13);
	printf(" G:::::G       G::::G    A:::::AAAAAAAAAAAAA:::::A    M::::::M     MMMMM     M::::::M  E:::::E       EEEEEE");
	GotoXY(3, 14);
	printf("  G:::::GGGGGGGG::::G   A:::::A             A:::::A   M::::::M               M::::::ME:::::: EEEEEEEEE::::E");
	GotoXY(3, 15);
	printf("   GG:::::::::::::::G  A:::::A               A:::::A  M::::::M               M::::::ME::::::::::::::::::::E");
	GotoXY(3, 16);
	printf("     GGG::::::GGG:::G A:::::A                 A:::::A M::::::M               M::::::ME::::::::::::::::::::E");
	GotoXY(3, 17);
	printf("        GGGGGG   GGGGAAAAAAA                   AAAAAAAMMMMMMMM               MMMMMMMMEEEEEEEEEEEEEEEEEEEEEE");
	char tam;
	GotoXY(30, 21);
	TextColor(11);
	cout << "NHAP ' T ' DE MO FILE HOAC NHAN BAT KI PHIM NAO DE BAT DAU GAME  ";
	cin >> tam;
	tam = toupper(tam);
	if (tam == 'T')
		ResetDataFile(); //Khởi tạo dữ liệu từ file
	else
		ResetData(); // Khởi tạo dữ liệu gốc 

	DrawBoard(0, 0, WIDTH_CONSOLE, HEIGHT_CONSOLE);
	STATE = true;
}

void GabageCollect()
{
	for (int i = 0; i < MAX_CAR; i++)
	{
		delete[] X[i];
	}
	delete[] X;
}

void ExitGame(HANDLE t)
{
	system("cls");
	TerminateThread(t, 0);
	GabageCollect();
	if (YL != NULL)
		free(YL);
}

void PauseGame(HANDLE t)
{
	SuspendThread(t);
}

void ProcessDead()
{

	STATE = 0;
	TextColor(6);
	for (int i = 0; i < MAX_CAR_LENGTH; i++)
	{
		GotoXY(X[Y.y - 2][i].x, Y.y);
		cout << ".";
	}

	GotoXY(Y.x, Y.y);
	cout << "Y";
	GotoXY(0, HEIGHT_CONSOLE + 1);
	cout << "Ban Da Thua, Nhan ' Y ' de tiep tuc hoac phim bat ki de thoat";
	TextColor(6);

}

void ProcessFinish(POINT& p)
{
	PushBackYL(YL, nYL, p.x);
	GotoXY(0, HEIGHT_CONSOLE + 1);
	if (SPEED == MAX_SPEED)
		cout << "Ban Thang, Hay nhan ESC de thoat";
	else
		cout << "Ban da vuot qua LEVEL " << SPEED;
	SPEED == MAX_SPEED ? SPEED = 1 : SPEED++;
	p = { 18, 19 };
	MOVING = 'D';
}

void VaChamNguoiTruoc(POINT& p)
{
	STATE = 0;
	GotoXY(0, HEIGHT_CONSOLE + 2);
	cout << " Ban da va cham voi nguoi ve truoc do _ Nao! hay nhan phim bat ki de tiep tuc :";
	SPEED == MAX_SPEED ? SPEED = 1 : SPEED++;
	p = { 18, 19 };
	MOVING = 'D';
}

void DrawCars(char* s)
{
	for (int i = 0; i < MAX_CAR; i++)
	{
		for (int j = 0; j < MAX_CAR_LENGTH; j++)
		{
			GotoXY(X[i][j].x, X[i][j].y);
			printf("*");
		}
	}
}

void DrawSticker(const POINT& p, char* s)
{
	GotoXY(p.x, p.y);
	printf(s);
}

bool IsImpact(const POINT& p, int d)
{
	if (d == 1 || d == 19) return false;
	for (int i = 0; i < MAX_CAR_LENGTH; i++)
	{
		if (p.x == X[d - 2][i].x && p.y == X[d - 2][i].y) return true;
	}
	return false;
}

bool ImpactYL(const POINT& p, int* YL)
{
	for (int i = 0; i < nYL; i++)
	{
		if (p.x == YL[i])
			return true;
	}
	return false;
}

void MoveCars()
{
	for (int i = 1; i < MAX_CAR; i += 2)
	{

		cnt = 0;
		if (i == DC) continue;
		do
		{
			cnt++;
			for (int j = 0; j < MAX_CAR_LENGTH - 1; j++)
			{
				X[i][j] = X[i][j + 1];
			}
			X[i][MAX_CAR_LENGTH - 1].x + 1 == WIDTH_CONSOLE ? X[i][MAX_CAR_LENGTH - 1].x = 1 : X[i][MAX_CAR_LENGTH - 1].x++;
		} while (cnt < SPEED);
	}
	for (int i = 0; i < MAX_CAR; i += 2)
	{
		cnt = 0;
		if (i == DC) continue;
		do
		{
			cnt++;
			for (int j = MAX_CAR_LENGTH - 1; j > 0; j--)
			{
				X[i][j] = X[i][j - 1];
			}
			X[i][0].x - 1 == 0 ? X[i][0].x = WIDTH_CONSOLE - 1 : X[i][0].x--;
		} while (cnt < SPEED);
	}
}

void EraseCars()
{
	for (int i = 0; i < MAX_CAR; i += 2)
	{
		cnt = 0;
		if (i == DC) continue;
		do
		{
			GotoXY(X[i][MAX_CAR_LENGTH - 1 - cnt].x, X[i][MAX_CAR_LENGTH - 1 - cnt].y);
			cout << "  ";
			cnt++;
		} while (cnt < SPEED);
	}

	for (int i = 1; i < MAX_CAR; i += 2)
	{
		cnt = 0;
		if (i == DC) continue;
		do
		{
			GotoXY(X[i][0 + cnt].x, X[i][0 + cnt].y);
			cout << " ";
			cnt++;
		} while (cnt < SPEED);
	}

	for (int i = 0; i < nYL; i++)
	{
		GotoXY(YL[i], 1);
		cout << "Y";
	}
}

void MoveRight()
{
	if (Y.x < WIDTH_CONSOLE - 1)
	{
		DrawSticker(Y, " ");
		Y.x++;
		DrawSticker(Y, "Y");
	}
}
void MoveLeft()
{
	if (Y.x > 1)
	{
		DrawSticker(Y, " ");
		Y.x--;
		DrawSticker(Y, "Y");
	}
}
void MoveDown()
{
	if (Y.y < HEIGHT_CONSOLE - 1)
	{
		DrawSticker(Y, " ");
		Y.y++;
		DrawSticker(Y, "Y");
	}
}
void MoveUp()
{
	if (Y.y > 1)
	{
		DrawSticker(Y, " ");
		Y.y--;
		DrawSticker(Y, "Y");
	}
}


void SubThread()
{
	while (1)
	{
		if (DUNG == DUNG_MAX)
		{
			DC++;
			DUNG = 0;
		}
		if (DC == MAX_CAR)
			DC = 0;
		if (STATE)
		{
			switch (MOVING)
			{
			case 'A':
				MoveLeft();
				break;
			case 'D':
				MoveRight();
				break;
			case 'W':
				MoveUp();
				break;
			case 'S':
				MoveDown();
				break;
			}
			TrangThai();
			MOVING = ' ';
			EraseCars();
			MoveCars();
			DrawCars(".");
			if (IsImpact(Y, Y.y))
			{
				ProcessDead();
			}
			if (Y.y == 1)
			{
				if (ImpactYL(Y, YL))
					VaChamNguoiTruoc(Y);
				else
				{
					ProcessFinish(Y);
				}
			}
			Sleep(50);
		}
		DUNG++;
	}
}


void LuuGame()
{
	char s[50];

	system("cls");
	DrawBoard(0, 0, WIDTH_CONSOLE, HEIGHT_CONSOLE);
	DrawCars(".");
	DrawSticker(Y, "Y");
	GotoXY(0, HEIGHT_CONSOLE + 3);
	cout << "Hay nhap ten tap tin  : ";
	cin >> s;
	fflush(stdin);


	for (int i = 0; i < 39; i++)
	{
		GotoXY(i, HEIGHT_CONSOLE + 3);
		cout << " ";
	}

	FILE *f;

	f = fopen(s, "wt");
	if (f == NULL)
	{
		printf("khong tao duoc file");
		return;
	}
	fprintf(f, "%d\n", STATE);
	fprintf(f, "%d ", HEIGHT_CONSOLE);
	fprintf(f, "%d\n", WIDTH_CONSOLE);
	fprintf(f, "%d\n", SPEED);
	fprintf(f, "%d\n", 'D');
	fprintf(f, "%d\n", cnt);
	fprintf(f, "%d ", Y.x);
	fprintf(f, "%d\n", Y.y);
	fprintf(f, "%d\n", nYL);
	for (int i = 0; i < nYL; i++)
	{
		fprintf(f, "%d ", YL[i]);
	}
	fprintf(f, "\n", NULL);
	for (int i = 0; i < MAX_CAR; i++)
	{
		for (int j = 0; j < MAX_CAR_LENGTH; j++)
		{
			fprintf(f, "%d ", X[i][j].x);
			fprintf(f, "%d\t", X[i][j].y);
		}
		fprintf(f, "\n", NULL);
	}
	fclose(f);
}


void ResetDataFile()
{
	char s[50];

	system("cls");
	DrawBoard(0, 0, WIDTH_CONSOLE, HEIGHT_CONSOLE);
	GotoXY(0, HEIGHT_CONSOLE + 4);
	cout << "Hay nhap ten tap tin da luu : ";
	cin >> s;
	fflush(stdin);

	FILE *f;

	f = fopen(s, "rt");
	if (f == NULL)
	{
		printf("khong tao duoc file");
		return;
	}

	fscanf(f, "%d", &STATE);
	fscanf(f, "%d", &HEIGHT_CONSOLE);
	fscanf(f, "%d", &WIDTH_CONSOLE);
	fscanf(f, "%d", &SPEED);
	fscanf(f, "%d", &MOVING);
	fscanf(f, "%d", &cnt);
	fscanf(f, "%d", &Y.x);
	fscanf(f, "%d", &Y.y);
	fscanf(f, "%d", &nYL);
	if (YL == NULL)
	{
		YL = new int[nYL];
	}
	for (int i = 0; i < nYL; i++)
	{
		fscanf(f, "%d", &YL[i]);
	}
	if (X == NULL)
	{
		X = new POINT*[MAX_CAR];

		for (int i = 0; i < MAX_CAR; i++)
		{
			X[i] = new POINT[MAX_CAR_LENGTH];
		}
	}

	for (int i = 0; i < MAX_CAR; i++)
	{
		for (int j = 0; j < MAX_CAR_LENGTH; j++)
		{
			fscanf(f, "%d ", &X[i][j].x);
			fscanf(f, "%d\t", &X[i][j].y);
		}
	}
	fclose(f);
}



void TextColor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

void TrangThai()
{
	GotoXY(93, HEIGHT_CONSOLE + 3);
	cout << "LEVEL " << SPEED;
	GotoXY(90, HEIGHT_CONSOLE + 4);
	cout << "Toc Do Xe : " << 10 * SPEED;
	GotoXY(90, HEIGHT_CONSOLE + 5);
	cout << "Vi tri Xe : " << Y.y;
}