#include "pch.h"
#include "CppUnitTest.h"
#include "Game.h"
#include "Item.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	/** Mock class for testing CItem */
	class CItemMock : public CItem
	{
	public:
		/**  Constructor
		 * \param game Game this item is a member of */
		CItemMock(CGame* game) : CItem(game, L"images/tower8.png") {}

		///  Default constructor (disabled)
		CItemMock() = delete;

		///  Copy constructor (disabled)
		CItemMock(const CItemMock&) = delete;

		~CItemMock() {}

		/** Accept a visitor
		* \param visitor The visitor we accept */
		virtual void Accept(CItemVisitor* visitor) override { }

	};
	TEST_CLASS(ItemTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		TEST_METHOD(TestItemConstructor)
		{
			CGame game;
			CItemMock item(&game);
		}
		TEST_METHOD(TestGettersSetters)
		{
			CGame game;
			CItemMock item(&game);

			// Test initial values
			Assert::AreEqual(0, item.GetX(), 0);
			Assert::AreEqual(0, item.GetY(), 0);

			// Test SetLocation
			item.SetLocation(150, 250);
			Assert::AreEqual(150, item.GetX(), 0);
			Assert::AreEqual(250, item.GetY(), 0);
		}

	};
}