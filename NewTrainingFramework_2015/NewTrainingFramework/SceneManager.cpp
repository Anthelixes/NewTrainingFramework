#include "stdafx.h"
#include "SceneManager.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "../Resources/rapidxml-1.13/rapidxml.hpp"

using namespace rapidxml;
using namespace std;

/*
void SceneManager::scene() {
xml_document<> doc;
xml_node<> * root_node;
// Read the xml file into a vector
ifstream theFile("../Resources/sceneManager/sceneManager.xml");
vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
buffer.push_back('\0');
// Parse the buffer using the xml file parsing library into doc
doc.parse<0>(&buffer[0]);
// Find our root node
root_node = doc.first_node("sceneManager");
// Iterate over the brewerys
//root_node = root_node->first_node("models");

cout << "backgroundColor\tr\t" << root_node->first_node("backgroundColor")->first_node("r")->value() << "\tg\t"
<< root_node->first_node("backgroundColor")->first_node("g")->value() << "\tb\t"
<< root_node->first_node("backgroundColor")->first_node("b")->value() << endl;

for (xml_node<> * modelNode = root_node->first_node("cameras"); modelNode; modelNode = modelNode->next_sibling()) {
for (xml_node<> * childNode = modelNode->first_node("camera"); childNode; childNode = childNode->next_sibling())
{
cout << "\t  camera\tid" << childNode->first_attribute("id")->value() << endl;
cout << "position\tx\t" << childNode->first_node("position")->first_node("x")->value()
<< "\ty\t" << childNode->first_node("position")->first_node("y")->value()
<< "\tz\t" << childNode->first_node("position")->first_node("z")->value() << endl;
cout << "\t target\tx\t" << childNode->first_node("target")->first_node("x")->value()
<< "\ty\t" << childNode->first_node("target")->first_node("y")->value()
<< "\tz\t" << childNode->first_node("target")->first_node("z")->value() << endl;
cout << "\t up\tx\t" << childNode->first_node("up")->first_node("x")->value()
<< "\ty\t" << childNode->first_node("up")->first_node("y")->value()
<< "\tz\t" << childNode->first_node("up")->first_node("z")->value() << endl;
cout << "\t translationSpeed\t" << childNode->first_node("translationSpeed")->value() << endl;
cout << "\t rotationSpeed\t" << childNode->first_node("rotationSpeed")->value() << endl;
cout << "\t fov\t" << childNode->first_node("fov")->value() << endl;
cout << "\t near\t" << childNode->first_node("near")->value() << endl;
cout << "\t far\t" << childNode->first_node("far")->value() << endl;

//pt posion mai trebuie - NU MERGE

}
}
cout << "activeCamera\t" << root_node->first_node("activeCamera")->value() << endl;

for (xml_node<> * modelNode = root_node->first_node("objects"); modelNode; modelNode = modelNode->next_sibling()) {
cout << "Obiect nou" << endl;
for (xml_node<> * childNode = modelNode->first_node("object"); childNode; childNode = childNode->next_sibling())
{
cout << "\t model\t" << childNode->first_node("model")->value() << endl;
cout << "\t shader\t" << childNode->first_node("shader")->value() << endl;
cout << "\t type\t" << childNode->first_node("type")->value() << endl;
cout << "\t depthTest\t" << childNode->first_node("depthTest")->value() << endl;
cout << "\t blend\t" << childNode->first_node("blend")->value() << endl;
if (childNode->first_node("name")->value())
cout << "\t name\t" << childNode->first_node("name")->value() << endl;

for (xml_node<> * schildNode = childNode->first_node("textures")->first_node("texture"); schildNode;
schildNode = schildNode->next_sibling())
{
cout << "\t  texture\tid" << schildNode->first_attribute("id")->value() << endl;
}

cout << "position\tx\t" << childNode->first_node("position")->first_node("x")->value()
<< "\ty\t" << childNode->first_node("position")->first_node("y")->value()
<< "\tz\t" << childNode->first_node("position")->first_node("z")->value() << endl;
cout << "\t rotation\tx\t" << childNode->first_node("rotation")->first_node("x")->value()
<< "\ty\t" << childNode->first_node("rotation")->first_node("y")->value()
<< "\tz\t" << childNode->first_node("rotation")->first_node("z")->value() << endl;

cout << "\t scale\tx\t" << childNode->first_node("scale")->first_node("x")->value()
<< "\ty\t" << childNode->first_node("scale")->first_node("y")->value()
<< "\tz\t" << childNode->first_node("scale")->first_node("z")->value() << endl;

//cout << "selfRotateSpeed\t" << childNode->first_node("selfRotateSpeed")->value() << endl;
//pentru followingCamera - NU MERGE

cout << "lights\tlight\t" << childNode->first_node("lights")->first_node("light")->value() << endl;
//pentru position - NU MERGE
}
}
theFile.close();
}
*/

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}
