#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>
#include <ctime>

using namespace std;

void func(vector<vector<string>>&result, vector<string>& nums, vector<int>& vis, vector<string>& temp){
    /* Deskripsi : Mencari seluruh permutasi dari array of string dengan merekursi tiap kemungkinan*/
    /* F.S : Mengembalikan kemungkinan permutasi dari array of string */

    if(temp.size() == 4){
        result.push_back(temp);
        return;
    }

    for(int i = 0; i < 4; i++){
        if(vis[i] == 0){
            vis[i] = 1;
            temp.push_back(nums[i]);
            func(result, nums, vis, temp);
            temp.pop_back();
            vis[i] = 0;
        }
    }
}

vector<vector<string>> permute(vector<string>& nums) {
    /* Deskripsi : Mencari seluruh permutasi dari array of string */
    /* F.S : Mengembalikan seluruh permutasi dari array of string */

    vector<vector<string>> result;
    vector<int> vis(4,0);
    vector<string> temp;
    func(result, nums, vis, temp);
    return result;
}

float stof(const char *s)
{
    /* Deskripsi : Mengkonversi string ke float dengan menambahkan tiap bilangan pada setiap bilangan yang ada di dalam string hingga menjadi satu bilangan utuh*/
    /* F.S : Mengembalikan hasil konversi string ke float */
    float i;
    i = 0;
    short sign = 1;

    if (*s == '-')
    {
        sign = -1;
        s++;
    }
    while(*s >= '0' && *s <= '9')
    {
        i = i * 10 + (*s - '0');
        s++;
    }
    if (*s == '.')
    {
        s++;
        float j = 0.1;
        while(*s >= '0' && *s <= '9')
        {
            i = i + (*s - '0') * j;
            j = j / 10;
            s++;
        }
    }
    return i * sign;
}

bool result(vector<string> arithmetic)
{
    /* Deskripsi : perhitungan akan dilakukan ketika menemukan ')' lalu ia akan mundur ke belakang sejauh 3 langkah dan mengeksekusi operasi aritmatik*/
    /* F.S : Mengembalikan hasil operasi aritmatika */
    auto p = arithmetic.begin();
    float num1, num2, result;
    char op;

    while (arithmetic.front() != arithmetic.back())
    {        
        if (*p == ")") {
            p = prev(p, 1); // p di num2
            arithmetic.erase(next(p,1)); // hapus )

            num2 = stof(p->c_str()); // assign value num2
            p = prev(p, 1); // p di op
            arithmetic.erase(next(p,1)); // hapus num2

            op = p->c_str()[0]; // assign value op
            p = prev(p, 1); // p di num 1
            arithmetic.erase(next(p,1)); // hapu sop

            num1 = stof(p->c_str()); // assign value num1
            p = prev(p, 1); // p di (
            arithmetic.erase(next(p,1)); // hapus num1

            switch (op)
            {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                result = num1 / num2;
                break;
            }
            arithmetic.insert(p, to_string(result));
            p = prev(p, 1); // p di sebelum (
            arithmetic.erase(next(p,2)); // hapus (
        }
        p = next(p, 1);
    }

    if (result >= 23.98 && result <= 24.02)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void solution(vector<vector<string>> permutation, long ctime)
{
    /* Deskripsi : mencari solusi untuk setiap kemungkinan operasi aritmatik dan kemungkinan tanda kurung*/
    /* F.S : Mengembalikan hasil array of int */
    vector<vector<string>> arithmetic(5);
    vector<vector<string>> solution(7680);
    long etime;
    bool found = false;
    int count = 0;

    for (vector<string> temp : permutation)
    {
        for (string i : {"+", "-", "*", "/"})
        {
            for (string j : {"+", "-", "*", "/"})
            {
                for (string k : {"+", "-", "*", "/"})
                {
                    /* ((a op b) op (c op d))*/
                    arithmetic[0].emplace_back("(");
                    arithmetic[0].emplace_back("(");
                    arithmetic[0].emplace_back(temp[0]);
                    arithmetic[0].emplace_back(i);
                    arithmetic[0].emplace_back(temp[1]);
                    arithmetic[0].emplace_back(")");
                    arithmetic[0].emplace_back(j);
                    arithmetic[0].emplace_back("(");
                    arithmetic[0].emplace_back(temp[2]);
                    arithmetic[0].emplace_back(k);
                    arithmetic[0].emplace_back(temp[3]);
                    arithmetic[0].emplace_back(")");
                    arithmetic[0].emplace_back(")");

                    /* (((a op b) op c) op d)*/
                    arithmetic[1].emplace_back("(");
                    arithmetic[1].emplace_back("(");
                    arithmetic[1].emplace_back("(");
                    arithmetic[1].emplace_back(temp[0]);
                    arithmetic[1].emplace_back(i);
                    arithmetic[1].emplace_back(temp[1]);
                    arithmetic[1].emplace_back(")");
                    arithmetic[1].emplace_back(j);
                    arithmetic[1].emplace_back(temp[2]);
                    arithmetic[1].emplace_back(")");
                    arithmetic[1].emplace_back(k);
                    arithmetic[1].emplace_back(temp[3]);
                    arithmetic[1].emplace_back(")");

                    /* ((a op (b op c)) op d)*/
                    arithmetic[2].emplace_back("(");
                    arithmetic[2].emplace_back("(");
                    arithmetic[2].emplace_back(temp[0]);
                    arithmetic[2].emplace_back(i);
                    arithmetic[2].emplace_back("(");
                    arithmetic[2].emplace_back(temp[1]);
                    arithmetic[2].emplace_back(j);
                    arithmetic[2].emplace_back(temp[2]);
                    arithmetic[2].emplace_back(")");
                    arithmetic[2].emplace_back(")");
                    arithmetic[2].emplace_back(k);
                    arithmetic[2].emplace_back(temp[3]);
                    arithmetic[2].emplace_back(")");

                    /* (a op (b op (c op d)))*/
                    arithmetic[3].emplace_back("(");
                    arithmetic[3].emplace_back(temp[0]);
                    arithmetic[3].emplace_back(i);
                    arithmetic[3].emplace_back("(");
                    arithmetic[3].emplace_back(temp[1]);
                    arithmetic[3].emplace_back(j);
                    arithmetic[3].emplace_back("(");
                    arithmetic[3].emplace_back(temp[2]);
                    arithmetic[3].emplace_back(k);
                    arithmetic[3].emplace_back(temp[3]);
                    arithmetic[3].emplace_back(")");
                    arithmetic[3].emplace_back(")");
                    arithmetic[3].emplace_back(")");

                    /* (a op ((b op c) op d))*/
                    arithmetic[4].emplace_back("(");
                    arithmetic[4].emplace_back(temp[0]);
                    arithmetic[4].emplace_back(i);
                    arithmetic[4].emplace_back("(");
                    arithmetic[4].emplace_back("(");
                    arithmetic[4].emplace_back(temp[1]);
                    arithmetic[4].emplace_back(j);
                    arithmetic[4].emplace_back(temp[2]);
                    arithmetic[4].emplace_back(")");
                    arithmetic[4].emplace_back(k);
                    arithmetic[4].emplace_back(temp[3]);
                    arithmetic[4].emplace_back(")");
                    arithmetic[4].emplace_back(")");

                    /* Cek apakah hasilnya 24 */
                    for (int i = 0; i < 5; i++)
                    {
                        if (result(arithmetic[i]))
                        {
                            found = true;
                            
                            for (string x : arithmetic[i])
                            {
                                solution[count].emplace_back(x);
                            }
                            count++;
                        }
                        arithmetic[i].clear();
                    }
                }
            }
        }
    }
    
    etime = time(NULL);
    cout << "Waktu Eksekusi : " << etime - ctime << " detik" << endl;
    
    if (!found)
    {
        cout << "Tidak ada solusi" << endl;
    } else 
    {
        cout << "Jumlah solusi : " << count << endl;

        for (int i = 0; i < count; i++)
        {
            cout << "Solusi : ";
            for (string x : solution[i])
            {
                cout << x;
            }
            cout << endl;
        }

        char c;
        string filename;

        while (true)
        {
            cout << "Apakah anda ingin menyimpan solusi? (y/n) : ";
            cin >> c;

            if (c == 'y')
            {
                cout << "Masukkan nama file : ";
                cin >> filename;
                ofstream fw("./test/" + filename + ".txt", ios::out | ios::trunc);

                if (!fw.is_open())
                {
                    cout << "File tidak dapat dibuka" << endl;
                    break;
                }
                
                fw << permutation[0][0] << " " << permutation[0][1] << " " << permutation[0][2] << " " << permutation[0][3] << endl;
                fw << "Jumlah solusi : " << count << endl;

                for (int i = 0; i < count; i++)
                {
                    for (auto x : solution[i])
                    {
                        fw << x;
                    }
                    fw << endl;
                }
                fw.close();
                break;
            } else if (c == 'n')
            {
                break;
            } else 
            {
                cout << "Input tidak valid" << endl;
            }
        }
    }
}

/* Main Program */
int main(int argc, char const *argv[])
{
    bool PlayGame = true;
    bool found;
    short mode;
    vector<string> temp(4);
    vector<vector<string>> permutation(24);
    short num[4];
    long ctime;

    cout << "===== Permainan Kartu 24 =====" << endl;
    while (PlayGame) {
        cout << "Pilih Mode Permainan" << endl;
        cout << "1. Main Sendiri" << endl;
        cout << "2. Kartu Acak" << endl;
        cout << "3. Bantuan" << endl;
        cout << "4. Keluar" << endl;

        cout << "Pilihan : ";
        cin >> mode;

        found = true;
        switch (mode)
        {
        case 1:
            cout << "Main Sendiri" << endl;
            cout << "Masukkan 4 Kartu! " << endl;
            for (int i = 0; i < 4; i++)
            {
                cout << "Masukkan Kartu Ke-" << i + 1 << " : ";
                cin >> temp[i];
                if (temp[i] == "A")
                {
                    temp[i] = "1";
                }
                else if (temp[i] == "J")
                {
                    temp[i] = "11";
                }
                else if (temp[i] == "Q")
                {
                    temp[i] = "12";
                }
                else if (temp[i] == "K")
                {
                    temp[i] = "13";
                }
                else if (!(temp[i] == "2" || temp[i] == "3" || temp[i] == "4" || temp[i] == "5" || temp[i] == "6" || temp[i] == "7" || temp[i] == "8" || temp[i] == "9" || temp[i] == "10" ))
                {
                    cout << "Kamu salah memasukkan kartu" << endl;
                    found = false;
                    break;
                }
                
            }   

            /* Solution Here */
            if (found)
            {
                ctime = time(NULL);
                permutation = permute(temp);
                solution(permutation, ctime);
            }
            
            for (int i = 0; i < 4; i++)
            {
                temp[i] = "";
            }
            break;
        case 2:
            cout << "Kartu Acak" << endl;
            srand(time(NULL));

            for (int i = 0; i < 4; i++)
            {
                temp[i] = to_string(rand() % 13 + 1);
            }

            for (int i = 0; i < 4; i++)
            {
                if (temp[i] == "1")
                {
                    cout << "A ";
                }
                else if (temp[i] == "11")
                {
                    cout << "J ";
                }
                else if (temp[i] == "12")
                {
                    cout << "Q ";
                }
                else if (temp[i] == "13")
                {
                    cout << "K ";
                }
                else
                {
                    cout << temp[i] << " ";
                }
            }
            cout << endl;
            
            ctime = time(NULL);
            permutation = permute(temp);
            solution(permutation, ctime);
            
            break;
        case 3:
            cout << "Bantuan" << endl;
            cout << "\nNilai-Nilai dari Kartu yang Bukan Angka : \nA : 1\nJ : 11\nQ : 12\nK : 13\n" << endl;
            break;
        case 4:
            cout << "Keluar" << endl;
            PlayGame = false;
            break;
        default:
            cout << "Pilihan Tidak Tersedia" << endl;
            break;
        }
    }
    return 0;
}