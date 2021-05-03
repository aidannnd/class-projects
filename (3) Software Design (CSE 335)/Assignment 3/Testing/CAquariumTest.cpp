#include "pch.h"
#include "CppUnitTest.h"

#include "Aquarium.h"
#include "FishBeta.h"
#include "FishMagikarp.h"
#include "FishGoldeen.h"
#include "DecorCastle.h"

#include <regex>
#include <string>
#include <fstream>
#include <streambuf>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
    TEST_CLASS(CAquariumTest)
    {
    public:
        TEST_METHOD_INITIALIZE(methodName)
        {
            extern wchar_t g_dir[];
            ::SetCurrentDirectory(g_dir);
        }

        TEST_METHOD(TestCAquariumConstruct)
        {
            CAquarium aquarium;
        }

        TEST_METHOD(TestCAquariumHitTest)
        {
            CAquarium aquarium;

            Assert::IsTrue(aquarium.HitTest(100, 200) == nullptr,
                L"Testing empty aquarium");

            shared_ptr<CFishBeta> fish1 = make_shared<CFishBeta>(&aquarium);
            fish1->SetLocation(100, 200);
            aquarium.Add(fish1);

            Assert::IsTrue(aquarium.HitTest(100, 200) == fish1,
                L"Testing fish at 100, 200");

            // fish on top of eachother
            shared_ptr<CFishBeta> fish2 = make_shared<CFishBeta>(&aquarium);
            fish2->SetLocation(100, 200);
            aquarium.Add(fish2);

            Assert::IsTrue(aquarium.HitTest(100, 200) == fish2,
                L"Testing fish2 at 100, 200");

            // return nullptr if no image
            Assert::IsTrue(aquarium.HitTest(10, 10) == nullptr,
                L"Testing for no image at 10, 10");
        }

        /**
        * Create a path to a place to put temporary files
        */
        wstring TempPath()
        {
            // Create a path to temporary files
            wchar_t path_nts[MAX_PATH];
            GetTempPath(MAX_PATH, path_nts);

            // Convert null terminated string to wstring
            return wstring(path_nts);
        }

        /**
        * Read a file into a wstring and return it.
        * \param filename Name of the file to read
        * \return File contents
        */
        wstring ReadFile(const wstring& filename)
        {
            ifstream t(filename);
            wstring str((istreambuf_iterator<char>(t)),
                istreambuf_iterator<char>());

            return str;
        }

        TEST_METHOD(TestCAquariumSave)
        {
            // Create a path to temporary files
            wstring path = TempPath();

            // Create an aquarium
            CAquarium aquarium;

            //
            // First test, saving an empty aquarium
            //
            wstring file1 = path + L"test1.aqua";
            aquarium.Save(file1);

            TestEmpty(file1);

            //
            // Now populate the aquarium
            //

            PopulateThreeBetas(&aquarium);

            wstring file2 = path + L"test2.aqua";
            aquarium.Save(file2);

            TestThreeBetas(file2);

            //
            // Test all types
            //
            CAquarium aquarium3;
            PopulateAllTypes(&aquarium3);

            wstring file3 = path + L"test3.aqua";
            aquarium3.Save(file3);

            TestAllTypes(file3);
        }

        /**
        * Test to ensure an aquarium .aqua file is empty
        */
        void TestEmpty(wstring filename)
        {
            Logger::WriteMessage(filename.c_str());

            wstring xml = ReadFile(filename);
            Logger::WriteMessage(xml.c_str());

            Assert::IsTrue(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
            Assert::IsTrue(regex_search(xml, wregex(L"<aqua/>")));

        }

        /**
         *  Populate an aquarium with three Beta fish
         */
        void PopulateThreeBetas(CAquarium* aquarium)
        {
            shared_ptr<CFishBeta> fish1 = make_shared<CFishBeta>(aquarium);
            fish1->SetLocation(100, 200);
            aquarium->Add(fish1);

            shared_ptr<CFishBeta> fish2 = make_shared<CFishBeta>(aquarium);
            fish2->SetLocation(400, 400);
            aquarium->Add(fish2);

            shared_ptr<CFishBeta> fish3 = make_shared<CFishBeta>(aquarium);
            fish3->SetLocation(600, 100);
            aquarium->Add(fish3);
        }

        /**
         *  Test the fish added
         */
        void TestThreeBetas(wstring filename)
        {
            Logger::WriteMessage(filename.c_str());

            wstring xml = ReadFile(filename);
            Logger::WriteMessage(xml.c_str());

            // Ensure three items
            Assert::IsTrue(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")));

            // Ensure the positions are correct
            Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\"")));
            Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\"")));
            Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\"")));

            // Ensure the types are correct
            Assert::IsTrue(regex_search(xml,
                wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"beta\"/><item.* type=\"beta\"/></aqua>")));
        }

        /**
         *  Populate an aquarium with all fish types
         */
        void PopulateAllTypes(CAquarium* aquarium)
        {
            shared_ptr<CFishGoldeen> fish1 = make_shared<CFishGoldeen>(aquarium);
            fish1->SetLocation(400, 400);
            aquarium->Add(fish1);

            shared_ptr<CFishMagikarp> fish2 = make_shared<CFishMagikarp>(aquarium);
            fish2->SetLocation(600, 100);
            aquarium->Add(fish2);

            shared_ptr<CDecorCastle> decor = make_shared<CDecorCastle>(aquarium);
            decor->SetLocation(700, 100);
            aquarium->Add(decor);
        }

        /**
         *  Test the fish added from PopulateAllTypes()
         */
        void TestAllTypes(wstring filename)
        {
            Logger::WriteMessage(filename.c_str());

            wstring xml = ReadFile(filename);
            Logger::WriteMessage(xml.c_str());

            // Ensure three items
            Assert::IsTrue(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")));

            // Ensure the positions are correct
            Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\"")));
            Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\"")));
            Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"700\" y=\"100\"")));

            // Ensure the types are correct
            Assert::IsTrue(regex_search(xml,
                wregex(L"<aqua><item.* type=\"goldeen\"/><item.* type=\"magikarp\"/><item.* type=\"castle\"/></aqua>")));
        }

        TEST_METHOD(TestCAquariumClear)
        {
            wstring path = TempPath();

            CAquarium aquarium;

            wstring file = path + L"test.aqua";

            PopulateAllTypes(&aquarium);
            aquarium.Clear();
            aquarium.Save(file);

            TestEmpty(file);
        }

        TEST_METHOD(TestCAquariumLoad)
        {
            // Create a path to temporary files
            wstring path = TempPath();

            // Create two aquariums
            CAquarium aquarium, aquarium2;

            //
            // First test, saving an empty aquarium
            //
            wstring file1 = path + L"test1.aqua";

            aquarium.Save(file1);
            TestEmpty(file1);

            aquarium2.Load(file1);
            aquarium2.Save(file1);
            TestEmpty(file1);

            //
            // Now populate the aquarium
            //

            PopulateThreeBetas(&aquarium);

            wstring file2 = path + L"test2.aqua";
            aquarium.Save(file2);
            TestThreeBetas(file2);

            aquarium2.Load(file2);
            aquarium2.Save(file2);
            TestThreeBetas(file2);

            //
            // Test all types
            //
            CAquarium aquarium3;
            PopulateAllTypes(&aquarium3);

            wstring file3 = path + L"test3.aqua";
            aquarium3.Save(file3);
            TestAllTypes(file3);

            aquarium2.Load(file3);
            aquarium2.Save(file3);
            TestAllTypes(file3);
        }
    };
}