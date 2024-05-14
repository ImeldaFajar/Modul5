#include <iostream>
#include <vector>
using namespace std;

const int MAX_SIZE = 10;

int hash_func(int key)
{
    return key % MAX_SIZE;
}

struct Node
{
    int nim;
    int nilai;
    Node *next;
    Node(int nim, int nilai) : nim(nim), nilai(nilai), next(nullptr) {}
};

class HashTable
{
private:
    Node **table;

public:
    HashTable()
    {
        table = new Node *[MAX_SIZE]();
    }

    ~HashTable()
    {
        for (int i = 0; i < MAX_SIZE; i++)
        {
            Node *current = table[i];
            while (current != nullptr)
            {
                Node *temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

    void insert(int nim, int nilai)
    {
        int index = hash_func(nim);
        Node *current = table[index];
        while (current != nullptr)
        {
            if (current->nim == nim)
            {
                current->nilai = nilai;
                return;
            }
            current = current->next;
        }
        Node *node = new Node(nim, nilai);
        node->next = table[index];
        table[index] = node;
    }

    int get(int nim)
    {
        int index = hash_func(nim);
        Node *current = table[index];
        while (current != nullptr)
        {
            if (current->nim == nim)
            {
                return current->nilai;
            }
            current = current->next;
        }
        return -1;
    }

    void remove(int nim)
    {
        int index = hash_func(nim);
        Node *current = table[index];
        Node *prev = nullptr;
        while (current != nullptr)
        {
            if (current->nim == nim)
            {
                if (prev == nullptr)
                {
                    table[index] = current->next;
                }
                else
                {
                    prev->next = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void search_by_value_range(int min_val, int max_val)
    {
        for (int i = 0; i < MAX_SIZE; i++)
        {
            Node *current = table[i];
            while (current != nullptr)
            {
                if (current->nilai >= min_val && current->nilai <= max_val)
                {
                    cout << "NIM: " << current->nim << ", Nilai: " << current->nilai << endl;
                }
                current = current->next;
            }
        }
    }

    void traverse()
    {
        for (int i = 0; i < MAX_SIZE; i++)
        {
            Node *current = table[i];
            while (current != nullptr)
            {
                cout << "NIM: " << current->nim << ", Nilai: " << current->nilai << endl;
                current = current->next;
            }
        }
    }
};

void display_menu()
{
    cout << "1. Tambah Data Mahasiswa" << endl;
    cout << "2. Hapus Data Mahasiswa" << endl;
    cout << "3. Cari Data Mahasiswa Berdasarkan NIM" << endl;
    cout << "4. Cari Data Mahasiswa Berdasarkan Rentang Nilai (80-90)" << endl;
    cout << "5. Tampilkan Semua Data Mahasiswa" << endl;
    cout << "6. Keluar" << endl;
}

int main()
{
    HashTable ht;
    int choice;
    do
    {
        display_menu();
        cout << "Pilihan: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            int nim, nilai;
            cout << "Masukkan NIM: ";
            cin >> nim;
            cout << "Masukkan Nilai: ";
            cin >> nilai;
            ht.insert(nim, nilai);
            break;
        }
        case 2:
        {
            int nim;
            cout << "Masukkan NIM yang akan dihapus: ";
            cin >> nim;
            ht.remove(nim);
            break;
        }
        case 3:
        {
            int nim;
            cout << "Masukkan NIM yang akan dicari: ";
            cin >> nim;
            int nilai = ht.get(nim);
            if (nilai != -1)
            {
                cout << "NIM: " << nim << ", Nilai: " << nilai << endl;
            }
            else
            {
                cout << "Data tidak ditemukan." << endl;
            }
            break;
        }
        case 4:
        {
            cout << "Mahasiswa dengan nilai antara 80 dan 90:" << endl;
            ht.search_by_value_range(80, 90);
            break;
        }
        case 5:
        {
            cout << "Semua Data Mahasiswa:" << endl;
            ht.traverse();
            break;
        }
        case 6:
        {
            cout << "Keluar." << endl;
            break;
        }
        default:
            cout << "Pilihan tidak valid." << endl;
        }
    } while (choice != 6);

    return 0;
}
