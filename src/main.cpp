#include "Engine.hpp"

int main(void)
{
	// Create and initialize the engine
	Engine engine = Engine(); 
	std::optional<EngineError> result;

	// Make sure initialization went alright before continuing
	if (engine.GetLastError() == EngineError::EE_OK)
		result = engine.Run(); // If result.has_value() is false, engine ran successfully.
	
	return engine.GetExitResult();
}

