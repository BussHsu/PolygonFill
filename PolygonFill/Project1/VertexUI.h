#pragma once
#include "BaseUI.h"
#include <glm\glm.hpp>

#include "Circle.h"
class VertexUI : public BaseUI
{
	Circle* circle;
	MyVertex* m_pModel;

public:
	VertexUI(MyVertex* p, int r, int groupId);
	virtual ~VertexUI();

	MyVertex* GetVertexData() { return m_pModel; }
	int GetGroupID() { return m_pModel->gid; }
	//void SetGroupID(int value) { m_pModel->gid = value; }
	void GetCenter(glm::vec2* center) {circle->GetCenter(center);}
	int  GetRadius() { return circle->GetRadius(); }
	void SetCenter(const int x, const int y) { circle->SetCenter(x,y); }
	void SetRadius(const int r) { circle->SetRadius(r); }
	void SetColors(const glm::vec3& originC, const glm::vec3& pressC, const glm::vec3& activeC);

	bool IsInside(int x, int y) override { return circle->IsInside(x, y); }

	void RenderInitial() override;
	void RenderHover() override;
	void RenderPressing() override;
	void RenderClicked() override;
};

