#include "SSEVector.h"


//#include <DirectXPackedVector.h>
//using namespace DirectX::PackedVector;

using namespace DirectX;
using namespace DogFW;

DogFW::SSEVector2::SSEVector2()
{
	mXMVec =(XMVectorZero());
}
DogFW::SSEVector2::SSEVector2(XMVECTOR invec)
{
	mXMVec = invec;
}
DogFW::SSEVector2::SSEVector2(float x, float y)
{
	mXMVec = XMVectorSet(x,y,0.f,0.f);

}
DogFW::SSEVector2::SSEVector2(uint32_t x, uint32_t y)
{
	mXMVec = XMVectorSetInt(x, y, 0, 0);
}
DogFW::SSEVector2::SSEVector2(float valueforXY)
{
	mXMVec = XMVectorReplicate(valueforXY);
}
DogFW::SSEVector2::SSEVector2(uint32_t valueforXY)
{
	mXMVec = XMVectorReplicateInt(valueforXY);
}

