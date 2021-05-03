#include "pch.h"
#include "CppUnitTest.h"
#include "Item.h"
#include "Tower.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	/** Mock class for testing CTower */
	class CTowerMock : public CTower
	{
	public:
		CTowerMock(CGame* game) : CTower(game, L"images/tower8.png"){}

		///  Default constructor (disabled)
		CTowerMock() = delete;

		///  Copy constructor (disabled)
		CTowerMock(const CTowerMock&) = delete;

		~CTowerMock() {}

		/** Accept a visitor
		* \param visitor The visitor we accept */
		virtual void Accept(CItemVisitor* visitor) override { }

	};
	TEST_CLASS(CTowerTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestTowerConstructor)
		{
			CGame game;
			CTowerMock tower(&game);
		}

		TEST_METHOD(TestTowerGettersSetters)
		{
			CGame game;
			CTowerMock tower(&game);

			// Test initial values
			Assert::AreEqual(0, tower.GetX(), 0);
			Assert::AreEqual(0, tower.GetY(), 0);

			// Test SetLocation
			tower.SetLocation(150, 250);
			Assert::AreEqual(150, tower.GetX(), 0);
			Assert::AreEqual(250, tower.GetY(), 0);

			// Test SetAttackTimer
			tower.SetAttackTimer(3);
			Assert::AreEqual(3, tower.GetAttackTimer(), 0);
			Assert::AreEqual(3, tower.GetTimeUntilAttack(), 0);
		}

		TEST_METHOD(TestTowerUpdate)
		{
			CGame game;
			CTowerMock tower(&game);
			tower.SetAttackTimer(5);
			tower.Update(6);
			Assert::AreEqual(4, tower.GetTimeUntilAttack(), 0);
			tower.Update(3);
			Assert::AreEqual(1, tower.GetTimeUntilAttack(), 0);
			
		}

	};
}