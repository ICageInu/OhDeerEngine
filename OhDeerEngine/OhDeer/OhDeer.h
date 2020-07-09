#pragma once
struct SDL_Window;
namespace OhDeerEngine
{
	class OhDeerEngine
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
		static const float SPerFrame; //16 for 60 fps, 33 for 30 fps
	private:
		SDL_Window* m_Window{};
	};
}