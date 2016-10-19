#pragma once
#include "PolyFillState.h"


class CreateLineState :
	public PolyFillState
{
	static std::string id;
	void CreateLine(int x, int y);

protected:
	void LeftClick(int x, int y) override;
	void RightClick(int x, int y) override;
	void LeftRelease(int x, int y) override;
	void RightRelease(int x, int y) override;
public:
	CreateLineState();
	virtual ~CreateLineState();

	//Getter
	std::string GetName()const override { return id; }

	//Render
	//void Render() override;
};

