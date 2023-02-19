#include "MyMesh.h"
void MyMesh::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = a_fSize * 0.5f;
	//3--2
	//|  |
	//0--1

	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	std::vector<vector3> vertex;

	double delta = 2.0f * PI / (double)a_nSubdivisions;

	//create vector3 data for cone
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 phi = vector3(cos(delta * i) * a_fRadius, sin(delta * i) * a_fRadius, 0.0f);
		vertex.push_back(phi);
	}

	//print out data for cone
	for (int j = 0; j < a_nSubdivisions; j++)
	{
		AddTri(vector3(0.0, 0.0, a_fHeight), vertex[j], vertex[(j + 1) % a_nSubdivisions]);
		AddTri(ZERO_V3, vertex[(j + 1) % a_nSubdivisions], vertex[j]);
	}
	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	std::vector<vector3> top;
	std::vector<vector3> bottom;

	double delta = 2.0f * PI / (double)a_nSubdivisions;

	//create vector3 data for the cylinder
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 phi = vector3(cos(delta * i) * a_fRadius, sin(delta * i) * a_fRadius, a_fHeight);
		vector3 beta = vector3(cos(delta * i) * a_fRadius, sin(delta * i) * a_fRadius, 0.0);

		top.push_back(phi);
		bottom.push_back(beta);
	}

	//print vector3 data to window
	for (int j = 0; j < a_nSubdivisions; j++)
	{
		AddTri(vector3(0.0, 0.0, a_fHeight), top[j], top[(j + 1) % a_nSubdivisions]);
		AddTri(ZERO_V3, bottom[(j + 1) % a_nSubdivisions], bottom[j]);
		AddQuad(top[(j + 1) % a_nSubdivisions], top[j],  bottom[(j + 1) % a_nSubdivisions], bottom[j]);
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	std::vector<vector3> outerBottom;
	std::vector<vector3> innerBottom;
	std::vector<vector3> outerTop;
	std::vector<vector3> innerTop;

	double delta = 2.0f * PI / (double)a_nSubdivisions;

	//create vector3 data for tube
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 phi = vector3(cos(delta * i) * a_fOuterRadius, sin(delta * i) * a_fOuterRadius, 0.0);
		vector3 alpha = vector3(cos(delta * i) * a_fInnerRadius, sin(delta * i) * a_fInnerRadius, 0.0);
		vector3 beta = vector3(cos(delta * i) * a_fOuterRadius, sin(delta * i) * a_fOuterRadius, a_fHeight);
		vector3 omega = vector3(cos(delta * i) * a_fInnerRadius, sin(delta * i) * a_fInnerRadius, a_fHeight);

		outerBottom.push_back(phi);
		innerBottom.push_back(alpha);
		outerTop.push_back(beta);
		innerTop.push_back(omega);
	}

	//print out data for tube
	for (int j = 0; j < a_nSubdivisions; j++)
	{
		AddQuad(outerBottom[(j + 1) % a_nSubdivisions], outerBottom[j], innerBottom[(j + 1) % a_nSubdivisions], innerBottom[j]);
		AddQuad(outerTop[j], outerTop[(j + 1) % a_nSubdivisions], innerTop[j], innerTop[(j + 1) % a_nSubdivisions]);
		AddQuad(outerBottom[j], outerBottom[(j + 1) % a_nSubdivisions], outerTop[j], outerTop[(j + 1) % a_nSubdivisions]);
		AddQuad(innerBottom[(j + 1) % a_nSubdivisions], innerBottom[j],  innerTop[(j + 1) % a_nSubdivisions], innerTop[j]);
	}
	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 360)
		a_nSubdivisionsA = 360;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 360)
		a_nSubdivisionsB = 360;

	Release();
	Init();

	// Replace this with your code
	std::vector<vector3> vertexTop;
	std::vector<vector3> vertexBot;
	std::vector<std::vector<vector3>> vertexListTop;
	std::vector<std::vector<vector3>> vertexListBot;

	double delta = (2.0 * PI) / (double)a_nSubdivisionsA;

	//create the vector3 data for the circles used in the torus
	for (int i = 0; i < a_nSubdivisionsA; i++)
	{
		vector3 phi = vector3(cos(delta * i) * a_fInnerRadius, sin(delta * i) * a_fInnerRadius, 0.0f);
		vector3 beta = vector3(cos(delta * i) * a_fInnerRadius, sin(delta * i) * a_fInnerRadius, 0.0f);
		vertexTop.push_back(phi);
		vertexBot.push_back(beta);
	}

	float fDelta = (360.0f / (float)a_nSubdivisionsB);

	//Rotate the positions of the circles to form the shape of the torus
	for (int z = 0; z < a_nSubdivisionsB; z++)
	{
		std::vector<vector3> newVertTop = vertexTop;
		std::vector<vector3> newVertBot = vertexBot;

		matrix4 m4Transform;
		float fDifference = glm::radians(fDelta) * z;
		m4Transform = glm::rotate(IDENTITY_M4, fDifference, AXIS_Y);
		m4Transform = glm::translate(m4Transform, vector3(a_fOuterRadius, 0.0f, 0.0f));

		//transform manipulation
		for (int j = 0; j < a_nSubdivisionsA; j++)
		{
			newVertTop[j] = m4Transform * vector4(newVertTop[j], 1.0f);
			newVertBot[j] = m4Transform * vector4(newVertBot[j], 1.0f);
		}
		
		vertexListTop.push_back(newVertTop);
		vertexListBot.push_back(newVertBot);

		vector3 v3Center = ZERO_V3;
		v3Center = m4Transform * vector4(v3Center, 1.0f);

		//Create the circles used for the torus
		for (int i = 0; i < a_nSubdivisionsA; i++)
		{
			AddTri(v3Center, newVertTop[i], newVertTop[(i + 1) % a_nSubdivisionsA]);
			AddTri(v3Center, newVertBot[(i + 1) % a_nSubdivisionsA], newVertBot[i]);
		}

	}

	//connect the circles to form the torus
	for (int i = 0; i < a_nSubdivisionsA; i++)
	{
		for (int j = 0; j < a_nSubdivisionsA; j++)
		{
			AddQuad(vertexListTop[(i + 1) % a_nSubdivisionsA][(j + 1) % a_nSubdivisionsA], vertexListTop[(i + 1) % a_nSubdivisionsA][j],
				vertexListTop[i][(j + 1) % a_nSubdivisionsA], vertexListTop[i][j]);
			AddQuad(vertexListBot[(i + 1) % a_nSubdivisionsA][(j + 1) % a_nSubdivisionsA], vertexListBot[(i + 1) % a_nSubdivisionsA][j],
				vertexListBot[i][(j + 1) % a_nSubdivisionsA], vertexListBot[i][j]);
		}
	}
	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2.0f, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	// Replace this with your code
	//formulas for calculating parts of sphere
	double delta = (2.0f * PI) / (double)a_nSubdivisions;
	double theta = PI / (double)a_nSubdivisions;

	//for each subdivision
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		//create vector lists
		std::vector<vector3> vertexTopRight;
		std::vector<vector3> vertexTopLeft;
		std::vector<vector3> vertexBotRight;
		std::vector<vector3> vertexBotLeft;

		double alpha = delta * i;

		//for each subdivision
		for (int j = 0; j < a_nSubdivisions + 1; j++)
		{
			double beta = theta * j;

			vector3 gamma = vector3(cos(alpha) * sin(beta + theta) * a_fRadius, 
				sin(alpha) * sin(beta + theta) * a_fRadius, cos(beta + theta) * a_fRadius);
			vector3 sigma = vector3(cos(alpha) * sin(beta) * a_fRadius, 
				sin(alpha) * sin(beta) * a_fRadius, cos(beta) * a_fRadius);
			vector3 epsilon = vector3(cos(alpha + delta) * sin(beta + theta) * a_fRadius, 
				sin(alpha + delta) * sin(beta + theta) * a_fRadius, cos(beta + theta) * a_fRadius);
			vector3 lambda = vector3(cos(alpha + delta) * sin(beta) * a_fRadius,
				sin(alpha + delta) * sin(beta) * a_fRadius, cos(beta) * a_fRadius);

			//store vector3 data in vectors
			vertexTopRight.push_back(gamma);
			vertexTopLeft.push_back(sigma);
			vertexBotRight.push_back(epsilon);
			vertexBotLeft.push_back(lambda);
		}

		//print out the walls of the circle
		for (int z = 0; z < a_nSubdivisions; z++)
		{
			AddQuad(vertexTopRight[z], vertexTopLeft[z], vertexBotRight[z], vertexBotLeft[z]);
		}
	}
	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::AddTri(vector3 a_vouterBottom, vector3 a_vinnerBottom, vector3 a_vouterTop)
{
	//C
	//| \
	//A--B
	//This will make the triangle A->B->C 
	AddVertexPosition(a_vouterBottom);
	AddVertexPosition(a_vinnerBottom);
	AddVertexPosition(a_vouterTop);
}
void MyMesh::AddQuad(vector3 a_vouterBottom, vector3 a_vinnerBottom, vector3 a_vouterTop, vector3 a_vinnerTop)
{
	//C--D
	//|  |
	//A--B
	//This will make the triangle A->B->C and then the triangle C->B->D
	AddVertexPosition(a_vouterBottom);
	AddVertexPosition(a_vinnerBottom);
	AddVertexPosition(a_vouterTop);

	AddVertexPosition(a_vouterTop);
	AddVertexPosition(a_vinnerBottom);
	AddVertexPosition(a_vinnerTop);
}
void MyMesh::Init(void)
{
	m_bBinded = false;
	m_uVertexCount = 0;

	m_VAO = 0;
	m_VBO = 0;

	m_pShaderMngr = ShaderManager::GetInstance();
}
void MyMesh::Release(void)
{
	m_pShaderMngr = nullptr;

	if (m_VBO > 0)
		glDeleteBuffers(1, &m_VBO);

	if (m_VAO > 0)
		glDeleteVertexArrays(1, &m_VAO);

	m_lVertex.clear();
	m_lVertexPos.clear();
	m_lVertexCol.clear();
}
MyMesh::MyMesh()
{
	Init();
}
MyMesh::~MyMesh() { Release(); }
MyMesh::MyMesh(MyMesh& other)
{
	m_bBinded = other.m_bBinded;

	m_pShaderMngr = other.m_pShaderMngr;

	m_uVertexCount = other.m_uVertexCount;

	m_VAO = other.m_VAO;
	m_VBO = other.m_VBO;
}
MyMesh& MyMesh::operator=(MyMesh& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyMesh temp(other);
		Swap(temp);
	}
	return *this;
}
void MyMesh::Swap(MyMesh& other)
{
	std::swap(m_bBinded, other.m_bBinded);
	std::swap(m_uVertexCount, other.m_uVertexCount);

	std::swap(m_VAO, other.m_VAO);
	std::swap(m_VBO, other.m_VBO);

	std::swap(m_lVertex, other.m_lVertex);
	std::swap(m_lVertexPos, other.m_lVertexPos);
	std::swap(m_lVertexCol, other.m_lVertexCol);

	std::swap(m_pShaderMngr, other.m_pShaderMngr);
}
void MyMesh::CompleteMesh(vector3 a_v3Color)
{
	uint uColorCount = m_lVertexCol.size();
	for (uint i = uColorCount; i < m_uVertexCount; ++i)
	{
		m_lVertexCol.push_back(a_v3Color);
	}
}
void MyMesh::AddVertexPosition(vector3 a_v3Input)
{
	m_lVertexPos.push_back(a_v3Input);
	m_uVertexCount = m_lVertexPos.size();
}
void MyMesh::AddVertexColor(vector3 a_v3Input)
{
	m_lVertexCol.push_back(a_v3Input);
}
void MyMesh::CompileOpenGL3X(void)
{
	if (m_bBinded)
		return;

	if (m_uVertexCount == 0)
		return;

	CompleteMesh();

	for (uint i = 0; i < m_uVertexCount; i++)
	{
		//Position
		m_lVertex.push_back(m_lVertexPos[i]);
		//Color
		m_lVertex.push_back(m_lVertexCol[i]);
	}
	glGenVertexArrays(1, &m_VAO);//Generate vertex array object
	glGenBuffers(1, &m_VBO);//Generate Vertex Buffered Object

	glBindVertexArray(m_VAO);//Bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);//Bind the VBO
	glBufferData(GL_ARRAY_BUFFER, m_uVertexCount * 2 * sizeof(vector3), &m_lVertex[0], GL_STATIC_DRAW);//Generate space for the VBO

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)(1 * sizeof(vector3)));

	m_bBinded = true;

	glBindVertexArray(0); // Unbind VAO
}
void MyMesh::Render(matrix4 a_mProjection, matrix4 a_mView, matrix4 a_mModel)
{
	// Use the buffer and shader
	GLuint nShader = m_pShaderMngr->GetShaderID("Basic");
	glUseProgram(nShader); 

	//Bind the VAO of this object
	glBindVertexArray(m_VAO);

	// Get the GPU variables by their name and hook them to CPU variables
	GLuint MVP = glGetUniformLocation(nShader, "MVP");
	GLuint wire = glGetUniformLocation(nShader, "wire");

	//Final Projection of the Camera
	matrix4 m4MVP = a_mProjection * a_mView * a_mModel;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(m4MVP));
	
	//Solid
	glUniform3f(wire, -1.0f, -1.0f, -1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);  

	//Wire
	glUniform3f(wire, 1.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f, -1.f);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);
	glDisable(GL_POLYGON_OFFSET_LINE);

	glBindVertexArray(0);// Unbind VAO so it does not get in the way of other objects
}
void MyMesh::GenerateCuboid(vector3 a_v3Dimensions, vector3 a_v3Color)
{
	Release();
	Init();

	vector3 v3Value = a_v3Dimensions * 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-v3Value.x, -v3Value.y, v3Value.z); //0
	vector3 point1(v3Value.x, -v3Value.y, v3Value.z); //1
	vector3 point2(v3Value.x, v3Value.y, v3Value.z); //2
	vector3 point3(-v3Value.x, v3Value.y, v3Value.z); //3

	vector3 point4(-v3Value.x, -v3Value.y, -v3Value.z); //4
	vector3 point5(v3Value.x, -v3Value.y, -v3Value.z); //5
	vector3 point6(v3Value.x, v3Value.y, -v3Value.z); //6
	vector3 point7(-v3Value.x, v3Value.y, -v3Value.z); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}