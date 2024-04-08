#include "stdafx.h"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

void Inventory::AddItem(string name)
{
    // find 함수를 사용하여 키가 이미 존재하는지 확인
    auto it = itemList.find(name);

    // 키가 이미 존재하지 않으면 추가
    if (it == itemList.end())
    {
        // 키가 존재하지 않는 경우, 새로운 아이템 추가
        itemList[name] = 1;
        cout << "아이템 '" << name << "'을(를) 추가했습니다." << endl;
        itemCount++;

        string upperSlot = "slot" + to_string(itemCount);   // slot1
        string itemName = name + ".png";
        GM->ui->upper->Find(upperSlot)->material->diffuseMap->LoadFile(itemName);
    }
    else
    {
        itemList[name]++;
        cout << "아이템 '" << name << "'의 개수는 " << itemList[name] << "개 입니다." << endl;
    }


}
