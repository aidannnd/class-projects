#include "pch.h"
#include "CppUnitTest.h"
#include "TowerBomb.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(TowerBombTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestConstructor)
		{
			CGame game;
			CTowerBomb bomb1(&game, 1);
		}

		TEST_METHOD(TestBombTimer)
		{
			CGame game;
			CTowerBomb bomb1(&game, 1);
			CTowerBomb bomb2(&game, 2);
			CTowerBomb bomb3(&game, 3);

			Assert::AreEqual(3, bomb1.GetAttackTimer(), 0);
			Assert::AreEqual(6, bomb2.GetAttackTimer(), 0);
			Assert::AreEqual(9, bomb3.GetAttackTimer(), 0);
		}

	};
}