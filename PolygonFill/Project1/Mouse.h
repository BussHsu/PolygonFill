#pragma once
enum MouseButton
{
	LEFT,
	RIGHT,
	MIDDLE,
	MB_Count
};

struct Mouse
{
	int x;
	int y;
	int startX;
	int startY;

	bool CurrBtnState[MB_Count] = { false, false, false };
	//bool* PrevBtnState;
	//bool states[2][MB_Count];

	Mouse()
		:x(0),
		y(0),
		startX(-1),
		startY(-1)
	{
		//CurrBtnState = states[0];
		//PrevBtnState = states[1];
	}

	bool IsDragging() { return (startX&&startY)&&(startX != x || startY != y); }
	void SetStartPoint(int x, int y) { startX = x; startY = y; }
	void ResetStartPoint() { startX = -1; startY = -1; }
	//void UpdateBtnInput(bool left, bool right, bool mid) 
	//{
	//	auto temp = PrevBtnState;
	//	PrevBtnState = CurrBtnState;
	//	CurrBtnState = temp;

	//	CurrBtnState[0] = left;
	//	CurrBtnState[1] = right;
	//	CurrBtnState[2] = mid;
	//}
};