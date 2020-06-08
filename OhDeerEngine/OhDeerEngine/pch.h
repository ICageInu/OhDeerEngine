#pragma once
//INCLUDES OF C RUNTIME
#include <vector>
#include <iostream>
#include "../../imgui-master/imgui.h"

//INCLUDE OF OWN FILES
//#include "../Managers/ServiceLocator.h"
#include "ServiceLocator.h"
#include "SFML/Graphics.hpp"
#include "BaseComponent.h"
//#include "../Components/TextureComponent.h"


#pragma region

template<class T>
inline void SafeDelete(T* pObjectToDelete)
{
	if (pObjectToDelete != nullptr)
	{
		delete(pObjectToDelete);
		pObjectToDelete = nullptr;
	}
}

#pragma endregion Templates

#include "ServiceLocator.h"
