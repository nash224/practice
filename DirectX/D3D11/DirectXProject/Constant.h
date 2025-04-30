#pragma once


namespace engine
{
	namespace window
	{
		typedef struct WindowSize
		{
			static constexpr int Width = 1280;
			static constexpr int Height = 720;
		}WinSize;
		typedef struct WindowPosition
		{
			static constexpr int XPos = 0;
			static constexpr int YPos = 0;
		}WinPos;
	}

	namespace render
	{
		#define BACKBUFFER_FORMAT DXGI_FORMAT_R8G8B8A8_UNORM;

	}
}