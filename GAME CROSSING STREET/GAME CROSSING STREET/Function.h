#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <malloc.h>
#include <time.h>
#include <conio.h>
#include <thread>
#include <mmsystem.h>
using namespace std;

// Hằng số 
#define MAX_CAR 17
#define MAX_CAR_LENGTH 15
#define MAX_SPEED 3

//Biến Toàn Cục 
extern POINT** X; //Mảng chứa xe 
extern POINT Y; // Người qua đường 
extern int* YL; // Người qua đường trước đó 
extern int nYL;
extern int cnt; // Hỗ trợ tăng tốc
extern int MOVING; // Xác định hướng di chuyển 
extern int SPEED; // Tốc dộ xe chạy 
extern int HEIGHT_CONSOLE, WIDTH_CONSOLE;
extern bool STATE; // Trạng thái người chơi 
extern int DUNG_MAX; // Dừng xe 
extern int DUNG;
extern int DC;


void FixConsoleWindow();

void GotoXY(int x, int y);



void ResetData();

/** Vẽ hình chữ nhật

*/
void DrawBoard(int x, int y, int width, int height);

void StartGame();

/** Hàm dọn dẹp tài nguyên

*/
void GabageCollect();

void ExitGame(HANDLE t);


void PauseGame(HANDLE t);


/** Hàm xử lý dừng xe
*/
void ProcessDead();

/** hàm xử lý qua đường thành công  
*/
void ProcessFinish(POINT& p);

void VaChamNguoiTruoc(POINT& p);

/** vẽ toa xe

*/
void DrawCars(char* s);

/** Vẽ người qua đường&

*/
void DrawSticker(const POINT& p, char* s);

/** Kiểm tra dừng xe&
*/
bool IsImpact(const POINT& p, int d);

void MoveCars();

/** Hàm xóa xe
*/
void EraseCars();

/** Hàm di chuyểm
*/
void MoveRight();
void MoveLeft();
void MoveDown();
void MoveUp();

void SubThread();

/** Hàm lưu vị trí người qua đường trước đó
*/
void PushBackYL(int* &a, int &n, int x);

/** Lưu tập tin
*/
void LuuGame();

/** Lấy dữ liệu từ  file
*/
void ResetDataFile();


void TextColor(int x);

void TrangThai();