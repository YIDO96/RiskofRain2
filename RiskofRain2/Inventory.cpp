#include "stdafx.h"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

void Inventory::AddItem(string name)
{
    // find �Լ��� ����Ͽ� Ű�� �̹� �����ϴ��� Ȯ��
    auto it = itemList.find(name);

    // Ű�� �̹� �������� ������ �߰�
    if (it == itemList.end())
    {
        // Ű�� �������� �ʴ� ���, ���ο� ������ �߰�
        itemList[name] = 1;
        cout << "������ '" << name << "'��(��) �߰��߽��ϴ�." << endl;
        itemCount++;

        string upperSlot = "slot" + to_string(itemCount);   // slot1
        string itemName = name + ".png";
        GM->ui->upper->Find(upperSlot)->material->diffuseMap->LoadFile(itemName);
    }
    else
    {
        itemList[name]++;
        cout << "������ '" << name << "'�� ������ " << itemList[name] << "�� �Դϴ�." << endl;
    }


}
