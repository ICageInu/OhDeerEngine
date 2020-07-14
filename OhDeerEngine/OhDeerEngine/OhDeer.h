#pragma once
struct SDL_Window;
namespace OhDeerEngine
{
	class OhDeer
	{
	public:
		void Initialize();
		void Cleanup();
		void Run();
		static const float SPerFrame; //16 for 60 fps, 33 for 30 fps
	protected:
		virtual void LoadGame() const = 0;
	private:
		SDL_Window* m_Window{};
	};
}