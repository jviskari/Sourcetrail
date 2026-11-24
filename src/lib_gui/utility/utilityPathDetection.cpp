#include "utilityPathDetection.h"

#include "language_packages.h"

#include "logging.h"
#include "utilityApp.h"

#if BUILD_CXX_LANGUAGE_PACKAGE
#	include "CxxFrameworkPathDetector.h"
#	include "CxxHeaderPathDetector.h"
#endif	  // BUILD_CXX_LANGUAGE_PACKAGE


std::shared_ptr<CombinedPathDetector> utility::getCxxHeaderPathDetector()
{
	std::shared_ptr<CombinedPathDetector> combinedDetector = std::make_shared<CombinedPathDetector>();
#if BUILD_CXX_LANGUAGE_PACKAGE
	combinedDetector->addDetector(std::make_shared<CxxHeaderPathDetector>("clang"));
	combinedDetector->addDetector(std::make_shared<CxxHeaderPathDetector>("gcc"));
#endif	  // BUILD_CXX_LANGUAGE_PACKAGE
	return combinedDetector;
}

std::shared_ptr<CombinedPathDetector> utility::getCxxFrameworkPathDetector()
{
	std::shared_ptr<CombinedPathDetector> combinedDetector = std::make_shared<CombinedPathDetector>();
#if BUILD_CXX_LANGUAGE_PACKAGE
	combinedDetector->addDetector(std::make_shared<CxxFrameworkPathDetector>("clang"));
	combinedDetector->addDetector(std::make_shared<CxxFrameworkPathDetector>("gcc"));
#endif	  // BUILD_CXX_LANGUAGE_PACKAGE
	return combinedDetector;
}
