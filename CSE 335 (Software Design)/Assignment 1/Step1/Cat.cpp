/**
 * \file Cat.cpp
 *
 * \author Aidan Delfuoco
 */

using namespace std;

#include <iostream>
#include "Cat.h"
#include "leak.h"

 /**
  * Obtain information from the user about this cat.
  *
  * Asks the user for the information that describes a cat.
  */
void CCat::ObtainCatInformation()
{
    cout << endl;
    cout << "Input information about the cat" << endl;

    // Obtain the name
    bool validName = false;
    cin.ignore();
    while (!validName) {
        cout << "Name: ";
        string name = "";
        getline(cin, name);
        if (name == "" || name[0] == ' ') {
            cout << "Bad input, try again." << endl;
        }
        else {
            mName = name;
            validName = true;
        }
    }


    // Obtain the type using a menu. We have a loop so
    // we can handle errors.
    bool valid = false;
    while (!valid)
    {
        cout << "1: American Shorthair" << endl;
        cout << "2: Persian" << endl;
        cout << "3: Siamese" << endl;
        cout << "4: Sphynx" << endl;
        cout << "Enter selection and return: ";
        int option;
        cin >> option;
        if (!cin)
        {
            // We have an error. Clear the input and try again
            cin.clear();
            cin.ignore();
            continue;
        }

        switch (option)
        {
        case 1:
            mType = Type::AmericanShorthair;
            valid = true;
            break;

        case 2:
            mType = Type::Persian;
            valid = true;
            break;

        case 3:
            mType = Type::Siamese;
            valid = true;
            break;

        case 4:
            mType = Type::Sphynx;
            valid = true;
            break;
        }

    }
}

/**
 * Display information about this cat.
 */
void CCat::DisplayAnimal()
{
    cout << mName << ": ";
    switch (mType)
    {
    case Type::AmericanShorthair:
        cout << "American Shorthair Cat" << endl;
        break;

    case Type::Persian:
        cout << "Persian Cat" << endl;
        break;

    case Type::Siamese:
        cout << "Siamese Cat" << endl;
        break;

    case Type::Sphynx:
        cout << "Sphynx Cat" << endl;
        break;
    }
}

/**
 * Checks if the animal is hairy.
 * \return true except for Type::Sphynx
 */
bool CCat::IsHairy()
{
    if (mType == Type::Sphynx) {
        return false;
    }
    return true;
}