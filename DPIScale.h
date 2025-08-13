#include <d2d1.h>

class DPIScale
{
	static float scaleX;
	static float scaleY;

public:
	static void Initialize(ID2D1Factory* pFactory)
	{
		FLOAT dpiX, dpiY;
#pragma warning(disable : 4996) // GetDesktopDpi is deprecated.
		pFactory->GetDesktopDpi(&dpiX, &dpiY);
		scaleX = dpiX / 96.0f;
		scaleY = dpiY / 96.0f;
	}

	template <typename T>
	static float PixelsToDipsX(T x)
	{
		return static_cast<float>(x) / scaleX;
	}

	template <typename T>
	static float PixelsToDipsY(T y)
	{
		return static_cast<float>(y) / scaleY;
	}
};
