#pragma once
#include "BaseUI.h"
#include <glm\glm.hpp>
class Edge :
	public BaseUI
{
	MyEdge* m_pModel;
public:
	Edge(MyEdge* e);
	virtual ~Edge();

	MyEdge* GetEdgeData() {	return m_pModel;}

	//const glm::vec2& GetStartP() const { return startP; }
	//const glm::vec2 GetEndP() const { return endP; }
	//const glm::vec2 GetVec() const { return endP - startP; }
	//void SetStartP(const glm::vec2& v) { startP = v; }
	//void SetEndP(const glm::vec2& v) { endP = v; }

	//Render
	void Render() override;
	void RenderInitial() override;
	void RenderHover() override;
	void RenderPressing() override;
	void RenderClicked() override;
};

