#include "pch.h"
#include "CppUnitTest.h"

#include "PanelScore.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CPanelScoreTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCPanelScore)
		{
			CPanelScore score;

			Assert::IsTrue(0 == score.GetScore(), 
				L"Initialized score is 0");

			score.UpdateScore(1);

			Assert::IsTrue(1 == score.GetScore(),
				L"Increase score to 1");

			score.UpdateScore(-1);

			Assert::IsTrue(0 == score.GetScore(),
				L"Decrease score to 0");

			score.UpdateScore(-1);

			Assert::IsFalse(0 == score.GetScore(),
				L"Check score is still not 0");

			Assert::IsTrue(-1 == score.GetScore(),
				L"Decrease score to -1");

		}
	};
}