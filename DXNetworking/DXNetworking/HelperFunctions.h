
#include <D3dx9math.h>

static float MeasureDistance(D3DXVECTOR3 item1, D3DXVECTOR3 item2)
{
	float distanceSqrd;
	distanceSqrd = (item2.x - item1.x)*(item2.x - item1.x) 
		+ (item2.y - item1.y)*(item2.y - item1.y)
		+ (item2.z - item1.z)*(item2.z - item1.z);

	return abs(distanceSqrd);
}
