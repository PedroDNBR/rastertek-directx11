#include "CameraClass.h"

CameraClass::CameraClass()
{
	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;
}

CameraClass::CameraClass(const CameraClass&)
{
}

CameraClass::~CameraClass()
{
}

void CameraClass::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;

	return;
}

void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;

	return;
}

XMFLOAT3 CameraClass::GetPosition()
{
	return XMFLOAT3(m_positionX, m_positionY, m_positionZ);
}

XMFLOAT3 CameraClass::GetRotation()
{
	return XMFLOAT3(m_rotationX, m_rotationY, m_rotationZ);
}

void CameraClass::Render()
{
	XMFLOAT3 up, position, lookAt;
	XMVECTOR upVector, positionVector, lookAtVector;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	// Setup the vector that points upwards
	up.x = 0.0f;
	up.y = 1.0f;
	up.z= 0.0f;

	// Load it into a XMVECTOR structure
	upVector = XMLoadFloat3(&up);
	
	// Setup the position of the camera in the world
	position.x = m_positionX;
	position.y = m_positionY;
	position.z = m_positionZ;

	// Load it into a XMVECTOR structure
	positionVector = XMLoadFloat3(&position);

	// Setup where the camera is looking by default
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Load it into a XVECTOR structure
	lookAtVector = XMLoadFloat3(&lookAt);
	
	// Set the yaw (Y axis), pitch (X axis) and roll (Z axis) rotations in radians
	pitch = m_rotationX * 0.0174532925f; // pi/180 or 0.0174532925 is used to convert from degrees to radians
	yaw = m_rotationY * 0.0174532925f;
	roll = m_rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch and roll values
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform from lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	// Translate to the rotated camera position to the location of te viewer
	lookAtVector = XMVectorAdd(positionVector, lookAtVector);
	
	// Finally create the view matrix from the three updated vectors
	m_viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
}

void CameraClass::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}
