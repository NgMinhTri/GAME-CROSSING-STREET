#include "Function.h"


int main()
{
	int temp;
	FixConsoleWindow();
	srand((unsigned int)time(NULL));
	StartGame();
	thread t1(SubThread);
	while (1)
	{
		temp = toupper(_getch());
		if (STATE == 1)
		{
			if (temp == 27)
			{
				ExitGame(t1.native_handle());
				if (t1.joinable())
					t1.join();
				return 0;
			}
			else if (temp == 'P')
			{
				PauseGame(t1.native_handle());
			}
			else if (temp == 'L')
			{
				PauseGame(t1.native_handle());
				LuuGame();
			}
			else if (temp == 'T')
			{
				PauseGame(t1.native_handle());
				ResetDataFile();
			}
			else
			{
				ResumeThread((HANDLE)t1.native_handle());
				if (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S')
				{
					MOVING = temp;
				}
			}
		}
		else
		{
			if (temp == 'Y') StartGame();
			else
			{
				ExitGame(t1.native_handle());
				if (t1.joinable())
					t1.join();
				return 0;
			}
		}
	}

}