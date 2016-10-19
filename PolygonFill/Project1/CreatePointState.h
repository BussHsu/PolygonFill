#pragma once
#include "PolyFillState.h"
class CreatePointState : public PolyFillState
{
	static std::string id;
	void CreatePoint(int x, int y);
protected:
	void LeftClick(int x, int y) override;
	void RightClick(int x, int y) override;
	void LeftRelease(int x, int y) override;
	void RightRelease(int x, int y) override;


public:
	CreatePointState();
	virtual ~CreatePointState();

	//Getter
	std::string GetName()const override { return id; }

	//Render
	//void Render() override;
};

